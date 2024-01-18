#include <stdio.h> //bilheteria padrão para entrada e saída de dados
#include <string.h> //biblioteca para manipulação de strings
#include <stdlib.h> //biblioteca para manipulação de processos
#include <time.h> //utilizado para saber o tempo atual

//structs
struct sessao
{
  int contador;
  char escolhaSessao[30];
};

struct TiposIngresso
{  
    int tipoComprado;
    int tipoContador;
	int ingressoTipo;
	float IngressoValor1;
	float IngressoValor2;
	float IngressoValor3;
	char escolha[30];
};

//iniciacao das funcoes
void pagamento();
void bilheteria();
void temas();
int gerarID();
// variavel global
char nomeSessao[30];

//funcao para definir formas de pagamento
void pagamento() 
{
    char formaPagamento[20];
    int respostaPagamento = 0;
    printf("Escolha a forma de pagamento\n");
	printf("1- Cartão\n");
    printf("2- Pix\n");
	printf("Digite a forma de pagamento: ");
	scanf("%d", &respostaPagamento);
	
    if (respostaPagamento == 1)
    {
	    printf("insira o cartão na maquina e selecione: crédito ou debito\n");
	    strcpy(formaPagamento, "cartão");
    }
	else if (respostaPagamento == 2)
	{
	    printf("Dirija-se ao balção para escanear o toten\n");
	    strcpy(formaPagamento, "PIX");
	}
	else
		printf("Código invalido!");
		
    FILE *ingressos = fopen("ingresso.csv", "w");

	if (ingressos == NULL)
	{
	   printf("Erro ao abrir arquivo.\n");
	}
	fprintf(ingressos, "Sessão: %s\n", nomeSessao);
	fprintf(ingressos,"forma de pagamento: %s\n", formaPagamento);
	        
	fclose(ingressos);
}

//funcao para escolher tipos de ingresso
void bilheteria()
{

    int escolhaFinal = 0;
    int tiposTotais = 0;
    int valoresTotais = 0;
    int respostaBilheteria;
    int XX = 0;
    
	struct TiposIngresso tipo[4];
	
	for (int i = 0; i < 3; i++)
    {
        tipo[i].tipoComprado = 0;
        tipo[i].IngressoValor1 = 0.00;
    }
    
    while (respostaBilheteria != 4)
    {
        printf("==========================================\n");
	    printf("                BILHETERIA                \n");
	    printf("==========================================\n");
	    
	    printf("Selecione o tipo de ingresso a ser comprado \n");
	    printf("[1] Ingresso Inteiro - R$20 \n");
	    printf("[2] Meia Entrada - R$10 \n");
	    printf("[3] Isento\n");
	    printf("[4] para sair\n");
	    
	    int clienteID = gerarID();
        
        FILE *ingressos = fopen("ingresso.csv", "a");

	        if (ingressos == NULL)
	        {
	            printf("Erro ao abrir arquivo.\n");
	        }
            fprintf(ingressos, "Seu ID de compra é: %d\n", clienteID);
        
	   fclose(ingressos);
	    
        scanf("%d", &respostaBilheteria);
        
        XX = respostaBilheteria-1;
        if (XX == 0)
        {
            strcpy(tipo[XX].escolha, "Inteiro");
            tipo[XX].IngressoValor1 = 20.00;  
        }
        
        if (XX == 1)
        {
            strcpy(tipo[XX].escolha, "Meia Entrada");
            tipo[XX].IngressoValor1 = 10.00;
        }
                
        if (XX == 2)
        strcpy(tipo[XX].escolha, "Isento");
                
        printf("Quantos ingresos deseja comprar do tipo %s ? \n",tipo[XX].escolha);
        scanf("%d", &tipo[XX].tipoComprado);
        tipo[XX].tipoContador = tipo[XX].tipoComprado;
        printf("\n");
        
        tipo[XX].IngressoValor1 *= tipo[XX].tipoComprado;
        printf("Valor Total %s: R$%.2f\n", tipo[XX].escolha,tipo[XX].IngressoValor1);
        printf("\n");
                
        printf("Deseja finalizar a compra ?\n");
        printf("[1] para SIM\n");
        printf("[2] para comprar mais ingressos\n");
        scanf("%d", &escolhaFinal);
                
        if (escolhaFinal == 1)
        {
            pagamento();
            tiposTotais = tipo[0].tipoComprado + tipo[1].tipoComprado + tipo[2].tipoComprado;
            printf("Total de ingressos: %d\n", tiposTotais);
        
            valoresTotais = tipo[0].IngressoValor1 + tipo[1].IngressoValor1;
            printf("Valor total:R$ %d,00\n", valoresTotais);
            printf("\n");
            
            FILE *ingressos = fopen("ingresso.csv", "a");

	        if (ingressos == NULL)
	        {
	            printf("Erro ao abrir arquivo.\n");
	        }
	        fprintf(ingressos, "Total de ingressos Inteiros: %d\n", tipo[0].tipoComprado);
	        fprintf(ingressos, "Valor total dos ingressos Inteiros: %.2f\n", tipo[0].IngressoValor1);
	        
	        fprintf(ingressos, "Total de ingressos Meia entrada: %d\n", tipo[1].tipoComprado);
	        fprintf(ingressos, "Valor total dos ingressos Meia entrada: %.2f\n", tipo[1].IngressoValor1);
	        
	        fprintf(ingressos, "Total de ingressos Isentos: %d\n", tipo[2].tipoComprado);
	        fprintf(ingressos, "Valor total dos ingressos Isentos: %.2f\n", tipo[2].IngressoValor1);
	        
	        fprintf(ingressos,"Total de ingressos: %d\n", tiposTotais);
            fprintf(ingressos, "Valor total:R$ %d,00\n", valoresTotais);    
        
	        fclose(ingressos);
        }
        //tipo[0].tipoContador
    }
}

