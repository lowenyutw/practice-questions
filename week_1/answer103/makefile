output:file-1.o file-2.o
	cc -o output file-1.c file-2.c
file-1.o:file-1.c
	cc -c file-1.c
file-2.o:file-2.c
	cc -c file-2.c
clean:
	rm -f file-1.o file-2.o output
