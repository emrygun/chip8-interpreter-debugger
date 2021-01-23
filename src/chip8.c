#include "chip8.h"
#include <stdlib.h> //For srand()
#include <stdint.h> 
#include <time.h>   //For time seed
#include <ncurses.h> //For getch()

#define OP_HEAD(o) ((o & 0xF000) >> 12)
#define OP_TAIL(o) (o & 0X000F)

#define SETOPNAME(...)    do{sprintf(self->currentOP.opcodeName, ##__VA_ARGS__);} \
                          while(0)

#define OP_nnn  (self->currentOP.opcode & 0xFFF)
#define OP_Vx   ((self->currentOP.opcode & 0x0F00) >> 8)
#define OP_Vy   ((self->currentOP.opcode & 0x00F0) >> 4)
#define OP_kk   (self->currentOP.opcode & 0x00FF)
#define OP_n    (self->currentOP.opcode & 0x000F)

#define SWAPBYTES(o) (o << 8) | (o >> 8)

uint8_t chip8_fontset[80] =
{
  0xF0, 0x90, 0x90, 0x90, 0xF0, // 0
  0x20, 0x60, 0x20, 0x20, 0x70, // 1
  0xF0, 0x10, 0xF0, 0x80, 0xF0, // 2
  0xF0, 0x10, 0xF0, 0x10, 0xF0, // 3
  0x90, 0x90, 0xF0, 0x10, 0x10, // 4
  0xF0, 0x80, 0xF0, 0x10, 0xF0, // 5
  0xF0, 0x80, 0xF0, 0x90, 0xF0, // 6
  0xF0, 0x10, 0x20, 0x40, 0x40, // 7
  0xF0, 0x90, 0xF0, 0x90, 0xF0, // 8
  0xF0, 0x90, 0xF0, 0x10, 0xF0, // 9
  0xF0, 0x90, 0xF0, 0x90, 0x90, // A
  0xE0, 0x90, 0xE0, 0x90, 0xE0, // B
  0xF0, 0x80, 0x80, 0x80, 0xF0, // C
  0xE0, 0x90, 0x90, 0x90, 0xE0, // D
  0xF0, 0x80, 0xF0, 0x80, 0xF0, // E
  0xF0, 0x80, 0xF0, 0x80, 0x80  // F
};

//Initialize CHIP-8 Machine
void chip8Init(chip8 *self, FILE_ROM ROM){
    int iter;
    for(iter = 0; iter < 0xF; self->V[iter] = 0, iter++)    //Reset V registers
    for(iter = 0; iter < 0xF; self->stack[iter] = 0, iter++)    //Reset stack
    self->PC = 0x200;   //Reset program counter
    self->SP = 0;   //Reset stack pointer 
    self->I = 0;    //Reset I register 
    self->delay_timer = 0; self->sound_timer = 0; //Reset timers

    //Write fontset
    for(iter = 0; iter < 80; iter++) self->Mem[iter] = chip8_fontset[iter];

    //Write rom to memory
    for(iter = 0; iter < ROM.size; iter++)
        self->Mem[0x200 + iter] = ROM.buffer[iter];
}

//Get Key
uint8_t getKey(){
    switch(kbhit()){

        case '4': return 0x1;
        case '5': return 0x2;
        case '6': return 0x3;
        case '7': return 0xc;

        case 'r': return 0x4;
        case 't': return 0x5;
        case 'y': return 0x6;
        case 'u': return 0xd;

        case 'f': return 0x7; 
        case 'g': return 0x8; 
        case 'h': return 0x9; 
        case 'j': return 0xe;

        case 'c': return 0xa;
        case 'v': return 0x0;
        case 'b': return 0xb;
        case 'n': return 0xf; 

        default: return NULL; 
    }
}

