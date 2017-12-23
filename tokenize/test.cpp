#include <iostream>
#include <fstream>
#include <string>
#include <iostream>
#include <chrono>
#include <thread>
#include <cwchar>
#include <clocale>
#include "Tokenizer.h"

using namespace std;
typedef std::chrono::high_resolution_clock Clock;

int main(int argc, char* argv[]) {
	if (argc != 2) {
		cout << "Usage: " << argv[0] << " <test_text>" << endl;
	}
	Tokenizer tokenizer;
	tokenizer.LoadDefaultConfig();
	string tokenized_line = tokenizer.TokenizeAndJuxtapose(argv[1], true, true);
	cout <<  "[" << tokenized_line << "]" << endl;
	return 0;
}
