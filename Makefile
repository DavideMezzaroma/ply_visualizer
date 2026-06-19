CC = gcc
CFLAGS = -Wall -I../dynamic_array
SRC = visualizer.c parser.c ../utilities/dynarr.c
TARGET = visualizer

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) $(SRC) -o $(TARGET) -lraylib -lm

clean:
	rm -f $(TARGET)
