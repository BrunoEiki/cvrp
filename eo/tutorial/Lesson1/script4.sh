#!/bin/bash
clear

instances=(
	 # "A-n32-k5.vrp"
	 # "XML100_1111_01.vrp"
	 # "Li-21.vrp"
	 "X-n1001-k43.vrp"
	 # "tai150a.vrp"
)


c++ -std=c++17 -DPACKAGE=\"eo\" -DVERSION=\"0.9.1\" -I. -I../../src -Wall -g -c academic_cvrp.cpp

c++ -std=c++17 -Wall -g -o academic_cvrp academic_cvrp.o ../../../build/lib/libeo.a ../../../build/lib/libeoutils.a

crossover=gox

for instance in ${instances[@]}; do
	# o argumento eh o nome do crossover
	echo "${crossover}" >> "./cumulative_results/all_generations_XML100_1111_01.txt"
	./academic_cvrp "$1.vrp.json"
done
