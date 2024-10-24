#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_ITEMS 1000  // Máximo de itens na lista
#define MAX_TAM_LINHA 100  // Tamanho máximo da linha
#define MAX_TAM_FINAL 450  // Tamanho máximo da string final.

// Function to upload and read a file
int upload_file(const char* filename, char items[MAX_ITEMS][MAX_TAM_LINHA]) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error opening file.\n");
        return 0;
    }

    int count = 0;
    while (fgets(items[count], MAX_TAM_LINHA, file) && count < MAX_ITEMS) {
        // Remover newline se houver
        size_t len = strlen(items[count]);
        if (len > 0 && items[count][len - 1] == '\n') {
            items[count][len - 1] = '\0';
        }
        count++;
    }

    fclose(file);
    return count;  // Retorna o tanto de itens
}

// Aleatorização dos itens do array
void shuffle(int *array, int n) {
    for (int i = n - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        int temp = array[i];
        array[i] = array[j];
        array[j] = temp;
    }
}

// Escolher itens aleatórios, e montar a string
void pick_random_items(char items[MAX_ITEMS][MAX_TAM_LINHA], int num_items, char *result_string) {
    int indices[MAX_ITEMS];
    for (int i = 0; i < num_items; i++) {
        indices[i] = i;
    }

    // Reembaralha
    shuffle(indices, num_items);

    result_string[0] = '\0';
    int current_length = 0;

    for (int i = 0; i < num_items; i++) {
        int idx = indices[i];
        char *item = items[idx];
        int item_length = strlen(item);

        // Conferir se tamanho máximo é respeitado
        if (current_length + item_length + 1 > MAX_TAM_FINAL) {
            break;
        }

        // Concatenar o item e um espaço
        strcat(result_string, item);
        strcat(result_string, " ");
        current_length += item_length + 1;
    }

    // Remover "trailing space"
    if (current_length > 0 && result_string[current_length - 1] == ' ') {
        result_string[current_length - 1] = '\0';
    }
}

int main() {
    srand(time(0));  // Seed para aleatorização

    char items[MAX_ITEMS][MAX_TAM_LINHA];
    char result_string[MAX_TAM_FINAL];

    const char *filename = "Lista de causas de morte (PT-BR).txt";
    int num_items = upload_file(filename, items);

    if (num_items == 0) {
        printf("Arquivo vazio.\n");
        return 1;
    }

    pick_random_items(items, num_items, result_string);

    printf("%s\n", result_string);

    return 0;
}
