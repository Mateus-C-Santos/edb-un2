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

SOURCES := $(wildcard $(SRC_DIR)/*.cpp)
TEST_SOURCES := $(wildcard $(TEST_DIR)/*.cpp)
APP_OBJECTS := $(patsubst $(SRC_DIR)/%.cpp,$(BIN_DIR)/obj/src/%.o,$(SOURCES))
TEST_SRC_OBJECTS := $(patsubst $(SRC_DIR)/%.cpp,$(BIN_DIR)/obj/test-src/%.o,$(filter-out $(SRC_DIR)/main.cpp,$(SOURCES)))
TEST_OBJECTS := $(patsubst $(TEST_DIR)/%.cpp,$(BIN_DIR)/obj/test/%.o,$(TEST_SOURCES))
DEPENDENCIES := $(APP_OBJECTS:.o=.d) $(TEST_SRC_OBJECTS:.o=.d) $(TEST_OBJECTS:.o=.d)

EXECUTABLE := $(BIN_DIR)/main
TEST_EXECUTABLE := $(BIN_DIR)/test

.DEFAULT_GOAL := all
.PHONY: all test run run-test clean

all: $(EXECUTABLE) $(TEST_EXECUTABLE)
test: $(TEST_EXECUTABLE)

$(EXECUTABLE): $(APP_OBJECTS)
	@mkdir -p $(@D)
	$(CXX) $(LDFLAGS) $^ -o $@

$(TEST_EXECUTABLE): $(TEST_SRC_OBJECTS) $(TEST_OBJECTS)
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

run-test: $(TEST_EXECUTABLE)
	./$(TEST_EXECUTABLE) $(ARGS)

clean:
	@mkdir -p "$(BIN_DIR)"
	@find "$(BIN_DIR)" -mindepth 1 -maxdepth 1 ! -name .gitkeep -exec rm -rf {} +

-include $(DEPENDENCIES)
