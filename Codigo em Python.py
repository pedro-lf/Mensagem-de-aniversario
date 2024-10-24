import random

# Abrir o arquivo
def upload_file(filename):
    filename = 'Lista de causas de morte (PT-BR).txt'  
    with open(filename, 'r') as file:
        items = [line.strip() for line in file]
    return items

# Function to pick random integers between 1 and N without repeating
def escolher_aleatoriamente(items):
    n = len(items)
    indices = random.sample(range(n), n)
    string_final = ""

    for indice in indices:
        item = items[indice]
        if len(string_final + item + " ") > 350:  # Verificar se atingiu um tamanho bom para a mensagem
            break
        string_final += item + " " 

    return string_final.strip()

# MAIN
def main(filename):
    items = upload_file(filename)
    
    if len(items) == 0:
        print("The file is empty.")
        return
    
    result = escolher_aleatoriamente(items)
    
    print(result)
