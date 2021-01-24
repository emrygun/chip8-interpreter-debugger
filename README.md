# chip8-interpreter-debugger

![chip8-interpreter-debugger](https://raw.githubusercontent.com/emrygun/chip8-interpreter-debugger/main/2021-01-23_22-20.png?token=AKRJFVOK3HVHR3FTXMU7FXLABR4TC)
## Table of contents
* [General info](#general-info)
* [Notes](#notes)
* [Setup](#setup)
* [Usage](#usage)
* [Technical Reference and Contact](#technical-reference-and-contact)

## General info
A basic CHIP-8 Interpreter with debugger. Interpreter's gui is powered by ncurses. Developed just for fun.<br/>
	
## Notes
Keep in mind:
* Sound not implemented.
* Refreshing rate is not stable. <br/>

I'll fix these issues soon.
	
## Setup
You'll need "libncurses5" and "CMake" to compile project
libncurses installation

After you clone the project:

```
$ cd chip8-interpreter-debugger
$ mkdir make
$ cd make
$ cmake ../

```

## Usage
* As Interpreter:
```
$ ./chip8-interpreter-debugger <rom_directory>
```
* As Debugger:
```
$ ./chip8-interpreter-debugger -s <rom_directory>
```
* As Disassembler:
```
$ ./chip8-interpreter-debugger -d <rom_directory>
```

Keypad: <br/>
<kbd>4</kbd><kbd>5</kbd><kbd>6</kbd><kbd>7</kbd> <br />
<kbd>R</kbd><kbd>T</kbd><kbd>Y</kbd><kbd>U</kbd> <br />
<kbd>F</kbd><kbd>G</kbd><kbd>H</kbd><kbd>J</kbd> <br />
<kbd>C</kbd><kbd>V</kbd><kbd>B</kbd><kbd>N</kbd> <br />

* To next step on debugger <kbd>SPACEBAR</kbd><br/>
* To Terminate <kbd>CTRL</kbd> + <kbd>C</kbd>

## Techinal Reference and Conctact
Technical reference: <a href="http://devernay.free.fr/hacks/chip8/C8TECH10.HTM">Cowgod's Chip-8 Technical Reference</a><br/>
Contact: emre6271@gmail.com
