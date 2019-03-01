
all: experiment test

test: project1_test
	./project1_test

project1_test: project1.hh project1_test.cc
	g++ -std=c++11 project1_test.cc -o project1_test

experiment: project1.hh timer.hh experiment.cc
	g++ -std=c++11 experiment.cc -o experiment

clean:
	rm -f project1_test experiment
