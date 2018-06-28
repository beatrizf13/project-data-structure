#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <unistd.h>
#include "include.h"

#define TRUE 1
#define FALSE 0

//cria a lista a partir do arquivo
int createList(){

	int i=0;

	//imprime todos os arquivos contidos na pasta files
	printf("\nVeririfique os arquivos disponiveis:\n");
	DIR *dir;
	struct dirent *lsdir;
	dir = opendir("files");
	while ( ( lsdir = readdir(dir) ) != NULL ) printf ("%s\n",lsdir->d_name);
	closedir(dir);

	char name_file[50];
	printf("\nDigite o nome do arquivo para ser lido com a extensão\nexemplo.txt\n>>");
	scanf("%s",name_file);
//inicio

//essa sequencia de comandos utiliza uma variavel auxiliar [name_file_] para armazenar a seguinte string:
// files/nomedoarquivo
// e por fim outra variavel do tipo const char* recebe essa variavel auxiliar, para que possa ser lida e interpretada pelo 'fopen' da forma correta
	char name_file_[50];
	name_file_[0] = 'f';
	name_file_[1] = 'i';
	name_file_[2] = 'l';
	name_file_[3] = 'e';
	name_file_[4] = 's';
	name_file_[5] = '/';
	for(i=0; name_file[i] != '\0' ; i++){
		name_file_[i+6] = name_file[i];
	}
	name_file_[i+6]= '\0';
	const char* name_file_c = name_file_;
//fim

	Occurrence occurrence;
	i=0;
	char date[11], hour[11], registration_num[7], name[60];

	FILE *read_file;

	read_file = fopen(name_file_c,"r");
	if(read_file==NULL) return FALSE;



	//separa o arquivo em "pedaços" por quantidade de caracteres definidos a cada fgets
	while( (fgets(date, 11, read_file)!=NULL) && (fgets(hour, 11, read_file)!= NULL) && (fgets(registration_num, 7, read_file) != NULL) && (fgets(name, 60, read_file)!= NULL) )
	{
		strcpy(occurrence.date, date);
		strcpy(occurrence.hour, hour);
		occurrence.registration_num=atoi(registration_num);
		for(i=0 ; name[i]!='\0' ; i++){
			if(name[i] == '\n') name[i] = name[i+1];
		}
		strcpy(occurrence.name, name);
		li.list[li.amount++] = occurrence;
	}
	fclose(read_file);

	return TRUE;
}

void clean_screen(){
	int foo;
	printf("\n_________________________________________________________________________________________________________\n");
	printf("\nDigite qualquer tecla para voltar ao menu de opções \nou 0 para voltar e limpar a tela\n>> " );
	scanf("%d",&foo);
	if(foo==0) system("clear");
}

void print_one_occurrence(int position){
	int i = position;
	printf("\nData: %s | Hora: %s | Inscrição: %d | Nome: %s",li.list[i].date, li.list[i].hour, li.list[i].registration_num, li.list[i].name );
}

void print_occurrences(){
	int i;
	int total_occurrences=0;

	for(i=0 ; i<li.amount ; i++){
		printf("\nData: %s | Hora: %s | Inscrição: %d | Nome: %s",li.list[i].date, li.list[i].hour, li.list[i].registration_num, li.list[i].name );
		total_occurrences++;
	}

	if(total_occurrences==0) printf("\nNão foram encontradas ocorrencias!\n");
	else printf("\n\nTotal de ocorrencias: %d\n",total_occurrences);
}

void print_occurrences_effective(Occurrence occurrence){
	int i;
	int total_occurrences=0;

	for(i=0 ; i<li.amount ; i++){
		printf("\nData: %s | Hora: %s | Inscrição: %d | Nome: %s",li.list[i].date, li.list[i].hour, li.list[i].registration_num, li.list[i].name );
		total_occurrences++;

		while(li.list[i+1].registration_num == li.list[i].registration_num) i++;
	}
	if(total_occurrences==0) printf("\nNão foram encontradas ocorrencias!\n");
	else printf("\n\nTotal de ocorrencias: %d\n",total_occurrences);
}

//ordena crescentemente a lista ocorrencias armazenando em uma lista secundária para preservar a original
Occurrence ascending_order_register(Occurrence secondary){
	int i,j;
	for(i=0; i<li.amount; i++){
		for(j=i+1;j<li.amount;j++){
			if(li.list[i].registration_num>li.list[j].registration_num){
				secondary = li.list[i];
				li.list[i] = li.list[j];
				li.list[j]=secondary;
			}
		}
	}
	return secondary;
}

