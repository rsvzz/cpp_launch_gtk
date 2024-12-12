INC = inc
INC_MODEL = $(INC)/model
INC_GTK = $(INC)/gtk
#Compile
CXX = g++ -std=c++17
#dir .0
BIN_DIR = bin
MODEL_DIR = $(BIN_DIR)/model
ROOT_GTK_DIR = $(BIN_DIR)/gtk
TARGET = $(BIN_DIR)/cpplouch

OBJ_SRC = src
OBJ_MODEL = $(OBJ_SRC)/model
OBJ_ROOT_GTK_DIR = $(ROOT_GTK_DIR)/main.o $(ROOT_GTK_DIR)/GtkMain.o
OBJ_MODEL_DIR = $(MODEL_DIR)/PathItemList.o
LIBS_GTKMM = `pkg-config --cflags --libs gtkmm-4.0`
CFLAGS = -Wall -g -I$(INC_MODEL)$(INC_GTK)

all : $(OBJ_MODEL_DIR) $(OBJ_ROOT_GTK_DIR)
	@mkdir bin -p
	$(CXX) -o $(TARGET) $? $(LIBS_GTKMM) $(CFLAGS)

$(ROOT_GTK_DIR)/%.o : $(OBJ_SRC)/%.cpp
	@mkdir $(BIN_DIR) -p
	@mkdir $(ROOT_GTK_DIR) -p
	$(CXX) -c $? -o $@ $(LIBS_GTKMM)

$(MODEL_DIR)/%.o : $(OBJ_MODEL)/%.cpp
	@mkdir $(BIN_DIR) -p
	@mkdir $(MODEL_DIR) -p
	$(CXX) -c $? -o $@

exe :
	@./$(TARGET)

clean :
	@rm -r $(BIN_DIR)
