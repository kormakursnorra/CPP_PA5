CXX = g++  
CXXFLAGS = -std=c++17 -Wall
LDFLAGS = -lncurses                                                                              
                                                                                                   
SRC = src/main.cpp src/maze.cpp src/renderer.cpp src/player.cpp                                              
TARGET = maze                                                                                    
                  
all:                                                                                             
	$(CXX) $(CXXFLAGS) $(SRC) -o $(TARGET) $(LDFLAGS)