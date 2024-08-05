#include <stdlib.h>
#include <stdio.h>
#include "lista.c"
#include "lista.h"
#include "patricia.c"
#include "patricia.h"

int tolower(int c);

void LowerCase(char* str){ //Funcao que recebe uma string e transforma todos elementos em letras minusculas
    for(int i=0; i<strlen(str); i++){
        str[i] = tolower(str[i]);
    }
}

void ApagarCaracter(char *str, int n) { //Funcao que recebe a string e o valor do indice a ser apagado
    int tam = strlen(str); //Tamanho da string
        
    for (int i=n; i<tam - 1; i++) { //Percorre a palavra a partir do ponto a ser apagado e substitui os elementos pelo anterior
        str[i] = str[i+1]; 
    } 
    
    if(str[tam-2] == '.'){ //Se string possui um "." ao final, o transforma em final da string
        str[tam-2] = '\0';
    }else{
        str[tam-1] = '\0'; //Transforma o ultimo elemento em "\0", final da string, diminuindo o tamanho da palavra em 1
    }
} 

void Recorrencia(char* str, char* nomeArq, Tree* patricia, Ingredient ing, int id_doc){ 
    FILE* arq; //Ponteiro para o elemento arquivo
    char linha[1000]; //String para receber a terceira linha do arquivo, modo de preparo
    int tam1,tam2,cont,j,com; //Variaveis de tamanho para realizar a comparacao de strings

    arq = fopen(nomeArq, "r"); //Abre arquivo atual recebido

    fgets(linha, 1000, arq); //Le a primeira linha do arquivo, o titulo, e o ignora
    fgets(linha, 1000, arq); //Le a segunda linha do arquivo, os ingredientes, e os ignora
    fgets(linha, 1000, arq); //Le a terceira linha do arquivo, o modo de preparo, e o salva
    LowerCase(linha); //Transforma todos caracteres da string em letras minusculas

    tam1 = strlen(linha); //Tamanho 1 da string que contem a terceira linha
    tam2 = strlen(str); //Tamanho 2 da string que contem a palavra a ser contada
    printf("TAM:%d\n",tam2);
    
    for (int i=0; i < tam1;){ //Loop percorre a linha buscando a palavra desejada
        j = 0; //J conta o indice da palavra desejada, quando encontrada
        cont = 0; //Contador do numero de caracteres iguais das palavras sendo comparadas
        while ((linha[i] == str[j])){ //Enquanto caracteres da linha e palavra continuam iguais
            cont++; //Caracteres iguais, adiciona no contador
            i++; //Proximo indice da linha
            j++; //Proximo indice da palavra
        }if (cont == tam2){ //Se o contador for igual ao tamanho da palavra
            *patricia = Insert(ing, patricia, &com, id_doc, 1);
            //r++; //Recorrencia da palavra, adiciona                                   
            cont = 0; //Contador volta a zero
        }else{
            i++; //Proximo indice da linha
        }
    }    

    printf("D:%s\n\n",linha);
    fclose(arq); //Fecha o arquivo
    //return r;
}

