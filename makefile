CXX = g++
CXXFLAGS = -Wall

proj3: DNA.o Sequencer.o proj3.cpp
	$(CXX) $(CXXFLAGS) DNA.o Sequencer.o proj3.cpp -o proj3

Sequencer.o: DNA.o Sequencer.cpp Sequencer.h
	$(CXX) $(CXXFLAGS) -c Sequencer.cpp

DNA.o: DNA.cpp DNA.h
	$(CXX) $(CXXFLAGS) -c DNA.cpp

clean:
	rm *.o*
	rm *~ 

run:
	./proj3

run1:
	./proj3 proj3_case1.txt

run2:
	./proj3 proj3_case2.txt

run3:
	./proj3 proj3_case3.txt

run4:
	./proj3 proj3_case4.txt

run5:
	./proj3 proj3_case5.txt

val1:
	valgrind ./proj3 proj3_case1.txt

val2:
	valgrind ./proj3 proj3_case2.txt

val3:
	valgrind ./proj3 proj3_case3.txt

val4:
	valgrind ./proj3 proj3_case4.txt

gdb1:
	gdb ./proj3 proj3_case1.txt

submit:
	cp DNA.h DNA.cpp Sequencer.h Sequencer.cpp proj3.cpp ~/cs202proj/proj3

