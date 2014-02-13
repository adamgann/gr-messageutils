#!/bin/bash

FLOWGRAPH="set_offset_with_message.py"
DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"




### create tap interface
#if [[ `ifconfig -a | grep tap0 | wc -l` -eq 0 ]]
#then
#	sudo ip tuntap add dev tap1 user ${USER} mode tap
#fi

### reconfigure it in any case, just to be sure it's up
#sudo ifconfig tap1 down
#sudo ifconfig tap1 hw ether 12:34:56:78:90:ab
#sudo ifconfig tap1 up
#sudo ifconfig tap1 192.168.123.1


### start transceiver
cd ${DIR}
cd ../examples/
./${FLOWGRAPH} &
sleep 1

### start netcat
echo "##########################################################################"
echo "Enter a value (0-9) and press enter to set amplitude"
echo "##########################################################################"
sleep 2

#echo | nc -u localhost 52001
nc localhost 52001




