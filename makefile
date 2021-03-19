INC = .
CFLAGS = -g -I$(INC) -Wall -Wextra
SFLAGS = -g -I$(INC) -Wall -Wextra -static
TARGET = binarytrees 
#OBJS = src/commands.c util/heap.c util/list.c
all: $(TARGET)
ringbuffer: binarytrees.c 
#	$(CC) $(CFLAGS) -o $@ $(OBJS) $<
	$(CC) $(CFLAGS) -o $@ $<
clean:
	$(RM) $(TARGET) 
