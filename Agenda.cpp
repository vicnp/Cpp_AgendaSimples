#include <stdio.h>
#include <stdlib.h>

#define maxchar 100
//Protótipos das funcões.
void menu(); // Menu principal permite acesso a todas as funcões do programa.
void write_file(); // Função que escreve no arquivo, e caso o mesmo não exista este é criado.
void read_file(); // Função que le o arquivo criado, se o arquivo não existe um aviso é retornado com instruções.
void key_continue(); // Pressione uma tecla para continuar.
void acess_error(); // Exibe mensagem de erro caso o arquivo não possa ser acessado.
void get_data(FILE *arq); // Recebe os dados do usuário e os escreve no arquivo.
void clear_book(); // Função que limpa o arquivo. (na prática ele sobreescreve o antigo com um novo ).

int main(){
	menu();
	return 0;
}// end of main

void key_continue(){
	setbuf(stdin, NULL);
	printf("\nPressione qualquer tecla para continuar.  \n");
	getchar();
	setbuf(stdin, NULL);
}// end of key_continue

void acess_error(){
	printf(">> Não foi possível acessar o arquivo, ou arquivo ainda não foi criado.\n");
	printf(">> Se a agenda ainda não foi escrita (2), talvez seja esta a razão.\n");
	key_continue();
}//end of acess_error 

void menu(){
	system("clear");
	int op = 0;

	printf("Digite a Opção desejada: \n");
	printf("1 - Ver agenda.\n");
	printf("2 - Escrever na agenda\n");
	printf("3 - Limpar agenda.\n");
	printf("4 - Sair.\n");

	scanf("%d", &op);
	switch(op){

		case 1:
			read_file();
			break;
		case 2:
			write_file();
			break;
		case 3:
			clear_book();
			break;
		case 4:
			exit(0);
			break;
		default:
			printf("\nPor favor, selecione uma opção válida.\n");
			key_continue();
			menu();
			break;
	}// end of switch
}// end of menu

void read_file(){
	FILE *arq;
	char leitura[maxchar];
	arq = fopen("arquivo.agd", "r");

	if(arq == NULL){
		acess_error();
		system("clear");
		menu();
	}//end of IF

	while(fgets(leitura,maxchar,arq)){
	printf("%s\n",leitura);
	printf("------------------------\n");
	}//end of WHILE

	fclose(arq);
	key_continue();
	menu();
}// end of read_file

void write_file(){
	FILE *arq;
	arq = fopen("arquivo.agd", "a");

	if(arq == NULL){
		acess_error();
		menu();
	}// end of IF

	get_data(arq);
	fclose(arq);
	key_continue();
	menu();
}// end of write_file

void get_data(FILE *arq){
	char nome[maxchar], sobre_nome[maxchar];
	int numero;

	printf("\t \t  Adicionar contatos:\n\n");
	//Recebe os dados do usuário
	printf(" Digite o primeiro nome:  ");
	scanf("%99s", nome);
	setbuf(stdin, NULL);

	printf(" Digite o sobre nome:  ");
	scanf("%99s", sobre_nome);
	setbuf(stdin, NULL);

	printf(" Digite o número de telefone:  ");
	scanf("%d", &numero);
	setbuf(stdin, NULL);

	fprintf(arq, "%s %s %d\n",nome,sobre_nome, numero); // Escreve no arquivo;
}// end of get_data

void clear_book(){
	setbuf(stdin, NULL);
	char op;
	FILE *arq;
	arq = fopen("arquivo.agd", "r");

	if(arq == NULL){
		acess_error();
		system("clear");
		menu();
	}// end of IF

	printf("\t   Atenção, todos os contatos serão apagados \n");
	printf("\t   Tem CERTEZA de que quer continuar ? \n");
	printf("\t   (Y- Sim/N - Não)\n");
	setbuf(stdin, NULL);
	scanf("%c", &op);

	if(op == 'y' || op == 'Y'){
		arq = fopen("arquivo.agd", "w");
		printf("Agenda limpa com sucesso !\n");
		key_continue();
		menu();
	} // end of IF

	else if(op == 'n' || op == 'N'){
		menu();
	}// end of ELSE IF

}// end of clear_book

//end of file