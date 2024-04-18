// caesarer.h : 標準のシステム インクルード ファイル用のインクルード ファイル、
// または、プロジェクト専用のインクルード ファイル。

#pragma once

#include <iostream>

#define LEN_ALPHABET 26

// TODO: プログラムに必要な追加ヘッダーをここで参照します。

class Caesarer {
private:
	std::string plaintext;
	int key;
	size_t len_plain;
public:
	Caesarer(std::string plain_arg, int key);
	std::string crypto();

};

inline Caesarer::Caesarer(std::string plain_arg, int key_arg) {
	plaintext = plain_arg;
	key = key_arg;
	len_plain = plaintext.length();
}

inline std::string Caesarer::crypto() {
	std::string cipher;
	for (int i = 0; i < len_plain; i++) {
		char plainchar = plaintext.at(i);
		bool is_alphabet = true;
		bool is_upper = false;
		if (plainchar >= 'A' && plainchar <= 'Z') {
			is_upper = true;
		}
		else if (plainchar >= 'a' && plainchar <= 'z') {
			is_upper = false;
		}
		else {
			is_alphabet = false;
		}
		char first, end;
		if (is_alphabet) {
			switch (is_upper) {
			case true:
				first = 'A'; end = 'Z';
				break;
			case false:
				first = 'a'; end = 'z';
				break;
			}
			int plain_alphanum = plainchar - first;
			int crypto_alphanum = (plain_alphanum + key) % LEN_ALPHABET;
			cipher += (first + crypto_alphanum);
		}
		else {
			cipher += plainchar;
		}
	}
	return cipher;
}

