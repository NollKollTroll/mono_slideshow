//Written in 2022 by Adam Klotblixt (adam.klotblixt@gmail.com)
//
//To the extent possible under law, the author have dedicated all
//copyright and related and neighboring rights to this software to the
//public domain worldwide.
//This software is distributed without any warranty.
//
//You should have received a copy of the CC0 Public Domain Dedication
//along with this software. If not, see
//<http://creativecommons.org/publicdomain/zero/1.0/>.

const PRT0 = $0007
const PRT1 = $2007
const PRT2 = $4007
const PRT3 = $6007
const PRT4 = $8007
const PRT5 = $a007
const PRT6 = $c007
const PRT7 = $e007

const API_ZXPANDCMD = $1ff2
const API_SENDSTRING = $1ffa
const API_FILEOP = $1ff8

//--------------------------
macro LED_GREEN_ON()
{
        //set green led
        ld      bc,PRT7
        ld      a,$b6
        out     (c),a
}

//--------------------------
macro LED_GREEN_OFF()
{
        //clear green led
        ld      bc,PRT7
        ld      a,$b7
        out     (c),a
}

//--------------------------
macro LED_RED_ON()
{
        //set red led
        ld      bc,PRT7
        ld      a,$b8
        out     (c),a
}

//--------------------------
macro LED_RED_OFF()
{
        //clear red led
        ld      bc,PRT7
        ld      a,$b9
        out     (c),a
}

//--------------------------
subroutine ZXPandLoRam
{
        //go low, ram at 8-40k
        ld      bc,PRT7            
        ld      a,$b2
        out     (c),a
        //pause, let it settle...
        ld      b,0
        {
		djnz	@loop
        }
        ret
}

//--------------------------
subroutine ZXPandHiRam
{
        //go high, ram at 16-48k
        ld      bc,PRT7            
        ld      a,$b3
        out     (c),a
        //pause, let it settle...
        ld      b,0
        {
		djnz	@loop
        }
        ret
}

//--------------------------
subroutine OpenAStringFile
{
        ld      hl,($400c)
        ld      bc,34        
        add     hl,bc
        push    hl
        pop     de
        jp      OpenFileForStreaming
}

//--------------------------
//DE = file path, zero-terminated zx-string
subroutine OpenFileForStreaming
{
        //prepare zxpand buffer for write
        ld      bc,PRT0
        ld      a,$ff
        out     (c),a
        //send filename to zxpand
        ld      bc,PRT2
        .NameOutLoop:
                ld      a,(de)
                out     (c),a                   //one character to zxpand
                inc     de
                and     a
        jp      nz,.NameOutLoop                 //repeat until zero-termination
        //open file for read
        ld      bc,PRT4
        xor     a
        out     (c),a
        call    GetResponse
        //do not read meta-data, not needed
        ret
}

//--------------------------
//A = nr of bytes to read
//HL = destination
subroutine ReadBytesFromFileToHL
{
        //request reg.a nr of bytes from file
        ld      bc,PRT5
        out     (c),a
        //save it for later
        ld      (.NrOfBytesToRead),a
        //wait for zxpand to finish command
        ld      bc,PRT5
        call    WaitForZXpand
        //prepare zxpand buffer for read
        ld      bc,PRT0
        ld      a,0
        out     (c),a
        repeat  4
        {        
                nop
        }
        //read bytes from zxpand to HL
        ld      b,.NrOfBytesToRead: 123
        inir
        ret
}

//--------------------------
subroutine CloseFile
{
        ld      bc,PRT4
        ld      a,$80
        out     (c),a
        call    GetResponse
        ret
}

//--------------------------
subroutine GetResponse
{
        .DelayStart:
		repeat  8
		{        
			nop
		}
                in      a,(c)                   //get response code
        jp      m,.DelayStart                   //and loop while negative
        cp      $40                             //all ok
        ret     z                               //ret if ok
        //error "handling", noise on screen
        {
                in      a,($fe)                 //VSync on, NMI off, HSYNC off
                out     ($fe),a                 //VSync off, NMI on, HSYNC on
                jp      @loop
        }
}

//--------------------------
subroutine WaitForZXpand
{
        {
                repeat  8
		{        
			nop
		}
                in      a,(c)                   //get response code
                jp      m,@loop                 //and loop while not done
        }
        ret
}
