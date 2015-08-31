#!/usr/bin/python

import socket
import struct

UDP_IP = "127.0.0.1"
FLOAT_PORT = 52001
BYTE_PORT = 52002

# Set up sockets
float_sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM) # Float Socket
byte_sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM) # Byte Socket

# Get what data I'm sending
float_vec = [-1,1,-1,1,-1,-1,-1,-1]
float_buf = struct.pack('%sf' % len(float_vec), *float_vec)

byte_vec = range(1,6)
byte_buf = struct.pack('%sb' % len(byte_vec), *byte_vec)

float_sock.sendto(float_buf, (UDP_IP, FLOAT_PORT))
byte_sock.sendto(byte_buf, (UDP_IP, BYTE_PORT))


