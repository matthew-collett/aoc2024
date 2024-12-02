CXX = g++

CXXFLAGS = -std=c++98 -Wall -g

TARGET = day1

.PHONY: build run clean list

build:
	$(CXX) $(CXXFLAGS) $(TARGET)/main.cpp -o $(TARGET)/$(TARGET)

run: build
	./$(TARGET)/$(TARGET) < $(TARGET)/input

clean:
	rm -rf day{1..30}/day*

list:
	@echo "Available days"
	@ls -d day*/ | sed 's:/::'

.DEFAULT_GOAL := list