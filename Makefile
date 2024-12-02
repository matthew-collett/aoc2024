# Compiler
CXX = g++

# Compiler flags
CXXFLAGS = -std=c++98 -Wall -g

# Default target
TARGET = day1

build:
	$(CXX) $(CXXFLAGS) $(TARGET)/main.cpp -o $(TARGET)/$(TARGET)

run: build
	./$(TARGET)/$(TARGET) < $(TARGET)/input

.PHONY: clean list

clean:
	rm -rf day{1..30}/day*

list:
	@echo "Available days"
	@ls -d day*/ | sed 's:/::'
