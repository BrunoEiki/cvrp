import sys

import matplotlib.pyplot as plt

# Leitura dos dados do primeiro arquivo

data = []
with open(sys.argv[1], "r") as stream:
    for line in stream:
        string_list = line.split(",")
        data.append([float(element)
                    for element in string_list if element.strip()])

# print(data)

# Criando o gráfico
plt.plot(data[0], label='Execução 1')
plt.plot(data[1], label='Execução 2')
plt.plot(data[2], label='Execução 3')
plt.plot(data[3], label='Execução 4')
plt.plot(data[4], label='Execução 5')
plt.plot(data[5], label='Execução 6')
plt.plot(data[6], label='Execução 7')
plt.plot(data[7], label='Execução 8')
plt.plot(data[8], label='Execução 9')
plt.plot(data[9], label='Execução 10')
plt.plot(data[10], label='Execução 11')
plt.plot(data[11], label='Execução 12')
plt.plot(data[12], label='Execução 13')
plt.plot(data[13], label='Execução 14')
plt.plot(data[14], label='Execução 15')
plt.plot(data[15], label='Execução 16')
plt.plot(data[16], label='Execução 17')
plt.plot(data[17], label='Execução 18')
plt.plot(data[18], label='Execução 19')
plt.plot(data[19], label='Execução 20')
plt.plot(data[20], label='Execução 21')
plt.plot(data[21], label='Execução 22')
plt.plot(data[22], label='Execução 23')
plt.plot(data[23], label='Execução 24')
plt.plot(data[24], label='Execução 25')
plt.plot(data[25], label='Execução 26')
plt.plot(data[26], label='Execução 27')
plt.plot(data[27], label='Execução 28')
plt.plot(data[28], label='Execução 29')
plt.plot(data[29], label='Execução 30')

# Adicionando rótulos e título
plt.xlabel('Gerações')
plt.ylabel('Distância (Km)')
plt.title(f'Gráfico de Linhas - {sys.argv[1]}')

# Adicionando uma legenda
plt.legend()

# Exibindo o gráfico
plt.show()
