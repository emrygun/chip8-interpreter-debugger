#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>

#include "utils.h"

int main(int argc, const char **argv){
    printf("(~~) CHIP-8 Terminal Emulator (~~)\n");

    //Check the arg count
    if (argc <= 1){
        printf("Bad usage. Try \"chip8Interpreter --help\" for more information\n");
        return 0;
    }
    
    //Cases 
    if (argv[1][0] == '-'){
        switch(argv[1][1]){
            case 'd':   //Disassembler
                chip8Disassembler(loadROM(argv[2]));
                break;
            default:    //Default
                printf("Bad usage. Try \"chip8Interpreter --help\" for more information\n");
                break;
        }
    }

    else{
        chip8Interpreter(loadROM(argv[1]));
    }
    return 0;
}   
