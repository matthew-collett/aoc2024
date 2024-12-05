CXX = g++
CXXFLAGS = -std=c++17 -Wall -g
TARGET = day1
DAYS := $(shell ls -d day*/ | sed 's:/::')

.PHONY: all build run clean list

all:
	@for day in $(DAYS); do \
		$(MAKE) TARGET=$$day build run; \
	done

build:
	$(CXX) $(CXXFLAGS) $(TARGET)/main.cpp -o $(TARGET)/$(TARGET)

run: build
	./$(TARGET)/$(TARGET) < $(TARGET)/input.txt

clean:
	rm -rf day{1..30}/day*

list:
	@echo "Available days:"
	@for day in $(DAYS); do \
		echo $$day; \
	done

.DEFAULT_GOAL := all