void LeArquivo(ListaEncadeada list, Tree* patricia){
    FILE* arq; //Ponteiro para o elemento arquivo
    char receitas[150]; //String para guardar a segunda linha do arquivo, os ingredientes
    char* item; //Token para guardar a separacao de elementos da linha
    char ingrediente[50]; //String para guardar os ingredientes separados
    char nomeArq[50]; //String para nome do arquivo a ser lido por vez
    Apontador ptr_celula = list.primeiro->proximo;
    Ingredient ing; 
    int id_doc = 1,com;
    
    ImprimeLista(list);
    for(int i=1; ptr_celula != NULL; i++){
        sprintf(nomeArq,"./Receitas/%s",ptr_celula->elemento.fileName); //Coloca na string o nome e numero do arquivo atual
        arq = fopen(nomeArq, "r"); //Abre o arquivo com o valor selecionado, para leitura
            if (NULL == arq) { //Se houve problema ao abrir o arquivo
                printf("Arquivo nao pode ser aberto.\n");
                return;
            }

        printf("\n\nARQUIVO %d:\n\n",i);
        fgets(receitas, 150, arq); //Le a primeira linha do arquivo, o titulo, e o ignora
        fgets(receitas, 150, arq); //Le a segunda linha do arquivo, os ingredientes e os salva
        printf("%s", receitas);
        
        item = strtok(receitas, ";"); //Separa os ingredientes da segunda linha pelo caractere ";"
        strcpy(ingrediente, item); //Copia o conteudo do token, item, na string, ingrediente para poder ser modificada
        LowerCase(ingrediente); //Transforma todos caracteres da string em letras minusculas
        printf("A:%s\nB:%d\n", ingrediente, id_doc);
        strcpy(ing.name, ingrediente);
        *patricia = Insert(ing, patricia, &com, id_doc, 1);
        Recorrencia(ingrediente,nomeArq,patricia,ing,id_doc); //Chama a funcao recorrencia, que conta quantas vezes o ingrediente aparece no arquivo
        item = strtok(NULL, ";"); //Token, item, le o proximo ingrediente da receita
        while(item != NULL){ //Enquanto o token nao for nulo, ou seja, nao chegou ao fim da segunda linha do arquivo
            strcpy(ingrediente, item); //Copia o conteudo do token, item, na string, ingrediente para poder ser modificada
            LowerCase(ingrediente); //Transforma todos caracteres da string em letras minusculas
            ApagarCaracter(ingrediente, 0); //Apagar o primeiro caracter dos ingredientes, vindo do arquivo sempre como um " "
            item = strtok(NULL, ";"); //Token, item le o proximo ingrediente da receita
            if(item == NULL){ //Se o proximo for nulo, ou seja, chegou ao final da linha
                ApagarCaracter(ingrediente, (strlen(ingrediente))); //Apagar o ultimo caractere do ingrediente, sempre vindo como "." ao final da segunda linha
            }
            strcpy(ing.name, ingrediente);
            printf("A:%s\nB:%d\n", ingrediente, id_doc);
            *patricia = Insert(ing, patricia, &com, id_doc, 1);
            Recorrencia(ingrediente,nomeArq,patricia,ing,id_doc); //Chama a funcao recorrencia, que conta quantas vezes o ingrediente aparece no arquivo 
        }
        
        printf("AQUI\n");
        fclose(arq); //Fecha o arquivo
        id_doc++;
        ptr_celula = ptr_celula->proximo;
    }
}

void RecebeEntrada(ListaEncadeada* list){
    int n_files;
    char files[3];
    Item item;
    
    FILE* arq;

    arq = fopen("entrada.txt", "r"); //Abre o arquivo com o valor selecionado, para leitura
        if (NULL == arq) { //Se houve problema ao abrir o arquivo
            printf("Arquivo nao pode ser aberto.\n");
            return;
         }
    
    fgets(files, 4, arq);
    n_files = atoi(files);

    for(int i=0; i<n_files;i++){
        fgets(item.fileName,30,arq);
        if(item.fileName[strlen(item.fileName)-1] == '\n'){
            ApagarCaracter(item.fileName,strlen(item.fileName));
        }
        InsereFim(list, item);
    }
}


int main(){
    int op=1;
    ListaEncadeada file_list;
    Tree patricia = NULL;
    int n_terms;
    char words[100];
    char* item;
    char s_word[40];
    
    printf("AQUI:\n\n");
    InicializaLista(&file_list);
    
    do{
        printf("0- Sair\n1- Ler o arquivo de entrada\n2- Construir os indices invertidos com Patricia e HASH\n3- Imprimir os indices invertidos\n4- Realizar busca de termos, separados por '/'\n");
        scanf(" %d", &op);

        switch(op){
        case 0:
            break;
        case 1:
            RecebeEntrada(&file_list);
            ImprimeLista(file_list);
            break;
        case 2:
            //Construir Patricia e HASH;
            LeArquivo(file_list, &patricia);
            print_tree(patricia);
            break;
        case 3:
            //Imprimir indices invertidos;

            break;
        case 4:
            //Busca de termos nos TADS
            printf("Digitar o numero de termos:\n");
            scanf("%d ", &n_terms);
            printf("Digite as palavras separadas por \"/\":\n");
            fgets(words, sizeof(words), stdin);
            ApagarCaracter(words, (strlen(words)));


            char **string_array;
            string_array = malloc(n_terms * sizeof(char*));
            
            item = strtok(words, "/");
            for(int i=0; item != NULL; i++){
                strcpy(s_word, item);
                string_array[i] = malloc((sizeof(s_word)+1) * sizeof(char));
                strcpy(string_array[i],s_word);
                item = strtok(NULL, "/");
            }
            tf_idf(string_array, patricia, n_terms);
            break;
        }
    }while(op != 0);
    
    DestroiLista(&file_list);
    return 0;
}   
