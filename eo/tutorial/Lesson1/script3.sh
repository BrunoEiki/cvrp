#!/bin/bash
clear

instances=(
	 # "A-n32-k5.vrp"
	 # "XML100_1111_01.vrp"
	 "Li-21.vrp"
	 # "X-n1001-k43.vrp"
	 # "tai150a.vrp"
)


c++ -std=c++17 -DPACKAGE=\"eo\" -DVERSION=\"0.9.1\" -I. -I../../src -Wall -g -c academic_cvrp.cpp

c++ -std=c++17 -Wall -g -o academic_cvrp academic_cvrp.o ../../../build/lib/libeo.a ../../../build/lib/libeoutils.a

# [ -f last_generation.txt ] && rm last_generation.txt
# [ -f tempo.txt ] && rm tempo.txt

# for crossover in ${crossovers[@]}; do
	# for instance in ${instances[@]}; do
		# echo "${instance}" >> tempo.txt
		# for i in {1..10}
		# do
			# # { time ./academic_cvrp "${instance}.json"; } 2>&1 | grep real >> tempo.txt
			# # time ./academic_cvrp "${instance}.json"
			# # sed -i "s|.*// CROSSOVER|${crossover}" academic_cvrp.cpp
			# { time ./academic_cvrp "${instance}.json"; "${crossover}" } 2>> tempo.txt
		# done
	# done
# done

crossover=gox

for instance in ${instances[@]}; do
	echo "${instance}" >> tempo_${crossover}.txt 
	echo "${instance}" >> "last_generation_${crossover}.txt" 	
	for i in {1..10}
	do
		{ time ./academic_cvrp "${instance}.json"; } 2>> tempo_${crossover}.txt
	done
done
