obj = main.o foo.o bar.o
dfile := $(obj:.o=.d)

main : $(obj)
	cc -o main $^

#$(obj:.o=.d) : %.d : %.c
#	cc -MM $< > $*.d 

dfile: %.d : %.c
	@set -e; rm -f $@; \
        cc -MM $(CPPFLAGS) $< > $@.$$$$; \
        sed 's,\($*\)\.o[ :]*,\1.o $@ : ,g' < $@.$$$$ > $@; \
        rm -f $@.$$$$

$(obj) : %.o : %.c
	cc -c -o $@ $<

-include *.d

c_file := *.c
wc_file := $(wildcard *.c)



.PHONY : clean print
clean :
	-rm main *.o *.d
print :
	@echo $(obj)
	@echo $(c_file)
	@echo $(wc_file)
	@echo $(VPATH)
	@echo $(.LIBPATTERNS)
