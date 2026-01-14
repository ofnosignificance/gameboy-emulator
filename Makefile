NAME := gameboy
CXX := g++
CXXFLAGS := -Wall -Wextra -pedantic -std=c++17 -O3

LDFLAGS := -lSDL2 -lSDL2_ttf

DST_DIR := dst
SRC_DIR := src

OBJS := $(DST_DIR)/Processor.cpp.o \
		$(DST_DIR)/SDL_stuff.cpp.o \
        $(DST_DIR)/Main.cpp.o \
        $(DST_DIR)/Memory.cpp.o \
		$(DST_DIR)/Debugger.cpp.o

all: $(DST_DIR) $(NAME)

$(DST_DIR):
	mkdir -p $(DST_DIR)

$(NAME): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

$(DST_DIR)/%.cpp.o: $(SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

clean:
	rm -rf $(DST_DIR)
	rm -f $(NAME)

.PHONY: clean all
