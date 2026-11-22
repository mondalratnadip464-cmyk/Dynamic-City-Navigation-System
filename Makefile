CC = gcc
CFLAGS = -Wall -Wextra -std=c11
SRC = main.c

ifeq ($(OS),Windows_NT)
	TARGET = city_nav.exe
	RUN_CMD = $(TARGET)
	RM = del /Q
else
	TARGET = city_nav
	RUN_CMD = ./$(TARGET)
	RM = rm -f
endif

.PHONY: all run test clean

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) $(SRC) -o $(TARGET)

run: $(TARGET)
	$(RUN_CMD)

test: $(TARGET)
	$(RUN_CMD) < sample_input.txt

clean:
	$(RM) $(TARGET)
