#include <stdint.h>
#include <stdio.h>
#include "headers/bitwork.h"
#include "headers/complexwork.h"

#define N 8
#define N_LENGH 256
#define NUM_ WN 128
const int NUM_GROUP[N] = {128,64,32,16,8,4,2,1};
const int NUM_BTFY[N]  = {1,2,4,8,16,32,64,128};   
const complex UNIT = {1, 0};
const complex NEG_UNIT = {-1, 0};

typedef union {
    complex fftX;
    complex fftY;
} MoveData;

int main(){
    bit_reversal_permutation(x, N_LENGH);
    MoveData REG1;
    MoveData REG2;

    for (int stage = 0; stage < 8; stage++) {
        int num_group =  NUM_GROUP[stage];
        int num_btfy  =  NUM_BTFY[stage];
        for (int group = 0; group < num_group; group++) {
            for (int btfy = 0; btfy < num_btfy; btfy++) {
                complex Wn = Wn_table[(btfy * num_group) + 1]; //Se obtien las dos partes del complejo son de tipo flotante
                int index1 = (group * (1 << (stage + 1))) + btfy;
                int index2 = index1 + num_btfy;
                REG1.fftX = dot_complex(x[index2 + 1], Wn);
                REG1.fftY = dot_complex(REG1.fftX, NEG_UNIT);


                
                //MoveData.fftX[index1 + 1] = x[index1 + 1] + W * x[index2 + 1];
                //MoveData.fftX[index2 + 1] = x[index1 + 1] - W * x[index2 + 1];
            }
        }
        //se hace swap entre otro arreglo para administrar el uso de memoria
    }
    return 0;
}
