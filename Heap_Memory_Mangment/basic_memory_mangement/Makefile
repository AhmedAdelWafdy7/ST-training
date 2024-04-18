CFLAGS=-O2 -nostdlib -nodefaultlibs -fno-builtin -fPIC -Wall
HEADERPATH=-I./


clean:
	rm -f ./*.o
	rm -f ./*.a
	rm -f ./*.so

compile:
	gcc $(HEADERPATH) $(CFLAGS) -static -c basic_mangement.c
	ar -rcv liballoc.a  *.o
	gcc $(HEADERPATH) $(CFLAGS) -shared basic_mangement.c -o liballoc.so


linux:
	gcc $(HEADERPATH) $(CFLAGS) -static -c basic_mangement.c
	ar -rcv liballoc.a  *.o
	gcc $(HEADERPATH) $(CFLAGS) -shared basic_mangement.c -o liballoc.so
