#include <iostream>

#include "timer.hh"
#include "maxprotein.hh"

using namespace std;

void time_greedy_alg(const FoodVector& foods, int greedy_n, int max_protein);
void time_exhaust_alg(const FoodVector& foods, int exhaust_n, int max_protein);
void get_experiment_values(int& n_value, int& max_protein, const string& purpose);

int main() {
  int greedy_n;
  int greedy_protein;
  int exhaust_n;
  int exhaust_protein;
  unique_ptr<FoodVector> all_foods = load_usda_abbrev("ABBREV.txt");

  get_experiment_values(greedy_n, greedy_protein, "greedy algorithm");
  time_greedy_alg(*all_foods, greedy_n, greedy_protein);
  get_experiment_values(exhaust_n, exhaust_protein, "exhaustive algorithm");
  time_exhaust_alg(*all_foods, exhaust_n, exhaust_protein);

  return 0;
}

//time_greedy_alg
//parameters: foods is the vector of all foods available, greedy_n is the desired n value, max_protein
//            is the max protein value desired
//returns: none
//this function will time the greedy algorithm with the desired values and time it, while printing the result
//afterwards
void time_greedy_alg(const FoodVector& foods, int greedy_n, int max_protein) {
  unique_ptr<FoodVector> greedy_foods = filter_food_vector(foods, 1, 2000, greedy_n);
  unique_ptr<FoodVector> results;
  double elapsed;
  
  cout << "Beginning greedy algorithm experiment. . . " << endl;

  Timer timer;
  results = greedy_max_protein(*greedy_foods, max_protein);
  elapsed = timer.elapsed();

  cout << "Greedy algorithm experiment completed, time elapsed: " << elapsed << endl;
  cout << "Results found:" << endl;
  print_food_vector(*results);
}

//time_exhaust_alg
//parameters: foods is the vector of all foods available, exhaust_n is the desired n value, max_protein
//            is the desired max protein value
//returns: none
//this function will time the exhaustive algorithm with the desired values and time it,
//while printing the result afterwards
void time_exhaust_alg(const FoodVector& foods, int exhaust_n, int max_protein) {
  unique_ptr<FoodVector> exhaust_foods = filter_food_vector(foods, 1, 2000, exhaust_n);
  unique_ptr<FoodVector> results;
  double elapsed;
  
  cout << "Beginning Exhaustive algorithm experiment. . . " << endl;

  Timer timer;
  results = exhaustive_max_protein(*exhaust_foods, max_protein);
  elapsed = timer.elapsed();

  cout << "Exhaustive algorithm experiment completed, time elapsed: " << elapsed << endl;
  cout << "Results found:" << endl;
  print_food_vector(*results);
}

//get_experiment_values
//parameters: n_value is an int to store n value input, max_protein is an int to store max protein
//            input, purpose is a string for defining the input's purpose
//returns: none
//this function will get values for the experiment and use a given string to specify which
//experiment the input is for
void get_experiment_values(int& n_value, int& max_protein, const string& purpose) {
    bool test;

    do {
      cout << "enter n value for " << purpose << ":";
      cin >> n_value;
      if (cin.fail()) {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << endl << "Error: integer values only" << endl;
        test = false;
      }
      else if (n_value < 1) {
        cout << endl << "Error: positive integer values >= 1 only" << endl;
        test = false;
      }
      else {
        test = true;
      }
    }while(!test);

    do {
      cout << "enter max kcal value for " << purpose << ":";
      cin >> max_protein;
      if (cin.fail()) {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << endl << "Error: integer values only" << endl;
        test = false;
      }
      else if (max_protein < 0) {
        cout << endl << "Error: positive integer values >= 0 only" << endl;
        test = false;
      }
      else {
        test = true;
      }
    }while(!test);
}
