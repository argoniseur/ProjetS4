CC=gcc
CFLAGS=-Wall -Werror -std=c99
LDFLAGS=


TEST_SRC=$(wildcard *.c)
TEST_OBJ=$(TEST_SRC:.c=.o)
TST_EXEC=Tests

All: $(TST_EXEC)
	@(./$(TST_EXEC))

%.o: %.c
	@$(CC) -o $@ -c $< $(CFLAGS)

$(TST_EXEC): $(TEST_OBJ)
	@$(CC) -o $@ $^ $(LDFLAGS)

clean:
	@rm -f *.o 				# Remove all test objs
	@rm -f $(TST_EXEC)		# Remove test exec