# CC stuff
CC=gcc
CFLAGS=-Wall -Werror -std=c99 -g
LDFLAGS=

# Directories
SRCDIR=src
BINDIR=bin
OBJDIR=obj
FILESDIR=saves
TESTDIR=tests

# Files
SRC=$(wildcard $(SRCDIR)/*.c)
OBJ=$(SRC:.c=.o)

EXEC=$(BINDIR)/HexGame

# Rules
all: $(BINDIR) $(OBJDIR) $(FILESDIR) $(EXEC)

%.o: $(SRCDIR)/%.c
	$(CC) -o $@ -c $< $(CFLAGS)

$(BINDIR):
	@mkdir -p $(BINDIR)
$(OBJDIR):
	@mkdir -p $(OBJDIR)
$(FILESDIR):
	@mkdir -p $(FILESDIR)

$(EXEC) : $(OBJ)
	@$(CC) -o $@ $^ $(LDFLAGS)
	@mv $^ $(OBJDIR)/

tests:
	@(cd $(TESTDIR) && $(MAKE))

# Phony and clean
.PHONY: clean tests all

clean:
	@rm -f $(OBJDIR)/*.o $(SRCDIR)/*.o	# Remove all objs
	@rm -f $(BINDIR)/*					# Remove all execs
	@(cd $(TESTDIR) && $(MAKE) $@)
	@echo "Cleaning done"
