#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <math.h>
/*
// Função para verificar se um número é primo
// 1 é true e 0 é false
int is_prime(int n) {
    if (n <= 1) return 0;
    if (n == 2) return 1;
    if (n % 2 == 0) return 0;

    for (int i = 3; i <= sqrt(n); i += 2) {
        if (n % i == 0) return 0;
    }

    return 1;
}

int choosin_M(int num) {
    int twoPow = 0;

    // Encontra a menor potência de 2 que é maior ou igual ao numero
    while (pow(2, twoPow) < num) twoPow++;
    int power_of_two = (int)pow(2, twoPow);

    // Procura o maior número primo abaixo dessa potência de 2
    for (int i = power_of_two - 1; i > 1; i--) {
        if (is_prime(i)) {
            return i;
        }
    }

    return 2; // Caso extremo onde 2 é o maior primo abaixo da potência de 2
    // Não é necessário pra nossa implementação especificamente
}

// Verificar esse calculo de hash code depois
int hash(char *word, int *weights, int M) {
    int hashcode = 0;
    int key_size = strlen(word);

    for (int i = 0; i < key_size; i++) {
        hashcode += (unsigned int)word[i] * weights[i]; // unsigned int pra garantir que não tenha num negativo
    }

    hashcode = hashcode % M;

    return hashcode;
}

void gera_pesos(int *pesos, int n) {
    int i;
    struct timeval semente;
    gettimeofday(&semente, NULL); 
    srand((int)(semente.tv_sec + 1000000*semente.tv_usec));

    for (i = 0; i < n; i++){
        pesos[i] =  1+(int) (10000.0*rand()/(RAND_MAX+1.0));
    }
}

int main(){

    //int pesos[20];
    char palavra[20];
    int M; // M é o tamanho da tabela
    int hashcode;
    int tamanho_palavra;

    printf("Escreva a palavra: ");
    scanf("%s", palavra);

    tamanho_palavra = strlen(palavra); // esse pedaço é pra deixar o vetor de pesos do mesmo tamanho da palavra
    int pesos[tamanho_palavra];

    gera_pesos(pesos, tamanho_palavra); // n é o numero de caracteres na palavra

    M = choosin_M(25);

    hashcode = hash(palavra, pesos, M);

    printf("n: %i\n", tamanho_palavra);
    printf("M: %i", M);
    printf("\nHashcode: %i\n", hashcode);

    printf("Vetor de pesos: ");
    for (int i = 0; i < tamanho_palavra; i++) {
        printf("%i, ", pesos[i]);
    }
    printf("\n");
    
}
*/