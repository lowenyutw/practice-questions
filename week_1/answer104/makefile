OBJS = file-1.o file-2.o
CC = cc

%.o: %.c
	$(CC) -c -o $@ $<
output: $(OBJS)
	$(CC) -o $@ $^
clean:
	rm -f $(OBJS) output
