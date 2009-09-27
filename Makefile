GCC=gcc
MAKE=make
TARGET=elfparser

TESTBIN=hello
TESTCC=-entry main

.PHONY : all test run clean 

all:
	$(MAKE) $(TARGET)
	$(MAKE) test 

$(TARGET): $(TARGET).c
	$(GCC) $< -o $@

run:
	./$(TARGET)

test: 
	$(MAKE) testbin
	@echo "*** start to test... ***"
	./$(TARGET) $(TESTBIN)
	@echo "*** finished test. ***"

testbin: $(TESTBIN).c
	$(GCC) $< -o $(TESTBIN)

clean:
	rm -rf *.o $(TARGET) $(TESTBIN)
