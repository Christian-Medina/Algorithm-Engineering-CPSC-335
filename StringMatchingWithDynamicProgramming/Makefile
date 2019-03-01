
all: project3 test

test: project3_test 
	./project3_test

project3_test: project3.hh rubrictest.hh project3_test.cc
	g++ -std=c++11 project3_test.cc -o project3_test

project3: project3.hh timer.hh project3_main.cc
	g++ -std=c++11 project3_main.cc -o experiment

clean:
	rm -f project3 project3_test
