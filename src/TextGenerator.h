#pragma once

#include <random>
#include <string>

#include "LanguageModel.h"

class TextGenerator {
  // Attributes
private:
  std::mt19937 engine;

public:
  // Constructors
  TextGenerator() {
    std::random_device device;
    engine.seed(device());
  }

  // Methods
  std::string generate(LanguageModel &model, int length);
};
