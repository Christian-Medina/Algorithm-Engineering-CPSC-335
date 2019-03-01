///////////////////////////////////////////////////////////////////////////////
// project1.hh
//
// The three algorithms specified in the project 1 requirements
// document, plus helper functions.
//
///////////////////////////////////////////////////////////////////////////////

#pragma once

#include <algorithm>
#include <cassert>
#include <fstream>
#include <string>
#include <vector>

// Convenient typedef for a vector of strings.
typedef std::vector<std::string> string_vector;

// Load words from the file at the given path. The words vector is
// cleared, and then each word from the file is added to the
// vector. Returns true on success or fale on I/O error.
bool load_words(string_vector& words, const std::string& path) {
  std::ifstream words_file;
  words_file.open(path);
  std::string word;

  if (!words_file.is_open()) {
    return false;
  } 
  else {
    words.clear();
    while (words_file >> word) {
      words.push_back(word);
    }
    words_file.close();
    return true;
  }
}

// Return true if string2 is a mirrored copy of string1, or false
// otherwise. In other words, return true if string1 is the reverse of
// string2. Return false when both strings are equal; by this rule,
// "aaa" is not a mirror of "aaa" even though they are technically the
// reverse of each other. Likewise "" is not a mirror of "". This
// function should be in-place, meaning that it only examines string1
// and string2 and never creates another string object.
bool is_mirrored(const std::string& string1, const std::string& string2) {
  int rev_i = string2.size() - 1;
  int i = 0;

  if (string1 == string2 || string1 == "" || string2 == "") {
    return false;
  }
  else {
    while (i < string1.size() || rev_i >= 0) {
      if (string1[i] != string2[rev_i]) {
        return false;
      }
      i++;
      rev_i--;
    }
    return true;
  }
}

// Return true if alleged_substring can be found as a substring of
// alleged_superstring. For example, "cat" is a substring of
// "catamaran"; "tama" is also a substring of "catamaran". This
// function should be in-place, meaning that it only examines string1
// and string2 and never creates another string object.
bool is_substring(const std::string& alleged_substring,
		  const std::string& alleged_superstring) {
        if (alleged_superstring.find(alleged_substring) != std::string::npos) {
          return true;
        }
        else {
          return false;
        }
}

// Return the character that occurs the most times in the given vector
// of strings. The vector must contain at least one character, so that
// the mode is defined. In the event of a tie (i.e. two characters
// have the same count), this function returns the tied character with
// the lesser ASCII code (i.e. the tied character that comes first in
// conventional alphabetical order).
char character_mode(const string_vector& strings) {
  int counts[256] = {0};
  int counts_len = sizeof(counts) / sizeof(int);
  int mode_index;
  char mode_char;
	
  for (int i = 0; i < strings.size(); i++) {
    for (int j = 0; j < strings[i].size(); j++) {
      counts[int(strings[i][j])] += 1;      //use ascii value of characters for counting
    }
  }
  mode_index = std::distance(counts, std::max_element(counts, counts + counts_len));
  mode_char = char(mode_index);		    //convert ascii index to char
  return mode_char;
}

// Return a longest string in the strings vector whose mirror is also
// in the vector. Strings are mirrors of each other in the same sense
// as described above for the is_mirrored(...) function. Either of the
// two mirrored strings may be returned; for example, if the vector
// contains both "cat" and "tac", this function is allowed to return
// either "cat" or "tac". If the vector contains no mirrored strings,
// returns an empty string.
std::string longest_mirrored_string(const string_vector& strings) {
  std::string best = "";
	
  for (int i = 0; i < strings.size(); i++) {
    for (int j = i + 1; j < strings.size() - i; j++) {
      if (is_mirrored(strings[i], strings[j]) && strings[i].size() > best.size()) {
        best = strings[i];
      }
    }
  }
  return best;
}

// Return a vector of length exactly three, containing the longest
// substring trio from the string vector. A substring trio is three
// non-empty, distinct, strings a, b, and c such that a is a substring
// of b, b is a substring of c. This function returns the substring
// trio with the longest total length of a, b, and c. If the input
// vector does not contain a substring trio, return a vector
// containing exactly three empty strings.
string_vector longest_substring_trio(const string_vector& strings) {
  int best_length = 0;
  int abc_length = 0;
  bool a_sub_b;
  bool b_sub_c;
  string_vector trio(3, "");
	
  for (std::string a : strings) {
    for (std::string b : strings) {
      for (std::string c : strings) {
        abc_length = a.size() + b.size() + c.size();
        a_sub_b = is_substring(a, b);
        b_sub_c = is_substring(b, c);
        if (a_sub_b && b_sub_c && (abc_length > best_length) && !(a == b || b == c)) {
          best_length = abc_length;
          trio[0] = a;
          trio[1] = b;
          trio[2] = c;
        }
      }
    }
  }
  return trio;
}
