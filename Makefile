# Compiler and flags
CC = gcc
CFLAGS = -Wall -std=c11

#Input file
INPUT = input.txt
OUTPUT = output.txt
REF = ref.txt
# Source file
SRCS = a1.c
# Output
TARGET = a1.out

# Default target
all: $(TARGET)

# Rule to build the executable
$(TARGET): $(SRCS)
	$(CC) $(CFLAGS) $(SRCS) -o $(TARGET)


convert_input: $(INPUT)
	dos2unix $(INPUT)

convert_output: $(OUTPUT)
	dos2unix $(OUTPUT)

check: $(OUTPUT) $(REF)
	@diff -q $(OUTPUT) $(REF) > /dev/null; \
	if [ $$? -eq 0 ]; then \
		echo "Pass"; \
	else \
		echo "Fail"; \
	fi

# Rule to run the program
run: $(TARGET)
	./$(TARGET) $(INPUT) $(OUTPUT)

# Rule to clean generated files
clean:
	rm -f $(TARGET)
