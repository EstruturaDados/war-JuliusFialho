// ============================================================================
//         PROJETO WAR ESTRUTURADO - DESAFIO DE CÓDIGO
// ============================================================================
//        
// ============================================================================
//
// OBJETIVOS:
// - Modularizar completamente o código em funções especializadas.
// - Implementar um sistema de missões para um jogador.
// - Criar uma função para verificar se a missão foi cumprida.
// - Utilizar passagem por referência (ponteiros) para modificar dados e
//   passagem por valor/referência constante (const) para apenas ler.
// - Foco em: Design de software, modularização, const correctness, lógica de jogo.
//
// ============================================================================

// Inclusão das bibliotecas padrão necessárias para entrada/saída, alocação de memória, manipulação de strings e tempo.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
// --- Constantes Globais ---
// Definem valores fixos para o número de territórios, missões e tamanho máximo de strings, facilitando a manutenção.
#define MAX_TERRITORIO 5
#define MAX_MISSAO 5
#define TAM_STRING 30
#define TAM_STRING_MISS 50

// --- Estrutura de Dados ---
// Define a estrutura para um território, contendo seu nome, a cor do exército que o domina e o número de tropas.
typedef struct{
    char nome[TAM_STRING];
    char cor[10];
    int tropas;
}Territorio;


// --- Protótipos das Funções ---
// Declarações antecipadas de todas as funções que serão usadas no programa, organizadas por categoria.
// Funções de setup e gerenciamento de memória:

Territorio* alocarMapa();


void inicializarTerritorios(Territorio *mapa);


void liberarMemoria(Territorio* mapa,char* missaoJogado);




// Funções de interface com o usuário:
void exibirMenuPrincipal(int *opcao);

void  exibirMapa(Territorio *mapa);

void exibirMissao();
   




// Funções de lógica principal do jogo:

void  simularAtacar(Territorio *atacante,Territorio *defensor);

int atribuirMissao(char* destino, char *missoes[], int totalMissoes);

void faseDeAtaque(Territorio *mapa);
     


// Função utilitária:
void limparBufferEntrada();


// --- Função Principal (main) ---
// Função principal que orquestra o fluxo do jogo, chamando as outras funções em ordem.
int main() {
    // 1. Configuração Inicial (Setup):
    // - Define o locale para português.
    // - Inicializa a semente para geração de números aleatórios com base no tempo atual.
    srand(time(NULL));
    // - Aloca a memória para o mapa do mundo e verifica se a alocação foi bem-sucedida.
    Territorio *mapa=alocarMapa();
    if(mapa==NULL){
        return 1;
    }


    // - Preenche os territórios com seus dados iniciais (tropas, donos, etc.).
    inicializarTerritorios(mapa);
    
    char *missaoJogador;

    missaoJogador=(char*)malloc(TAM_STRING_MISS*sizeof(char ));
     if(missaoJogador==NULL){
        return 1;
    }


    // - Define a cor do jogador e sorteia sua missão secreta.
    char *missao[MAX_MISSAO];
    int indiceMissao=atribuirMissao(missaoJogador,missao,MAX_MISSAO);
;
  // 
  

  //  }

    // 2. Laço Principal do Jogo (Game Loop):
    // - Roda em um loop 'do-while' que continua até o jogador sair (opção 0) ou vencer.
    // - A cada iteração, exibe o mapa, a missão e o menu de ações.
    // - Lê a escolha do jogador e usa um 'switch' para chamar a função apropriada:
    //   - Opção 1: Inicia a fase de ataque.
    //   - Opção 2: Verifica se a condição de vitória foi alcançada e informa o jogador.
    //   - Opção 0: Encerra o jogo.
    // - Pausa a execução para que o jogador possa ler os resultados antes da próxima rodada.
    int opcao;
   
   
    int vitoria;// para receber o estado de vitoria do jogo
    do
    {   
        exibirMapa(mapa);
        exibirMissao(missaoJogador);
        exibirMenuPrincipal(&opcao);


        switch (opcao)
        {
        case 1:
            faseDeAtaque(mapa);
            break;
        case 2:
            vitoria=verificarVitoria(indiceMissao,missao,mapa);
            if(vitoria==0){
                printf("\n  Vitoria");
                opcao=0;
            }
            break;
        case 0: 
            
            printf("\nsaindo\n");
            break;
        
        default:
            printf("\ncomando invalido\n");
            break;
        }
        
    } while (opcao!=0);
    

    // 3. Limpeza:
    // - Ao final do jogo, libera a memória alocada para o mapa para evitar vazamentos de memória.
    printf("\nDigite qualquer tecla paa sair");
    liberarMemoria(mapa,*missaoJogador);
    getchar();
    return 0;
}

