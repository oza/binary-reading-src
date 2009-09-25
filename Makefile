GCC=gcc
MAKE=make
TARGET=elfparser

.PHONY : all clean

all:
	$(MAKE) elfparser

$(TARGET): $(TARGET).c
	$(GCC) $< -o $@

clean:
	rm -rf *.o $(TARGET)
