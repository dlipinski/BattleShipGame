!bin/bash

gcc test.c -o test `pkg-config --cflags --libs gtk+-2.0`
./test