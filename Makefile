ROOT_DIR := $(dir $(abspath $(lastword $(MAKEFILE_LIST))))

debug:
	mkdir -pv bin/Debug
	mkdir -pv obj/Debug
	g++ -Wall -m64 -lboost_system -lboost_filesystem -lboost_regex -std=c++11 -m64 -g -lboost_system -lboost_filesystem -lboost_regex -std=c++11 -m64 -pthread -Iinclude -c ${ROOT_DIR}main.cpp -o obj/Debug/main.o
	g++ -Wall -m64 -lboost_system -lboost_filesystem -lboost_regex -std=c++11 -m64 -g -lboost_system -lboost_filesystem -lboost_regex -std=c++11 -m64 -pthread -Iinclude -c ${ROOT_DIR}src/s2dbanalyser.cpp -o obj/Debug/src/s2dbanalyser.o
	g++ -Wall -m64 -lboost_system -lboost_filesystem -lboost_regex -std=c++11 -m64 -g -lboost_system -lboost_filesystem -lboost_regex -std=c++11 -m64 -pthread -Iinclude -c ${ROOT_DIR}src/Spooky2DatabaseAnalyser.cpp -o obj/Debug/src/Spooky2DatabaseAnalyser.o
	g++  -o bin/Debug/Spooky2DatabaseAnalyser obj/Debug/main.o obj/Debug/src/s2dbanalyser.o obj/Debug/src/Spooky2DatabaseAnalyser.o  -m64 -lboost_system -lboost_filesystem -m64 -lboost_system -lboost_filesystem -lboost_regex -m64 -pthread

release:
	mkdir -pv bin/Release
	mkdir -pv obj/Release
	g++ -Wall -m64 -lboost_system -lboost_filesystem -lboost_regex -O2 -std=c++11 -m32 -lboost_system -lboost_filesystem -lboost_regex -std=c++11 -m64 -pthread -Iinclude -c ${ROOT_DIR}main.cpp -o obj/Release/main.o
	g++ -Wall -m64 -lboost_system -lboost_filesystem -lboost_regex -O2 -std=c++11 -m32 -lboost_system -lboost_filesystem -lboost_regex -std=c++11 -m64 -pthread -Iinclude -c ${ROOT_DIR}src/s2dbanalyser.cpp -o obj/Release/src/s2dbanalyser.o
	g++ -Wall -m64 -lboost_system -lboost_filesystem -lboost_regex -O2 -std=c++11 -m32 -lboost_system -lboost_filesystem -lboost_regex -std=c++11 -m64 -pthread -Iinclude -c ${ROOT_DIR}src/Spooky2DatabaseAnalyser.cpp -o obj/Release/src/Spooky2DatabaseAnalyser.o
	g++  -o bin/Release/Spooky2DatabaseAnalyser obj/Release/main.o obj/Release/src/s2dbanalyser.o obj/Release/src/Spooky2DatabaseAnalyser.o  -m64 -lboost_system -lboost_filesystem -s -m32 -lboost_system -lboost_filesystem -lboost_regex -m64 -pthread

install:
	$(MAKE) release
	cp bin/Release/Spooky2DatabaseAnalyser /usr/bin/s2dbanalyser
