# Source Code Stats Makefile

CC = g++
CFLAGS = -std=c++17 -W -Wall -march  -I "lib/inc/" -L "lib/"
LDFLAGS = 
EXEC = dist/sc_stat
SRC_DIR = src
BIN_DIR = bin
DEP_DIR = dep

SRC = $(wildcard $(SRC_DIR)/**.cpp)
OBJ = $(SRC:$(SRC_DIR)/%.cpp=$(BIN_DIR)/%.o)
DEP = $(OBJ:$(BIN_DIR)/%.o=$(DEP_DIR)/%.d)

all: $(EXEC)

out:
	@echo $(SRC)

$(DEP_DIR)/%.d: $(SRC_DIR)/%.cpp
	mkdir -p $(@D)
	$(CC) -MM -MT '$(patsubst $(SRC_DIR)/%.cpp,$(BIN_DIR)/%.o,$<)' $< -MF $@ $(CFLAGS)

$(BIN_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CC) -o $@ -c $< $(CFLAGS)

$(EXEC): $(OBJ)
	mkdir -p $(@D)
	$(CC) -o $@ $^ $(LDFLAGS)

.PHONY: clean mrproper

clean:
	rm -rf $(BIN_DIR)/*.* $(DEP_DIR)/*.*

mrproper: clean
	rm -rf $(EXEC).*
	
-include $(DEP)