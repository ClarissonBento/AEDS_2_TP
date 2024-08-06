#include "node.h"


//Cria um novo nó
//colocar tratamento de erros se necessário
Node *createNode(char *word, int id_doc) {

    Node *new_node = (Node*)malloc(sizeof(Node));
    if (new_node == NULL) {
        printf("\nFalhou, erro no node.h\n");
        return NULL;
    }

    strcpy(new_node->ingredient_name, word);
    new_node->next = NULL;
    new_node->i_list = initialize_indexList();

    if (new_node->i_list == NULL) {
        free(new_node);
        return NULL;
    }

    insert_indexNode(new_node->i_list, id_doc);

    return new_node;
}

// Verificar esse calculo de hash code depois
// Percorre uma palavra letra a letra e um vetor e pesos elemento a elemento
// Transforma uma palavra num numero
int hash(char *word, int *weights, int M) {
    int hashcode = 0;
    int key_size = strlen(word);

    for (int i = 0; i < key_size; i++) {
        hashcode += (unsigned int)word[i] * weights[i]; // unsigned int pra garantir que não tenha num negativo
        //hashcode += (unsigned int)word[i] * weights[i % M];
    }

    hashcode = hashcode % M;

    return hashcode;
}

// Função para verificar se um número é primo
// 1 é true e 0 é false
int is_prime(int n) {
    if (n <= 1) return false;
    if (n == 2) return true;
    if (n % 2 == 0) return false;

    for (int i = 3; i <= sqrt(n); i += 2) {
        if (n % i == 0) return false;
    }

    return true;
}

// Sedgewick sugere escolher uma potência de 2 que esteja próxima do valor desejado de M (ou
// seja, de um valor que seja apropriado para os seus dados). Depois, adote para M o número
// primo que esteja logo abaixo da potência escolhida.
int choose_M(int num) {
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