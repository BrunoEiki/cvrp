clear

# cd /home/bruno/cvrp/eo/tutorial/Lesson1

docker start osrm

c++ -std=c++17 -DPACKAGE=\"eo\" -DVERSION=\"0.9.1\" -I. -I../../src -Wall -g -c academic_cvrp.cpp

c++ -std=c++17 -Wall -g -o academic_cvrp academic_cvrp.o ../../../build/lib/libeo.a ../../../build/lib/libeoutils.a -lcurl

instance=cvrp-2-rj-17.json

# for i in {1..5}
# do
echo "$1" >> "academic_${instance}.txt"
./academic_cvrp #nome do crossover
# done

echo "> DONE $1"
