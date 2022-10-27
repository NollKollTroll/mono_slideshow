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

format zx81
;labelusenumeric
;LISTOFF
// hardware options to be set and change defaults in ZX81DEF.INC
MEMAVL	   EQU	   MEM_16K	  // can be MEM_1K, MEM_2K, MEM_4K, MEM_8K, MEM_16K, MEM_32K, MEM_48K
STARTMODE  EQU	   SLOW_MODE	  // SLOW or FAST
DFILETYPE  EQU	   EXPANDED	  // COLLAPSED or EXPANDED or AUTO
include '..\..\SINCL-ZX\ZX81.INC' // definitions of constants
;LISTON
      1 REM _hide _asm
	file 'VideoMain60.bin' //VideoMain50.bin or VideoMain60.bin
	END _asm
AUTORUN:
//The slideshow stack
    100 LOAD "TEST01.RAW;32768"
	GOSUB 1000
	LOAD "TEST02.RAW;32768"
	GOSUB 1000
	LOAD "TEST03.RAW;32768"
	GOSUB 1000
	LOAD "TEST04.RAW;32768"
	GOSUB 1000
	GOTO 100
//Show a picture for a while, subroutine
   1000 RAND USR 16516	//EnableHires
	//Delay a bit, PAUSE does not work
	FOR I=1 TO 200
	NEXT I
	RAND USR 16519	//DisableHires
	RETURN

//include D_FILE and needed memory areas
include '..\..\SINCL-ZX\ZX81DISP.INC'

VARS_ADDR:
	db 80h //DO NOT REMOVE!!!

WORKSPACE:

assert ($-MEMST)<MEMAVL
// end of program
