# CC stuff
export CC=gcc
export CFLAGS=-Wall -Werror -std=c99
export LDFLAGS=

# Directories
SRCDIR=src
BINDIR=bin
OBJDIR=obj
FILESDIR=fichiers
TESTDIR=tests

# Files
SRC=$(wildcard $(SRCDIR)/*.c)
OBJ=$(SRC:.c=.o)

EXEC=$(BINDIR)/HexGame

# Rules
all: $(EXEC)

%.o: $(SRCDIR)/%.c
	$(CC) -o $@ -c $< $(CFLAGS)
	
$(EXEC) : $(OBJ)
	$(CC) -o $@ $^ $(LDFLAGS)
	mv $^ $(OBJDIR)/

# Tests is not finished. Gotta wait something to work on
tests: $(OBJ)
	cd $(TESTDIR) && $(MAKE)

# Phony and clean
.PHONY: clean

clean:
	rm -f $(OBJDIR)/*.o 	# Remove all objs
	rm -f $(BINDIR)/*		# Remove all execs
	rm -f $(TESTDIR)/*.o 	# Remove all test objs
