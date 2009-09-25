GCC=gcc
MAKE=make
TARGET=elfparser

.PHONY : all test run clean 

all:
	$(MAKE) $(TARGET)
	$(MAKE) test

$(TARGET): $(TARGET).c
	$(GCC) $< -o $@

run:
	./$(TARGET)

test:
	@echo "start to test..."
	@echo "do something..."

clean:
	rm -rf *.o $(TARGET)
