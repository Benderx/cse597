CC = g++
CFLAGS  = -g -std=c++17 -Wall -Wno-unused-variable -Wno-unused-value

TARGET = cache_timing

all: $(TARGET)

$(TARGET): $(TARGET).cpp
	$(CC) $(CFLAGS) -o run $(TARGET).cpp

clean:
	$(RM) $(TARGET)