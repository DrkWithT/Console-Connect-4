# makefile
# Originally By: gskapoor @ GitHub 
# Edited By: DrkWithT @ GitHub

# C Compiler
CC := gcc -std=c11
CFLAGS := -Wall -Werror

# Directory
BIN_DIR := ./bin
HDR_DIR := ./headers
SRC_DIR := ./src

# Auto generate needed .o files for each C source file. 
SRCS := $(shell find $(SRC_DIR) -name '*.c')
OBJS := $(patsubst $(SRC_DIR)/%.c,%.o,$(SRCS))

# Executable
EXE := $(BIN_DIR)connect4

# Directives
vpath %.h $(HDR_DIR) # search headers/ for C definition files.

.PHONY: all listfiles clean

all: $(EXE)

# For checking build dependency file names. The auto gen for OBJS may screw up sometimes?
listfiles:
	@echo "Source:\n"
	@echo $(SRCS)
	@echo "Objects:\n"
	@echo $(OBJS)

$(EXE): $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@

%.o: %.c
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f $(EXE) *.o
