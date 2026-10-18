#pragma once

#include <map>
#include <set>
#include <string>

class LanguageModel {
  // Attributes
private:
  int k;
  double alpha;
  std::map<std::string, int> kgramCounts;
  std::map<std::string, std::map<char, int>> nextCounts;
  std::map<std::string, int> followCounts;
  std::set<char> alphabet;

public:
  // Constructors
  LanguageModel(int k_init, double alpha_init = 0.0) {
    k = k_init;
    alpha = alpha_init;
  }

  // Methods
  void train(const std::string &text);
  double probability(const std::string &w, char c);
  std::map<std::string, int> getKgramCounts();
  std::set<char> getAlphabet();
};
