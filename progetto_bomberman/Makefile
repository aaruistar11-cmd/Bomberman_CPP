# Makefile base per il progetto Bomberman
# Conforme alle richieste standard di compilazione

CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++11 -g -Iinclude
LDFLAGS = -lncurses

# Trova automaticamente tutti i file .cpp e genera gli .o corrispondenti
SRCS = $(wildcard src/*.cpp)
OBJS = $(patsubst src/%.cpp, build/%.o, $(SRCS))

TARGET = bomberman

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(OBJS) -o $(TARGET) $(LDFLAGS)

build/%.o: src/%.cpp | build
	$(CXX) $(CXXFLAGS) -c $< -o $@

build:
	mkdir -p build

clean:
	rm -rf build $(TARGET)

.PHONY: all clean
