current:
	g++ -std=c++11 TestKVMultiThreaded.cpp -o TestKVMultiThreaded.o -lkvstore -lboost_serialization -Wno-deprecated

all:
	g++ -std=c++11 TestKVSingleRead.cpp -o TestKVSingleRead.o -lkvstore -lboost_serialization -Wno-deprecated

clean:
	rm *.o *.out
