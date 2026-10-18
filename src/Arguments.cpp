#include "Arguments.h"

#include <stdexcept>

Arguments::Arguments(int argc, char *argv[]) {
  alpha = 0.0;
  int first = 1;

  if (argc > 1 && argv[1][0] == '-') {
    std::string option = argv[1];
    if (option != "-a") {
      throw std::invalid_argument("unknown option '" + option + "'");
    }
    if (argc < 3) {
      throw std::invalid_argument(
          "-a must be followed by a non-negative number");
    }
    alpha = parseAlpha(argv[2]);
    first = 3;
  }

  if (argc - first != 3) {
    throw std::invalid_argument(
        "wrong number of arguments (usage: slm [-a alpha] k file length)");
  }

  k = parsePositiveInt(argv[first], "k");
  filename = argv[first + 1];
  length = parsePositiveInt(argv[first + 2], "output length");

  if (length < k) {
    throw std::invalid_argument("output length must be at least k");
  }
}

int Arguments::parsePositiveInt(const std::string &text,
                                const std::string &name) {
  std::string message =
      name + " must be a positive integer, got '" + text + "'";

  if (text.empty()) {
    throw std::invalid_argument(message);
  }
  for (std::size_t i = 0; i < text.size(); i++) {
    if (text[i] < '0' || text[i] > '9') {
      throw std::invalid_argument(message);
    }
  }

  int value = 0;
  try {
    value = std::stoi(text);
  } catch (const std::out_of_range &) {
    throw std::invalid_argument(name + " is too large, got '" + text + "'");
  }

  if (value <= 0) {
    throw std::invalid_argument(message);
  }
  return value;
}

double Arguments::parseAlpha(const std::string &text) {
  std::string message =
      "-a must be followed by a non-negative number, got '" + text + "'";

  int digits = 0;
  int dots = 0;
  for (std::size_t i = 0; i < text.size(); i++) {
    if (text[i] >= '0' && text[i] <= '9') {
      digits++;
    } else if (text[i] == '.') {
      dots++;
    } else {
      throw std::invalid_argument(message);
    }
  }

  if (digits == 0 || dots > 1) {
    throw std::invalid_argument(message);
  }
  return std::stod(text);
}

int Arguments::getK() { return k; }

double Arguments::getAlpha() { return alpha; }

std::string Arguments::getFilename() { return filename; }

int Arguments::getLength() { return length; }
