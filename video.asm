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

processor "z80"

section code, "VideoMain.bin", 16514
{       
JpEnableHires:
        jp      EnableHires //+0
JpDisableHires:
        jp      DisableHires //+3

        const TV_STD = TV_STD_60HZ //TV_STD_50HZ or TV_STD_60HZ
        include "video.inc"
        include "zxpand.inc"
}
