CC = g++ --std='c++20' -Wall -Wextra -Wpedantic -w

.PHONY: all
all: $(patsubst %.cpp, %.out, $(wildcard *.cpp))

%.out: %.cpp makefile
	$(CC) $< -o $@ -lfltk -lfltk_images
