#CXXFLAGS = -std=c++11 -O2 -g -Wall -fmessage-length=0 -DDEBUG=1 -fopenmp -DOMP=0 -DTWODIM=1
CXXFLAGS = -std=c++11 -Ofast -fopenmp -DOMP=0 -DTWODIM=0

OBJS = BurningTrees.o Screen.o Forest.o

LIBS = -lSDL -lgomp -fopenmp

TARGET = BurningTrees

$(TARGET):	$(OBJS)
	$(CXX) -o $(TARGET) $(OBJS) $(LIBS)

all:	$(TARGET)

clean:
	rm -f $(OBJS) $(TARGET)
