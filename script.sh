!bin/bash

gcc client.c -o client `pkg-config --cflags --libs gtk+-2.0`
./client