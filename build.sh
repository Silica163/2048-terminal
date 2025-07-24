#!/usr/bin/sh
echo gcc -static -o 2048 2048.c
time gcc -static -o 2048 2048.c
echo
echo x86_64-w64-mingw32-gcc -static -fexec-charset=cp437 2048.c -o 2048.exe
time x86_64-w64-mingw32-gcc -static -fexec-charset=cp437 2048.c -o 2048.exe
