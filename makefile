# Var definitions
CXX = g++-4.8
CC_FLAGS = -W -Wall -g -std=c++11

SRC_FILES := $(wildcard src/*.cpp)

TEST_FILES := $(wildcard test/*.cpp)
TEST_FILES += $(SRC_FILES)
TEST_FILES := $(filter-out src/Main.cpp, $(TEST_FILES)) 

OBJ_FILES := $(addprefix obj/,$(notdir $(SRC_FILES:.cpp=.o)))
OBJ_TEST_FILES := $(addprefix obj/,$(notdir $(TEST_FILES:.cpp=.o)))

all: Deepov DeepovTesting

Deepov: $(OBJ_FILES)
	$(CXX) $(LD_FLAGS) -o $@ $^

obj/%.o: src/%.cpp
	$(CXX) $(CC_FLAGS) -c -o $@ $<

clean:
	rm -rf *.bak rm -rf $(OBJ_FILES)

DeepovTesting: $(OBJ_TEST_FILES)
	$(CXX) $(LD_FLAGS)  -o $@ $^


