void print_words_by_letter(char **word_array, int word_count) {
    // Itera sobre cada letra do alfabeto, de 'a' a 'z'
    for (char letter = 'a'; letter <= 'z'; letter++) {
        printf("Palavras iniciadas com '%c':\n", letter);  // Imprime o cabeçalho para a letra atual

        // Itera sobre cada palavra no array
        for (int i = 0; i < word_count; i++) {
            // Verifica se a primeira letra da palavra corresponde à letra atual (ignorando maiúsculas/minúsculas)
            if (tolower(word_array[i][0]) == letter) {
                printf("%s\n", word_array[i]);  // Imprime a palavra se ela começa com a letra atual
            }
        }

        printf("\n");  // Linha em branco entre grupos de letras para melhor legibilidade
    }
}