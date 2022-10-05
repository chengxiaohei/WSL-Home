PROJECTDIR = $(HOME)/Downloads/sensor

INC=-I$(PROJECTDIR)/include
LIB= -L$(PROJECTDIR)/lib -lcurl
BINDIR=$(PROJECTDIR)/bin
SRCDIR=$(PROJECTDIR)/src
LIBDIR=$(PROJECTDIR)/lib

.PHONY = all clean
VPATH = include:src:lib:bin

subObjects = Measurement.o Oil_Level.o Temperature.o Vibration.o Status.o Reporter.o
mainObjects = device1.o device2.o

all : device1 device2
	-@mv *.o lib
	-@mv $^ $(BINDIR)

$(mainObjects:.o=): % : %.o $(subObjects)
	g++ $(INC) $^ $(LIB) -o $@

$(mainObjects): %.o : main.cpp
	g++ -c $(INC) $^ $(LIB) -D$* -o $@

$(subObjects): %.o : %.cpp include/%.h
	g++ -c $(INC) $< $(LIB) -o $@

clean:
	@rm -f */*.o
	@rm -f $(BINDIR)/device1
	@rm -f $(BINDIR)/device2