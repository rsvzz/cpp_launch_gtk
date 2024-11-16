INC = inc
INC_MODEL = $(INC)/model
INC_GTK = $(INC)/gtk
OBJ_SRC = src
OBJ_CPP = $(OBJ_SRC)/main.cpp $(OBJ_SRC)/GtkMain.cpp
CFLAGS = -Wall -g -I$(INC_MODEL)$(INC_GTK)
all : 
	@mkdir bin -p
	g++-11 -std=c++17 -o bin/app $(OBJ_CPP) `pkg-config --cflags --libs gtkmm-3.0` $(CFLAGS)

exe :
	@./bin/app