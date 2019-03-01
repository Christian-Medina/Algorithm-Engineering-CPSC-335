///////////////////////////////////////////////////////////////////////////////
// maxprotein_test.cc
//
// Unit tests for maxprotein.hh
//
///////////////////////////////////////////////////////////////////////////////


#include <cassert>
#include <sstream>

#include "project3.hh"
#include "rubrictest.hh"

int main() {
	Rubric rubric;

	ProteinVector proteins;
	auto load_successful = load_proteins(proteins, "proteins.txt");
	assert( load_successful );


  rubric.criterion("load_protein still works", 1, [&]() {
		     TEST_EQUAL("size", 2000, proteins.size());
		   });
  
  rubric.criterion("dynamic programming simple cases", 2,
		   [&]() {
		     auto soln = dynamicprogramming_longest_common_subsequence("", "");
		     TEST_EQUAL("same", 0, soln);
		     soln = dynamicprogramming_longest_common_subsequence("A", "A");;
		     TEST_EQUAL("same 1", 1, soln);
		     soln = dynamicprogramming_longest_common_subsequence("AB", "AB");;
		     TEST_EQUAL("same 2", 2, soln);
		     soln = dynamicprogramming_longest_common_subsequence("ABC", "ABC");;
		     TEST_EQUAL("same 3", 3, soln);
		   });
  
  rubric.criterion("dynamic programming simple deletion and insertion cases", 2,
		   [&]() {
		     auto soln = dynamicprogramming_longest_common_subsequence("A", "");
		     TEST_EQUAL("deletion A", 0, soln);
		     soln = dynamicprogramming_longest_common_subsequence("", "A");;
		     TEST_EQUAL("insertion A", 0, soln);
		     soln = dynamicprogramming_longest_common_subsequence("ABC", "AC");;
		     TEST_EQUAL("deletion B", 2, soln);
		     soln = dynamicprogramming_longest_common_subsequence("AC", "ABC");;
		     TEST_EQUAL("insertion B", 2, soln);
		   });
  
  rubric.criterion("dynamic programming simple substitution case", 2,
		   [&]() {
		     auto soln = dynamicprogramming_longest_common_subsequence("ABC", "XBC");
		     TEST_EQUAL("substitution 1", 2, soln);
		     soln = dynamicprogramming_longest_common_subsequence("XBC", "ABC");;
		     TEST_EQUAL("substitution 1", 2, soln);
		     soln = dynamicprogramming_longest_common_subsequence("AXC", "ABC");;
		     TEST_EQUAL("substitution 2", 2, soln);
		     soln = dynamicprogramming_longest_common_subsequence("ABC", "AXC");;
		     TEST_EQUAL("substitution 2", 2, soln);
		     soln = dynamicprogramming_longest_common_subsequence("ABX", "ABC");;
		     TEST_EQUAL("substitution 2", 2, soln);
		     soln = dynamicprogramming_longest_common_subsequence("ABC", "ABX");;
		     TEST_EQUAL("substitution 2", 2, soln);
		   });
  
  rubric.criterion("exhaustive simple deletion and insertion cases", 2,
		   [&]() {
		     auto soln = exhaustive_longest_common_subsequence("", "");
		     TEST_EQUAL("same", 0, soln);
		     soln = exhaustive_longest_common_subsequence("A", "A");;
		     TEST_EQUAL("same 1", 1, soln);
		     soln = exhaustive_longest_common_subsequence("AB", "AB");;
		     TEST_EQUAL("same 2", 2, soln);
		     soln = exhaustive_longest_common_subsequence("ABC", "ABC");;
		     TEST_EQUAL("same 3", 3, soln);
		   });
  
  rubric.criterion("exhaustive simple deletion and insertion cases", 2,
		   [&]() {
		     auto soln = exhaustive_longest_common_subsequence("A", "");
		     TEST_EQUAL("deletion A", 0, soln);
		     soln = exhaustive_longest_common_subsequence("", "A");;
		     TEST_EQUAL("insertion A", 0, soln);
		     soln = exhaustive_longest_common_subsequence("ABC", "AC");;
		     TEST_EQUAL("deletion B", 2, soln);
		     soln = exhaustive_longest_common_subsequence("AC", "ABC");;
		     TEST_EQUAL("insertion B", 2, soln);
		   });
  
  rubric.criterion("exhaustive programming simple substitution case", 2,
		   [&]() {
		     auto soln = exhaustive_longest_common_subsequence("ABC", "XBC");
		     TEST_EQUAL("substitution 1", 2, soln);
		     soln = exhaustive_longest_common_subsequence("XBC", "ABC");;
		     TEST_EQUAL("substitution 1", 2, soln);
		     soln = exhaustive_longest_common_subsequence("AXC", "ABC");;
		     TEST_EQUAL("substitution 2", 2, soln);
		     soln = exhaustive_longest_common_subsequence("ABC", "AXC");;
		     TEST_EQUAL("substitution 2", 2, soln);
		     soln = exhaustive_longest_common_subsequence("ABX", "ABC");;
		     TEST_EQUAL("substitution 2", 2, soln);
		     soln = exhaustive_longest_common_subsequence("ABC", "ABX");;
		     TEST_EQUAL("substitution 2", 2, soln);
		   });
  

  ProteinVector trivial_proteins;
  trivial_proteins.push_back(std::shared_ptr<Protein>(new Protein("Dummy1", "ABCDE")));
  trivial_proteins.push_back(std::shared_ptr<Protein>(new Protein("Dummy2", "FGHIJ")));
  trivial_proteins.push_back(std::shared_ptr<Protein>(new Protein("Dummy2", "KLMNO")));
  trivial_proteins.push_back(std::shared_ptr<Protein>(new Protein("Dummy2", "PQRST")));
  trivial_proteins.push_back(std::shared_ptr<Protein>(new Protein("Dummy2", "UVWXY")));
  
  rubric.criterion("dynamic_best_match correctness", 4,
		   [&]() {
			 auto best_protein = dynamicprogramming_best_match(trivial_proteins, "ABXDE");
		     TEST_TRUE("non-null", best_protein);
		     TEST_EQUAL("ABXDE", "ABCDE", best_protein->sequence);
			 best_protein = dynamicprogramming_best_match(trivial_proteins, "KLMN");
		     TEST_EQUAL("XKLMN", "KLMNO", best_protein->sequence);
			 best_protein = dynamicprogramming_best_match(trivial_proteins, "LHIJ");
		     TEST_EQUAL("KLHIJ", "FGHIJ", best_protein->sequence);
			 best_protein = dynamicprogramming_best_match(trivial_proteins, "VWX");
		     TEST_EQUAL("VWX", "UVWXY", best_protein->sequence);
		   });

  rubric.criterion("exhaustive_best_match correctness", 4,
		   [&]() {
			 auto best_protein = exhaustive_best_match(trivial_proteins, "ABXDE");
		     TEST_TRUE("non-null", best_protein);
		     TEST_EQUAL("ABXDE", "ABCDE", best_protein->sequence);
			 best_protein = exhaustive_best_match(trivial_proteins, "KLMN");
		     TEST_EQUAL("XKLMN", "KLMNO", best_protein->sequence);
			 best_protein = exhaustive_best_match(trivial_proteins, "LHIJ");
		     TEST_EQUAL("KLHIJ", "FGHIJ", best_protein->sequence);
			 best_protein = exhaustive_best_match(trivial_proteins, "VWX");
		     TEST_EQUAL("VWX", "UVWXY", best_protein->sequence);
		   });

  return rubric.run();
}

