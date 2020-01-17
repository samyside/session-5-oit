#include <stdlib.h>
#include <stdio.h>

#define KEY_PASS "ГРИБЫ" 

FILE* create_file(char *filename) {
	FILE *file = NULL;
	file = fopen(filename, "w");
	if(file == NULL) {
		printf("Error: in create_file()! Couldn't open file\n");
		exit(-1);
	}
}

FILE* open_file(char *filename) {
	FILE *file = NULL;
	file = fopen(filename, "r+");
	if(file == NULL) {
		printf("Error: in open_file()! Couldn't open file\n");
		exit(-1);
	}
	return file;
}

void write_file_array(FILE *file, char *array) {

}

void write_file_symbol(FILE *file, char symbol) {
	fprintf(file, "%c", symbol);
}

int main(int argc, char const *argv[]) {
	printf("Program started.\n");

	FILE *file_source = open_file("input.txt");
	FILE *file_crypted = create_file("output.txt");
	char str_table[132] = "АБВГДЕЁЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯабвгдеёжзийклмнопрстуфхцчшщъыьэюя";

	printf("%d\t%c\n",  str_table[6], str_table[6]);
	printf("%s\n", KEY_PASS);

	int symbol = 0, i = 0;
	while((symbol = getc(file_source)) != EOF) {
		for(int i=0; i<66; i++) {
			printf("%d\t%d\n", str_table[i], symbol);
			if(str_table[i] == symbol) printf("%c", str_table[i]);
		}

		symbol++;
		i++;
	}

	return 0;
}