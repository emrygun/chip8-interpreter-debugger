#ifndef UTILS_H
#define UTILS_H

#include <stdint.h>
#include <ncurses.h>
#include "chip8.h"

FILE_ROM loadROM(const char ROMdir[]);      //Load rom and return rom structure
void chip8Disassembler(FILE_ROM tempROM);   //Get rom and disassemble
void chip8ScreenDraw(chip8 *self, WINDOW *screen, int xOffset, int yOffset);
void chip8Interpreter(FILE_ROM tempROM);    //Run CHIP-8 Interpreter
void chip8DebuggerUpdate(chip8 *self, WINDOW *reg, WINDOW *op, WINDOW *stack, WINDOW *timer);
int getArgs(int argc, const char **argv);   //Get args and do stuff

void rectangle(int y1, int x1, int y2, int x2);

#endif
