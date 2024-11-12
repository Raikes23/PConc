#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_WORD_LENGTH 100

int compare_words(const void *a, const void *b) {
    // Função de comparação para ordenar as palavras alfabeticamente (ignora case).
    char *word1 = *(char **)a;
    char *word2 = *(char **)b;
    return strcasecmp(word1, word2);
}

int main() {
    FILE *file;
    file = fopen("C:\\Users\\henri\\Desktop\\PConc\\Lab1\\lusiadas-words.txt", "r");

    if (file == NULL){
        printf("O ficheiro nao existe");
        exit(0);
    }

    if (!file) {
        perror("Erro ao abrir o arquivo");
        return 1;
    }

    // Alocação inicial do array de strings
    int capacity = 100;
    char **word_array = malloc(capacity * sizeof(char *));
    if (!word_array) {
        perror("Erro ao alocar memória");
        fclose(file);
        return 1;
    }

    int count = 0;
    char word[MAX_WORD_LENGTH];

    // Lê cada palavra do arquivo e armazena no array
    while (fgets(word, sizeof(word), file)) {
        // Remove o newline do final da palavra
        word[strcspn(word, "\n")] = 0;

        // Realoca memória se necessário
        if (count >= capacity) {
            capacity *= 2;
            word_array = realloc(word_array, capacity * sizeof(char *));
            if (!word_array) {
                perror("Erro ao realocar memória");
                fclose(file);
                return 1;
            }
        }

        // Aloca memória para a palavra e a copia para o array
        word_array[count] = malloc((strlen(word) + 1) * sizeof(char));
        if (!word_array[count]) {
            perror("Erro ao alocar memória para palavra");
            fclose(file);
            return 1;
        }
        strcpy(word_array[count], word);
        count++;
    }
    fclose(file);

    // Ordena o array de palavras alfabeticamente (ignorando maiúsculas/minúsculas)
    qsort(word_array, count, sizeof(char *), compare_words);

    // Imprime as palavras em ordem alfabética, agrupadas por letra inicial
    char current_letter = 'a';
    printf("Palavras iniciadas com '%c' ou '%c':\n", toupper(current_letter), current_letter);

    for (int i = 0; i < count; i++) {
        // Verifica se é uma nova letra inicial
        if (tolower(word_array[i][0]) != current_letter) {
            current_letter = tolower(word_array[i][0]);
            printf("\nPalavras iniciadas com '%c' ou '%c':\n", toupper(current_letter), current_letter);
        }
        printf("%s\n", word_array[i]);
    }

    // Imprime a contagem total de palavras
    printf("\nTotal de palavras: %d\n", count);

    // Libera memória alocada
    for (int i = 0; i < count; i++) {
        free(word_array[i]);
    }
    free(word_array);

    return 0;
}
