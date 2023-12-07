clear

cd /home/bruno/cvrp/eo/tutorial/Lesson1

docker start osrm

sleep 10

c++ -std=c++17 -DPACKAGE=\"eo\" -DVERSION=\"0.9.1\" -I. -I../../src -Wall -g -c teste.cpp

c++ -std=c++17 -Wall -g -o teste teste.o ../../../build/lib/libeo.a ../../../build/lib/libeoutils.a -lcurl

for i in {1..5}
do
	./teste >> "$1.txt" #nome do crossover
done

echo "> DONE $1"