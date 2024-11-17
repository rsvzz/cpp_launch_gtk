INC = inc
INC_MODEL = $(INC)/model
INC_GTK = $(INC)/gtk
OBJ_SRC = src
OBJ_MODEL = $(OBJ_SRC)/model
OBJ_SRC_DIR = $(OBJ_SRC)/main.cpp $(OBJ_SRC)/GtkMain.cpp
OBJ_MODEL_DIR = $(OBJ_MODEL)/PathBin.cpp
CFLAGS = -Wall -g -I$(INC_MODEL)$(INC_GTK)
all : 
	@mkdir bin -p
	g++-11 -std=c++17 -o bin/app $(OBJ_SRC_DIR) $(OBJ_MODEL_DIR)  `pkg-config --cflags --libs gtkmm-3.0` $(CFLAGS)

exe :
	@./bin/app

clean :
	@rm -r bin