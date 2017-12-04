#include <iostream>
#include <sstream>
#include <vector>
#include <stdio.h>
#include <string.h>
#include <fstream>

// File with useful fucntions
#include "utilities.h"

using namespace std;


template<typename Out>
void split(const std::string &s, char delim, Out result) {
    std::stringstream ss(s);
    std::string item;
    while (getline(ss, item, delim)) {
        *(result++) = item;
    }
}

vector<string> split(const std::string &s, char delim) {
  std::vector<std::string> elems;
  split(s, delim, std::back_inserter(elems));
  return elems;
}

string getline(ifstream &a_stream) {
  string s;
  getline(a_stream, s);
  return s;
}

string trim(string& str) {
    size_t first = str.find_first_not_of(' ');
    size_t last = str.find_last_not_of(' ');
    return str.substr(first, (last-first+1));
}
// template<class T>
string to_string(vector<string> v) {
  string s; 
  s += v[0];
  if (v.size() > 1){
    for (unsigned i=1; i<v.size(); i++) {
      s += v[i];
    }
  }
  return s;
}

string to_string(vector<int> v) {
  string s; 
  s += to_string(v[0]);
  if (v.size() > 1) {
    for (unsigned i=0; i<v.size(); i++) {

      s += to_string(v[i]) + " ";
    }
  }
  return trim(s);
}

// Convert vector of strings to vector of ints. Use responsibly
std::vector<int> string_to_int(std::vector<string> v) {
  std::vector<int> elems;

  for ( unsigned i=0; i<v.size(); i++){ 
    elems.push_back( std::stoi(v[i]) );  
  }

  return elems;
}
 
bool contains(std::vector<int> v, int a) {
  for (unsigned i=0; i<v.size(); i++){
    if ( v[i] == a ){
      return true;
    }
  }
  return false;
}

// Returns length of the suffix
int overlap_length(string suffix, string prefix) {

  int suf_pos = 0;
  bool overlap = false;
  while ( !overlap ) {

    string s1 = suffix.substr(suf_pos);
    string s2 = prefix.substr(0, s1.length());

    overlap = true;
    if (s1 != s2) {
      suf_pos++ ;
      overlap = false;
    }

  }
  return suffix.length() - suf_pos;
}