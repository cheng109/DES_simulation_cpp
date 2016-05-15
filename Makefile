appname := desAnalysis

CXX := g++
INC := -I/Users/cheng109/toberemoved/phosim/phosim_core/source/cfitsio
CXXFLAGS := -Wall -O3 -g -std=c++11 $(INC)
LDFLAGS := -L. -L/Users/cheng109/toberemoved/phosim/phosim_core/source/cfitsio
LDLIBS := -lcfitsio 
#-lgsl -lgslcblas -lm -lfortranstuff

SRCS := main.cpp Image.cpp commons.cpp Star.cpp des_catalogGenerate.cpp
OBJS  := $(patsubst %.cpp, %.o, $(SRCS))

all: $(appname)
	./$(appname)
	@#valgrind --tool=memcheck --leak-check=full --verbose --log-file=memcheck.log --track-origins=yes ./$(appname)

$(appname): $(OBJS)
	$(CXX) $(LDFLAGS) -o $(appname) $(OBJS) $(LDLIBS)

#depend: .depend

.depend: $(SRCS)
	rm -f ./.depend
	$(CXX) $(CXXFLAGS) -MM $^>>./.depend;

clean:
	rm -f $(OBJS)
	rm -f $(appname)

dist-clean: clean
	rm -f *~ .depend

plot: 
	python plotDES.py

include .depend