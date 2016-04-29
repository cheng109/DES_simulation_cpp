appname := desAnalysis

CXX := g++
INC := -I/Users/juncheng/work/cfitsio
CXXFLAGS := -Wall -O3 -g -std=c++11 $(INC)
LDFLAGS := -L. -L/Users/juncheng/work/cfitsio
LDLIBS := -lcfitsio 
#-lgsl -lgslcblas -lm -lfortranstuff

SRCS := main.cpp Image.cpp commons.cpp Star.cpp
OBJS  := $(patsubst %.cpp, %.o, $(SRCS))

all: $(appname)
	./$(appname)

$(appname): $(OBJS)
	$(CXX) $(LDFLAGS) -o $(appname) $(OBJS) $(LDLIBS)

#depend: .depend

.depend: $(SRCS)
	rm -f ./.depend
	$(CXX) $(CXXFLAGS) -MM $^>>./.depend;

clean:
	rm -f $(OBJS)

dist-clean: clean
	rm -f *~ .depend

include .depend