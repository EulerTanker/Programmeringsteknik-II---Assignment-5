#include <exception>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string>

#include "Arguments.h"
#include "LanguageModel.h"
#include "TextGenerator.h"

std::string readFile(const std::string &filename) {
  std::ifstream file(filename);
  if (!file) {
    throw std::runtime_error("cannot open file '" + filename + "'");
  }

  std::string text;
  char c;
  while (file.get(c)) {
    text += c;
  }
  return text;
}

int main(int argc, char *argv[]) {
  try {
    Arguments args(argc, argv);
    std::string text = readFile(args.getFilename());

    LanguageModel model(args.getK(), args.getAlpha());
    model.train(text);

    TextGenerator generator;
    std::cout << generator.generate(model, args.getLength()) << std::endl;
  } catch (const std::exception &e) {
    std::cerr << "slm: " << e.what() << std::endl;
    return 1;
  }

  return 0;
}
