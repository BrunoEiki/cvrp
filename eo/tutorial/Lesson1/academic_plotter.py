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
def get_result(current_dir, data_file):
    data = {}
    with open(f"{current_dir}/cumulative_results/{data_file}", "r") as stream:
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
        "pm",
        "cycle",
        "order",
        "precedence",
        "gox"
    ]
    
    current_dir = pathlib.Path(__file__).parent.resolve()
    data_file = sys.argv[1]

    # for xover in xover_names:
    data = get_result(current_dir, data_file)
    # print("MEAN")
    # for i in data.values():
        # print(stdev(i))


    # # Criando o gráfico
    plt.plot(data[xover_names[0]], label="gx")
    plt.plot(data[xover_names[1]], label="pm")
    plt.plot(data[xover_names[2]], label="cycle")
    plt.plot(data[xover_names[3]], label="order")
    plt.plot(data[xover_names[4]], label="precedencee")
    plt.plot(data[xover_names[5]], label="gox")



    # # Adicionando rótulos e título
    plt.xlabel("Gerações")
    plt.ylabel("Distância")
    plt.title(f"Gráfico de Linhas - {sys.argv[1]}")

    # # Adicionando uma legenda
    plt.legend()

    # # Exibindo o gráfico
    plt.show()
