 FLAGS= -lfltk  -Wall --std='c++20' -lfltk -lfltk_images -w

 FICHIER = candy_crush.cpp class_candy/plateau.cpp class_candy/candy.cpp class_candy/text.cpp class_candy/rectangle.cpp class_candy/textrectangle.cpp class_candy/cell.cpp class_candy/score.cpp class_candy/effacer_bonbon.cpp class_candy/mouvement.cpp class_candy/canvas.cpp


all: candy_crush 

candy_crush: $(FICHIER)
         g++ $(FICHIER) -o candy_crush $(FLAGS)