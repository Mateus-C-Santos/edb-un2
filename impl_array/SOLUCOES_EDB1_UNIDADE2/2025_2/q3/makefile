CC = g++
CFLAGS = -Wall -Wextra -pedantic -std=c++17 -Iheader -I../lib -MMD -MP -fsanitize=address -fno-omit-frame-pointer -g
CFLAGS_TEST = $(CFLAGS) -DTESTE

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
TEST_OBJECTS = $(patsubst %.cpp, $(BIN_DIR)/%.test.o, $(notdir $(TEST_SOURCES)))
TEST_EXECUTABLE = $(BIN_DIR)/test

# Regra padrão
all: $(EXECUTABLE) $(TEST_EXECUTABLE)

# Compilar o executável principal
$(EXECUTABLE): $(OBJECTS)
	$(CC) $(CFLAGS) $^ -o $@

# Compilar o executável de teste
$(TEST_EXECUTABLE): $(TEST_OBJECTS)
	$(CC) $(CFLAGS_TEST) $^ -o $@

# Compilar fontes regulares
$(BIN_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(BIN_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Compilar fontes de teste com -DTESTE
$(BIN_DIR)/%.test.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(BIN_DIR)
	$(CC) $(CFLAGS_TEST) -c $< -o $@

$(BIN_DIR)/%.test.o: $(TEST_DIR)/%.cpp
	@mkdir -p $(BIN_DIR)
	$(CC) $(CFLAGS_TEST) -c $< -o $@

# Incluir dependências geradas automaticamente (.d)
-include $(OBJECTS:.o=.d)
-include $(TEST_OBJECTS:.o=.d)

# Alvos utilitários
.PHONY: run run-test clean test

test: $(TEST_EXECUTABLE)

run-test: $(TEST_EXECUTABLE)
	./$(TEST_EXECUTABLE) $(ARGS)

run: $(EXECUTABLE)
	./$(EXECUTABLE)

clean:
	rm -f $(BIN_DIR)/*.o $(BIN_DIR)/*.test.o $(BIN_DIR)/*.d $(EXECUTABLE) $(TEST_EXECUTABLE)