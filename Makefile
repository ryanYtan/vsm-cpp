CXXC			= clang++
CXXFLAGS		= -std=c++17 -Wall -Wextra -Wpedantic -g -Wno-unknown-pragmas -Wno-write-strings

DIR_SRC			= ./src
DIR_TEST		= ./test
DIR_LIB			= ./lib

CPPFILES		= $(shell find ./src -type f -name "*.cpp" ! -name index.cpp ! -name search.cpp)
CPPFILES_TEST	= $(shell find ./test -type f -name "*.cpp")

CPPINDEX		= ./src/index.cpp
CPPSEARCH		= ./src/search.cpp
OUTPUT_INDEX	= ./index
OUTPUT_SEARCH	= ./search
OUTPUT_TEST		= ./main_test

.PHONY: index search test

index:
	$(CXXC) $(CXXFLAGS) $(CPPFILES) -I $(DIR_SRC) -I $(DIR_LIB) $(CPPINDEX) -o $(OUTPUT_INDEX)

search:
	$(CXXC) $(CXXFLAGS) $(CPPFILES) -I $(DIR_SRC) -I $(DIR_LIB) $(CPPSEARCH) -o $(OUTPUT_SEARCH)

test:
	$(CXXC) $(CXXFLAGS) $(CPPFILES) $(CPPFILES_TEST) -I $(DIR_SRC) -I $(DIR_TEST) -I $(DIR_LIB) -o $(OUTPUT_TEST)

OBJFILES = $(shell find . -type f -name "*.o")
clean:
	rm -f OBJFILES
