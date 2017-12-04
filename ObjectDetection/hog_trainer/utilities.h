#ifndef UTILITIES_H
#define UTILITIES_H

using namespace std;

// Function to split a string on a delimeter and store the vector to 'result'
template<typename Out>
void split(const std::string &s, char delim, Out result);

// Function to split a string on a delimeter and return the vector
vector<string> split(const std::string &s, char delim);

// Returns a string instead of storing the value
string getline(ifstream &a_stream);

// Removes the first and last space in a string if one exits, returns string
string trim(string& str);

// Returns a string of elements of a vector, concatenated using delim
// template<class T>s
std::string to_string(std::vector<string> v);

std::string to_string(std::vector<int> v);

// Converts a vector of string to vector of int
std::vector<int> string_to_int(std::vector<string> v);

bool contains(std::vector<int> v, int a);

int overlap_length(string suffix, string prefix);
#endif
