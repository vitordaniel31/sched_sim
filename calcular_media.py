from statistics import mean
import sys
import os

# Verifica se o arquivo foi fornecido como argumento
if len(sys.argv) < 2:
    print("Uso: {} arquivo".format(sys.argv[0]))
    sys.exit(1)

# Verifica se o arquivo existe
if not os.path.isfile(sys.argv[1]):
    print("O arquivo '{}' não existe.".format(sys.argv[1]))
    sys.exit(1)

# Variável para armazenar os valores
valores = []

# Loop para ler cada linha do arquivo
with open(sys.argv[1], 'r') as arquivo:
    for linha in arquivo:
        linha = linha.strip()
        # Verifica se a linha contém um valor numérico
        if linha.replace('.', '', 1).isdigit():
            # Adiciona o valor à soma
            valores.append(float(linha)/1000)

# Verifica se foram encontrados valores numéricos no arquivo
if len(valores) == 0:
    print("Nenhum valor numérico encontrado no arquivo.")
    sys.exit(1)

# Calcula a média
media = mean(valores)

# Exibe a média
print(media)
