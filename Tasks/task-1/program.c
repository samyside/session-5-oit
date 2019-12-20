#include <stdio.h>
//#include <conio.h>
#include <stdlib.h>
#include <string.h>
#include "math.h"

#define DIVISION_BY_ZERO -2
#define ERROR_FILE_OPEN -3
#define COUNT_BYTES 256

double get_entropy(double);

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

// Сортировака массива методом пузырька
void bubble_sort(double *array) {
	int i, j;
		for (i = 0; i < COUNT_BYTES; ++i) {
			for (j = COUNT_BYTES - 1; j > i; --j) {
				if (array[j] < array[j-1]) {
				double t = array[j - 1];
				array[j - 1] = array[j];
				array[j] = t;
			}
		}
	}
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
void show_int_array(FILE *file_output, int *array_b, double *array_f, const int total_bytes, double *entropy) {
	double frequency = 0.0f;
	for (int i = 0; i < COUNT_BYTES; ++i) {
		// Сохранение частотности текущего байта
		// во временную переменную
		frequency = get_frequency_byte(array_b[i], total_bytes);
		
		// Сохранение частотности текущего байта
		// в общий массив для дальнейшего анализа
		array_f[i] = frequency;
		printf("array_f[%d]\t= %3.17f\n", i, array_f[i]);
		
		// Вычисление энтропии по формуле Шеннона
		// при этом каждый раз (всего 256) значение
		// будет прибавляться
		*entropy += get_entropy(frequency);
	}
	fprintf(file_output, "\n");
}

//	Чтение и вывод бинарного значения из файла
void frequency_bytes(FILE *file, int *array) {
	int symbol = 0;
	while((symbol = getc(file)) != EOF) {
		array[symbol]++;
	}
}

double get_entropy(double frequency) {
	double temp_freq = 0.0f;
	if(frequency == 0) {
		return 0;
	} else if(frequency < 0) {
		printf("frequency < 0. %f\n", frequency);
		return 0;
	} else {
		temp_freq = -(frequency * log2(frequency));
		return temp_freq;
	}
}

void write_in_report(FILE *file, double *array) {
	for(int i=0; i < COUNT_BYTES; ++i) {
		fprintf(file, "%d\t%2.17f\n", i, array[i]);
	}
}

// Основная функция исследования
void research(const char *fname_research, const char *fname_report) {
	char path_research[20] = "Arh02/";
	strcat(path_research, fname_research);

	FILE *file_report = NULL;
	FILE *file_research = NULL;
	// Инициализация массива и заполнение нулями
	// Доступно в компиляторе GCC в стандарте C11
	int array_bytes[COUNT_BYTES] = {[0 ... 255] = 0};
	double array_frequecies[COUNT_BYTES] = {[0 ... 255] = 0.0f};
	
	file_report = open_file(fname_report);
	file_research = fopen(path_research, "ab+");

	// Запись размера файла
	int size = fsize(file_research);
	fprintf(file_report, "%d\n\n", size);

	if (file_research == NULL) {
		printf("Error in research();\n\tFile couldn't open: \n");
		exit(ERROR_FILE_OPEN);
	}
	int total_bytes = fsize(file_research);
	char temp_symbol = getc(file_research);

	// write entropy result
	double entropy = 0.0f;
	double *ptr_entropy;
	ptr_entropy = &entropy;

	frequency_bytes(file_research, array_bytes);
	show_int_array(file_report, array_bytes, array_frequecies, total_bytes, ptr_entropy);
	for(int i=0; i < 256; ++i) {
		printf("array_frequecies[%d] : %f\n", i, array_frequecies[i]);
	}

	bubble_sort(array_frequecies);
	write_in_report(file_report, array_frequecies);

	// Запись значения энтропии в файл отчета
	fprintf(file_report, "%f\n", entropy);

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
