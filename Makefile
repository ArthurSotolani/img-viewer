CC = gcc
CFLAGS = -Wall -Wextra -g
LDFLAGS = -lSDL2
TARGET = iv
SRC = iv.c

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRC) $(LDFLAGS)

clean:
	rm -f $(TARGET)

.PHONY: clean
