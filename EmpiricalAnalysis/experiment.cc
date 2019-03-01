///////////////////////////////////////////////////////////////////////////////
// experiment.cc
//
// Example code showing how to run an algorithm once and measure its elapsed
// time precisely. You should modify this program to gather all of your
// experimental data.
//
///////////////////////////////////////////////////////////////////////////////

#include <iostream>

#include "project1.hh"
#include "timer.hh"

using namespace std;

void test_char_mode_alg(int n, const string_vector& words);
void test_mirrored_alg(int n, const string_vector& words);
void test_sub_str_trio_alg(int n, const string_vector& words);

int main() {

  string_vector all_words;
  if ( ! load_words(all_words, "words.txt") ) {
    cerr << "error: cannot open \"words.txt\"" << endl;
    return 1;
  }
  //modify accordingly for each experiment
  test_char_mode_alg(10000, all_words);
  test_mirrored_alg(10000, all_words);
  test_sub_str_trio_alg(200, all_words);
  return 0;
}

//testing function for character mode algorithm
//parameters: n represents number of words to use (input size), words is the collection of all words
//output: prints given n value, character mode output, and elapsed time to the screen
void test_char_mode_alg(int n, const string_vector& words) {
  int test_num = n;
  string_vector n_words(words.begin(), words.begin() + n);
  Timer timer;
  char output = character_mode(n_words);
  double elapsed = timer.elapsed();
  cout << "character_mode, "
       << "n=" << n << ", "
       << "output=\"" << output << "\", "
       << "elapsed time=" << elapsed << " seconds" << endl;
}

//testing function for longest mirrored string algorithm
//parameters: n represents number of words to use (input size), words is the collection of all words
//output: prints given n value, longest mirrored string output, and elapsed time to the screen
void test_mirrored_alg(int n, const string_vector& words) {
  int test_num = n;
  string_vector n_words(words.begin(), words.begin() + n);
  Timer timer;
  string output = longest_mirrored_string(n_words);
  double elapsed = timer.elapsed();
  cout << "longest_mirrored_string, "
       << "n=" << n << ", "
       << "output=\"" << output << "\", "
       << "elapsed time=" << elapsed << " seconds" << endl;
}

//testing function for sub string trio algorithm
//parameters: n represents number of words to use (input size), words is the collection of all words
//output: prints given n value, sub string trio output, and elapsed time to the screen
void test_sub_str_trio_alg(int n, const string_vector& words) {
  int test_num = n;
  string_vector n_words(words.begin(), words.begin() + n);
  Timer timer;
  string_vector output = longest_substring_trio(n_words);
  double elapsed = timer.elapsed();
  cout << "longest_substring_trio, "
       << "n=" << n << ", "
       << "output=\"" << output[0] << ", " << output[1] << ", " << output[2] << "\", "
       << "elapsed time=" << elapsed << " seconds" << endl;
}
