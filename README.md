# Mono slideshow

ZX81 program to show pictures, 256x384i monochrome.

## General info

This software enables a ZX81 with a ZXpand-interface to do a slideshow of hires pictures, all programmed in BASIC.<br>
The pictures are monochrome 256x384 pixels, and can be created quite easily.

## Example usage

Put all the files from the release-binary folder on an SD-card, load the file **show.p** and then sit back and enjoy.

## Creating your own slideshow

First, gather the pictures and convert them to 1-bit 256x384 headerless raw files with your program of choice.<br>
The following examples are created with ImageMagick available for Linux, Windows and MacOS.<br>
First create a BMP file to test what it looks like:<br>
> convert -resize 256x384\\! -ordered-dither o4x4 -colors 2 -type bilevel -depth 1 ~/Pictures/mirage1.jpg test.bmp<br>

Finally create the headerless RAW file when you are satisfied. Note that the ZX81 uses inverted values for black and white:<br>
> convert -resize 256x384\\! -ordered-dither o4x4 -colors 2 -type bilevel -depth 1 -channel RGB -negate ~/Pictures/mirage1.jpg test.gray<br>
> rename test.gray test.raw<br>

Open the file **show.asm** in ZX-IDE and change the BASIC-lines loading the pictures, make sure to use the same LOAD address.<br>
Compile the program (Ctrl-F9).<br>
Put all the converted pictures and the file **show.p** on an SD-card.

**NOTE:** 50hz interlaced is VERY flickery, choose 60Hz if at all possible!

A different way of creating the pictures is to save as uncompressed 1-bit BMP-files and find a way to cut the header.

## Building source

The source code is divided into several files. The code most people would want to edit is the BASIC-code in **show.asm** where the names and order of the slideshow pictures are defined.<br>
It is also possible to change the scan rate of the display. Choose **VideoMain50.bin** for 50Hz, or **VideoMain60.bin** for 60Hz.

The files **VideoMain50.bin** and **VideoMain60.bin** are included pre-built, and can be built using the jasm assembler.<br>
Use the following command line to build VideoMain.bin with jasm:<br>
> jasm -om -v2 video.asm

## Emulators

My trusty go-to emulator EightyOne v1.29 works well with this program but needs some specific settings:<br>
- RAM Pack: 32k<br>
- High resolution: WRX<br>
- ZXpand+: ON<br>
- TV-emulation / Advanced effects: ON<br>
- TV-emulation / Interlace: ON

## History

While doing a release of the Chroma slideshow I realized that there was no such program for the monochrome ZX81-users. I have now fixed that deficiency.

## Future

I hope many slideshows will be created and shown using our lovely little door-stoppers!<br>
It is possible to do 320x480i/320x576i resolutions with more RAM and a lot of code juggling. I will not do that, feel free to expand on the source code!

## Links

The assembler jasm can be found at http://kollektivet.nu/jasm<br>
The compiler/assembler ZX-IDE and discussion about using it can be found at http://sinclairzxworld.com/viewtopic.php?f=6&t=1064

## License

The code I created for this project is licensed under Creative Commons CC0 1.0 Universal.

## Contact

Mail: <adam.klotblixt@gmail.com><br>
Github: <https://github.com/NollKollTroll/mono_slideshow>