//funcao para escolher os temas
void temas() {
    struct sessao sessoes[4];
    int respostaSessao = 0;

    for (int i = 0; i < 4; i++) {
        sessoes[i].contador = 0;
        sessoes[i].escolhaSessao[30];
    }

    while (respostaSessao != 5) {
        printf("========= TEMAS DISPONIVEIS =========\n");
        printf("\n");
        printf("Selecione uma sessão a baixo:\n");
        printf("[1] para Cibersegurança\n");
        printf("[2] para 100 anos da semana de arte moderna\n");
        printf("[3] para 150 anos de Santos Drummont\n");
        printf("[4] para Jogos Olímpicos de Paris 2024\n");
        printf("[5] para sair\n");
        scanf("%d", &respostaSessao);

        switch (respostaSessao) {
            case 1:
                strcpy(nomeSessao, "Cibersegurança");
                printf("Sessão %s selecionada.\n", nomeSessao);
                printf("SELECIONE o tipo de ingresso:\n");
                printf("\n");
                bilheteria();
                break;
            case 2:
                strcpy(nomeSessao, "100 anos da semana de arte moderna");
                printf("Sessão %s selecionada.\n", nomeSessao);
                printf("SELECIONE o tipo de ingresso:\n");
                printf("\n");
                bilheteria();
                break;
            case 3:
                strcpy(nomeSessao, "150 anos de Santos Drummont");
                printf("Sessão %s selecionada.\n", nomeSessao);
                printf("SELECIONE o tipo de ingresso:\n");
                printf("\n");
                bilheteria();
                break;
            case 4:
                strcpy(nomeSessao, "Jogos Olímpicos");
                printf("Sessão %s selecionada.\n", nomeSessao);
                printf("SELECIONE o tipo de ingresso:\n");
                printf("\n");
                bilheteria();
                break;
        }
    }
}

int gerarID()
{
    srand(time(NULL));
    
    int id = rand() % 500 + 1;
    
    return id;
}

//funcao inicial onde o codigo sera rodado
int main()
{
    
    int escolha = 0;
    
    while (escolha != 2)
    {
        printf("==========================================\n");
	    printf("     SEJA VEM VINDO(A) AO NOSSO MUSEU     \n");
	    printf("==========================================\n");
	    printf(" \n");
	    printf("O que deseja fazer: \n");
	    printf("[1] para comprar ingresso\n");
	    printf("[2] para sair\n");
	    scanf("%d", &escolha);
	    
	    if (escolha == 1)
	    {
	        //limpar tela
	        printf("\n");
	        temas();
        }   
    }
    return 0;
}
