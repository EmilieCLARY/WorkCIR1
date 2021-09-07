CC=gcc
CFLAGS=-I.

SRC_DIR=./src
OBJ_DIR=./obj
SRC_FILES := $(wildcard $(SRC_DIR)/*.c)
OBJ_FILES := $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRC_FILES))

main.exe: $(OBJ_FILES) 
	clang $(LDFLAGS) -o $@ $^

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p obj
	clang $(CFLAGS) -c -o $@ $<