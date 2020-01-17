import java.io.*;
import java.util.Scanner;

public class Prog {
	private static final String KEY = "множитель";

	public static void main(String[] args) throws Exception {
		int N = 66;
		final char ALPHABET[N] = "АБВГДЕЁЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯабвгдеёжзийклмнопрстуфхцчшщъыьэюя".toCharArray();
		FileReader fr = new FileReader("input.txt");
		FileWriter fw = new FileWriter("output.txt");
		Scanner scan = new Scanner(fr);

		char bufferChar = 0;

		// Получение последовательности из ключа
		char arrayChar[] = KEY.toCharArray();
		int keyMove[];
		for (int i=0; i<KEY.length(); i++) {
			for (int j=0; j<N; j++) {
				if (KEY[i] == ALPHABET[j]) {
					keyMove[i] = j;
				}
			}
		}

		// Считывание файла построчно
		String line;
		while(scan.hasNextLine()) {
			line = scan.nextLine();

			for (int i=0; i<line.length(); i++) {
				bufferChar = line.charAt(i);
				bufferChar += 3; // hardcoded value for movement symbol

				// Запись в файл зашифрованного символа
				fw.write(bufferChar);
				System.out.println(bufferChar);
			}
		}

		fw.close();
		fr.close();
	}
}
