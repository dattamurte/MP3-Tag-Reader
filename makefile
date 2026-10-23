
CC = gcc
CFLAGS = -Wall -Wextra
TARGET = mp3_tag_reader
SOURCES = main.c reader.c editor.c

all:
	$(CC) $(CFLAGS) $(SOURCES) -o $(TARGET)

clean:
	rm -f $(TARGET) *.o
