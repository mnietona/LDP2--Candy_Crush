 FLAGS= -Wall --std='c++20' -lfltk -lfltk_images 


all: candy_crush

candy_crush: candy_crush.cpp
	g++ candy_crush.cpp -o candy_crush $(FLAGS)
