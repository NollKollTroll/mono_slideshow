# Mono slideshow

ZX81 program to show pictures, 256x384i monochrome.

## General info

This software enables a ZX81 with a ZXpand-interface to do a slideshow of hires pictures, all programmed in BASIC.<br>
The pictures are 256x384, monochrome and can be created easily.

## Example usage

Put all the files from the release-binary folder on an SD-card and load the file show.p and then sit back and enjoy.

## Creating your own slideshow

First, gather the pictures and convert them to 256x384 with whatever program of your choice. Save the files as uncompressed 24-bit BMP.<br>
Use the bmp2nkt program to convert the BMP-files to the format usable for the ZX81 slideshow.<br>
ImageMagick can be used as a GUI-program or as a CLI program.<br>
First to test what it looks like:<br>
> convert -resize 256x384\\! -ordered-dither o4x4 -colors 2 -type bilevel -depth 1 ~/Pictures/mirage1.jpg test.bmp<br>

Finally when you are satisfied:<br>
> convert -resize 256x384\\! -ordered-dither o4x4 -colors 2 -type bilevel -depth 1 ~/Pictures/mirage1.jpg test.gray<br>
> rename test.gray test.raw<br>

Open the file show.asm in ZX-IDE and change the BASIC-lines loading the pictures, but do not change the load address. Compile the program.<br>
Put all the converted pictures and the file show.p on an SD-card.<br>

**NOTE:** 50hz interlaced is VERY flickery, choose 60Hz if at all possible!

## Emulators

My trusty go-to emulator EightyOne v1.29 works fine with this program but needs some specific settings:<br>
- RAM Pack: 32k<br>
- High resolution: WRX<br>
- ZXpand+: ON<br>
- TV-emulation / Advanced effects: ON<br>
- TV-emulation / Interlace: ON

## History

While doing a release of the Chroma slideshow I realized that there was no such program for the monochrome ZX81-users. I have now fixed that deficiency.

## Future

I hope many slideshows will be created and shown using the lovely little door-stopper!<br>
It is possible to do 320x480i/320x576i resolutions with more RAM, and a lot of code juggling. I will not do that, feel free to expand on the source code!

## License

The code I created for this project is licensed under Creative Commons CC0 1.0 Universal.

## Contact

Mail: <adam.klotblixt@gmail.com><br>
Github: <https://github.com/NollKollTroll/chroma_slideshow>