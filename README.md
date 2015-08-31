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

###Socket PDU Repacker
Floats are sent over UDP as bytes (4 bytes per float). The Socket PDU Repacker block repacks the received vector of bytes
as a vector of floats fixing the data type and the vector length so they can be read by other blocks. 

The direction is set as Input (from external socket to GNU Radio blocks) or Output (from GNU Radio blocks to 
an external socket)


###PDU Debug

Adds a few options for debugging PDUs. Can select to print just the contents of the
metadata to the console. The data type of the PDU data blob is selectable. ASCII strings can be decoded from a PDU with its data in byte format. Byte order (reversed or not) can be selected. 


###Vector PDU Source

Creates a PDU with data blob containing elements of a vector. Type is selectable (float and byte 
are implemented as of now). User can set period with which the message is sent and optionally set a limit
on the number of messages sent.


###Message Threshold Switch

If the value of data contained in a message is below a threshold the block copies its input to 
'above'. If the value of data is below the threshold the block copies its input to 'below'.


###Add Constant From Message

Adds an offset to the input data stream based on value received from a message. 

