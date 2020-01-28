import java.io.*;
import java.util.Scanner;

public class Prog {
	static final char[] ALPHABET = new String("_АБВГДЕЁЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯабвгдеёжзийклмнопрстуфхцчшщъыьэюя").toCharArray();
	static final char[] PASS_KEY = new String("множитель").toCharArray();
	public static void main(String[] args) throws Exception {
		FileReader fr = new FileReader("input.txt");
		FileWriter fw = new FileWriter("output.txt");
		Scanner scan = new Scanner(fr);

		// Получение цифрового ключа из слова
		int pass_num[] = new int[PASS_KEY.length];
		for (int i=0; i<PASS_KEY.length; i++) {
			for (int j=0; j<ALPHABET.length; j++) {
				if (PASS_KEY[i] == ALPHABET[j]) {
					if (j > 33) pass_num[i] = j - 33;
					else pass_num[i] = j;
				}
			}
		}

		// Вывести на экран цифровой ключ
		for (int key : pass_num) {
			System.out.print(key + "_");
		}

		int currentStepKey = pass_num[0];
		String line;
		String bufferLine = null;
		// Считывание файла построчно
		while (scan.hasNextLine()) {
			// Считываем следующую строку
			line = scan.nextLine();
			// Перебираем символы из считанной строки
			for (char symbolLine : line.toCharArray()) {
				// Проверяем каждый символ на соответствие
				// символу из алфавита
				for (char symbolAlphabet : ALPHABET) {
					// Если совпало, добавить в строку для шифрования
					if (symbolAlphabet == symbolLine) {
						currentStepKey = currentStepKey % PASS_KEY.length;
						char encryptedSymbol = encryptSymbol(symbolLine, pass_num[currentStepKey]);
						bufferLine += encryptedSymbol;
					}
				}
				// Запись в файл зашифрованного символа
				fw.write(symbolLine);
			}
		}

		fw.close();
		fr.close();
	}

	// Шифрование исходного символа
	static char encryptSymbol(char symbol, int move) {


		return 0;
	}

	static String doEncryptLine(String line) {

		return null;
	}
}
