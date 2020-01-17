	// std::cin.ignore(32767, '\n'); // игнорируем до 32767 символов до тех пор, пока \n не будет удалён из потока
#include <iostream>
#include <fstream>

using namespace std;

int main(int argc, char const *argv[]) {
	std::string new_str = "Привет. этот текст надо зашифровать";
	ifstream file_arch("output.txt");

	string str;
	if(file_arch.is_open()) {
		while(getline(file_arch, str)) {
			cout << str[0] << endl;
		}
	} else cout << "Couldn't open file" << endl;

	file_arch.close();

	return 0;
}