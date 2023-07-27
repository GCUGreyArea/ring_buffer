
NAME  = producer_consumer

CXSRC = $(shell find src -name *.cpp)
CSRC  = $(shell find src -name *.c)
UNAME = $(shell uname)

OBJ := $(patsubst %.cpp,$(BUILD)/%.o,$(CXSRC)) $(patsubst %.c,$(BUILD)/%.o,$(CSRC))

BUILD = build
LIBDIR = .

BASIC := $(BUILD)/src/Basic
NUMBERS := $(BUILD)/src/Numbers

TARGET  = lib$(NAME).so
LIBDIR  =  .
INSTALL = /usr/local/lib
HDRINST = /usr/local/include

OBJ   := $(patsubst %.cpp,$(BUILD)/%.o,$(CXSRC)) $(patsubst %.c,$(BUILD)/%.o,$(CSRC))
UNAME := $(shell uname -s)

CFLAGS += -fPIC
CXXFLAGS += -fPIC

$(TARGET) : build $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -lm -shared -o $(BUILD)/$(TARGET)

all: $(TARGET)

$(TARGET) : build $(OBJ)

build :
	mkdir -p $(BASIC)
	mkdir -p $(NUMBERS)

$(BUILD)/%.o: %.c
	$(CC) -c $(CFLAGS) $< -o $@

$(BUILD)/%.o: %.cpp
	$(CXX) -c $(CXXFLAGS) $< -o $@

clean:
	rm -rf $(BUILD)
