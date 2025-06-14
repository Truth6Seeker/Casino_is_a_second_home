CXX = g++
CXXFLAGS = -std=c++17 -Iheaders
SRC_DIR = src
MAIN_DIR = main
SRC = $(wildcard $(SRC_DIR)/*.cpp) $(MAIN_DIR)/main.cpp
OBJ = $(SRC:.cpp=.o)
EXEC = casino_app

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CXX) $(CXXFLAGS) $^ -o $@

$(SRC_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(MAIN_DIR)/%.o: $(MAIN_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(EXEC)

.PHONY: all clean