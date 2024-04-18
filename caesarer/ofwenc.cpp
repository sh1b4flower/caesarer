#include "ofwenc.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <tuple>

using namespace std;

#define UTF8_BOMSIZE 3
static unsigned char UTF8_BOM[UTF8_BOMSIZE] = { 0xef, 0xbb, 0xbf };

static void  string_to_bytes(std::string str, unsigned char* binaries, long long int size);

static bool cmp_binaries(unsigned char* first, unsigned char* second, long long int size);

static void  string_to_bytes(std::string str, unsigned char* binaries, long long int size) {
	for (int i = 0; i < size; i++) {
		ostringstream oss;
		oss << hex << +str[i];
		string signed_str_hex = oss.str();
		string unsigned_str_hex;
		if (signed_str_hex.length() > 5) {
			unsigned_str_hex = signed_str_hex.substr(6, 2);
		}
		else {
			unsigned_str_hex = signed_str_hex;
		}
		int binary;
		istringstream iss(unsigned_str_hex);
		iss >> hex >> binary;

		binaries[i] = binary;
	}
}

static bool cmp_binaries(unsigned char* first, unsigned char* second, long long int size) {
	if (!(sizeof(first) == sizeof(second))) cerr << "Error" << endl;
	for (int i = 0; i < size; i++) {
		if (!(first[i] == second[i])) return false;
	}
	return true;
}

//Whether there is BOM in the file
static tuple<bool, string> check_utf8_bom(string text, bool bom_eraser = true) {
	
	string bom_check = text.substr(0, UTF8_BOMSIZE);
	long long int size = bom_check.length();
	unsigned char bom_binaries[UTF8_BOMSIZE];
	string_to_bytes(bom_check, bom_binaries, size);
	if (cmp_binaries(UTF8_BOM, bom_binaries, UTF8_BOMSIZE)) {
		return { true, text.substr(UTF8_BOMSIZE)};
	}
	else return { false, text };
	
}

//Open the file
string Ofwenc::open_utf8() {
	ifstream ifs;
	if (encoding != 1) {
		cerr << "Error 141 : The file must be UTF-8." << endl;
		exit(0);
	}
	ifs.open(filename, ios::binary);
	if (!ifs) {
		cerr << "Error 110 : Such file '" << filename << "' not found" << endl;
		exit(0);
	}
	setlocale(LC_ALL, ".UTF8");
	string filetext;
	ostringstream oss;
	oss << ifs.rdbuf();
	filetext = oss.str();
	filetext = get<1>(check_utf8_bom(filetext));
	ifs.close();
	return filetext;
}