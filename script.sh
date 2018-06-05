#!/bin/sh

#compile
gcc -g -o client client.c -L /usr/X11R6/lib  -lX11  -lm

#run
#./client &
./client
#gdb client