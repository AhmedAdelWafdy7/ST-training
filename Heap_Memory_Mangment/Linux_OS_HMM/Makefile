
# Define color escape codes
RED=$(shell echo  "\033[31m")
GREEN=$(shell echo  "\033[32m")
YELLOW=$(shell echo  "\033[33m")
RESET=$(shell echo  "\033[0m")

CFLAGS=-O2 -nostdlib -g -nodefaultlibs -fno-builtin -fPIC -Wall

HEADERPATH=-I./


LONG_SENTENCE="${GREEN}Welcome To WAFDUNIX${RED} HMM"


all: clean compile

	@echo "${LONG_SENTENCE}"
	@echo "${YELLOW}Compiling the library${RESET}"
	@echo "${GREEN}Done${RESET}"
	@echo "${YELLOW}Please run 'make test' to test the library${RESET}"



clean:
	
	rm -f ./*.o
	rm -f ./*.a
	rm -f ./*.so


compile:
	
	gcc $(HEADERPATH) $(CFLAGS) -static -c basic_mangement.c
	ar -rcv liballoc.a *.o
	gcc $(HEADERPATH) $(CFLAGS) -shared basic_mangement.c -o liballoc.so

test:
	export LD_PRELOAD=$(PWD)/liballoc.so
	@echo "${YELLOW}Running test${RESET}"
	@echo "now you can run your programs to test the library"
	@echo "Example: ./test"
	@echo "test gdb , vim , nano , ls , cat , echo , etc"
	


linux:
	gcc $(HEADERPATH) $(CFLAGS) -static -c basic_mangement.c
	ar -rcv liballoc.a *.o
	gcc $(HEADERPATH) $(CFLAGS) -shared basic_mangement.c -o liballoc.so

