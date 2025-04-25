

default:
	clang main.c -o main -Llib -lraylib -Iinclude -ldl -lGL -lm -lpthread -lrt -lX11
