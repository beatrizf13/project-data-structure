#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <unistd.h>
#include "include.h"

#define TRUE 1
#define FALSE 0

int main(){

	if(createList()==FALSE){
		printf("\nDesculpe! O arquivo não pode ser lido.\nVerifique se o nome foi digitado corretamente e com a devida extensão e reinicialize o programa.\n");
		return FALSE;
	 }

	Occurrence secondary;

	int option=1,registration_num,shift;
	char name[60], date[10];

	system("clear");

	while (option!=0)
	{
		printf("\n_________________________________________________________________________________________________________\n");
		printf("\n                                                Opções");
		printf("\n_________________________________________________________________________________________________________");
		printf("\n1 -> Listar todas as ocorrências de participantes presentes");
		printf("\n2 -> Listar todos participantes presentes em ordem numerica pelo número de inscrição ");
		printf("\n3 -> Listar todos participantes presentes em ordem alfabetica ");
		printf("\n4 -> Pesquisar ocorrências de participante presente pelo numero de inscricao");
		printf("\n5 -> Pesquisar ocorrências de participante presente pelo nome");
		printf("\n6 -> Pesquisar ocorrências de participantes presente por data");
		printf("\n7 -> Pesquisar ocorrências de participante presente por data e turno");
		printf("\n0 -> Encerrar");
		printf("\n_________________________________________________________________________________________________________");

		printf("\n\nDigite sua escolha:  ");
		scanf("%d",&option);

		if(option==1){
			print_occurrences();
			clean_screen();
		}
		else if(option==2){
			sort_by_numerical_order(secondary);
			clean_screen();
		}
		else if(option==3){
			sort_by_alphabetifal_order(secondary);
			clean_screen();
		}
		else if(option==4){
			printf("Numero de inscricao: ");
			scanf("%d",&registration_num);
			search_by_registration(registration_num);
			clean_screen();
		}
		else if(option==5){
			printf("Nome do participante: ");
			scanf(" %[^\n]s",name);
			search_by_name(name);
			clean_screen();
		}
		else if(option==6){
			printf("Data dd/mm/aaaa: ");
			scanf("%s",date);
			search_by_date(date);
			clean_screen();
		}
		else if(option==7){
			printf("1 -> Manhã | 2 -> Tarde | 3 -> Noite \nTurno: ");
			scanf("%d",&shift);
			while( shift != 1 && shift != 2 && shift != 3 ) {
				printf("Turno inexistente! Digite novamente!\n\nTurno: ");
				scanf("%d",&shift);
			}
			printf("Data dd/mm/aaaa: ");
			scanf("%s",date);
			search_by_date_shift(date,shift);
			clean_screen();
		}
		else if(option==0) break;
		else printf("\nOpção invalida, digite novamente!\n");
	}
	system("clear");
	printf("\nPrograma encerrado!\n");
	return TRUE;
}
