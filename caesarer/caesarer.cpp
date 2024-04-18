// caesarer.cpp

/**
Copyright 2024 sh1b4flower

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the “Software”), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED “AS IS”, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

**/


#include "caesarer.h"
#include "ofwenc.h"
#include <cassert>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;

#define INF 1000000001

static vector<string> argv_to_vector(int argc, char* argv[]);

static void caesarer_help();

static void caesarer_version();

static string open_file(string file_name, string encoding);

static vector<string> argv_to_vector(int argc, char* argv[]) {
	vector<string> cmdline(argc+1);
	for (int i = 0; i < argc; i++) {
		cmdline[i] = argv[i];
	}
	return cmdline;
}

static void caesarer_help() {
	string caesarer_helper =
		"Welcome to caesarer1.0 !\n\n"

		"This system ciphers with caesar cipher when you need to do it.\n\n"

		"What is Caesar cipher(ROT13)? - Caesar cipher is one of the classic ciphers.\n"

		"Long long ago, in ancient Rome, Gaius Iulius Caesar developed caesar cipher. "

		"He shifted the each letter with key that indicates the number of times to shift. "

		"It is Caesar cipher. " "He needed to convey secret message to hide information."

		"Like him, Caesarer ciphers with caesar cipher.\n"

		"Now, there are some questions that want ctfers solve with it. "

		"In cryptography, we need to decrypt it with ciphertext-only attack."

		"This system may be contibute to solve such questions.\n\n"

		"suppl. ) ROT13 is a special name that indicates caesar cipher with a key, 13.\n\n"

		"<Options>\n"

		"-h  --help : Use the helper\n"
		"-v  --version : Show the version of Caesarer\n"
		"-k  --key : Input the number of times to shift. Usually, the key is 13.\n"
		"-f  --file : Input the plain text written in the file. Usually plain text is an empty.\n"
		"-o  --output: Write the cipher text to the file. \n"
		"--all : Show the cipher text encrypted with the key, 0-25\n"

		"<Sample>\n"
		"caesarer \"my secret message\" --key 13\n"
		"caesarer \"zqc{zxbpxobo_absbilmba_yv_pe1yociltbo}\" --all\n"
		"caesarer -f flag.txt -o answer.txt\n"

		;
	cout << caesarer_helper << endl;
	exit(1);
}

static void caesarer_version() {
	cout << "Caesarer verson 1.0 developed by sh1b4flower" << endl;
}

static string open_file(string file_name,string encoding) {
	Ofwenc file(file_name, encoding);
	string filetext = file.open_utf8();
	return filetext;

}

int main(int argc, char* argv[])
{
	//Input the cleartext, or no answer
	string cleartext = "";

	// Input the key, or cipher with ROT13
	int key = 13; 

	// Whether the user wants to input the file
	bool is_file = false;

	// Whether the system should write the cipher to the file.
	bool is_write = true;

	// Whether the system should output the cipher with 0-26 key.
	bool all = false;

	string file_arg = "";
	string wfile_arg = "";

	string encoding = "UTF-8";

	//command line arguments which are inputed by the user
	vector<string> cmdline(argc); 

	vector<string> flags{
		"-h" ,"--help",
		"-v", "--version",
		"-k", "--key",
		"-f", "--file",
		"-o", "--output",
		"--all",
	};
	vector<int> cmdline_split(argc); // the places that there are option flags
	vector<int> cmdline_flag(argc, INF);

	cmdline_flag[0] = 1;

	//The places of the option flags
	cmdline = argv_to_vector(argc, argv);
	for (int i = 0; i < argc; i++) {
		for (int j = 0; j < flags.size(); j++) {
			if (cmdline[i] == flags.at(j))cmdline_split.push_back(i);
		}
	}

	//Checking option flags which need option arguments
	auto check_option_arguments = [&](int num) -> string{
		if (num + 1 == argc) {
			cerr << "Error 131 : No option arguments." << endl;
			exit(0);
		}
		else if (count(cmdline_split.begin(), cmdline_split.end(), num + 1)) {
			cerr << "Error 131 : No option arguments." << endl;
			exit(0);
		}
		cmdline_flag[num + 1] = 1;
		return cmdline[num + 1];
	};

	//If there are no command line arguments, the system calls caesarer_help()
	if (argc == 1) caesarer_help();
	 
	//If 2nd argument isn't the option flag, it indicates the plain text.
	if (!count(cmdline_split.begin(), cmdline_split.end(), 1)) {
		cleartext = cmdline[1];
		cmdline_flag[1] = 1;
	}

	//Check the option flags
	for (int i = 0; i < cmdline_split.size(); i++) {
		int p = cmdline_split[i];
		string cl = cmdline[p];
		if (cl == "-h" || cl == "--help") {
			caesarer_help();
			break;
		}
		else if (cl == "-v" || cl == "--version") {
			caesarer_version();
			break;
		}
		else if (cl == "-k" || cl == "--key") {
			string option_arg = check_option_arguments(p);
			key = stoi(option_arg);
			cmdline_flag[p] = 1;
		}
		else if (cl == "-f" || cl == "--file") {
			file_arg = check_option_arguments(p);
			is_file = true;
			cmdline_flag[p] = 1;
		}
		else if (cl == "-o" || cl == "--output") {
			wfile_arg = check_option_arguments(p);
			is_write = true;
			cmdline_flag[p] = 1;
		}
		else if (cl == "--all") {
			all = true;
			cmdline_flag[p] = 1;

		}
	}

	//Whether there are invalid options
	for (int i = 0; i < argc; i++) {
		if (cmdline_flag[i] == INF) {
			cerr << "Error 132 : " << cmdline[i] << " is an invalid option" << endl;
			exit(0);
		}
	}

	//Cipher text
	string wfile_text = "";

	//Ciphering
	if (is_file) {
		cleartext = open_file(file_arg, encoding);
	}
	if (!all) {
		Caesarer res(cleartext, key);
		string cipher = res.crypto();
		cout << cipher << endl;
		wfile_text = cipher;
	}
	else {
		for (int i = 0; i <= 25;i++) {
			Caesarer res(cleartext, i);
			string cipher = res.crypto();
			cout << "key:" << i << " " << cipher << endl;
			wfile_text += cipher + "\n";
		}
	}

	if (is_write) {
		ofstream ofile(wfile_arg);
		ofile << wfile_text;
		ofile.close();
	}
	return 0;
}
