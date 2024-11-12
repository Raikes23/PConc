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
    // Aloca memória para o array de ponteiros para strings (um ponteiro para cada palavra)
    // 'word_count' define o número de palavras e cada elemento do array aponta para uma palavra.
    char **word_array = malloc(word_count * sizeof(char *));
    if (!word_array) {  // Verifica se a alocação foi bem-sucedida
        perror("Erro ao alocar memória");
        fclose(file);   // Fecha o arquivo em caso de erro
        exit(1);        // Encerra o programa
    }

    int index = 0;  // Índice para controlar a posição atual no array de palavras
    char word[MAX_WORD_LENGTH];  // Buffer para armazenar temporariamente cada palavra lida do arquivo

    // Loop para ler cada linha do arquivo até o final
    while (fgets(word, sizeof(word), file)) {
        // Remove o caractere de nova linha ('\n') do final da palavra, caso esteja presente.
        // 'strcspn' retorna o índice do primeiro caractere '\n' ou o final da string se '\n' não existir.
        word[strcspn(word, "\n")] = 0;

        // Aloca memória para armazenar a palavra atual (inclui +1 para o caractere nulo '\0')
        word_array[index] = malloc((strlen(word) + 1) * sizeof(char));
        if (!word_array[index]) {  // Verifica se a alocação foi bem-sucedida
            perror("Erro ao alocar memória para palavra");
            fclose(file);   // Fecha o arquivo em caso de erro
            exit(1);        // Encerra o programa
        }

        // Copia a palavra do buffer temporário 'word' para o array 'word_array' na posição atual
        strcpy(word_array[index], word);

        // Incrementa o índice para a próxima posição no array de palavras
        index++;
    }

    // Retorna o array de palavras que agora contém todas as palavras lidas do arquivo
    return word_array;
}


int count_words(char **word_array, int n_total_words, char letter){

    int count = 0;

    for (int i = 0; i < n_total_words; i++){

        if (tolower(word_array[i][0]) == letter){
            count++;
        }

    }

    return count;
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

    for (char letter = 'a'; letter <= 'z'; letter++){

        int n_words = count_words(word_array, n_total_words, letter);
        printf("Numero de palavras com '%c' = '%d'\n", letter, n_words);

        n_words = 0;
    }

    free_memory(word_array, n_total_words);
    return 0;
}
