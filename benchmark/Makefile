NAME  = producer_consumer
CXSRC = $(wildcard src/*.cpp)
CSRC  = $(wildcard src/*.c)

TARGET = benchmark_$(NAME)

LIB     = lib$(NAME).so
LIBDEP  = $(LIBDIR)/$(BUILD)/$(LIB)


OBJ := $(patsubst %.cpp,$(BUILD)/%.o,$(CXSRC)) $(patsubst %.c,$(BUILD)/%.o,$(CSRC))

LIBRARIES = -lpthread -lbenchmark -lbenchmark_main
UNAME := $(shell uname -s)

ifeq ($(UNAME), Darwin)
CC       = cc
CXX      = c++
CFLAGS   = -std=c11 -Wall -fsanitize=address -I$(LIBDIR)/src
CXXFLAGS = -std=c++17 -Wall -fsanitize=address -I$(LIBDIR)/src
else
CC     = gcc
CXX    = g++
CFLAGS   = -std=c11 -Wall -fsanitize=address -I$(LIBDIR)/src
CXXFLAGS = -std=c++17 -Wall -fsanitize=address -I$(LIBDIR)/src
endif

all:  build $(TARGET) $(OBJ) $(LIBDEP)

$(TARGET) : build $(OBJ) $(LIBDEP)
	$(CXX) $(CXXFLAGS) $(OBJ) -o $(BUILD)/$(TARGET) -L$(LIBDIR)/$(BUILD) -l$(NAME) $(LIBRARIES) -Wl,-rpath,$(LIBDIR)/build

build:
	mkdir -p "$(BUILD)/src"

$(LIBDEP) :
	cd $(LIBDIR) && make

run: $(TARGET)
	./$(BUILD)/$(TARGET)

$(BUILD)/%.o: %.c
	$(CC) -c $(CFLAGS) $< -o $@

$(BUILD)/%.o: %.cpp
	$(CXX) -c $(CXXFLAGS) -c $< -o $@

clean:
	rm -rf $(BUILD)
