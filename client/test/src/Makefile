current:
	g++ -std=c++11 -o TestKVMultiThreaded.o TestKVMultiThreaded.cpp -lkvstore -lboost_serialization -lpthread -Wno-deprecated

all:
	g++ -std=c++11 TestKVSingleRead.cpp -o TestKVSingleRead.o -lkvstore -lboost_serialization -Wno-deprecated

clean:
	rm *.o *.out
