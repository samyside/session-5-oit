#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>

#define ERROR_FILE_OPEN -3
#define FILENAME "output.db"
#define COUNT_BYTES 256

//	Подсчет всех байтов в файле
int fsize(FILE *file) {
	fseek(file, 0L, SEEK_END);
	int size = ftell(file);
	rewind(file);
	return size;
}

FILE* open_file(const char *filename) {
	FILE *file = NULL;
	char path[80] = "Arh02/";
	printf("open_file();01\n");
	strcat(path, filename);
	printf("path = %s\n", path);

	file = fopen(path, "wb+");
	if (file == NULL) {
		printf("Error in open_file();\n\tCouldn't open file: '%s'\n", filename);
		exit(ERROR_FILE_OPEN);
	}
	fprintf(file, "%s\n", filename);

	// Запись размера файла во вторую строку
	// int size = fsize(file);
	// fprintf(file, "%d\n", size);

	return file;
}

// Запись в бинарный файл случайные значения
void fill_random(FILE * file, const int count) {
	unsigned char c = 0;
	if (file == NULL) {
		file = fopen(FILENAME, "wb+");
	}
	for (int i = 0; i < count; ++i) {
		c = rand() % 100;
		fwrite(&c, sizeof(char), 1, file);
	}
	fclose(file);
}

double get_frequency_byte(int byte, const int total_bytes) {
	if (total_bytes == 0) {
		printf("Error int get_frequency_byte();\n\tDivision by zero\n");
		exit(-1);
	}
	return ((double)byte / (double)total_bytes) * 100;
}

//	Вывод всех элементов массива
void show_int_array(FILE *file_output, int * array, const int count, const int total_bytes) {
	double frequency = 0.0f;
	for (int i = 0; i < count; ++i) {
		// printf("%d\t%d\n", i, array[i]);
		frequency = get_frequency_byte(array[i], total_bytes);
		printf("%d\t%2.17f\n", i, frequency);
		fprintf(file_output, "%d\t%2.17f\n", i, frequency);
	}
	fprintf(file_output, "\n");
}

//	Чтение и вывод бинарного значения из файла
void frequency_bytes(FILE * file, int * array_bytes) {
	int symbol = 0;
	do {
		symbol = getc(file);
		array_bytes[symbol]++;
	} while(symbol != EOF);
}

void research(const char *fname_research, const char *fname_report) {
	char *path_research = 0;
	strcat(path_research, fname_research);
	printf("path_research = %s\n", path_research);

	FILE *file_report = NULL;
	FILE *file_research = NULL;
	printf("research();\n");
	// Инициализация массива и заполнение нулями
	int array_bytes[COUNT_BYTES] = {[0 ... 255] = 0};
	
	char path[80] = "Arh02/";
	strcat(path, fname_report);
	file_report = open_file(fname_report);
	file_research = fopen(fname_research, "ab+");
	if (file_research == NULL) {
		printf("Error in research();\n\tFile couldn't open: \n");
		exit(ERROR_FILE_OPEN);
	}

	int total_bytes = fsize(file_research);
	char temp_symbol = getc(file_research);
	printf("temp_symbol = %c\n", temp_symbol);
	printf("array_bytes = %d\n", *array_bytes);

	frequency_bytes(file_research, array_bytes);
	show_int_array(file_report, array_bytes, COUNT_BYTES, total_bytes);

	fclose(file_research);
	fclose(file_report);
}

int main(int argc, char const *argv[]) {
	printf("Program has started...\n");

	research("Text02.docx", "Docx02.tab");
	// Вывод массива

	// Открыть файл как бинарный
	// Считать количество байт в массив
	// 1) Имя файла. Tip: константа
	// 2) all_bytes = Получить кол-во байт в файле
	// 
	// 4) Вычислить частотность каждого байта в файле
	// H = array[i] / all_bytes * 100
	// 6) Вычислить величину энтропии
	// ???
	// Создать отчет по обработанному файлу (ext02.tab)
	// Создать новый файл и записать в него все полученные данные

	printf("Program finished...\n");
	return 0;
}
