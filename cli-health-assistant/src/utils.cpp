#include "utils.h"
#include <algorithm>
#include<cctype>
#include <limits>
#include <iostream>
#include <vector>
#include <sstream>
#include <string>

std::string trim(const std::string & str){
    auto start = str.begin();
    while (start != str.end() && std::isspace(*start)) ++start;
    auto end = str.end();
    do { --end; } while (std::distance(start, end) > 0 && std::isspace(*end));
    return std::string(start, end + 1);
    
}

void clearInput(){
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}
//converts a string to lowercase
std::string tolower(const std::string & str){
    std::string result = str;
    std::transform(result.begin(), result.end(), result.begin(),
                   [](unsigned char c){ return std::tolower(c);});

   return result;
}

//checks if a string is a number
bool isNumber(const std::string & str){
    return !str.empty() && std::all_of(str.begin(), str.end(), ::isdigit);
}

//splits a string by delimiter
std::vector<std::string> split(const std::string& str, char delimiter) {
    std::vector<std::string> tokens;
    std::stringstream ss(str);
    std::string item;
    while (std::getline(ss, item, delimiter)) {
        tokens.push_back(item);
    }
    return tokens;
}