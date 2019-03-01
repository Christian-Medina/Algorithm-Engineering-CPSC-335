///////////////////////////////////////////////////////////////////////////////
// maxprotein.hh
//
// Compute the set of foods that maximizes protein, within a calorie budget,
// with the greedy method or exhaustive search.
//
///////////////////////////////////////////////////////////////////////////////


#pragma once

#include <algorithm>
#include <cassert>
#include <cmath>
#include <fstream>
#include <iostream>
#include <map>
#include <memory>
#include <queue>
#include <sstream>
#include <string>
#include <vector>

// Simple structure for a single protein
struct Protein {
	Protein() {
		description = "";
		sequence = "";
	}
	Protein(std::string desc, std::string seq) {
		description = desc;
		sequence = seq;
	}
	std::string		description;
	std::string 	sequence;
};

// Alias for a vector of shared pointers to Protein objects.
typedef std::vector<std::shared_ptr<Protein>> ProteinVector;


// -------------------------------------------------------------------------
// Load all the proteins from a standard FASTA format file with one line
// per sequence (multi-line sequences are not allowed).
// Returns false on I/O error.
// -------------------------------------------------------------------------
bool load_proteins(ProteinVector & proteins, const std::string& path) 
{
  //std::cout << "Loading proteins from [" << path << "]" << std::endl;
  proteins.clear();
  std::ifstream ifs(path.c_str());
  if (!ifs.is_open() || !ifs.good()) {
    std::cout << "Failed to open [" << path << "]" << std::endl;
    return false;
  }
  int proteinsLoaded = 0;
  bool have_description = false;
  std::shared_ptr<Protein> newProtein = nullptr;
  while (!ifs.eof()) {
    std::string lineBuffer;
    std::getline(ifs, lineBuffer);
    if (ifs.eof()) {
      break;
    }
    if (lineBuffer.size() == 0) {
		continue;
	}
    if (lineBuffer[0] == '>') {
		newProtein = std::shared_ptr<Protein>(new Protein);
		newProtein->description = lineBuffer.substr(1);
        have_description = true;
    } else if (have_description) {
		newProtein->sequence = lineBuffer;
	    proteins.push_back(newProtein);
        proteinsLoaded++;
        have_description = false;
    }
  }

	ifs.close();
  //std::cout << "Loaded " << proteinsLoaded << " proteins from [" << path << "]" << std::endl;

  return true;
}

// -------------------------------------------------------------------------
// dynamicprogramming_longest_common_subsequence
// parameters: two strings representing sequences
// returns: an int representing the longest common subsequence between the two
//          sequences
// this function uses dynamic programming to calculate the longest common
// subsequence
// -------------------------------------------------------------------------
int dynamicprogramming_longest_common_subsequence(const std::string & string1, 
												  const std::string & string2)
{
  int n = string1.size();
  int m = string2.size();
  std::vector<std::vector<int>> D(n + 1, std::vector<int>(m+1));
  int up;
  int left;
  int diag;

  for (int i = 0; i <= n; i++) {
    D[i][0] = 0;
  }
  for (int j = 0; j <= m; j++) {
    D[0][j] = 0;
  }

  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= m; j++) {
      up = D[i - 1][j];
      left = D[i][j - 1];
      diag = D[i -1][j - 1];
      if (string1[i - 1] == string2[j - 1]) {
        diag += 1;
      }
      D[i][j] = std::max(std::max(up, left), diag);
    }
  }

  return D[n][m];
}

// -------------------------------------------------------------------------
// generate_all_subsequences
// parameters: string representing a sequence
// returns: a unique_ptr to a vector of strings representing all subsequences
// this function is used to generate all subsequences of a given sequence
// -------------------------------------------------------------------------
std::unique_ptr<std::vector<std::string>> generate_all_subsequences(const std::string & sequence)
{
  std::unique_ptr<std::vector<std::string>> subsequences(new std::vector<std::string>());
  int n = pow(2, sequence.size());
  std::string subseq;

  for (int bits = 0; bits < n; bits++) {
    subseq = "";
    for (int j = 0; j < sequence.size(); j++) {
      if (((bits >> j) & 1) == 1) {
        subseq += sequence[j];
      }
    }
    subsequences->push_back(subseq);
  }

	return subsequences;
}


// -------------------------------------------------------------------------
// exhaustive_longest_common_subsequence
// parameters: two strings representing sequences
// returns: an int representing the longest common subsequence between the two
//          sequences
// this function will exhaustively generate all the subsequences of two sequences
// and then find the longest between the two
// -------------------------------------------------------------------------
int exhaustive_longest_common_subsequence(const std::string & string1, 
										  const std::string & string2)
{
  std::unique_ptr<std::vector<std::string>> all_subseqs1 = generate_all_subsequences(string1);
  std::unique_ptr<std::vector<std::string>> all_subseqs2 = generate_all_subsequences(string2);
  int best_score = 0;

  for (std::string s1 : *all_subseqs1) {
    for (std::string s2 : *all_subseqs2) {
      if (s1 == s2 && s1.size() > best_score) {
        best_score = s1.size();
      }
    }
  }

	return best_score;
}


// -------------------------------------------------------------------------
// exhaustive_best_match
// parameters: proteins is a vector of protein objects, string1 is a string
//             representing a sequence to match
// returns: a shared_ptr to the best match produced by an exhaustive algorithm
// this function will use exhaustive_longest_common_subsequence to find a best match
// -------------------------------------------------------------------------
std::shared_ptr<Protein> exhaustive_best_match(ProteinVector & proteins, const std::string & string1)
{
	//	std::shared_ptr<Protein> best_protein = nullptr;
	int best_i = 0;
	int best_score = 0;
	int score = 0;
	for (int i = 0; i < proteins.size(); i++)
	{
		score = exhaustive_longest_common_subsequence(proteins[i]->sequence, string1);
		//std::cout << "\nproteins[i]->sequence : " << proteins[i]->sequence << "\n";
		//std::cout << "\nstring1 : " << string1 << "\n";
		//std::cout << "\n1score : " << score << "\n";
		//std::cout << "\n1best_score : " << best_score << "\n";

		if (score > best_score)
		{
			best_score = score;
			best_i = i;
		}
	//std::cout << "\n2score : " << score << "\n";
	//std::cout << "\n2best_score : " << best_score << "\n";
	}





	//std::cout << "proteins[best_i] : " << proteins[best_i]->sequence << "\n";
	
	return proteins[best_i];
	
	//return best_protein
}

// -------------------------------------------------------------------------
// dynamicprogramming_best_match
// parameters: proteins is a vector of protein objects, string1 is a string
//             representing a sequence to match
// returns: a shared_ptr to the best match produced by a dynamic programming algorithm
// this function will use dynamicprogramming_longest_common_subsequence to find a best match
// -------------------------------------------------------------------------
std::shared_ptr<Protein> dynamicprogramming_best_match(ProteinVector & proteins, const std::string & string1)
{
//	std::shared_ptr<Protein> best_protein = nullptr;
int best_i = 0;
	int best_score = 0;
	int score = 0;
	for (int i = 0; i < proteins.size(); i++)
	{
		score = dynamicprogramming_longest_common_subsequence(proteins[i]->sequence, string1);
		if (score > best_score)
		{
			best_score = score;
			best_i = i;
		}
	}
	return proteins[best_i];




//	return best_protein;
}


