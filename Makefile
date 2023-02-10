CXX=g++
OPT=-O2
HEAD_DIR=header/
SRC_DIR=src/
CXXFLAGS=-Wall -Wextra -g -std=c++20 $(OPT) -I$(HEAD_DIR)

APPNAME=app.exe

SRC := $(wildcard $(SRC_DIR)*.cpp)
OBJ := $(SRC:.cpp=.o)
HDR := $(wildcard $(HEAD_DIR)*.h)

all: $(APPNAME)

$(APPNAME): $(OBJ)
	$(CXX) $(OBJ) -o $@

$(notdir $(OBJ)): $(SRC) $(HDR)
	$(CXX) $(CXXFLAGS) -c $(SRC)

.PHONY : clean

clean:
	-rm $(OBJ) $(APPNAME)