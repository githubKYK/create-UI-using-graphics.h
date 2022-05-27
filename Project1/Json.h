#pragma once
#include <string>

using namespace std;

class Json {
public:

	Json();

	static string* split(const char&, string);

	void set(const string&);

	string getValue();

private:
	string json;
};

Json::Json() {
	json = {};
}

string* Json::split(const char& delim, string str) {
	int size = 1;
	for (size_t i = 0; i < str.length(); i++)
		if (str[i] == delim)
			size++;
	string* result = new string[size];
	for (size_t i = 0; i < size; i++) {
		result[i] = str.substr(0, str.find(delim));
		str.erase(0, str.find(delim) + 1);
	}

	return result;
}

void Json::set(const string& str) {
	json = str;
}

string Json::getValue() {
	return json;
}
