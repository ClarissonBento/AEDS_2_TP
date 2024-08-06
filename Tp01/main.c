#include "Funcoes_read/read.c"

int main(){
    int op=1;
    ListaEncadeada file_list;
    Tree patricia = NULL;
    
    printf("MENU:\n");
    InicializaLista(&file_list); //Lista para nomes dos arquivos
    
    do{
        printf("\n0- Sair\n1- Ler o arquivo de entrada\n2- Construir os indices invertidos com Patricia e HASH\n3- Imprimir os indices invertidos\n4- Realizar busca de termos, separados por '/'\n");
        scanf(" %d", &op);

        switch(op){
        case 0:
            break;
        case 1:
            //Le o arquivo de entrada
            RecebeEntrada(&file_list);
            break;
        case 2:
            //Construir Patricia;
            LeArquivo(file_list, &patricia);
            break;
        case 3:
            //Imprimir indices invertidos;
            print_tree(patricia);
            break;
        case 4:
            //Busca de termos nos TADS
            BuscarTads(patricia);
            break;
        }
    }while(op != 0);
    
    DestroiLista(&file_list);
    return 0;
}   
