ROOT_DIR := $(dir $(abspath $(lastword $(MAKEFILE_LIST))))

debug:
	mkdir -pv bin/Debug
	mkdir -pv obj/Debug
	g++ -Wall -lboost_system -pthread -lboost_filesystem -std=c++11 -m32 -g -lboost_system -lboost_filesystem -lboost_regex -std=c++11 -m64 -pthread -Iinclude -c ${ROOT_DIR}main.cpp -o obj/Debug/main.o
	g++ -Wall -lboost_system -pthread -lboost_filesystem -std=c++11 -m32 -g -lboost_system -lboost_filesystem -lboost_regex -std=c++11 -m64 -pthread -Iinclude -c ${ROOT_DIR}src/Spooky2DatabaseAnalyser.cpp -o obj/Debug/src/Spooky2DatabaseAnalyser.o
	g++  -o bin/Debug/BoostFileSystem obj/Debug/main.o obj/Debug/src/Spooky2DatabaseAnalyser.o  -lboost_system -pthread -lboost_filesystem -m32 -lboost_system -lboost_filesystem -lboost_regex -m64 -pthread

release:
	mkdir -pv bin/Release
	mkdir -pv obj/Release
	g++ -Wall -m32 -lboost_system -lboost_filesystem -O2 -m32 -lboost_system -lboost_filesystem -lboost_regex -std=c++11 -m64 -pthread -Iinclude -c ${ROOT_DIR}main.cpp -o obj/Release/main.o
	g++ -Wall -m32 -lboost_system -lboost_filesystem -O2 -m32 -lboost_system -lboost_filesystem -lboost_regex -std=c++11 -m64 -pthread -Iinclude -c ${ROOT_DIR}src/Spooky2DatabaseAnalyser.cpp -o obj/Release/src/Spooky2DatabaseAnalyser.o
	g++  -o bin/Release/BoostFileSystem obj/Release/main.o obj/Release/src/Spooky2DatabaseAnalyser.o  -m32 -lboost_system -lboost_filesystem -s -m32 -lboost_system -lboost_filesystem -lboost_regex -m64 -pthread
