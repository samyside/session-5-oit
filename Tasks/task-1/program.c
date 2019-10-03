#include <stdio.h>
#include <conio.h>
#include <stdlib.h>

#define ERROR_FILE_OPEN -3
#define FILENAME "output.db"

void write_in(FILE * file, char c) {
	fwrite(&c, sizeof(char), 1, file);
}

void fill_random(FILE * file, const int count) {
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

int main(int argc, char const *argv[]) {
	printf("The program has started...\n");

	FILE *file_report = NULL;
	file_report = fopen(FILENAME, "wb+");

	// Запись в бинарный файл случайные значения
	// fill_random(file, 150);

	// Чтение и вывод бинарного значения из файла
	
	read_byte();
	
	// Открыть файл как бинарный
	// Считать количество байт в массив
	// 1) Имя файла. Tip: константа
	// 2) Получить кол-во байт в файле
	// Сумма всех значений массива
	// 4) Вычислить частотность байте в файле
	// Частотность = все_байты / элемент_массива
	// 6) Вычислить величину энтропии
	// ???
	// Создать отчет по обработанному файлу (File02.tab)
	// Создать новый файл и записать в него все полученные данные

	return 0;
}