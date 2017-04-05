all:
	g++ Queue.cpp beagleController.cpp test.cpp -pthread --std=c++11 -o test
arm:
	arm-linux-gnueabihf-g++ Queue.cpp beagleController.cpp test.cpp -static-libgcc -static-libstdc++ -pthread --std=c++11 -o test_arm
