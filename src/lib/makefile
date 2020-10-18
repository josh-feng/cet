# make shared lib
include ../makefile.include

###########################################################################

clean:
	@-rm -f *.o 2> /dev/null

build: $(OBJS) $(CPPOBJS)

# gcc -shared -fPIC library.c -I/usr/include/lua5.2 -o libname.so
