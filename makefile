# Var definitions

export MAKEFLAGS=-j9

CXX = g++-4.8 -O3
CC_FLAGS = -W -Wall -g -std=c++11
LD_FLAGS = -lpthread -lboost_thread -lboost_system


SRC_FILES := $(wildcard src/*.cpp)

TEST_FILES := $(wildcard test/*.cpp)
TEST_FILES += $(sort $(SRC_FILES) $(TEST_FILES))
TEST_FILES := $(filter-out src/Main.cpp, $(TEST_FILES)) 

OBJ_FILES := $(addprefix obj/,$(notdir $(SRC_FILES:.cpp=.o)))
OBJ_TEST_FILES := $(addprefix obj/,$(notdir $(TEST_FILES:.cpp=.o)))

SRC_DIR = $(shell pwd)/src

all: Deepov DeepovTesting

Deepov: $(OBJ_FILES)
	$(CXX)  -o $@ $^ $(LD_FLAGS)

obj/%.o: src/%.cpp
	$(CXX) $(CC_FLAGS) -c -o $@ $<

clean:
	rm -rf $(OBJ_TEST_FILES) rm -rf $(OBJ_FILES)

DeepovTesting: $(OBJ_TEST_FILES) 
	$(CXX) -o $@ $^ $(LD_FLAGS)

obj/%.o: test/%.cpp
	$(CXX) $(CC_FLAGS) -I $(SRC_DIR) -c -o $@ $<




