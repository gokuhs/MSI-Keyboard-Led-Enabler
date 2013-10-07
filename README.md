MSI Led Enabler
=====================

This is a modded code of PaNaVTEC's MSI_GT_GE_Led_Enabler to compile in Linux Debian.

How to compile:
===============

It's simple firs tclone the repository with 

$ git clone https://github.com/gokuhs/MSI_GT_GE_Led_Enabler

Now in a terminal type:

$ make

How to use:
===========

This program uses 4 arguments:

1º Mode:

- Gaming: Only turn on the left leds
- Normal: Turn all leds on

2º Color Area 1:
- Sets the color of the area 1 of the keyboard * (see supported color modes)

3º Color Area 2:
- Sets the color of the area 2 of the keyboard * (see supported color modes)

4º Color Area 3:
- Sets the color of the area 3 of the keyboard * (see supported color modes)

5º Light level:
- Establish the intensity level of the leds


Example of use:

sudo ./msiledenabler -mode normal -color1 blue -color2 green -color3 red -level 3


Original text
================


This is a proof of concept to get MSI keyboard light working on unix and OSX (hackintosh). It works on a MSI GT60 so I think this can activate backlight led keyboard on series GT and GE that have the same keyboard by steelseries.
The attached source is for compile on Mac if you want to compile on Unix I attached in https://dl.dropbox.com/u/5977601/MSI_GT_GE_Led_Enabler-master-unix.tar.gz the modifications needed. Also you need to get dependencies:


Thanks to Signal11 for their HIDAPI.
Thanks to PaNaVTEC for the original Source Code ( https://github.com/PaNaVTEC/MSI_GT_GE_Led_Enabler )
