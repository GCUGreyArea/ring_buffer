NAME	= producer_consumer

TARGET  = test_$(NAME)

PWD = $(shell pwd)

CXXSRC = $(wildcard src/*.cpp)
CSRC   = $(wildcard src/*.c)

LIB     = lib$(NAME).a

CXXOBJ    := $(patsubst %.cpp,$(BUILD)/%.o,$(CXXSRC))
COBJ      := $(patsubst %.c,$(BUILD)/%.o,$(CSRC))


LIBRARIES := -lgtest -lpthread -lglog
UNAME     := $(shell uname -s)

# ifeq ($(UNAME), Darwin)
# CC       = cc
# CXX      = c++
# CFLAGS   = -std=c11 -Wall -g -I$(LIBDIR)/src 
# CXXFLAGS = -std=c++17 -Wall -g -I$(LIBDIR)/src 
# else
# CC     = gcc
# CXX    = g++
# CFLAGS   = -std=c11 -Wall -g -I$(LIBDIR)/src 
# CXXFLAGS = -std=c++17 -Wall -g -I$(LIBDIR)/src 
# endif

LNK = -Wl,-rpath,$(LIB)/build

all: $(TARGET) $(OBJ) $(COBJ) $(LIBDEP)

$(TARGET) : build $(CXXOBJ) $(COBJ)
	$(CXX) $(CXXFLAGS) $(CXXOBJ) $(COBJ) -o $(BUILD)/$(TARGET) -L$(LIBDIR)/$(BUILD) -l$(NAME) $(LIBRARIES) -Wl,-rpath,$(LIBDIR)/$(BUILD)

build:
	mkdir -p "$(BUILD)/src"

$(LIBDEP) :
	cd $(LIBDIR) && make

$(BUILD)/%.o: %.c
	$(CC) -c $(CFLAGS) $< -o $@

$(BUILD)/%.o: %.cpp
	$(CXX) -c $(CXXFLAGS) -c $< -o $@

clean:
	rm -rf $(BUILD)

