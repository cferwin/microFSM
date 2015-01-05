# Compiler flags
CC = gcc
CFLAGS = -Wall -Werror -I$(IDIR)

# Directories
ODIR = obj
IDIR = src
CDIR = src
TEST_DIR = tests

# Object files
_OBJ = microFSM.o
OBJ  = $(patsubst %,$(ODIR)/%,$(_OBJ))

# Output files (binaries)
TEST_OUT = $(TEST_DIR)/tests.exe
OUT			 = libmicrofsm.a


# Build object files
$(ODIR)/%.o: $(CDIR)/%.c $(DEPS)
	$(CC) -c $(CFLAGS) -o $@ $<

# Build the binary file
$(OUT): $(OBJ) $(DEPS)
	ar rcs $(OUT) $(OBJ)


.PHONY: clean test

clean:
	rm -f $(ODIR)/*.o $(TEST_OUT) $(OUT)

# Build and run all tests.
test:
	$(CC) -c $(CFLAGS) -o $(TEST_DIR)/main.o -c $(TEST_DIR)/main.c
	$(CC) -o $(TEST_OUT) $(TEST_DIR)/main.o -L. -lmicrofsm
	$(TEST_OUT)
