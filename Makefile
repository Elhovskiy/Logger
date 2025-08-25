CXX = g++
CXXFLAGS = -std=c++17 -Wall -fPIC
LDFLAGS = -shared

all: liblogger.so ThreadQueue

# библиотека
liblogger.so: logger.o
	$(CXX) $(LDFLAGS) -o $@ $^

logger.o: logger.cpp logger.h
	$(CXX) $(CXXFLAGS) -c logger.cpp

# основное приложение (часть 2)
ThreadQueue: main.o liblogger.so
	$(CXX) -std=c++17 -Wall -o $@ main.o -L. -llogger -lpthread -Wl,-rpath=.

main.o: main.cpp logger.h
	$(CXX) -std=c++17 -Wall -c main.cpp

clean:
	rm -f *.o *.so ThreadQueue main log.txt

