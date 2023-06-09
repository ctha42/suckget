CC = gcc
CFLAGS = -O2
LIBS = `pkg-config --cflags --libs libcurl`
LDFLAGS = -lcurl
TARGET = suckget

all: $(TARGET)

$(TARGET): suckget.c
	$(CC) $(CFLAGS) -o $@ $< $(LIBS) $(LDFLAGS)

clean:
	rm -f $(TARGET)
