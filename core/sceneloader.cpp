#include "sceneloader.h"

#include <cstdio>
#include <exception>
#include <iostream>
#include <set>
#include <cstring>

const char* blank=" \t\r\n";
std::set<char> S(blank,blank+strlen(blank));

std::string trim(std::string s) 
{
	if (s.empty()) {
		return s;
	}
	int posA = 0, posB = s.length();
	while (posA < posB) {
		if (S.find(s[posA]) == S.end())
			break;
		posA ++;
	}
	while (posA < posB) {
		if (S.find(s[posB-1]) == S.end())
			break;
		posB --;
	}
	s = s.substr(posA,posB-posA);
	return s;
}

SceneLoader::SceneLoader(const char* filename) : std::stringstream() {
	std::ifstream handler;
	handler = std::ifstream(filename);
	std::istreambuf_iterator<char>beg(handler), end;
	txt = std::string(beg, end);
	handler.close();
}


void SceneLoader::prepare() {
	std::stringstream ss;
	std::string last_item = "$";
	std::string zipped_txt = "";
	std::string str;
	mapper.clear();
	ss << txt;
	int level = 0;
	while (std::getline(ss,str)) {
		str = trim(str);
		if (str == "\0")
			continue;
		if (str == "{")
			level ++;
		if (str == "}") {
			level --;
		}
		if (level == 1) {
			if (str == "{") {
				//DO NOTING
			}else if (str == "}") {
				mapper[last_item] = zipped_txt;
				zipped_txt = "";
			}else {
				size_t pos = str.find_first_of('=');
				last_item = trim(str.substr(0,pos));
				zipped_txt = trim(str.substr(pos+1,str.length()-pos-1));
				mapper[last_item] = zipped_txt;
			}
		}
	}
}
SceneLoader& SceneLoader::operator()(const char* item_name) {
	this->clear();
	if (mapper.find(trim(item_name)) == mapper.end()) {
		throw std::runtime_error("The item "+std::string(item_name)+" is not found");
		return (*this);
	}
	(*this) << mapper[item_name];
	return *this;
}
