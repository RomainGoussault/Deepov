# Var definitions

export MAKEFLAGS=-j3

CXX = clang++ -std=c++14 -O3 -W

CC_FLAGS =
LD_FLAGS =

ifeq ($(NO_POPCNT), 1)
    EXTRA_FLAGS += -DNO_POPCNT
    NO_POPCNT = 0
endif


SRC_FILES := $(wildcard src/*.cpp)

TEST_FILES := $(wildcard test/*.cpp)
TEST_FILES += $(sort $(SRC_FILES) $(TEST_FILES))
TEST_FILES := $(filter-out src/Main.cpp, $(TEST_FILES))

OBJ_FILES := $(addprefix obj/,$(notdir $(SRC_FILES:.cpp=.o)))
OBJ_TEST_FILES := $(addprefix obj/,$(notdir $(TEST_FILES:.cpp=.o)))

SRC_DIR = $(shell pwd)/src

all: Deepov DeepovTesting

Deepov: $(OBJ_FILES)
	$(CXX)  -o $@ $^ $(LD_FLAGS) $(EXTRA_FLAGS)

obj/%.o: src/%.cpp
	mkdir -p obj
	$(CXX) $(CC_FLAGS) -c -o $@ $<

clean:
	rm -rf $(OBJ_TEST_FILES) rm -rf $(OBJ_FILES)

DeepovTesting: $(OBJ_TEST_FILES)
	$(CXX) -o $@ $^ $(LD_FLAGS) $(EXTRA_FLAGS)

obj/%.o: test/%.cpp
	$(CXX) $(CC_FLAGS) -I $(SRC_DIR) -c -o $@ $<




