rm -rf build && mkdir build && cd build
g++ -o main.o ../main.cc ../test.cc
./main.o
cd .. && rm -rf build

