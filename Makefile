CXX						:=	g++
CXXFLAGS	:=	-std=c++17	-g	-Isrc	-Wall	-Werror	-Wextra	-fsanitize=address	-MMD	-MP
LDFLAGS		:=	-lncurses

SRC_DIR			:=	src
BIN_DIR			:=	bin
BUILD_DIR	:=	build

TARGET	:=	$(BIN_DIR)/main

# SOURCES := $(shell find $(SRC_DIR) -name '*.cpp')
SOURCES :=	$(shell find $(SRC_DIR) -type f -name '*.cpp' -not \( -name 'maze_k.cpp' \))

OBJECTS	:=	$(patsubst $(SRC_DIR)/%.cpp, $(BUILD_DIR)/%.o, $(SOURCES))

DEPS	:=	$(OBJECTS:.o=.d)

all:	$(TARGET)

$(TARGET):	$(OBJECTS)
	@mkdir	-p	$(BIN_DIR)
	$(CXX)	$(CXXFLAGS)	$(LDFLAGS)	$^	-o	$@
	@echo	"Built	target:	$@"

$(BUILD_DIR)/%.o:	$(SRC_DIR)/%.cpp
	@mkdir	-p	$(dir $@)
	$(CXX)	$(CXXFLAGS)	-c	$<	-o	$@

clean:
	rm	-rf	$(BUILD_DIR)	$(BIN_DIR)
	@echo	"Clean complete"

run:	$(TARGET)
	./$(TARGET)	$(ARGS)

log:
	$(MAKE)	all	2>&1	|	tee	build.log

.PHONY:	all	clean	run	log

-include	$(DEPS)
