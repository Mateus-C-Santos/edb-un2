CXX := g++

# -MMD/-MP criam dependencias de cabecalhos sem manutencao manual.
CPPFLAGS := -Iheader -Ilib -MMD -MP
# Simbolos, cores e sanitizers tornam os diagnosticos mais claros.
CXXFLAGS := -std=c++20 -Wall -Wextra -Wpedantic -g3 -O0 \
	-fno-omit-frame-pointer -fdiagnostics-color=always -fsanitize=address,undefined
LDFLAGS := -fsanitize=address,undefined

SRC_DIR := src
TEST_DIR := test
BIN_DIR := bin
TEST_SUITES := ConstrutorTamanho Consistencia Inserir Remover Buscar

SOURCES := $(wildcard $(SRC_DIR)/*.cpp)
TEST_SOURCES := $(addprefix $(TEST_DIR)/Teste,$(addsuffix .cpp,$(TEST_SUITES)))
APP_OBJECTS := $(patsubst $(SRC_DIR)/%.cpp,$(BIN_DIR)/obj/src/%.o,$(SOURCES))
TEST_SRC_OBJECTS := $(patsubst $(SRC_DIR)/%.cpp,$(BIN_DIR)/obj/test-src/%.o,$(filter-out $(SRC_DIR)/main.cpp,$(SOURCES)))
TEST_OBJECTS := $(patsubst $(TEST_DIR)/%.cpp,$(BIN_DIR)/obj/test/%.o,$(TEST_SOURCES))
DEPENDENCIES := $(APP_OBJECTS:.o=.d) $(TEST_SRC_OBJECTS:.o=.d) $(TEST_OBJECTS:.o=.d)

EXECUTABLE := $(BIN_DIR)/main
FUNCTIONAL_TEST_EXECUTABLES := $(BIN_DIR)/test-construtor-tamanho $(BIN_DIR)/test-consistencia \
	$(BIN_DIR)/test-inserir $(BIN_DIR)/test-buscar $(BIN_DIR)/test-remover

.DEFAULT_GOAL := all
.PHONY: all test run run-test run-test-construtor-tamanho run-test-consistencia run-test-inserir \
	run-test-buscar run-test-remover clean

all: $(EXECUTABLE) $(FUNCTIONAL_TEST_EXECUTABLES)
test: $(FUNCTIONAL_TEST_EXECUTABLES)

$(EXECUTABLE): $(APP_OBJECTS)
	@mkdir -p $(@D)
	$(CXX) $(LDFLAGS) $^ -o $@

# Cada suíte possui seu próprio main do doctest e compartilha a implementação da lista.
$(BIN_DIR)/test-construtor-tamanho: $(BIN_DIR)/obj/test/TesteConstrutorTamanho.o $(TEST_SRC_OBJECTS)
	@mkdir -p $(@D)
	$(CXX) $(LDFLAGS) $^ -o $@

$(BIN_DIR)/test-consistencia: $(BIN_DIR)/obj/test/TesteConsistencia.o $(TEST_SRC_OBJECTS)
	@mkdir -p $(@D)
	$(CXX) $(LDFLAGS) $^ -o $@

$(BIN_DIR)/test-inserir: $(BIN_DIR)/obj/test/TesteInserir.o $(TEST_SRC_OBJECTS)
	@mkdir -p $(@D)
	$(CXX) $(LDFLAGS) $^ -o $@

$(BIN_DIR)/test-buscar: $(BIN_DIR)/obj/test/TesteBuscar.o $(TEST_SRC_OBJECTS)
	@mkdir -p $(@D)
	$(CXX) $(LDFLAGS) $^ -o $@

$(BIN_DIR)/test-remover: $(BIN_DIR)/obj/test/TesteRemover.o $(TEST_SRC_OBJECTS)
	@mkdir -p $(@D)
	$(CXX) $(LDFLAGS) $^ -o $@

$(BIN_DIR)/obj/src/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(@D)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@

$(BIN_DIR)/obj/test-src/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(@D)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@

$(BIN_DIR)/obj/test/%.o: $(TEST_DIR)/%.cpp
	@mkdir -p $(@D)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@

run: $(EXECUTABLE)
	./$(EXECUTABLE) $(ARGS)

run-test: test
	@set -e; for executable in $(FUNCTIONAL_TEST_EXECUTABLES); do ./$$executable $(ARGS); done

run-test-construtor-tamanho: $(BIN_DIR)/test-construtor-tamanho
	./$< $(ARGS)

run-test-consistencia: $(BIN_DIR)/test-consistencia
	./$< $(ARGS)

run-test-inserir: $(BIN_DIR)/test-inserir
	./$< $(ARGS)

run-test-buscar: $(BIN_DIR)/test-buscar
	./$< $(ARGS)

run-test-remover: $(BIN_DIR)/test-remover
	./$< $(ARGS)

clean:
	@mkdir -p "$(BIN_DIR)"
	@find "$(BIN_DIR)" -mindepth 1 -maxdepth 1 ! -name .gitkeep -exec rm -rf {} +

-include $(DEPENDENCIES)
