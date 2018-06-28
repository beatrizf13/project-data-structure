typedef struct{
	char date[11];
	char hour[11];
	int registration_num;
	char name[60];
}Occurrence;

typedef struct{
	Occurrence list[999999]; //quantidade maxima de ocorrências aceitada pelo programa
	int amount;
}List;

List li;

//Prototipos
int createList();

void print_occurrences();
void print_occurrences_effective(Occurrence);
void print_one_occurrence(int position);
void clean_screen();

Occurrence alphabetical_order (Occurrence);
Occurrence ascending_order_register(Occurrence);

void sort_by_alphabetifal_order(Occurrence);
void sort_by_numerical_order(Occurrence);
void sort_by_numerical_date(Occurrence);

void search_by_date(char[]);
void search_by_registration(int);
void search_by_date_shift(char [], int);
void search_by_name(char*);
