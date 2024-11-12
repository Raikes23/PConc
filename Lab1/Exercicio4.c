#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_WORD_LENGTH 100

// Definindo a estrutura word_info para a lista ligada
typedef struct word_info {
    char *word;
    int count;
    struct word_info *next;
} word_info;

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

// Função para encontrar palavras únicas e suas contagens
word_info *find_unique_words(char **word_array, int n_total_words) {
    word_info *head = NULL;

    for (int i = 0; i < n_total_words; i++) {
        char *word = word_array[i];
        for (char *p = word; *p; p++) *p = tolower(*p); // Converte a palavra para minúsculas

        // Verifica se a palavra já está na lista ligada
        word_info *current = head;
        while (current != NULL) {
            if (strcmp(current->word, word) == 0) {
                current->count++;  // Incrementa a contagem se a palavra já existir
                break;
            }
            current = current->next;
        }

        // Se a palavra não estiver na lista, cria um novo nó para ela
        if (current == NULL) {
            word_info *new_node = malloc(sizeof(word_info));
            new_node->word = malloc(strlen(word) + 1);
            strcpy(new_node->word, word);
            new_node->count = 1;
            new_node->next = head;
            head = new_node;
        }
    }

    return head;
}

// Função para imprimir palavras únicas e suas contagens
void print_unique_words(word_info *word_list) {
    word_info *current = word_list;
    while (current != NULL) {
        printf("Palavra: '%s' - Ocorrências: %d\n", current->word, current->count);
        current = current->next;
    }
}

// Função para liberar a memória alocada para a lista ligada
void free_word_info(word_info *head) {
    word_info *current = head;
    while (current != NULL) {
        word_info *next = current->next;
        free(current->word);
        free(current);
        current = next;
    }
}

// Função para liberar a memória alocada para o array de palavras
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

    // Encontra palavras únicas e suas contagens
    word_info *unique_words = find_unique_words(word_array, n_total_words);

    // Imprime palavras únicas e suas contagens
    print_unique_words(unique_words);

    // Libera memória
    free_memory(word_array, n_total_words);
    free_word_info(unique_words);

    return 0;
}
