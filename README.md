# chip8-interpreter-debugger

## Table of contents
* [General info](#general-info)
* [Notes](#notes)
* [Setup](#setup)
* [Usage](#usage)

## General info
A basic CHIP-8 Interpreter with debugger.<br />
Interpreter's gui is powered by ncurses.
	
## Notes

* Lorem version: 12.3
* Ipsum version: 2.33
* Ament library version: 999
	
## Setup
You'll need "libncurses5" and "CMake" to compile project
libncurses installation

<h3>libncurses Installation</h3>

For Debian/Ubuntu: 
```
$  sudo apt-get install libncurses5-dev libncursesw5-dev
```
For CentOS/RHEL/Scientific Linux 6.x/7.x+ and Fedora Linux 21 or older
```
$  sudo yum install ncurses-devel
```
For Fedora Linux 22.x+
```
$   sudo dnf install ncurses-devel
```
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

Interpreter and Original Keys <br/>
<kbd>4</kbd><kbd>5</kbd><kbd>6</kbd><kbd>7</kbd> | <kbd>1</kbd><kbd>2</kbd><kbd>3</kbd><kbd>C</kbd><br />
<kbd>R</kbd><kbd>T</kbd><kbd>Y</kbd><kbd>U</kbd> | <kbd>4</kbd><kbd>5</kbd><kbd>6</kbd><kbd>D</kbd><br />
<kbd>F</kbd><kbd>G</kbd><kbd>H</kbd><kbd>J</kbd> | <kbd>7</kbd><kbd>8</kbd><kbd>9</kbd><kbd>E</kbd><br />
<kbd>C</kbd><kbd>V</kbd><kbd>B</kbd><kbd>N</kbd> | <kbd>A</kbd><kbd>0</kbd><kbd>B</kbd><kbd>F</kbd><br />

* To next step on debugger <kbd>SPACEBAR</kbd><br/>
* To Terminate <kbd>CTRL</kbd> + <kbd>C</kbd>
