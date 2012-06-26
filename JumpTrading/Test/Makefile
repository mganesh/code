
TARGET		:= TestData 
CXX			:= g++
CXXFLAGS	:= -O3 -Wall -W -g -D_REENTRANT

SOURCES 	:= $(wildcard *.cpp)
OBJS 		:= $(SOURCES:.cpp=.o)

all: 		$(TARGET)

$(TARGET): 	$(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS) $(LFLAGS) $(LIBS)

.cpp.o:
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $<

clean:
	$(RM) *.o $(TARGET)
