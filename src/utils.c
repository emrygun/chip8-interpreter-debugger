#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <ncurses.h>

#include "chip8.h"
#include "utils.h"

FILE_ROM loadROM(const char ROMdir[]){
    FILE_ROM ROM;

    ROM.ROM = fopen(ROMdir, "r");    //Open file 
    if(ROM.ROM == NULL){ //fopen exception
        printf("(-) Error while oppening file (errno = %d).\n", errno);
        exit(0);
    } 
    else{
        memcpy(ROM.ROMName, ROMdir, 100);
    }
    
    //Get ROM size and copy context into buffer
    fseek(ROM.ROM, 0UL, SEEK_END);
    ROM.size = ftell(ROM.ROM);
    rewind(ROM.ROM);
    fread(ROM.buffer, ROM.size, 1, ROM.ROM);
    return ROM;
}

void chip8Disassembler(FILE_ROM tempROM){
    chip8 *myChip8 = malloc(sizeof(chip8));
    chip8Init(myChip8, tempROM);

    for(myChip8->PC = 0x200; (myChip8->PC - 0x200) < tempROM.size; myChip8->PC += 2){
        fetchOP(myChip8);
        printf("0x%03x: %s\n",myChip8->PC - 0x200, myChip8->currentOP.opcodeName);
    }
}
//Interpreter routines

void rectangle(int y1, int x1, int y2, int x2) {
    mvhline(y1, x1, 0, x2-x1);
    mvhline(y2, x1, 0, x2-x1);
    mvvline(y1, x1, 0, y2-y1);
    mvvline(y1, x2, 0, y2-y1);
    mvaddch(y1, x1, ACS_ULCORNER);
    mvaddch(y2, x1, ACS_LLCORNER);
    mvaddch(y1, x2, ACS_URCORNER);
    mvaddch(y2, x2, ACS_LRCORNER);
}

void chip8ScreenDraw(chip8 *self, WINDOW *screen, int xOffset, int yOffset){
    int drawY = self->V[(self->currentOP.opcode & 0xF0) >> 4];
    int temp;

    for (drawY; drawY < self->V[(self->currentOP.opcode & 0xF0)>>4] + 
                                (self->currentOP.opcode & 0xF); drawY++){
        int drawX = self->V[(self->currentOP.opcode & 0xF00)>>8];
        for (drawX; drawX < (self->V[(self->currentOP.opcode & 0xF00)>>8]) + 8 & drawX < 64; drawX++){
            if (self->gfxBuffer[(64 * drawY) + drawX])
                mvwprintw(screen, drawY + yOffset, ((drawX % 65) * 2) + xOffset, "##");
            else
                mvwprintw(screen, drawY + yOffset, ((drawX % 65) * 2) + xOffset, "  ");
        }
    }
    self->screenUpdate = 0;
}

void chip8DebuggerUpdate(chip8 *self, WINDOW *reg, WINDOW *op, WINDOW *stack, WINDOW *timer){
    int i;
    //Register Update
    mvwprintw(reg, 2, 3, "PC:\t0x%04x", self->PC); 
    mvwprintw(reg, 3, 3, "SP:\t0x%04x", self->SP);
    mvwprintw(reg, 4, 3, "I:\t0x%04x", self->I);
    for (i = 0; i < 16; i++) mvwprintw(reg, 6 + i, 3, "V[%x]: 0x%04x", i, self->V[i]);

    //Timer Update
    mvwprintw(timer, 2, 3, "DT:\t0x%04x", self->delay_timer);
    mvwprintw(timer, 3, 3, "ST:\t0x%04x", self->sound_timer);

    //OP update
    mvwprintw(op, 2, 3, "Opcode: 0x%04x", self->currentOP.opcode); 
    mvwprintw(op, 3, 3, "                      ");
    mvwprintw(op, 3, 3, "%s", self->currentOP.opcodeName);

    //Stack update
    for(i = 0x0; i < 0x10; i++){
        if (self->SP >= (15 - i))   mvwprintw(stack, i + 2, 3, "[0x%x]: 0x%04x", 15 - i, self->stack[15 - i]);
        else mvwprintw(stack, i + 2, 3, "[0x%x]:       ", 15 - i);
    }
}

void chip8Interpreter(FILE_ROM tempROM, int step){
    int stepFlag = step;
    int temp;
    chip8 *myChip8 = malloc(sizeof(chip8));
    chip8Init(myChip8, tempROM);
    
    //Initialize of screens
    initscr();
    cbreak();
    noecho();
    nodelay(stdscr, TRUE);
    curs_set(0);

    WINDOW * interpreterScreen = newwin(34, 130, 0, 0);
    WINDOW * registerScreen = newwin(24, 18, 0, 131);
    WINDOW * opScreen = newwin(6, 28, 24, 150);
    WINDOW * stackScreen = newwin(20, 19, 0, 150);
    WINDOW * timerScreen = newwin (6, 18, 24 , 131);

    refresh();
    
    //Game screen init
    box(interpreterScreen, 0, 0);
    mvwprintw(interpreterScreen, 0, 2, "CHIP-8 Interpreter Screen");
    mvwprintw(interpreterScreen, 33, 2, "Directory: %.*s", 80, tempROM.ROMName);
    mvwprintw(interpreterScreen, 33, 112, "ROM Size: 0x%04x", tempROM.size);
    touchwin(interpreterScreen);
    wrefresh(interpreterScreen);

    //Register screen init
    box(registerScreen, 0, 0);
    mvwprintw(registerScreen, 0, 2, "Registers");
    wrefresh(registerScreen);
    touchwin(registerScreen);

    //opScreen screen init
    box(opScreen, 0, 0);
    mvwprintw(opScreen, 0, 2, "Opcode");
    wrefresh(opScreen);
    touchwin(opScreen);

    //stackScreen init
    box(stackScreen, 0, 0);
    mvwprintw(stackScreen, 0, 2, "Stack");
    wrefresh(stackScreen);
    touchwin(stackScreen);

    //timerScreen init
    box(timerScreen, 0, 0);
    mvwprintw(timerScreen, 0, 2, "Timers");
    wrefresh(timerScreen);
    touchwin(timerScreen);

    //Fill
    rectangle(30, 131, 33, 178);
    mvprintw(30, 133, "======= CHIP-8 Interpreter/ Debugger =======");
    mvprintw(32, 133, "Step-By-Step Mode: [%c]", (stepFlag ? '+' : '-'));
    for (temp = 0; temp < 30; temp++) mvhline(temp, 150, 0, 28);
    refresh();

    //Engine loop
    while(1){
        fetchOP(myChip8);
        chip8DebuggerUpdate(myChip8, registerScreen, opScreen, stackScreen, timerScreen);
        wrefresh(interpreterScreen);
        wrefresh(registerScreen);
        wrefresh(opScreen);
        wrefresh(stackScreen);
        wrefresh(timerScreen);
        refresh();
        napms(5);
        //Step by step mode
        if (stepFlag) while (getch() != ' '); 
        if(executeOP(myChip8)) myChip8->PC += 2;
        if(myChip8->screenUpdate) chip8ScreenDraw(myChip8, interpreterScreen, 1, 1);
    }
    endwin();
}
