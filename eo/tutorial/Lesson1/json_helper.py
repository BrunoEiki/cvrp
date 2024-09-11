import argparse
import json
import os
import re

import jsonschema
import jsonschema.exceptions

# Schema JSON
json_schema = {
    "name": {"type": "string"},
    "dimension": {"type": "number"},
    "capacity": {"type": "number"},
    "origin": {"x": {"type": "number"}, "y": {"type": "number"}},
    "deliveries": {
        "type": "array",
        "items": {
            "type": "object",
            "properties": {
                "id": {"type": "string"},
                "point": {"x": {"type": "number"}, "y": {"type": "number"}},
                "size": {"type": "integer"},
            },
        },
    },
    "solution": {"type": "number"},
}


def get_all_file_names(target_path):
    instance_files = []
    solution_files = []
    for filename in os.listdir(target_path):
        if os.path.isfile(os.path.join(target_path, filename)):
            if filename[-3:].endswith("vrp"):
                instance_files.append(filename)
            if filename[-3:].endswith("sol"):
                solution_files.append(filename)

    with open(os.path.join(target_path, "instance_names.txt"), "w") as txt_file:
        for instance in instance_files:
            txt_file.write(instance + "\n")

    return instance_files, solution_files


# Função para extrair números de uma string
def extract_numbers(s):
    return [int(num) for num in re.findall(r"\b\d+\b", s)]


def extract_numbers_float(s):
    return [float(num) for num in re.findall(r"\-?\d+\.?\d*", s)]


def data_extraction_setA(instance_file, solution_file, target_path):
    """
    Ensure that the instance and solution files still hold to the positions
    sought. This method will create a python dictionary equal to the json schema.
    """
    # Dicionário para armazenar os dados extraídos do arquivo .txt
    data = {}

    with open(os.path.join(target_path, instance_file), "r") as txt_file:
        lines = txt_file.readlines()

    # find_second_number = r"\b\d+\s+(\d+)\s+\d+\b"
    # find_third_number = r"\b\d+\s+\d+\s+(\d+)\b"
    find_second_number = r"\b-?\d+\s+(-?\d+)\s+-?\d+\b"
    find_third_number = r"\b-?\d+\s+-?\d+\s+(-?\d+)\b"
    init_coord_section = 7

    # Extração dos dados do arquivo .txt
    data["name"] = lines[0].split(":")[1].strip()
    data["dimension"] = int(lines[3].split(":")[1].strip()) - 1
    data["capacity"] = int(lines[5].split(":")[1].strip())



    origin_x = float(re.findall(find_second_number, lines[init_coord_section])[0])
    origin_y = float(re.findall(find_third_number, lines[init_coord_section])[0])
    data["origin"] = {"x": origin_x, "y": origin_y}

    # Extração das coordenadas dos pontos
    init_coord_section += 1
    end_coord_section = init_coord_section + data["dimension"]
    coordinates = [
        extract_numbers(line) for line in lines[init_coord_section:end_coord_section]
    ]
    demands = [extract_numbers(line)[1] for line in lines[end_coord_section + 2 : -4]]

    delivery_data = []

    for coord in coordinates:
        delivery = {
            "id": coord[0] - 2,  # talvez mudar para str()
            "point": {"x": float(coord[1]), "y": float(coord[2])},
            "size": demands[coord[0] - 2],
        }
        delivery_data.append(delivery)

    data["deliveries"] = delivery_data

    with open(os.path.join(target_path, solution_file), "r") as txt_file:
        lines = txt_file.readlines()

    data["solution"] = extract_numbers(lines[-1])[0]  # Extraindo o custo da solução
    return data


def data_extraction_li2005(instance_file, solution_file, target_path):
    """
    Ensure that the instance and solution files still hold to the positions
    sought. This method will create a python dictionary equal to the json schema.
    """
    # Dicionário para armazenar os dados extraídos do arquivo .txt
    data = {}

    with open(os.path.join(target_path, instance_file), "r") as txt_file:
        lines = txt_file.readlines()

    find_second_number = r"\b\d+\s+(\-?\d+)\s+\d+"
    find_third_number = r"\b\d+\s+\d+\s+(\-?\d+)"

    # Extração dos dados do arquivo .txt
    init_coord_section = 7
    data["name"] = lines[0].split(":")[1].strip()
    data["dimension"] = int(lines[3].split(":")[1].strip()) - 1
    data["capacity"] = int(lines[5].split(":")[1].strip())

    origin_x = float(re.findall(find_second_number, lines[init_coord_section])[0])
    origin_y = float(re.findall(find_third_number, lines[init_coord_section])[0])

    data["origin"] = {"x": origin_x, "y": origin_y}

    # Extração das coordenadas dos pontos
    init_coord_section += 1
    end_coord_section = init_coord_section + data["dimension"]
    coordinates = [
        extract_numbers_float(line)
        for line in lines[init_coord_section:end_coord_section]
    ]
    demands = [extract_numbers(line)[1] for line in lines[end_coord_section + 2 : -4]]

    delivery_data = []

    for coord in coordinates:
        delivery = {
            "id": int(coord[0] - 2),
            "point": {"x": float(coord[1]), "y": float(coord[2])},
            "size": demands[int(coord[0]) - 2],  # ! melhorar depois
        }
        delivery_data.append(delivery)

    data["deliveries"] = delivery_data

    with open(os.path.join(target_path, solution_file), "r") as txt_file:
        lines = txt_file.readlines()

    data["solution"] = extract_numbers_float(lines[-1])[
        0
    ]  # Extraindo o custo da solução
    return data


def validate_json(schema, data):
    try:
        jsonschema.validate(instance=data, schema=schema)
        print("JSON válido conforme o esquema fornecido.")
        return True
    except jsonschema.exceptions.ValidationError as e:
        print(f"Erro de validação JSON: {e}")
        return False


def main_function():
    parser = argparse.ArgumentParser("json_helper")
    parser.add_argument(
        "target_path",
        help="Target's path of the instance files. [Arnold], [Li-2005], [Vrp-Set-A/A], [Vrp-Set-XML100], [XML100]",
        type=str,
    )
    args = parser.parse_args()
    print(args.target_path)

    # Caminho do arquivo .txt
    target_path = os.path.join(
        os.getcwd(), "dataset", args.target_path
    )

    instance_files, solution_files = get_all_file_names(target_path)
    instance_files.sort()
    solution_files.sort()

    for instance_file, solution_file in zip(instance_files, solution_files):
        data = data_extraction_li2005(instance_file, solution_file, target_path)

        # Validando e imprimindo o JSON
        # validate_json(json_schema, json_str)

        with open(
            os.path.join(target_path, instance_file + ".json"), "w", encoding="utf8"
        ) as file:
            # Escreve a string JSON no arquivo
            json.dump(data, file, ensure_ascii=False)


main_function()
