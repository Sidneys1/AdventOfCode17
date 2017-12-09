CXX = clang++
CXXFLAGS += -std=c++14 -Wall -Wextra -Werror -MD -MP

SRC = $(wildcard ./*/*.cc)
HEADERS = $(wildcard ./*/*.hpp)
OUTS = $(SRC:%.cc=%.out)

.SECONDARY: $(SRC:%.cc=%.o)
.PHONY: clean all tidy format

all: $(OUTS) ;

%.out: %.o ; $(CXX) -o $@ $^

tidy: ; @clang-tidy $(SRC) -- $(CXXFLAGS)

format: ; @clang-format -style=file -i $(SRC) $(HEADERS)

clean: ; rm -f */*.out */*.o

-include $(SRC:%.cc=%.d)