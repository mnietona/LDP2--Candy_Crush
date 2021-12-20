all: candy_crush

candy_crush: plateau.cpp image.cpp
	g++ plateau.cpp -o plateau -lfltk -lfltk_images -w
	g++ image.cpp -o image -lfltk -lfltk_images -w

clean:
	rm -f plateau image
