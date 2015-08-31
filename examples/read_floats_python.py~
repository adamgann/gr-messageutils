#!/usr/bin/python

import socket
import struct

UDP_IP = "127.0.0.1"
FLOAT_PORT = 52001
BYTE_PORT = 52002


float_sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM) # Float Socket
byte_sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM) # Byte Socket

# Bind these sockets to their respective ports
float_sock.bind((UDP_IP, FLOAT_PORT))
byte_sock.bind((UDP_IP, BYTE_PORT))

#Set the timeouts 
float_sock.settimeout(2.0)
byte_sock.settimeout(2.0)

while True:
  # Grab the floating point vector
  try:
    data, addr = float_sock.recvfrom(1024) # buffer size is 1024 bytes
  except socket.timeout:
    print "Caught at timeout."
    continue

  # Unpack the floats
  offset = 0
  floats_rx = []
  while (offset<len(data)):
    floats_rx.append(struct.unpack_from('f',data,offset))
    offset+=4
  print "Received Floats",floats_rx

  # Grab the byte vector
  try:
    data, addr = byte_sock.recvfrom(1024) # buffer size is 1024 bytes
  except socket.timeout:
    print "Caught at timeout."
    continue


  #Unpack the byte vector
  offset = 0
  bytes_rx = []
  while(offset<len(data)):
    bytes_rx.append(struct.unpack_from('B',data,offset))
    offset+=1
  print "Received Bytes",bytes_rx
  
