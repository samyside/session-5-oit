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

void write_char(FILE * file, char c) {
	fwrite(&c, sizeof(char), 1, file);
}

double getFrequencyByte(int byte, const int total_bytes) {
	return ((double)byte / (double)total_bytes) * 100;
}

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

unsigned char read_byte(FILE * file) {
	unsigned char c = 0;

	if (file == NULL) {
		printf("Error! Couldn't open file. Program will be closed.\n");
		exit(ERROR_FILE_OPEN);
	}
	fread(&c, sizeof(char), 1, file);

	return c;
}

size_t length_int(int * array) {
	int * temp_array = array;
	size_t length = sizeof(temp_array) / sizeof(temp_array[0]);
	return length;
}

void show_int_array(int * array, const int count, const int total_bytes) {
	double frequency = 0.0f;
	for (int i = 0; i < count; ++i) {
		// printf("%d\t%d\n", i, array[i]);
		frequency = getFrequencyByte(array[i], total_bytes);
		printf("%d\t%2.17f\n", i, frequency);
	}
}

int main(int argc, char const *argv[]) {
	printf("The program has started...\n");

	FILE *file_report = NULL;

	// Инициализация массива и заполнение нулями
	int array_bytes[COUNT_BYTES] = {[0 ... 255] = 0};
	file_report = fopen(FILE_DOCX, "ab+");

	// Запись в бинарный файл случайные значения
	// fill_random(file_report, 150);

	// Чтение и вывод бинарного значения из файла
	int sym = 0, total_bytes = -1;
	do {
		sym = getc(file_report);
		array_bytes[sym]++;
		total_bytes++;
		
		// printf("[%d]\t= %d\n", count_sym++, sym);
	} while(sym != EOF);

	// Вывод массива
	show_int_array(array_bytes, COUNT_BYTES, total_bytes);

	printf("total_bytes = %d\n", total_bytes);
	printf("array_bytes[0] = %d\n", array_bytes[0]);

	double frequency = getFrequencyByte(array_bytes[0], total_bytes);
	printf("frequency = %5.16f\n", frequency);
	
	// Открыть файл как бинарный
	// Считать количество байт в массив
	// 1) Имя файла. Tip: константа
	// 2) all_bytes = Получить кол-во байт в файле
	// 
	// 4) Вычислить частотность каждого байта в файле
	// H = array[i] / all_bytes * 100
	// 6) Вычислить величину энтропии
	// ???
	// Создать отчет по обработанному файлу (File02.tab)
	// Создать новый файл и записать в него все полученные данные

	return 0;
}