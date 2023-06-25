import os
import sys
from statistics import pvariance

pasta = f'./dados_execucao/{sys.argv[1]}'
resultado = {}

for nome_arquivo in os.listdir(pasta):
    caminho_arquivo = os.path.join(pasta, nome_arquivo)
    with open(caminho_arquivo, 'r') as arquivo:
        valores = [(float(linha) / 1000) for linha in arquivo]
        resultado[nome_arquivo] = pvariance(valores)

for key in sorted(resultado.keys()):
    print(key, '\t', resultado[key])