//Fetch Opcode
void fetchOP(chip8 *self){
    self->currentOP.opcode = SWAPBYTES(*(uint16_t *) &(self->Mem[self->PC]));
    switch (OP_HEAD(self->currentOP.opcode)){
        case 0x0: 
            switch (OP_TAIL(self->currentOP.opcode)){
                case 0x0: SETOPNAME("CLS"); break;
                case 0xE: SETOPNAME("RET"); break;
                default : SETOPNAME("SYS\t0x%x", OP_nnn); break; 
                }
            break;
        case 0x1: SETOPNAME("JP\t0x%x", OP_nnn); break;
        case 0x2: SETOPNAME("CALL\t0x%x", OP_nnn); break;
        case 0x3: SETOPNAME("SE\tV%x,\t0x%x", OP_Vx, OP_kk); break;
        case 0x4: SETOPNAME("SNE\tV%x,\t0x%x", OP_Vx, OP_kk); break;
        case 0x5: SETOPNAME("SE\tV%x,\t0x%x", OP_Vx, OP_kk); break;
        case 0x6: SETOPNAME("LD\tV%x,\t0x%x", OP_Vx, OP_kk); break;
        case 0x7: SETOPNAME("ADD\tV%x,\t0x%x", OP_Vx, OP_kk); break;
        case 0x8:
            switch (OP_TAIL(self->currentOP.opcode)){
                case 0x0: SETOPNAME("LD\tV%x,\t0x%x", OP_Vx, OP_Vy); break;
                case 0x1: SETOPNAME("OR\tV%x,\t0x%x", OP_Vx, OP_Vy); break;
                case 0x2: SETOPNAME("AND\tV%x,\t0x%x", OP_Vx, OP_Vy); break;
                case 0x3: SETOPNAME("XOR\tV%x,\t0x%x", OP_Vx, OP_Vy); break;
                case 0x4: SETOPNAME("ADD\tV%x,\t0x%x", OP_Vx, OP_Vy); break;
                case 0x5: SETOPNAME("SUB\tV%x,\t0x%x", OP_Vx, OP_Vy); break;
                case 0x6: SETOPNAME("SHR\tV%x\t{, 0x%x}", OP_Vx, OP_Vy); break;
                case 0x7: SETOPNAME("SUBN\tV%x,\t0x%x", OP_Vx, OP_Vy); break;
                case 0xE: SETOPNAME("SHL\tV%x\t{, 0x%x}", OP_Vx, OP_Vy); break;
                }
            break;
        case 0x9: SETOPNAME("SNE\tV%x,\t0x%x", OP_Vx, OP_Vy); break;
        case 0xA: SETOPNAME("LD\tI,\t0x%x", OP_nnn); break;
        case 0xB: SETOPNAME("JP\tV0,\t0x%x", OP_nnn); break;
        case 0xC: SETOPNAME("RND\tV%x,\t0x%x", OP_Vx, OP_nnn); break;
        case 0xD: SETOPNAME("DRW\tV%x,\tV%x,\t%x", OP_Vx, OP_Vy, OP_n); break;
        case 0xE:
            switch (OP_TAIL(self->currentOP.opcode)){
                case 0xE: SETOPNAME("SKP\tV%x", OP_Vx); break;
                case 0x1: SETOPNAME("SKNP\tV%x", OP_Vx); break;
                }
            break;
        case 0xF:
            switch (self->currentOP.opcode & 0x00FF){
                case 0x07: SETOPNAME("LD\tV%x,\tDT", OP_Vx); break;
                case 0x0A: SETOPNAME("LD\tV%x,\tK", OP_Vx); break;
                case 0x15: SETOPNAME("LD\tDT,\tV%x", OP_Vx); break;
                case 0x18: SETOPNAME("LD\tST,\tV%x", OP_Vx); break;
                case 0x1E: SETOPNAME("ADD\tI,\tV%x", OP_Vx); break;
                case 0x29: SETOPNAME("LD\tF,\tV%x", OP_Vx); break;
                case 0x33: SETOPNAME("LD\tB,\tV%x", OP_Vx); break;
                case 0x55: SETOPNAME("LD\t[0x%x],\tV%x",self->I, OP_Vx); break;
                case 0x65: SETOPNAME("LD\tV%x,\t[%x]",OP_Vx, self->I); break;
                }
            break;
    }
}

