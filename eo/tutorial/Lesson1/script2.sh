#!/bin/bash
clear

linhas=()
arquivo="instance_names.txt"

# Lê cada linha do arquivo e a armazena no array
while IFS= read -r linha; do
    linhas+=("$linha")
done < "$arquivo"

c++ -std=c++17 -DPACKAGE=\"eo\" -DVERSION=\"0.9.1\" -I. -I../../src -Wall -g -c academic_cvrp.cpp

c++ -std=c++17 -Wall -g -o academic_cvrp academic_cvrp.o ../../../build/lib/libeo.a ../../../build/lib/libeoutils.a

#for linha in "${linhas[@]}"; do
#    if [ -n "$linha" ] && [ -f "${linha}.json" ]; then
#        ./academic_cvrp "${linha}.json"
#    else
#        echo "Erro: Linha inválida ou arquivo não encontrado para ${linha}"
#    fi
#done

for i in {1..2}
do
	./academic_cvrp >> "academic_result.txt"
done
#echo "> DONE $1"
