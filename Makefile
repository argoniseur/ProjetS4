CC = gcc
CC_PARAM = -Wall

SRCDIR = src
BINDIR = bin
OBJDIR = obj
FILESDIR = fichiers

OBJ_HEX = Hex.o
OBJ_PLATEAU = Plateau.o

All : $(OBJ_HEX) $(OBJ_PLATEAU)
	$(CC) -o $(BINDIR)/HexGame $(OBJ_HEX) $(OBJ_PLATEAU)
	mv *.o $(OBJDIR)/

%.o: $(SRCDIR)/%.c
	$(CC) -o $@ -c $< $(CC_PARAM)
	
clean:
	rm -f *.o
	rm -f $(OBJDIR)/*.o
	rm -f $(BINDIR)/*
