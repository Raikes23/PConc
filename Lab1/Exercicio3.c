#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_WORD_LENGTH 100

// Função para abrir o arquivo
FILE *open_file(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Erro ao abrir o arquivo");
        exit(1);
    }
    return file;
}

// Função para contar o número de palavras no arquivo
int count_total_words(FILE *file) {
    int count = 0;
    char word[MAX_WORD_LENGTH];

    while (fgets(word, sizeof(word), file)) {
        count++;
    }

    // Volta o ponteiro do arquivo para o início
    rewind(file);
    return count;
}

// Função para ler as palavras do arquivo e armazená-las em um array dinâmico
char **read_words(FILE *file, int word_count) {
    char **word_array = malloc(word_count * sizeof(char *));
    if (!word_array) {
        perror("Erro ao alocar memória");
        fclose(file);
        exit(1);
    }

    int index = 0;
    char word[MAX_WORD_LENGTH];

    while (fgets(word, sizeof(word), file)) {
        word[strcspn(word, "\n")] = 0;
        word_array[index] = malloc((strlen(word) + 1) * sizeof(char));
        if (!word_array[index]) {
            perror("Erro ao alocar memória para palavra");
            fclose(file);
            exit(1);
        }
        strcpy(word_array[index], word);
        index++;
    }

    return word_array;
}

// Função para liberar a memória alocada
void free_memory(char **word_array, int word_count) {
    for (int i = 0; i < word_count; i++) {
        free(word_array[i]);
    }
    free(word_array);
}

int main() {
    const char *filename = "/mnt/c/Users/henri/Desktop/PConc/Lab1/lusiadas-words.txt";

    FILE *file = open_file(filename);
    int n_total_words = count_total_words(file);
    char **word_array = read_words(file, n_total_words);
    fclose(file);

    // Passo 1 e 2: Declarar e inicializar o array count_letters com 0
    int count_letters[26] = {0};

    // Passo 3: Iterar pelo array de palavras e atualizar count_letters
    for (int i = 0; i < n_total_words; i++) {
        char first_letter = tolower(word_array[i][0]);
        if (first_letter >= 'a' && first_letter <= 'z') {
            count_letters[first_letter - 'a']++;
        }
    }

    // Passo 4: Imprimir os valores do array count_letters
    for (char letter = 'a'; letter <= 'z'; letter++) {
        printf("Numero de palavras com '%c' = '%d'\n", letter, count_letters[letter - 'a']);
    }

    free_memory(word_array, n_total_words);
    return 0;
}
