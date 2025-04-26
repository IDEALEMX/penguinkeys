

default:
	clang++ main.cpp -o main -Llib -lraylib -Iinclude -ldl -lGL -lm -lpthread -lrt -lX11
