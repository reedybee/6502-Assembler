make: 
	gcc -Wall -g src/main.c src/compiler/token.c -o main.exe -Isrc/
	gdb -q main.exe example.asm