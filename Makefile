all: candy_crush

candy_crush: plateau.cpp
	g++ plateau.cpp -o plateau -lfltk -lfltk_images

clean:
	rm -f plateau
