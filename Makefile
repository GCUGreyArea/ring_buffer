TARGET = producer_consumer

PWD = $(shell pwd)


TESTDIR    = $(PWD)/test
BENCHDIR   = $(PWD)/benchmark
LIBDIR     = $(PWD)/lib
DOXYDIR	   = $(PWD)/docs
BUILD      = build


PWD = $(shell pwd)

TESTTARGET = $(TESTDIR)/$(BUILD)/test_$(TARGET)
BNCTARGET  = $(BENCHDIR)/$(BUILD)/benchmark_$(TARGET)
LIBTARGET  = $(LIBDIR)/$(BUILD)/lib$(TARGET).so
DOCTARGET  = $(DOXYDIR)/generated

SRC = $(shell find src -name '*.c')

OBJ := $(patsubst %.c,$(BUILD)/%.o,$(SRC))

UNAME := $(shell uname -s)

ifeq ($(UNAME), Darwin)
CC       = cc
CXX      = c++
CFLAGS   = -std=c11 -Wall -g -fsanitize=address -I$(LIBDIR)/src -I.
CXXFLAGS = -std=c++17 -Wall -g -fsanitize=address -I$(LIBDIR)/src -I.
else
CC     = gcc
CXX    = g++
CFLAGS   = -std=c11 -Wall -fsanitize=address -I$(LIBDIR)/src -I.
CXXFLAGS = -std=c++17 -Wall -fsanitize=address -I$(LIBDIR)/src -I.
endif


export TESTDIR 
export BENCHDIR
export LIBDIR  
export DOXYDIR
export BUILD   


all: $(LIBTARGET) $(TESTTARGET) $(BNCTARGET) $(TARGET)

$(TARGET) : build $(LIBTARGET) $(TESTTARGET) $(BENCHTARGET) $(OBJ)
	$(CC) $(CCFLAGS) $(OBJ) -o $(BUILD)/$(TARGET) -I$(LIBDIR)/src -L$(LIBDIR)/build -lasan -l$(TARGET) -lpthread -Wl,-rpath,$(LIBDIR)/build

build :
	mkdir -p "$(BUILD)/src"

$(LIBTARGET) :
	cd $(LIBDIR) && make

$(TESTTARGET) : $(LIBTARGET)
	cd $(TESTDIR) && make

$(BNCTARGET) : $(LIB)
	cd $(BENCHDIR) && make

$(DOCTARGET) :
	cd $(DOXYDIR) && make

$(BUILD)/%.o: %.c
	$(CC) -c $(CFLAGS) $< -o $@

$(BUILD)/%.o: %.cpp
	$(CXX) -c $(CXXFLAGS) -c $< -o $@

clean:
	cd $(DOXYDIR) && make clean
	cd $(BENCHDIR) && make clean
	cd $(TESTDIR) && make clean
	cd $(LIBDIR) && make clean
	rm -rf $(BUILD)


install: $(TARGET)
	cp $(TARGET) $(INSTDIR)

valgrind: $(TARGET)
	valgrind --leak-check=full ./$(TARGET)

docs: $(DOCTARGET)
	cd $(DOXYDIR) && doxygen Doxyfile

test: $(TESTTARGET)
	cd $(LIBDIR) && make
	cd $(TESTDIR) && make
	$(TESTTARGET)

benchmark: $(BNCTARGET)
	cd $(LIBDIR) && make
	cd $(BENCHDIR) && make
	$(BNCTARGET)

runtest:
	cd $(TESTDIR) && make run

runbench:
	cd $(BENCHDIR) && make run

run:
	./$(TARGET) $(ARGS)

project:
	cd $(LIBDIR) && make
	cd $(TESTDIR) && make
	cd $(BENCHDIR) && make
	make

help:
	@echo "\n\n"
	@echo "============================================================================================="
	@echo "Run: 'make' to build the project"
	@echo "Run: 'make test' to build and run unit tests"
	@echo "Run: 'make benchmark' to build and run unit tests - currently no benchmarks are implemented"
	@echo "Run: 'make runtest' to run the unit tests"
	@echo "Run: 'make runbench' to run the benchmarks - currently no benchmarks are implemented"
	@echo "Run: 'make doxygen' to build doxygen documentation\n"
	@echo "This project depends on:\n"
	@echo "\tGoogles test framework availible at https://github.com/google/googletest"
	@echo "\tGoogles benchmark framework availible at https://github.com/google/benchmark"
	@echo "\tcpp-yaml availible at https://github.com/jbeder/yaml-cpp"
	@echo "============================================================================================="
	@echo "\n\n"

