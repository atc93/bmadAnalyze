ROOT_FLAGS = `root-config --cflags`
ROOT_LIBS  = `root-config --libs`
CFLAGS     = -I.
RCXX = $(CFLAGS) $(ROOT_FLAGS) $(ROOT_LIBS) $(LIBS)

INC_PATH = -I/usr/include -Iinc
LIB_PATH = -L/usr/lib -L/usr/local/lib
LIBS     = -lboost_system -lMinuit -lpthread

OBJECTS = $(patsubst obj/%.cpp, build/%.o, $(wildcard obj/*.cpp))
TARGETS = $(patsubst src/%.cpp,bin/%,$(wildcard src/*.cpp))

# compiler flags:
 #    -g    adds debugging information to the executable file
#    -Wall turns on most, but not all, compiler warnings

DBG    = -g -O3 -Wall

CC     = g++ $(DBG) $(LIB_PATH) $(LIBS) $(INC_PATH) -lpthread
MIN_CC = g++ $(DBG) $(INC_PATH) $(CFLAGS) $(ROOT_FLAGS) -std=c++0x

BIN_DIR = bin
OBJ_DIR = obj
SRC_DIR = src
INC_DIR = inc

all: $(OBJECTS) $(TARGETS)

build/%.o: obj/%.cpp obj/%.hh
	$(CXX)  -c $< -o $@ $(RCXX)

bin/%: src/%.cpp $(OBJECTS)
	$(CXX) -o $@ $+ $(RCXX)

clean:
	rm -f *~ $(TARGETS) $(OBJECTS)

