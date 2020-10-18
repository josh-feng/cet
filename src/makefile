include makefile.include

# /usr/local/lib/lua/5.3/cetcore.so
TARGET = cetcore

build install uninstall:
	@cd core ; $(MAKE) $@
	@cd lib ; $(MAKE) $@
	$(CXX) -shared -o $(TARGET).so */*.o $(LIBDIR) $(LDFLAGS) $(LIBS)

clean :
	@cd core ; $(MAKE) $@
	@cd lib ; $(MAKE) $@
	rm -f  $(TARGET).symbols $(TARGET).so 2> /dev/null

symbols: build
	@objdump -T $(TARGET).so > $(TARGET).symbols

# docs:
#     @cd ../doc;  $(MAKE)

cleanall: clean

backup: clean
