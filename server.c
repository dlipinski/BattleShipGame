#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <signal.h>

#define key 5535

int endNumber = 5 + 4 + 4 + 3 + 3 + 2 + 2;

int players1_fields[10][10];
int players2_fields[10][10];

void set_players_fields(){
    for(int i=0;i<10;i++)
        for(int j=0;j<10;j++){
            players1_fields[i][j]=0;
            players2_fields[i][j]=0;
        }
}