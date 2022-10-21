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

const SCREEN_WIDTH_PIXELS               = 256
const SCREEN_WIDTH_BYTES                = SCREEN_WIDTH_PIXELS / 8  //x-resolution in bytes
const SCREEN_HEIGHT_RASTERS             = 384 //y-resolution in lines
const SCREEN_HEIGHT_RASTERS_PER_FIELD   = SCREEN_HEIGHT_RASTERS / 2
const TV_STD_50HZ                       = 312
const TV_STD_60HZ                       = 262
const VSYNC_RASTERS                     = 4
const WASTED_RASTERS                    = 2
const TOTAL_BLANK_RASTERS               = TV_STD - WASTED_RASTERS - SCREEN_HEIGHT_RASTERS_PER_FIELD - VSYNC_RASTERS
const TOP_BLANK_RASTERS                 = TOTAL_BLANK_RASTERS / 2
const BOTTOM_BLANK_RASTERS              = TOTAL_BLANK_RASTERS - TOP_BLANK_RASTERS
const SCREEN_PIXELS                     = 32768


//--------------------------
subroutine EnableHires
{
        //change to hires
        ld      ix,GenerateVsyncEven
        ret
}

//--------------------------
subroutine DisableHires
{
        //restore ROM character patterns
        ld      a,$1e
        ld      i,a
        //restore standard ROM video mode
        ld      ix,$0281
        ret
}

//--------------------------
subroutine FastVideo
{
        //start VSync, disable NMI
        in      a,($fe)
        ret
}

//--------------------------
subroutine SlowVideo
{
        //end VSync, enable NMI
        out     ($fe),a 
        ret
}

//--------------------------
subroutine GenerateVsyncEven
{
        //waste time
        repeat 5
        {
                nop                             //4
        }
        scf                                     //4
        //start VSync, disable NMI
        in      a,($fe)                         //11
        //waste time to create VSync, 441 cycles
        ld      b,32                            //7
        djnz    *                               //13/8
        ret     nc                              //5
        ret     nc                              //5        
        //prepare top border
        ld      ix,GenerateHiresScreenEven      //14
        ld      a,256 - TOP_BLANK_RASTERS       //7
        ex      af,af'                          //4
        //restore registers
        pop     hl                              //10
        pop     de                              //10
        pop     bc                              //10
        pop     af                              //10
        //end VSync, enable NMI
        out     ($fe),a                         //11
        //return to do some useful work, and generate top blank lines
        ret                                     //10
}

//--------------------------
subroutine GenerateVsyncOdd
{
        //waste time, half a line extra
        repeat 26
        {
                nop                             //4
        }
        //waste time
        repeat 5
        {
                nop                             //4
        }
        scf                                     //4
        //start VSync, disable NMI
        in      a,($fe)                         //11
        //waste time to create VSync, 441 cycles
        ld      b,32                            //7
        djnz    *                               //13/8
        ret     nc                              //5
        ret     nc                              //5        
        //prepare top border
        ld      ix,GenerateHiresScreenOdd      //14
        ld      a,256 - TOP_BLANK_RASTERS       //7
        ex      af,af'                          //4
        //restore registers
        pop     hl                              //10
        pop     de                              //10
        pop     bc                              //10
        pop     af                              //10
        //end VSync, enable NMI
        out     ($fe),a                         //11
        //return to do some useful work, and generate top blank lines
        ret                                     //10
}

//--------------------------
subroutine LineBuffer
{
	ld	r,a                             //load screen address lsb
	repeat SCREEN_WIDTH_BYTES
        {
		nop
	}
	ret	nz
}

//--------------------------
subroutine GenerateHiresScreenEven
{
	//delay to position picture left/right
	ld	b,7
	djnz	*
	nop
	nop
	//clear Z-flag, needed later
	dec	b
	ld	hl,SCREEN_PIXELS        //start of hires-screen, field even
	ld	de,SCREEN_WIDTH_BYTES * 2
	ld	b,SCREEN_HEIGHT_RASTERS_PER_FIELD
.HiresLines:
		ld	a,h
		ld	i,a		//load screen address msb
		ld	a,l
		call	LineBuffer+$8000//generate the hires screen
		add	hl,de		//point to next hires line
		dec	b
	jp	nz,.HiresLines	        //repeat until last line is done
.PrepareBottomBorder:
	ld	ix,GenerateVsyncOdd
	//prepare for bottom border
	ld	a,256 - BOTTOM_BLANK_RASTERS
	ex	af,af'
        //restore registers
	pop	hl
	pop	de
	pop	bc
	pop	af
        //enable NMI
        out     ($fe),a 
        //return to do some useful work, and generate bottom blank lines
	ret
}

//--------------------------
subroutine GenerateHiresScreenOdd
{
	//delay to position picture left/right
	ld	b,7
	djnz	*
	nop
	nop
	//clear Z-flag, needed later
	dec	b
	ld	hl,SCREEN_PIXELS + SCREEN_WIDTH_BYTES //start of hires-screen, field odd
	ld	de,SCREEN_WIDTH_BYTES * 2
	ld	b,SCREEN_HEIGHT_RASTERS_PER_FIELD
.HiresLines:
		ld	a,h
		ld	i,a		//load screen address msb
		ld	a,l
		call	LineBuffer+$8000//generate the hires screen
		add	hl,de		//point to next hires line
		dec	b
	jp	nz,.HiresLines	        //repeat until last line is done
.PrepareBottomBorder:
	ld	ix,GenerateVsyncEven
	//prepare for bottom border
	ld	a,256 - BOTTOM_BLANK_RASTERS
	ex	af,af'
        //restore registers
	pop	hl
	pop	de
	pop	bc
	pop	af
        //enable NMI
        out     ($fe),a 
        //return to do some useful work, and generate bottom blank lines
	ret
}
