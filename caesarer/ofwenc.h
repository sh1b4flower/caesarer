// Ofwenc v1.0 developed by sh1b4flower

#include <iostream>
#include <fstream>
#include <map>
#include <utility>
#include <string>
#include <sstream>
#include <vector>

#define UTF_8 "UTF-8"

// encoding
// In this version, the system usually deals with UTF-8 file.
typedef std::map<std::string, int> encoding_num;

class Ofwenc {
private:
	std::string filename;
	int encoding;
public:
	Ofwenc(std::string fn_arg, std::string enc_arg);
	std::string open_utf8();
	std::string open_utf16();
	void write_utf8(std::string wtext);
};

// Managing the file detail
inline Ofwenc::Ofwenc(std::string fn_arg, std::string enc_arg) {
	filename = fn_arg;
	encoding_num enc_list;
	enc_list[UTF_8] = 1;
	if (enc_arg == UTF_8) {
		encoding = enc_list[enc_arg];
	}
	else encoding = 0;
}




