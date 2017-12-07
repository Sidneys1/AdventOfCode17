CXX=clang++
CXX_ARGS=-std=c++14 -Wall -Wextra -Werror

SOURCES:=$(shell find . -type f -name *.cpp)
HEADERS:=$(shell find . -type f -name *.hpp)
OUTS:=$(patsubst %.cpp,%.out,$(SOURCES))

.PHONY: all clean tidy format

all:  $(OUTS)
	@echo Done.

%.out: %.cpp
	@$(CXX) $(CXX_ARGS) -o $@ $^
	@echo "\tBuilt $<"

tidy:
	@clang-tidy $(SOURCES) -- $(CXX_ARGS)

format:
	@clang-format -style=file -i $(SOURCES) $(HEADERS)

clean:
	rm ./*/*.out