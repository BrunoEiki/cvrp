#!/bin/bash
clear

declare -a instances=("XML100_1111_01.vrp")

arquivo="instance_names.txt"

# Lê cada linha do arquivo e a armazena no array
# while IFS= read -r linha; do
    # linhas+=("$linha")
# done < "$arquivo"

c++ -std=c++17 -DPACKAGE=\"eo\" -DVERSION=\"0.9.1\" -I. -I../../src -Wall -g -c academic_cvrp.cpp

c++ -std=c++17 -Wall -g -o academic_cvrp academic_cvrp.o ../../../build/lib/libeo.a ../../../build/lib/libeoutils.a
for i in {1..30}
do
	time ./academic_cvrp "X-n1001-k43.vrp.json"
done
