#include "TextGenerator.h"

#include <vector>

std::string TextGenerator::generate(LanguageModel &model, int length) {
  // Choose the starting k-gram, weighted by how often each k-gram occurs
  std::map<std::string, int> kgramCounts = model.getKgramCounts();
  std::vector<std::string> kgrams;
  std::vector<int> counts;
  for (std::pair<std::string, int> entry : kgramCounts) {
    kgrams.push_back(entry.first);
    counts.push_back(entry.second);
  }

  std::discrete_distribution<int> startDistribution(counts.begin(),
                                                    counts.end());
  std::string current = kgrams[startDistribution(engine)];
  std::string output = current;

  // Add one character at a time until the output is long enough
  std::set<char> alphabet = model.getAlphabet();
  while (static_cast<int>(output.size()) < length) {
    std::vector<char> characters;
    std::vector<double> probabilities;
    double total = 0.0;

    for (char c : alphabet) {
      double p = model.probability(current, c);
      characters.push_back(c);
      probabilities.push_back(p);
      total += p;
    }

    if (total == 0.0) {
      break;
    }

    std::discrete_distribution<int> nextDistribution(probabilities.begin(),
                                                     probabilities.end());
    char next = characters[nextDistribution(engine)];

    output += next;
    current = current.substr(1) + next;
  }

  return output;
}
