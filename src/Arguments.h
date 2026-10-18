#pragma once

#include <string>

class Arguments {
  // Attributes
private:
  int k;
  double alpha;
  std::string filename;
  int length;

  // Helper methods
  int parsePositiveInt(const std::string &text, const std::string &name);
  double parseAlpha(const std::string &text);

public:
  // Constructors
  Arguments(int argc, char *argv[]);

  // Methods
  int getK();
  double getAlpha();
  std::string getFilename();
  int getLength();
};
