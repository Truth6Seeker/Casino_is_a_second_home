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

find_package(Doxygen REQUIRED)
if(DOXYGEN_FOUND)
    set(DOXYGEN_OUTPUT_DIR ${CMAKE_CURRENT_BINARY_DIR}/docs)
    set(DOXYGEN_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
    doxygen_add_docs(
        generate_docs
        ${DOXYGEN_SOURCE_DIR}
        COMMENT "Generating Doxygen docs"
    )
endif()