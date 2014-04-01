#Introduction

The files in gr-messageutils are useful for experimenting with Message Passing in 
GNU Radio (ver 3.7 or later).


#Installation

Naviagate to your desired install directory. This should be outside of the main
GNU Radio source code directory. From the terminal: 

  	git clone https://github.com/adamgann/gr-messageutils.git
  	cd gr-messageutils
  	mkdir build
  	cd build
  	cmake ..
  	make
  	sudo make install
  	sudo ldconfig



#Blocks

###PDU Debug

Adds a few options for debugging PDUs. Can select to print just the contents of the
metadata to the console. The data type of the PDU data blob is selectable.

###Vector PDU Source

Creates a PDU with data blob containing elements of a vector. Type is selectable (float and byte 
are implemented as of now). User can set period with which the message is sent. 





Other blocks in the directory may not be operational
