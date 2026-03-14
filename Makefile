CC = gcc
CFLAGS = -Wall -I../dynamic_array
SRC = ply_visualizer.c ply_parser.c ../dynamic_array/dynarr.c
TARGET = ply_visualizer

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) $(SRC) -o $(TARGET) -lraylib -lm

clean:
	rm -f $(TARGET)
