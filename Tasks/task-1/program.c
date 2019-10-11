#include <stdio.h>
#include <conio.h>
#include <stdlib.h>

#define ERROR_FILE_OPEN -3
#define FILENAME "output.db"
#define COUNT_BYTES 256
#define FILE_BMP "Arh02/Pic02.bpm"
#define FILE_JPG "Arh02/Pic02.jpg"
#define FILE_DOC "Arh02/Text02.doc"
#define FILE_DOCX "Arh02/Text02.docx"
#define FILE_TXT "Arh02/Text02.txt"

//	Подсчет всех байтов в файле
// 	Запись числа в файл отчета
int fsize(FILE *file) {
	fseek(file, 0L, SEEK_END);
	int size = ftell(file);
	rewind(file);
	return size;
}

FILE* open_file(const char *filename) {
	FILE *file = NULL;
	file = fopen(filename, "wb+");
	if (file == NULL) {
		printf("Error! Couldn't open file: '%s'\n", filename);
		exit(ERROR_FILE_OPEN);
	}
	fprintf(file, "%s\n", filename);

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
		printf("Error! Division by zero\n");
		exit(-1);
	}
	return ((double)byte / (double)total_bytes) * 100;
}

//	Вывод всех элементов массива
void show_int_array(int * array, const int count, const int total_bytes) {
	double frequency = 0.0f;
	for (int i = 0; i < count; ++i) {
		// printf("%d\t%d\n", i, array[i]);
		frequency = get_frequency_byte(array[i], total_bytes);
		printf("%d\t%2.17f\n", i, frequency);
	}
}

//	Чтение и вывод бинарного значения из файла
void frequency_bytes(FILE * file, int * array_bytes) {
	int symbol = 0;
	do {
		symbol = getc(file);
		array_bytes[symbol]++;
	} while(symbol != EOF);
}

int main(int argc, char const *argv[]) {
	printf("Program has started...\n");

	FILE *file_report = NULL;
	file_report = fopen(FILE_DOCX, "ab+");
	// Инициализация массива и заполнение нулями
	int array_bytes[COUNT_BYTES] = {[0 ... 255] = 0};

	FILE *file_output = NULL;
	file_output = open_file("output.db");
	int size = fsize(file_report);

	// fwrite(file_output, "%d\n", &temp_bytes);
	fprintf(file_output, "%d\n\n", size);
	frequency_bytes(file_report, array_bytes);
	printf("test\n");

	fclose(file_output);
	// Вывод массива
	// show_int_array(array_bytes, COUNT_BYTES, total_bytes);

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
