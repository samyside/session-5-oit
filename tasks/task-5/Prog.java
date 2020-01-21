import java.io.*;
import java.util.Scanner;

public class Prog {
	public static void main(String[] args) throws Exception {
		final char[] ALPHABET = new String("АБВГДЕЁЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯабвгдеёжзийклмнопрстуфхцчшщъыьэюя").toCharArray();
		final char[] PASS_KEY = new String("множитель").toCharArray();
		FileReader fr = new FileReader("input.txt");
		FileWriter fw = new FileWriter("output.txt");
		Scanner scan = new Scanner(fr);

		// Получение цифрового ключа из слова
		int pass_num[] = new int[PASS_KEY.length];
		for (int i=0; i<PASS_KEY.length; i++) {
			for (int j=0; j<ALPHABET.length; j++) {
				if (PASS_KEY[i] == ALPHABET[j]) {
					if (j > 32) pass_num[i] = j - 32;
					else pass_num[i] = j;
				}
			}
		}

		String line;
		String bufferLine;
		char bufferChar = 0;
		// Считывание файла построчно
		while (scan.hasNextLine()) {
			// Считываем следующую строку
			line = scan.nextLine();
			// Перебираем символы из считанной строки
			for (char bufferChar : line) {
				// Проверяем каждый символ на соответствие
				// символу из алфавита
				for (char c : ALPHABET) {
					// Если совпало, добавить в строку для 
					// шифрования
					if (c == bufferChar) {
						char encryptedSymbol = encryptSymbol(bufferChar);
						bufferLine += encryptedSymbol;
					}
				}

				// Запись в файл зашифрованного символа
				fw.write(bufferChar);
			}
		}

		fw.close();
		fr.close();
	}

	// Шифрование исходного символа
	char encryptSymbol(char symbol) {

		return 0;
	}

	String doEncryptLine(String line) {

		return null;
	}
}