uint8_t executeOP(chip8 *self){
    uint8_t retVal = 0;
    srand(time(NULL));  //Seed for random number 
    switch (OP_HEAD(self->currentOP.opcode)){
        case 0x0: 
            switch (OP_TAIL(self->currentOP.opcode)){
                case 0x0: //CLS
                    {
                        int i;
                        for(i = 0; i < 64 * 32; i++)
                            self->gfxBuffer[i] = 0;
                    }
                    self->screenUpdate = 1;
                    retVal = 1; break;
                case 0xE: //RET
                    self->PC = self->stack[self->SP];
                    self->SP--;
                    break;
                default : //SYS addr SIKINTILI ve görmezden gelinebilir
                    self->PC = OP_nnn;
                    retVal = 1; break;
                }
            break;
        case 0x1: //JP addr
            self->PC = OP_nnn;
            break;
        case 0x2: //CALL addr
            self->SP++;
            self->stack[self->SP] = self->PC;
            self->PC = OP_nnn;
            break;
        case 0x3: //SE Vx, byte
            if(self->V[OP_Vx] == OP_kk) self->PC += 2;
            retVal = 1; break;
        case 0x4: //SNE Vx, byte
            if(self->V[OP_Vx] != OP_kk) self->PC += 2;
            retVal = 1; break;
        case 0x5: //SE Vx, Vy
            if(self->V[OP_Vx] == self->V[OP_Vy]) self->PC += 2;
            retVal = 1; break;
        case 0x6: //LD Vx, byte
            self->V[OP_Vx] = OP_kk;
            retVal = 1; break;
        case 0x7: //ADD Vx, byte
            self->V[OP_Vx] += OP_kk;
            retVal = 1; break;
        case 0x8:
            switch (OP_TAIL(self->currentOP.opcode)){
                case 0x0: self->V[OP_Vx] = self->V[OP_Vy]; 
                    retVal = 1; break; //LD Vx, Vy
                case 0x1: self->V[OP_Vx] |= self->V[OP_Vy]; 
                    retVal = 1; break; //OR Vx, Vy
                case 0x2: self->V[OP_Vx] &= self->V[OP_Vy];
                      retVal = 1; break; //AND Vx, Vy
                case 0x3: self->V[OP_Vx] ^= self->V[OP_Vy]; 
                      retVal = 1; break; //XOR Vx, Vy
                case 0x4: //ADD Vx, Vy
                    if((0xFF - self->V[OP_Vx]) < self->V[OP_Vy])  self->V[0xF] = 1;
                    else    self->V[0xF] = 0;
                    self->V[OP_Vx] += self->V[OP_Vy];
                    retVal = 1; break;
                case 0x5: //SUB Vx, Vy
                    if(self->V[OP_Vx] > self->V[OP_Vy]) self->V[0xF] = 1;
                    else    self->V[0xF] = 0;
                    self->V[OP_Vx] -= self->V[OP_Vy];
                    retVal = 1; break;
                case 0x6: //SHR Vx {, Vy}
                    self->V[0xF] = self->V[OP_Vx] & 0x1;
                    self->V[OP_Vy] = self->V[OP_Vy] >> 1;
                    retVal = 1; break;
                case 0x7: //SUBN Vx, Vy
                    if(self->V[OP_Vy] > self->V[OP_Vx]) self->V[0xF] = 1;
                    else    self->V[0xF] = 0;
                    self->V[OP_Vx] = self->V[OP_Vy] - self->V[OP_Vx];
                    retVal = 1; break;
                case 0xE: //SHL Vx {, Vy}
                    self->V[0xF] = (self->V[OP_Vx] >> 7) & 0x1;
                    self->V[OP_Vy] = self->V[OP_Vy] << 1;
                    retVal = 1; break;
                }
            break;
        case 0x9: //SNE Vx, Vy
            if(self->V[OP_Vx] != self->V[OP_Vy]) self->PC += 2;
            retVal = 1; break;
        case 0xA: self->I = OP_nnn; retVal = 1; break; //LD I, addr
        case 0xB: self->PC = OP_nnn + self->V[0x0]; break; //JP V0, addr
        case 0xC: //RND Vx, byte
              self->V[OP_Vx] = (rand() % 256) & OP_kk; 
              retVal = 1; break;
        case 0xD: //DRW Vx, Vy, nibble 
            {
                int height = OP_TAIL(self->currentOP.opcode);
                int x, y;
                int pixel;

                for (y = 0; y < height; y++){
                    pixel = self->Mem[self->I + y];
                    for (x = 0; x < 8; x++){
                        if(pixel & (0x80 >> x)){
                            if(self->gfxBuffer[self->V[OP_Vx] + x + (self->V[OP_Vy] + y)*64])
                                self->V[0xF] = 1;
                            self->gfxBuffer[x + self->V[OP_Vx] + (y + self->V[OP_Vy]) * 64] ^= 1;
                        }
                    }
                }
            }
            self->screenUpdate = 1;
            retVal = 1; break;
        case 0xE:
            switch (OP_TAIL(self->currentOP.opcode)){
                case 0xE: //SKP Vx      
                    if(self->activeKey == self->V[OP_Vx]) self->PC += 2;
                    retVal = 1; break;
                case 0x1: //SKNP Vx     BURAYA GELICEM
                    if(self->activeKey != self->V[OP_Vx]) self->PC += 2;
                    retVal = 1; break;
                }
            break;
        case 0xF:
            switch (self->currentOP.opcode & 0x00FF){
                case 0x07: self->V[OP_Vx] = self->delay_timer; retVal = 1; break; //LD Vx, DT
                case 0x0A:  //LD Vx, K      //DOLDURUCAM 
                    getch();
                    retVal = 1; break;
                case 0x15: self->delay_timer = self->V[OP_Vx]; retVal = 1; break; //LD DT, Vx
                case 0x18: self->sound_timer = self->V[OP_Vx]; retVal = 1; break; //LD ST, Vx
                case 0x1E: self->I += self->V[OP_Vx]; retVal = 1; break; //ADD I, Vx
                case 0x29: self->I = self->V[OP_Vx] * 5; retVal = 1; break; //LD F, Vx
                case 0x33: //LD B, Vx
                    self->Mem[self->I] = self->V[OP_Vx] / 100;
                    self->Mem[self->I + 1] = (self->V[OP_Vx] / 10) % 10;
                    self->Mem[self->I + 2] = self->V[OP_Vx] % 10;
                    retVal = 1; break;
                case 0x55: //LD [I], Vx
                    {
                        int i;
                        for (i = 0; i < OP_Vx; i++)
                            self->Mem[self->I + i] = self->V[i];
                    }
                    retVal = 1; break;
                case 0x65: //LD Vx, [I]
                    {
                        int i;
                        for (i = 0; i < OP_Vx; i++)
                            self->V[i] = self->Mem[self->I + i];
                    }
                    retVal = 1; break;

                }
            break;
    }
    if (self->delay_timer) self->delay_timer--;
    if (self->sound_timer) self->sound_timer--;
    return retVal;
}
