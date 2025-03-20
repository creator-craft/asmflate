bin:
	@mkdir bin

compile: bin
	@nasm -o bin/prog src/ASM/prog.asm

compile_c: bin
	@gcc -o bin/prog src/C/*.c -I include

run:
	@./bin/prog Makefile

test_c: compile_c run

all: compile run