// --- Implementação das Funções ---

// alocarMapa():
// Aloca dinamicamente a memória para o vetor de territórios usando calloc.
// Retorna um ponteiro para a memória alocada ou NULL em caso de falha.
Territorio* alocarMapa(){
    Territorio* mapa;
    mapa=(Territorio*)calloc(MAX_TERRITORIO,sizeof(Territorio ));

    
    
    if(mapa== NULL){
        printf("Erro: falha ao alocar memoria");
        return NULL;// return 1 para erro 
    }
    return mapa;
}

// inicializarTerritorios():
// Preenche os dados iniciais de cada território no mapa (nome, cor do exército, número de tropas).
// Esta função modifica o mapa passado por referência (ponteiro).
void inicializarTerritorios(Territorio *mapa){

    mapa[0].tropas = 6;
    strcpy(mapa[0].nome, "Brasil");
    strcpy(mapa[0].cor, "Verde");
    
     mapa[1].tropas = 3;
    strcpy(mapa[1].nome, "China");
    strcpy(mapa[1].cor, "Vermelho");

     mapa[2].tropas = 2;
    strcpy(mapa[2].nome, "Canada");
    strcpy(mapa[2].cor, "Amarelo");

     mapa[3].tropas = 2;
    strcpy(mapa[3].nome, "Italia");
    strcpy(mapa[3].cor, "Azul");

     mapa[4].tropas = 1;
    strcpy(mapa[4].nome, "Argetina");
    strcpy(mapa[4].cor, "Rosa");
     
   
}

// liberarMemoria():
// Libera a memória previamente alocada para o mapa usando free.
void liberarMemoria(Territorio* mapa,char* missaoJogador){
    free(mapa);
    free(missaoJogador);
}

// exibirMenuPrincipal():
// Imprime na tela o menu de ações disponíveis para o jogador.
void exibirMenuPrincipal(int *opcao){
    // ler a opcao do usuario
        int enter;
        printf("\n---- Menu de Acoes---- \n");
        printf("1 -- para Ataque \n");
        printf("2 -- para Verificar Missoes---- \n");
        printf("0 -- para de Sair---- \n");
        printf("--- escolha sua acao: ");
        scanf("%d",&enter);
        limparBufferEntrada();
        // limpar o \n deixado pelo scanf
        *opcao=enter;
}

// exibirMapa():
// Mostra o estado atual de todos os territórios no mapa, formatado como uma tabela.
// Usa 'const' para garantir que a função apenas leia os dados do mapa, sem modificá-los.
void  exibirMapa(Territorio *mapa){
    printf("\n==========Mapa do Mundo==============\n");
    for(int i=0;i<MAX_TERRITORIO;i++)
   {
        //printf("1 nome (territorio cor, tropas: x)\n");
        printf("%d %s (territorio %s, tropas: %d)\n",i+1,mapa[i].nome,mapa[i].cor,mapa[i].tropas);

       
     
   }
    printf("======================================\n");
}

// exibirMissao():
void exibirMissao(char *missaoatual){
    
    printf("\n=============================\n");
    printf("         Missao\n");
    printf("Exercito verde: %s",missaoatual);
    printf("\n=============================\n");

}

// faseDeAtaque():
// Gerencia a interface para a ação de ataque, solicitando ao jogador os territórios de origem e destino.
// Chama a função simularAtaque() para executar a lógica da batalha.
void faseDeAtaque(Territorio *mapa){
    int indice,indice2;
    printf("============ Fase de Ataque ==============\n");

    //atacar
    printf("\ndigite o atacante(1 a %d): ",MAX_TERRITORIO);
    scanf("%d",&indice);
    limparBufferEntrada();

                
    //escolher o numero do defensor
    printf("digite o defensor (1 a %d): ",MAX_TERRITORIO);
    scanf("%d",&indice2);
    limparBufferEntrada();
                //strcmp("Verde",mapa[i].cor)==0
    printf("Atacante: %s  Defensor: %s\n",mapa[indice-1].cor,mapa[indice2-1].cor);
    if(strcmp(mapa[indice-1].cor,mapa[indice2-1].cor)==0){
        printf("\nTente novamente: nao pode atacar territorio com cores iguais\n");
        //break;
        
    }else{
        //chama simulaAtacar se os territorios terem cores da equipe difretes
        simularAtacar(&mapa[indice-1],&mapa[indice2-1]);
    }
    printf("\n======================================\n");
    
}

