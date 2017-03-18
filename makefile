ROOT_FLAGS = `root-config --cflags`
ROOT_LIBS  = `root-config --libs`
CFLAGS     = -I.
RCXX = $(CFLAGS) $(ROOT_FLAGS) $(ROOT_LIBS) $(LIBS)

INC_PATH = -I/usr/include -Iinc
LIB_PATH = -L/usr/lib -L/usr/local/lib
LIBS     = -lboost_system -lMinuit -lpthread


# compiler flags:
 #    -g    adds debugging information to the executable file
#    -Wall turns on most, but not all, compiler warnings

DBG    = -g -O3 -Wall

CC     = g++ $(DBG) $(LIB_PATH) $(LIBS) $(INC_PATH) -lpthread
MIN_CC = g++ $(DBG) $(INC_PATH) $(CFLAGS) $(ROOT_FLAGS) -std=c++11

BIN_DIR = bin
OBJ_DIR = obj
SRC_DIR = src
INC_DIR = inc

all: Analyze textFileToRootFile FastRotation RawFFT FirstApproxFreqDistrib DeltaFreqDistrib fiberHarpTextFileToRootFile fiberHarpAnalyze

fiberHarpAnalyze: $(SRC_DIR)/fiberHarpAnalyze.cpp
	$(CC) -o $(BIN_DIR)/fiberHarpAnalyze $(SRC_DIR)/fiberHarpAnalyze.cpp $(RCXX)

fiberHarpTextFileToRootFile: $(SRC_DIR)/fiberHarpTextFileToRootFile.cpp
	$(CC) -o $(BIN_DIR)/fiberHarpTextFileToRootFile $(SRC_DIR)/fiberHarpTextFileToRootFile.cpp $(RCXX)

Analyze: $(SRC_DIR)/Analyze.cpp
	$(CC) -o $(BIN_DIR)/Analyze $(SRC_DIR)/Analyze.cpp $(RCXX)

textFileToRootFile: $(SRC_DIR)/textFileToRootFile.cpp
	$(CC) -o $(BIN_DIR)/textFileToRootFile $(SRC_DIR)/textFileToRootFile.cpp $(RCXX)

FastRotation: $(SRC_DIR)/FastRotation.cpp
	$(CC) -o $(BIN_DIR)/FastRotation $(SRC_DIR)/FastRotation.cpp $(RCXX)

RawFFT: $(SRC_DIR)/RawFFT.cpp
	$(CC) -o $(BIN_DIR)/RawFFT $(SRC_DIR)/RawFFT.cpp $(RCXX)

FirstApproxFreqDistrib: $(SRC_DIR)/FirstApproxFreqDistrib.cpp
	$(CC) -o $(BIN_DIR)/FirstApproxFreqDistrib $(SRC_DIR)/FirstApproxFreqDistrib.cpp $(RCXX)

DeltaFreqDistrib: $(SRC_DIR)/DeltaFreqDistrib.cpp
	$(CC) -o $(BIN_DIR)/DeltaFreqDistrib $(SRC_DIR)/DeltaFreqDistrib.cpp $(RCXX)

clean:
	rm -f $(OBJ_DIR)/*.o $(BIN_DIR)/*
