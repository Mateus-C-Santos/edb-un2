CC = g++
CFLAGS = -Wall -Wextra -pedantic -std=c++17 -Iheader -Ilib -g

# Diretórios
SRC_DIR = src
TEST_DIR = test
BIN_DIR = bin

# Fontes
SOURCES = $(wildcard $(SRC_DIR)/*.cpp)
OBJECTS = $(patsubst $(SRC_DIR)/%.cpp, $(BIN_DIR)/%.o, $(SOURCES))

# Executável principal
EXECUTABLE = $(BIN_DIR)/main

# Testes
TEST_SOURCES = $(filter-out $(SRC_DIR)/main.cpp, $(SOURCES)) $(wildcard $(TEST_DIR)/*.cpp)
TEST_OBJECTS = $(patsubst %.cpp, $(BIN_DIR)/%.o, $(notdir $(TEST_SOURCES)))
TEST_EXECUTABLE = $(BIN_DIR)/test

# Regra padrão
all: $(EXECUTABLE) $(TEST_EXECUTABLE)

# Compilar o executável principal
$(EXECUTABLE): $(OBJECTS)
	$(CC) $(CFLAGS) $^ -o $@

# Compilar o executável de teste
$(TEST_EXECUTABLE): $(addprefix $(BIN_DIR)/, $(notdir $(TEST_OBJECTS)))
	$(CC) $(CFLAGS) $^ -o $@

# Compilar .cpp → bin/*.o
$(BIN_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(BIN_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(BIN_DIR)/%.o: $(TEST_DIR)/%.cpp
	@mkdir -p $(BIN_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Alvos utilitários
.PHONY: run run-test clean test

test: $(TEST_EXECUTABLE)

run-test: $(TEST_EXECUTABLE)
	./$(TEST_EXECUTABLE) $(ARGS)

run: $(EXECUTABLE)
	./$(EXECUTABLE)

clean:
	rm -f $(BIN_DIR)/*.o $(EXECUTABLE) $(TEST_EXECUTABLE)