Occurrence alphabetical_order (Occurrence secondary){
	int i,j;
	for(i=0;i<li.amount;i++){
		for(j=i+1;j<li.amount;j++){
			secondary=li.list[i];

			if(strcmp(secondary.name,li.list[j].name)>0){
				secondary = li.list[i];
				li.list[i] = li.list[j];
				li.list[j]=secondary;
			}
		}
	}
	return secondary;
}

//imprime todas as ocorrencias de presenças pela ordem que foi lida
void print_original_order(Occurrence occurrence){
	print_occurrences(occurrence);
}

void sort_by_alphabetifal_order(Occurrence secondary){
	secondary = alphabetical_order(secondary); //armazenará a lista ordenada
	print_occurrences_effective(secondary);
}

//imprime as ocorrencias de presenças sem repetições de nomes de participantes em ordem numerica pelo numero de inscricao
void sort_by_numerical_order(Occurrence secondary){
	secondary = ascending_order_register(secondary); //armazenará a lista ordenada
	print_occurrences_effective(secondary);
}

//pesquisa pelo número de inscrição e imprime todas as ocorrencias do participante
void search_by_registration(int registration_num){
	int i,id=0;
	int total_participant_occurrence=0;

	for (i=0; i<li.amount; i++){
		if (registration_num == li.list[i].registration_num){
			print_one_occurrence(i);
			id=i;
			total_participant_occurrence++;
		}
	}
	if(total_participant_occurrence==0) printf("\nNão foram encontradas ocorrencias para a inscriçao!\n");
	else printf("\n\nTotal de ocorrencias do(a) participante: %d\n", total_participant_occurrence);
}

//pesquisa pelo nome e imprime todas as ocorrencias do participante
void search_by_name(char *name){
	int i, j;
	int total_participant_occurrence=0;

	for(i=0;i<li.amount;i++){
		j = strcmp(li.list[i].name, name);
		if(j == 0){
			print_one_occurrence(i);
			total_participant_occurrence++;
		}
	}
	if (total_participant_occurrence==0) printf("\nNão foram encontradas ocorrencias para o nome\n");
	else printf("\n\nTotal de ocorrencias do(a) participante: %d\n", total_participant_occurrence);
}

//pesquisa pela data e imprime todas as ocorrencias em ordem alfabetica dos nomes dos participantes
// como o mes e o ano se repetem, apenas o dia será utilizado para a busca
void search_by_date(char day_c[]){

	Occurrence secondary= alphabetical_order(secondary);

	int i,j;
	int days, day, total_occurrences_date=0;

	day=atoi(day_c);

	for(i=0; i<li.amount;i++){
		days = atoi(li.list[i].date);
		if(days == day){
			print_one_occurrence(i);
			total_occurrences_date++;
		}
	}

	if(total_occurrences_date==0) printf("\nNão foram encontradas ocorrencias para a data!\n");
	else printf("\n\nTotal de ocorrencias da data: %d\n",total_occurrences_date);
}

//pesquisa pela data e turno e imprime todas as ocorrencias em ordem alfabetica dos nomes dos participantes
void search_by_date_shift(char day_c[], int shift){

	int i,j,k=0;
	int hour, days, day, total_occurrences_date=0;
	day=atoi(day_c);

	char hour_c[9]; //variavel hora com espaço inicial

	Occurrence secondary= alphabetical_order(secondary);

	for(i=0; i<li.amount; i++){
		days= atoi(li.list[i].date);

		if(days == day){
			hour=atoi(li.list[i].hour);

			if(shift==1 && (hour >= 06 && hour <= 12)){
				print_one_occurrence(i);
				total_occurrences_date++;

			}else if(shift == 2 && (hour > 12 && hour < 18)){
				print_one_occurrence(i);
				total_occurrences_date++;

			}else if(shift == 3 && (hour >= 18 && hour <= 22)){
				print_one_occurrence(i);
				total_occurrences_date++;
			}
		}

	}
	if (total_occurrences_date==0) printf("\nNão foram encontradas ocorrencias para a data com esse turno!\n");
	else printf("\nTotal de ocorrencias da data e turno: %d\n",total_occurrences_date);
}
