# CC stuff
export CC=gcc
export CFLAGS=-Wall -Werror
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

EXEC=HexGame

# Rules
all: $(EXEC)

$(EXEC) : $(OBJ)
	$(CC) -o $(BINDIR)/$(EXEC) $(LDFLAGS)
	mv *.o $(OBJDIR)/

# Tests is not finished. Gotta wait something to work on
tests: $(OBJ)
	cd $(TESTDIR) && $(MAKE)

%.o: $(SRCDIR)/%.c
	$(CC) -o $@ -c $< $(CFLAGS)

# Phony and clean
.PHONY: clean

clean:
	rm -f *.o 
	rm -f $(OBJDIR)/*.o 	# Remove all objs
	rm -f $(BINDIR)/*		# Remove all execs
	rm -f $(TESTDIR)/*.o 	# Remove all test objs
