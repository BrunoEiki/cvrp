#!/bin/bash
clear

# declare -a instances=("A-n44-k6.vrp" "A-n63-k9.vrp" "A-n60-k9.vrp" "A-n80-k10.vrp" "A-n65-k9.vrp" "A-n64-k9.vrp" "A-n37-k6.vrp" "A-n39-k5.vrp" "A-n32-k5.vrp" "A-n61-k9.vrp" "A-n33-k6.vrp" "A-n48-k7.vrp" "A-n45-k6.vrp" "A-n63-k10.vrp" "A-n37-k5.vrp" "A-n38-k5.vrp" "A-n45-k7.vrp" "A-n62-k8.vrp" "A-n54-k7.vrp" "A-n34-k5.vrp" "A-n46-k7.vrp" "A-n69-k9.vrp" "A-n36-k5.vrp" "A-n39-k6.vrp" "A-n53-k7.vrp" "A-n33-k5.vrp" "A-n55-k9.vrp")
declare -a instances=("A-n32-k5.vrp")

declare -a xover_types=("greedy" "cycle" "pm" "precedence")
arquivo="instance_names.txt"

# Lê cada linha do arquivo e a armazena no array
# while IFS= read -r linha; do
    # linhas+=("$linha")
# done < "$arquivo"

c++ -std=c++17 -DPACKAGE=\"eo\" -DVERSION=\"0.9.1\" -I. -I../../src -Wall -g -c academic_cvrp.cpp

c++ -std=c++17 -Wall -g -o academic_cvrp academic_cvrp.o ../../../build/lib/libeo.a ../../../build/lib/libeoutils.a

for instance in "${instances[@]}"; do
	if [ -n "$instance" ] && [ -f "./dataset/Vrp-Set-A/A/${instance}.json" ]; then
		echo "$instance" >> greedy_academic_result.txt
		echo "$instance" >> greedy_result_only.txt
		for i in {1..2}
		do
			./academic_cvrp "${instance}.json"
		done
	else
		echo "Erro: Linha inválida ou arquivo não encontrado para ${linha}"
	fi
done
#echo "> DONE $1"
