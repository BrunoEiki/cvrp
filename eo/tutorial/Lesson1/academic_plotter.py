import sys

import matplotlib.pyplot as plt
from statistics import mean, stdev
import pathlib


def is_float(value):
    try:
        float(value)
        return True
    except ValueError:
        return False


# Leitura dos dados do primeiro arquivo
def get_result(current_dir):
    data = {}
    with open(f"{current_dir}/table_results_Li.txt", "r") as stream:
        for line in stream:
            line = line.strip()
            if not (is_float(line)):
                instance_name = line
                print(instance_name)
                data[instance_name] = []
            else:
                data[instance_name].append(float(line))
    return data

if __name__ =="__main__":
    xover_names = [
        "greedy",
        "cycle",
        "pm",
        "precedence",
        "order" 
    ]
    
    current_dir = pathlib.Path(__file__).parent.resolve()

    # for xover in xover_names:
    data = get_result(current_dir)
    print(data.keys())
    for i in data.values():
        print(mean(i))


# # Criando o gráfico
# plt.plot(data[0], label="Execução 1")
# plt.plot(data[1], label="Execução 2")


# # Adicionando rótulos e título
# plt.xlabel("Gerações")
# plt.ylabel("Distância (Km)")
# plt.title(f"Gráfico de Linhas - {sys.argv[1]}")

# # Adicionando uma legenda
# plt.legend()

# # Exibindo o gráfico
# plt.show()
