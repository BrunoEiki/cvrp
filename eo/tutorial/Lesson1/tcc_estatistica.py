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
def get_result(current_dir, file_distance_results):
    data = {}
    with open(f"{current_dir}/final_results/{file_distance_results}", "r") as stream:
        for line in stream:
            line = line.strip()
            if not (is_float(line)):
                instance_name = line
                # print(instance_name)
                data[instance_name] = []
            else:
                data[instance_name].append(float(line))
    return data


if __name__ =="__main__":
    xover_names = [
        # "greedy",
        # "cycle",
        # "pm",
        # "precedence",
        "order" 
    ]

    if len(sys.argv) > 1:
        file_distance_results = sys.argv[1]
        print("\n")
        print("=============================================================")
        print(f"================= {file_distance_results} =================\n")
        current_dir = pathlib.Path(__file__).parent.resolve()

        # for xover in xover_names:
        data = get_result(current_dir, file_distance_results)
        print("MEAN")
        print("MIN")
        print("STDEV")

        for i in data.items():
            print(f"=== {i[0]} ===")
            print(mean(i[1]))
            print(min(i[1]))
            print(stdev(i[1]))

    else:
        print("MISSING ARG PARAMETER!")
