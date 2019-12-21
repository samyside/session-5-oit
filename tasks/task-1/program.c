#include <stdio.h>
#include <math.h>
#include <stdlib.h>

void research(char*, char*);
void write_header(FILE*, char*);
void write_fsize(FILE*, int);
void write_frequency();
void write_entropy(FILE*, float);
FILE* open_file(char*);
FILE* create_file(char*);
void save_array_frequency(FILE*, float*, const int);
float get_entropy(float*);
int get_total_bytes(FILE*);

int main(int argc, char const *argv[]) {
	research("arh02/Pic02.bmp", "arh02/bmp02.tab");
	research("arh02/Pic02.jpg", "arh02/jpg02.tab");
	research("arh02/Text02.doc", "arh02/doc02.tab");
	research("arh02/Text02.docx", "arh02/docx02.tab");
	research("arh02/Text02.txt", "arh02/txt02.tab");
	
	return 0;
}

// Вызов функции исследования
void research(char *filename_in, char *filename_out) {
	FILE *file_research = open_file(filename_in);
	FILE *file_report = create_file(filename_out);
	float array_frequency[256] = {[0 ... 255] = 0};
	float entropy = 0.0f;

	write_header(file_report, filename_in);
	const int total_bytes = get_total_bytes(file_research);
	write_fsize(file_report, total_bytes);

	save_array_frequency(file_research, array_frequency, total_bytes);
	// TODO sort array_frequency[]
	write_frequency(file_report, array_frequency);

	entropy = get_entropy(array_frequency);
	write_entropy(file_report, entropy);

	fclose(file_research);
	fclose(file_report);
}

// Запись в указанный файл имя исследуемого файла
void write_header(FILE *file, char *filename) {
	fprintf(file, "%s\n", filename);
}

// Запись в указанный файл размер исследуемого файла
void write_fsize(FILE *file, const int total_bytes) {
	fprintf(file, "%d\n\n", total_bytes);
}

// Вычисление количества байтов в файле
// И перемещение курсора в позицию до вызова функции
int get_total_bytes(FILE *file) {
	const long int current_position = ftell(file);
	fseek(file, 0L, SEEK_END);
	int size = ftell(file);
	fseek(file, current_position, SEEK_SET);
	return size;
}

// Вычисление и сохранение массива частотности байтов
// исследуемого файла
void save_array_frequency(FILE *file, float *array_frequency, const int total_bytes) {
	// Зполнение массива нулями. Стандарт C11
	int array_bytes[256] = {[0 ... 255] = 0};
	int symbol = 0;

	// Считывя файл, записываем количество каждого байта в файле
	while((symbol = getc(file)) != EOF) {
		array_bytes[symbol]++;
	}

	for(int i=0; i < 256; ++i) {
		array_frequency[i] = (float)array_bytes[i] / (float) total_bytes;
	}
}

// Запись массива частотности в указанный файл
void write_frequency(FILE *file, float *array_frequency) {
	for(int i=0; i < 256; ++i) {
		fprintf(file, "%d\t%f\n", i, array_frequency[i]);
	}
}

// Вычисление энтропии на основе частоты байтов
float get_entropy(float *array_frequency) {
	float entropy = 0.0f;
	for(int i=0; i < 256; ++i) {
		entropy += array_frequency[i] * log2(array_frequency[i]);
	}
	return -entropy;
}

// Запись значения энтропии в указанный файл
void write_entropy(FILE *file, float entropy) {
	fprintf(file, "\n%f\n", entropy);
}

// Открытие файла как бинарный для чтения
FILE* open_file(char *filename) {
	FILE *file = NULL;
	file = fopen(filename, "rb");
	if(file == NULL) {
		printf("Error! Couldn't open file: %s\n", filename);
		exit(-1);
	}
	return file;
}

// Открытие (либо перезапись и открытие) файла как бинарный для чтения 
FILE* create_file(char *filename) {
	FILE *file = NULL;
	file = fopen(filename, "wb+");
	if(file == NULL) {
		printf("Error! Couldn't open file: %s\n", filename);
		exit(-1);
	}
	return file;
}