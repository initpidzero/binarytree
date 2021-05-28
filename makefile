INC = .
CFLAGS = -g -I$(INC) -Wall -Wextra
SFLAGS = -g -I$(INC) -Wall -Wextra -static
TARGET = binarytrees binarytrees_parent
all: $(TARGET)
binarytees:
	$(CC) $(CFLAGS) -o $@ $<
clean:
	$(RM) $(TARGET) 
