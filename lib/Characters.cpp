#include "Characters.h"

#include <algorithm>
#include <cctype>
#include <iostream>
#include <numeric>
using namespace swo::chars;

void Characters::collect(char input) { data.push_back(input); }

double Characters::letterFrequency() const {
  const auto letters =
      std::count_if(std::begin(data), std::end(data),
                    [](unsigned char ch) { return std::isalpha(ch); });
  return (double)letters / count();
}

double Characters::frequencyCertainLetter(const char& letter) const {
  const auto letters = std::count_if(
      std::begin(data), std::end(data), [letter](unsigned char ch) {
        return std::tolower(ch) == std::tolower(letter);
      });
  return (double)letters / count();
}

void Characters::checkIfEmpty() const {
  if (data.empty()) {
    throw std::invalid_argument("Vector is empty");
  }
}
double Characters::getLowestFrequency() const {
  checkIfEmpty();
  double min_frequency = 1;
  for (auto letter : data) {
    if (frequencyCertainLetter(letter) < min_frequency) {
      min_frequency = frequencyCertainLetter(letter);
    }
  }
  return min_frequency;
}