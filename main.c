#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void LowerCase(char* str){
    
    for(int i=0; i<strlen(str); i++){
        str[i] = tolower(str[i]);
    }
}

void Recorrencia(char* str){
    FILE* arq;
    char linha[1000];
    int tam1,tam2,cont,j,r=1;

    arq = fopen("./Receitas/arquivo1.txt", "r");

    fgets(linha, 1000, arq);
    fgets(linha, 1000, arq);
    fgets(linha, 1000, arq);
    LowerCase(linha);

    tam1 = strlen(linha);
    tam2 = strlen(str);
    printf("TAM:%d\n",tam2);
    
    for (int i=0; i < tam1;)
    {
        j = 0;
        cont = 0;
        while ((linha[i] == str[j])){
            cont++;
            i++;
            j++;
        }if (cont == tam2){
            r++;                                   
            cont = 0;
        }
        else
            i++;
    }    

    printf("N:%d\nD:%s\n\n", r,linha);
    fclose(arq);
}

void ApagarCaracter(char *str, int n) { 
    int tam = strlen(str); 
        
    for (int i=n; i<tam - 1; i++) { 
        str[i] = str[i+1]; 
    } 
    
    if(str[tam-2] == '.'){
        str[tam-2] = '\0';
    }else{
        str[tam-1] = '\0'; 
    }
} 

int main(){
    FILE* arq;
    char receitas[150];
    char* item;
    char ingrediente[20];
    
    arq = fopen("./Receitas/arquivo1.txt", "r");
        if (NULL == arq) {
            printf("Arquivo nao pode ser aberto.\n");
        }
    fgets(receitas, 150, arq);
    fgets(receitas, 150, arq);
    printf("%s", receitas);

    
    item = strtok(receitas, ";");
    strcpy(ingrediente, item);
    LowerCase(ingrediente);
    printf("%s\n",ingrediente);
    Recorrencia(ingrediente);
    item = strtok(NULL, ";");
    while(item != NULL){
        if(item != NULL){
            strcpy(ingrediente, item);
            LowerCase(ingrediente);
            ApagarCaracter(ingrediente, 0);
            item = strtok(NULL, ";");
        }if(item == NULL){
            ApagarCaracter(ingrediente, (strlen(ingrediente)));
        }
        printf("A:%s\n", ingrediente);
        Recorrencia(ingrediente);
    }
    
    printf("AQUI\n");
    fclose(arq);
    return 0;
}   
