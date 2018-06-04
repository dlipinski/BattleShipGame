#!/bin/sh

#compile
gcc -o client client.c -L /usr/X11R6/lib -lX11 -lm


#run
./client &
./client