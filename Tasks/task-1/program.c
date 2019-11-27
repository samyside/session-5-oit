#include <stdio.h>
//#include <conio.h>
#include <stdlib.h>
#include <string.h>

#define DIVISION_BY_ZERO -2
#define ERROR_FILE_OPEN -3
#define COUNT_BYTES 256

//	Подсчет всех байтов в файле
int fsize(FILE *file) {
	const long int current_position = ftell(file);
	fseek(file, 0L, SEEK_END);
	int size = ftell(file);
	fseek(file, current_position, SEEK_SET);
	return size;
}

//	Открыть файл отчёта
FILE* open_file(const char *filename) {
	FILE *file = NULL;
	char path[80] = "Arh02/";
	strcat(path, filename);
	printf("path_report = %s\n", path);

	file = fopen(path, "wb+");
	if (file == NULL) {
		printf("Error in open_file();\n\tCouldn't open file: '%s'\n", filename);
		exit(ERROR_FILE_OPEN);
	}
	fprintf(file, "%s\n", filename);

	return file;
}

//	Вычисляет значение частоты байта в файле
double get_frequency_byte(int byte, const int total_bytes) {
	if (total_bytes == 0) {
		printf("Error int get_frequency_byte();\n\tDivision by zero\n");
		exit(DIVISION_BY_ZERO);
	}
	return ((double)byte / (double)total_bytes) * 100;
}

//	Вывод всех элементов массива
void show_int_array(FILE *file_output, int * array, const int count, const int total_bytes) {
	double frequency = 0.0f;
	for (int i = 0; i < count; ++i) {
		frequency = get_frequency_byte(array[i], total_bytes);
		// Вывод полученной частоты байта в консоль
		// printf("%d\t%2.17f\n", i, frequency);
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

// Основная функция исследования
void research(const char *fname_research, const char *fname_report) {
	char path_research[40] = "Arh02/";
	strcat(path_research, fname_research);

	FILE *file_report = NULL;
	FILE *file_research = NULL;
	// Инициализация массива и заполнение нулями
	// Доступно в компиляторе GCC в стандарте C11
	int array_bytes[COUNT_BYTES] = {[0 ... 255] = 0};
	
	file_report = open_file(fname_report);
	file_research = fopen(path_research, "ab+");

	//debug segmentation 
	int testint = 234;
	int *testpoint;
	testpoint = &testint;

	// Запись размера файла
	int size = fsize(file_research);
	fprintf(file_report, "%d\n\n", size);

	if (file_research == NULL) {
		printf("Error in research();\n\tFile couldn't open: \n");
		exit(ERROR_FILE_OPEN);
	}

	int total_bytes = fsize(file_research);
	char temp_symbol = getc(file_research);

	frequency_bytes(file_research, array_bytes);
	show_int_array(file_report, array_bytes, COUNT_BYTES, total_bytes);

	fclose(file_research);
	fclose(file_report);
}

int main(int argc, char const *argv[]) {
	printf("Program has started...\n");

	research("Pic02.bmp", "Bmp02.tab");
	research("Pic02.jpg", "Jpg02.tab");
	research("Text02.doc", "Doc02.tab");
	research("Text02.docx", "Docx02.tab");
	research("Text02.txt", "Txt02.tab");

	printf("Program finished...\n");
	return 0;
}
