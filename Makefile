CC = gcc
CCFLAGS = -Wall -I include -g
SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = bin

SOURCES = $(wildcard $(SRC_DIR)/*.c)
OBJECTS = $(patsubst $(SRC_DIR),$(OBJ_DIR)/%.o,$(SOURCES))

EXECUTABLE = $(BIN_DIR)/xdc

all: $(EXECUTABLE)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CCFLAGS) -c $< -o $@

$(EXECUTABLE): $(OBJECTS)
	@mkdir -p $(BIN_DIR)
	$(CC) $(CCFLAGS) $^ -o $@

.PHONY: clean
clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)
