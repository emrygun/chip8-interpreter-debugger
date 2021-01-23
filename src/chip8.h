#ifndef CHIP8_H
#define CHIP8_H

//Chip8 interpreter here
#include <stdint.h>
#include <stdio.h>

typedef struct FILE_ROM{
    char ROMName[100];         //Rom Name
    FILE *ROM;                 //Rom file descriptor
    uint8_t buffer[0x1000];    //Rom buffer
    uint16_t size;             //Rom size
} FILE_ROM;

typedef struct OP{
    uint16_t    opcode;
    char        opcodeName[15];
    uint8_t     opbyte;
} OP;


typedef struct chip8 chip8;
struct chip8{
    uint8_t V[0x10]; //General Purpose Registers
    uint8_t delay_timer, sound_timer;   //Timers

    uint16_t    PC; //Program Counter
    uint8_t     SP; //Stack Pointer
    uint16_t     I; //General Purpose Register

    uint16_t    stack[0x10];     //16 level stack
    uint8_t     Mem[0x1000];    //4kB memory

    uint8_t gfxBuffer[64 * 32]; 

    OP currentOP;           //Holds the current opcode

    uint8_t screenUpdate;
};

void fetchOP(chip8 *self);      //Fetch the opcode
uint8_t executeOP (chip8 *self);    //Execute the opcode
uint8_t getKey();

void chip8Init(chip8 *self, FILE_ROM ROM); //Init chip-8

#endif
