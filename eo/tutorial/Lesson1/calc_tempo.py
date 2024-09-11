from collections import defaultdict

def calcular_media_real_por_instancia(file_path):
    with open(file_path, 'r') as file:
        real_times = defaultdict(list)
        current_instance = None

        for line in file:
            line = line.strip()
            if line.endswith(".vrp"):
                # Nova instância detectada
                current_instance = line
            elif line.startswith("real"):
                # Extrai o valor de tempo no formato "0mX,XXXs"
                time_str = line.split()[1]
                minutes, seconds = time_str.split('m')
                seconds = seconds.replace('s', '').replace(',', '.')
                total_seconds = float(minutes) * 60 + float(seconds)
                
                if current_instance:
                    real_times[current_instance].append(total_seconds)

        # Calcula e imprime a média para cada instância
        for instance, times in real_times.items():
            if times:
                media = sum(times) / len(times)
                print(f"Média dos tempos reais para {instance}: {media:.3f} segundos")
            else:
                print(f"Nenhum valor 'real' encontrado para {instance}.")

# Exemplo de uso
calcular_media_real_por_instancia('./final_results/tempo_precedence.txt')
