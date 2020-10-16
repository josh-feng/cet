# make shared lib
include ../makefile.include

###########################################################################
TARGET = cetcore

clean:
	@-rm -f *.o 2> /dev/null
	@-rm -f  $(TARGET).symbols $(TARGET).so 2> /dev/null

build: $(OBJS) $(CPPOBJS)
	@-$(CXX) -shared -o $(TARGET).so $(OBJS) $(CPPOBJS) $(LIBDIR) $(LDFLAGS) $(LIBS)

symbols: build
	@objdump -T $(TARGET).so > $(TARGET).symbols

# gcc -shared -fPIC library.c -I/usr/include/lua5.2 -o libname.so
