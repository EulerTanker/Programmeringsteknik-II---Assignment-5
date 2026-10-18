#include "LanguageModel.h"

#include <stdexcept>

void LanguageModel::train(const std::string &text) {
  if (text.size() <= static_cast<std::size_t>(k)) {
    throw std::runtime_error("training text is too short for k = " +
                             std::to_string(k));
  }

  for (std::size_t i = 0; i < text.size(); i++) {
    alphabet.insert(text[i]);
  }

  for (std::size_t i = 0; i + k <= text.size(); i++) {
    std::string kgram = text.substr(i, k);
    kgramCounts[kgram]++;

    if (i + k < text.size()) {
      char next = text[i + k];
      nextCounts[kgram][next]++;
      followCounts[kgram]++;
    }
  }
}

double LanguageModel::probability(const std::string &w, char c) {
  int n_w = 0;
  if (followCounts.count(w) > 0) {
    n_w = followCounts[w];
  }

  int n_wc = 0;
  if (nextCounts.count(w) > 0 && nextCounts[w].count(c) > 0) {
    n_wc = nextCounts[w][c];
  }

  double denominator = n_w + alpha * alphabet.size();
  if (denominator == 0) {
    return 0.0;
  }
  return (n_wc + alpha) / denominator;
}

std::map<std::string, int> LanguageModel::getKgramCounts() {
  return kgramCounts;
}

std::set<char> LanguageModel::getAlphabet() { return alphabet; }