// simularAtaque():
// Executa a lógica de uma batalha entre dois territórios.
// Realiza validações, rola os dados, compara os resultados e atualiza o número de tropas.
// Se um território for conquistado, atualiza seu dono e move uma tropa.
void simularAtacar(Territorio *atacante,Territorio *defensor){
        
    //
        
        

        printf("Invasor %s Defensor %s \n",atacante->nome,defensor->nome);
        int ataque=(rand() % 6) + 1;;
        int defesa=(rand() % 6) + 1;;

        printf("Atacante tira %d no dado\nDefensor tira %d no dado\n",ataque,defesa);

        if(ataque==defesa){
            printf("Empate, defensor perde tropa");
            defensor->tropas-=1;
        }else{
            if(ataque>defesa){
                printf("Invasor Ganha\n");
                //defensor="";
                strcpy(defensor->cor, atacante->cor);
                defensor->tropas=atacante->tropas/2;
                atacante->tropas/=2;
                
              

            }else{
                printf("Denfensor Ganha");
                atacante->tropas-=1;
                
            }
        }       


}

// sortearMissao():
// Sorteia e retorna um ID de missão aleatório para o jogador.
int sortearMissao(int i){
   
    int id=(rand() % i) + 1;
    return id;
}

// verificarVitoria():
// Verifica se o jogador cumpriu os requisitos de sua missão atual.
// Implementa a lógica para cada tipo de missão (destruir um exército ou conquistar um número de territórios).
// Retorna 1 (verdadeiro) se a missão foi cumprida e 0 (falso) caso contrário.
int verificarVitoria(int indice,char *missoes[],Territorio *mapa ){
    
    
    
    int contagem[MAX_TERRITORIO]={0,0,0,0,0}; //variavel para contar o numero de territotio para cada cor
    //conta o numero de terreno paara cada cor, contagem[0] guarda a quantidade de terrenos com a cor verde
    for(int i=0;i<MAX_TERRITORIO;i++)
        {
            if(strcmp("Verde",mapa[i].cor)==0){
                   
                   contagem[0]+=1;
                   printf("\ncontage %d", contagem[0]);
            }
            if(strcmp("Vermelho",mapa[i].cor)==0){
                    
                    contagem[1]+=1;
            }
            if(strcmp("Amarelo",mapa[i].cor)==0){
                   
                    contagem[2]+=1;
            }
            if(strcmp("Azul",mapa[i].cor)==0){
                    
                    contagem[3]+=1;
            }
            if(strcmp("Rosa",mapa[i].cor)==0){
                    
                    contagem[4]+=1;
            }
            
       
     
        }
        
            
        
   //com base no id da missao é selecionada uma das duas forma de vencer
    if(indice>1){
        //para as missões de conquista territorios com uma determinada cor
      
       switch (indice)
       {
        case 2:
            if(contagem[1]!=0){
                return 1;
            }
            break;
        case 3:
            if(contagem[3]!=0){
                return 1;
            }
            break;
        case 4:
            if(contagem[2]!=0){
                return 1;
            }
       
            break;
       default:

        break;
       }
       
    }else{
      // para missões de  conquistar varios terrenos
         switch (indice)
       {
        case 0:
            if(contagem[0]>3){
                return 1;
            }
            break;
        case 1:
            if(contagem[0]>4){
                return 1;
            }
            break;
       default:

        break;
       }
        
        
    }

    
}

// limparBufferEntrada():
// Função utilitária para limpar o buffer de entrada do teclado (stdin), evitando problemas com leituras consecutivas de scanf e getchar.
void limparBufferEntrada(){
    int c;
    while((c=getchar())!='\n'&& c != EOF);
}

int atribuirMissao(char* destino, char *missoes[], int totalMissoes){
    // definir missao
    missoes[0]="Conquistar 3 territórios ";
    missoes[1]= "Conquistar 4 territórios ";
    missoes[2]= "Eliminar todas as tropas da cor vermelha";
    missoes[3]= "Eliminar todas as tropas da cor azul";
    missoes[4]= "Eliminar todas as tropas da cor amarelo";
    int i=sortearMissao(totalMissoes);
    
    strcpy(destino, missoes[i]);
    return i;
 }
