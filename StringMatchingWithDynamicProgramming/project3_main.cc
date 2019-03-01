
#include "project3.hh"
#include "timer.hh"

int main() {
	ProteinVector proteins;
	auto load_successful = load_proteins(proteins, "proteins.txt");
	assert( load_successful );

	std::vector<std::string> testProteins;
	testProteins.push_back("QSDITV");
	testProteins.push_back("KDITVXR");
	testProteins.push_back("YKSDTWRN");
	testProteins.push_back("AYKDIRNLX");
	testProteins.push_back("BQSITVARGL");

	std::cout << "------------------- Exhaustive Method --------------------" << std::endl;
	for (int i = 0; i < testProteins.size(); i++) {
		std::string searchString = 	testProteins[i];
		Timer timer;
		std::shared_ptr<Protein> best_protein = exhaustive_best_match(proteins, searchString);
		std::cout << "String to Match = " << testProteins[i] << std::endl;
		std::cout << best_protein->description << std::endl;
		std::cout << timer.elapsed() << std::endl;
	}

	std::cout << "------------------- Dynamic Programming ------------------" << std::endl;
	for (int i = 0; i < testProteins.size(); i++) {
		std::string searchString = 	testProteins[i];
		Timer timer;
		std::cout << "String to Match = " << testProteins[i] << std::endl;
		std::shared_ptr<Protein> best_protein = dynamicprogramming_best_match(proteins, searchString);
		std::cout << best_protein->description << std::endl;
		std::cout << timer.elapsed() << std::endl;
	}

  return 0;
}

