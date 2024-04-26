import numpy
import pandas as pd
from matplotlib.plt import plt

def is_number(s):
    try:
        float(s)
        return True
    except ValueError:
        return False


with open("table_results.txt", "r") as data:
    dicionario = {}
    for line in data:
        if is_number(line):
            line
        else:


# Leitura dos dados do primeiro arquivo
def get_result(current_dir, xover):
    data = {}
    with open(f"{current_dir}/{xover}_result_only.txt", "r") as stream:
        for line in stream:
            line = line.strip()
            if not (is_float(line)):
                instance_name = line
                data[instance_name] = []
            else:
                data[instance_name].append(float(line))
    return data

'''
executar 30 vezes

mostrar valores intermediarios das gerações

gen_max = 100
pop_size = 80

media
desvio padrao
pior resultado
melhor resultado

grafico de convergencia
'''