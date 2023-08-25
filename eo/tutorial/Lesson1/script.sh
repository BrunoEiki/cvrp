clear

c++ -std=c++17 -DPACKAGE=\"eo\" -DVERSION=\"0.9.1\" -I. -I../../src -Wall -g -c teste.cpp

c++ -std=c++17 -Wall -g -o teste teste.o ../../../build/lib/libeo.a ../../../build/lib/libeoutils.a -lcurl

./teste > "output.txt"