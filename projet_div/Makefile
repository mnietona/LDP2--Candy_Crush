all: candycrush

candycrush: Candy.cpp Canvas.cpp Cell.cpp main.cpp Plateau.cpp window.cpp
	g++ --std='c++20' Candy.cpp Canvas.cpp Cell.cpp main.cpp Plateau.cpp window.cpp -o candycrush -lfltk -lfltk_images

clean:
	rm -f candycrush