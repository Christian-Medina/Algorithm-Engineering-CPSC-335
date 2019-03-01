///////////////////////////////////////////////////////////////////////////////
// project1_test.cc
//
// Unit tests for project1.hh
//
///////////////////////////////////////////////////////////////////////////////

#include "rubrictest.hh"

#include "project1.hh"

#include <algorithm>
#include <random>
#include <sstream>
#include <vector>

using namespace std;

int main() {

  string_vector slogan = { "titans", "reach", "higher" };
  
  string_vector animals = {
    "dog", "cat", "mouse", "rat", "horse", "cow", "pig", "donkey", "penguin",
    "grouse", "rabbit", "catamount", "moose"
  };
  
  string_vector words_txt;
  bool load_words_ok = load_words(words_txt, "words.txt");

  Rubric rubric;

  rubric.criterion("load_words(...)", 1,
		   [&]() {
		     string_vector unused;
		     TEST_FALSE("try to load nonexistant file", load_words(unused, "NOT A PATH"));
		     TEST_TRUE("load words.txt", load_words_ok);
		     TEST_EQUAL("words.txt got every word", 99171, words_txt.size());
		     TEST_EQUAL("words.txt word 0", "A", words_txt[0]);
		     TEST_EQUAL("words.txt word 1", "A's", words_txt[1]);
		     TEST_EQUAL("words.txt word 2", "AA's", words_txt[2]);
		     TEST_EQUAL("words.txt word 3", "AB's", words_txt[3]);
		     TEST_EQUAL("words.txt word 4", "ABM's", words_txt[4]);
		     TEST_EQUAL("words.txt last word", "études", words_txt[99170]);
		   });

  rubric.criterion("is_mirrored(...)", 1,
		   [&]() {
		     TEST_TRUE("true: 2 characters", is_mirrored("ba", "ab"));
		     TEST_TRUE("true: 3 characters", is_mirrored("bal", "lab"));
		     TEST_TRUE("true: 4 characters", is_mirrored("balk", "klab"));
		     TEST_TRUE("true: 5 characters", is_mirrored("balki", "iklab"));
		     TEST_FALSE("false: 1 different character", is_mirrored("x", "y"));
		     TEST_FALSE("false: 1 identical character", is_mirrored("x", "x"));
		     TEST_FALSE("false: 2 characters", is_mirrored("ba", "al"));
		     TEST_FALSE("false: 3 characters", is_mirrored("bal", "ral"));
		     TEST_FALSE("false: 4 characters", is_mirrored("balk", "rral"));
		     TEST_FALSE("false: 5 characters", is_mirrored("balki", "yrral"));
		     TEST_FALSE("false: same string", is_mirrored("aaaaa", "aaaaa"));
		     TEST_FALSE("false: empty string", is_mirrored("", ""));
		   });

  rubric.criterion("is_substring(...)", 1,
		   [&]() {
		     TEST_TRUE("true: two empty strings", is_substring("", ""));
		     TEST_TRUE("true: one empty string", is_substring("", "ratamacue"));
		     TEST_TRUE("true: found at beginning", is_substring("rat", "ratamacue"));
		     TEST_TRUE("true: found in middle", is_substring("mac", "ratamacue"));
		     TEST_TRUE("true: found at end", is_substring("cue", "ratamacue"));
		     TEST_FALSE("false: one empty string", is_substring("ratamacue", ""));
		     TEST_FALSE("false: not even close", is_substring("ratamacue", "horseradish"));
		     TEST_FALSE("false: close call", is_substring("radix", "horseradish"));
		   });
  
  rubric.criterion("character_mode(...)", 2,
		   [&]() {
		     TEST_EQUAL("slogan", 'h', character_mode(slogan));
		     TEST_EQUAL("animals", 'o', character_mode(animals));
		     TEST_EQUAL("words.txt", 's', character_mode(words_txt));
		   });

  rubric.criterion("longest_mirrored_string(...)", 2,
		   [&]() {
		     TEST_EQUAL("not found: slogan", "", longest_mirrored_string(slogan));
		     TEST_EQUAL("not found: animals", "", longest_mirrored_string(animals));
		     // words.txt takes too long

		     string_vector has_mirrored = {
		       "mink", "ferret", "owl", "eagle",
		       "knim", "terref", "low", "elgae"
		     };
		     string result = longest_mirrored_string(has_mirrored);
		     TEST_TRUE("found", (result == "ferret") || (result == "terref"));
		   });

  rubric.criterion("longest_mirrored_string(...)", 2,
		   [&]() {
		     TEST_EQUAL("not found: slogan", "", longest_mirrored_string(slogan));
		     TEST_EQUAL("not found: animals", "", longest_mirrored_string(animals));
		     // words.txt takes too long

		     string_vector has_mirrored = {
		       "mink", "ferret", "owl", "eagle",
		       "knim", "terref", "low", "elgae"
		     };
		     string result = longest_mirrored_string(has_mirrored);
		     TEST_TRUE("found", (result == "ferret") || (result == "terref"));
		   });
  
  rubric.criterion("longest_substring_trio(...)", 2,
		   [&]() {
		     string_vector trio;

		     trio = longest_substring_trio(slogan);
		     TEST_EQUAL("returns 3 strings", 3, trio.size());
		     TEST_TRUE("not found: slogan", trio[0].empty() && trio[1].empty() && trio[2].empty() );

		     trio = longest_substring_trio(animals);
		     TEST_EQUAL("returns 3 strings", 3, trio.size());
		     TEST_TRUE("not found: animals", trio[0].empty() && trio[1].empty() && trio[2].empty() );

		     // words.txt takes too long

		     string_vector has_trio = {
		       "a", "act", "react", // total length 9
		       "boa", "boat", "boats" // total length 12
		     };

		     trio = longest_substring_trio(has_trio);
		     TEST_EQUAL("returns 3 strings", 3, trio.size());
		     sort(trio.begin(), trio.end());
		     TEST_EQUAL("found: short trio", "boa", trio[0]);
		     TEST_EQUAL("found: short trio", "boat", trio[1]);
		     TEST_EQUAL("found: short trio", "boats", trio[2]);

		     // total length 16
		     has_trio.push_back("garage");
		     has_trio.push_back("age");
		     has_trio.push_back("garaged");

		     trio = longest_substring_trio(has_trio);
		     TEST_EQUAL("returns 3 strings", 3, trio.size());
		     sort(trio.begin(), trio.end());
		     TEST_EQUAL("found: short trio", "age", trio[0]);
		     TEST_EQUAL("found: short trio", "garage", trio[1]);
		     TEST_EQUAL("found: short trio", "garaged", trio[2]);
		   });


  return rubric.run();
}
