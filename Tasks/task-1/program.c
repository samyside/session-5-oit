#include <stdio.h>
#include <conio.h>
#include <stdlib.h>

#define ERROR_FILE_OPEN -3

int main(int argc, char const *argv[]) {
	const char* FILE_BMP = "Arh02/Pic02.bmp";
	const char* FILE_JPG = "Arh02/Pic02.jpg";
	const char* FILE_DOC = "Arh02/Text02.doc";
	const char* FILE_DOCX= "Arh02/Text02.docx";
	const char* FILE_TXT = "Arh02/Text02.txt";

	printf("The program has started...\n");

	FILE *file_report = NULL;
	int number_in;
	int number_out = -1;
	char * filename = "output.db";
	file_report = fopen(filename, "wb+");

	printf("number_in = ");
	scanf("%d", &number_in);

	// Запись бинарного значения в файл
	fwrite(&number_in, sizeof(int), 1, file_report);
	fclose(file_report);

	// Чтение и вывод бинарного значения из файла
	file_report = fopen(filename, "rb");
	fread(&number_out, sizeof(int), 1, file_report);
	printf("number_out = %d", number_out);

	fclose(file_report);

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