#include "Characters.h"

#include <algorithm>
#include <cctype>
#include <iostream>
#include <numeric>
#include <unordered_set>
using namespace swo::chars;

void Characters::collect(char input) { data.push_back(input); }

std::vector<char> Characters::getLetters() const {
  std::vector<char> letters;
  for (auto letter : data) {
    if (std::isalpha(letter)) {
      letters.push_back(letter);
    }
  }
  return letters;
}
double Characters::letterFrequency() const {
  const auto letters =
      std::count_if(std::begin(data), std::end(data),
                    [](unsigned char ch) { return std::isalpha(ch); });
  return (double)letters / count();
}

double Characters::frequencyCertainLetter(const char& letter) const {
  if (!std::isalpha(letter)) {
    throw std::invalid_argument("Not a letter");
  }
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
double Characters::getLowestFrequency(
    const std::vector<char>& searchData) const {
  checkIfEmpty();
  double min_frequency = 1;
  for (auto letter : searchData) {
    if (frequencyCertainLetter(letter) < min_frequency) {
      min_frequency = frequencyCertainLetter(letter);
    }
  }
  return min_frequency;
}

std::vector<char> Characters::getLeastFrequentLetter() const {
  checkIfEmpty();
  std::vector<char> data_letters = getLetters();
  char least_frequent_letter = data_letters[0];
  double min_frequency = getLowestFrequency(data_letters);
  std::unordered_set<char> unique_data_set(data_letters.begin(),
                                           data_letters.end());
  std::vector<char> unique_data(unique_data_set.begin(), unique_data_set.end());
  std::vector<char> least_frequent_letters;
  for (auto letter : unique_data) {
    if (frequencyCertainLetter(letter) == min_frequency)
      least_frequent_letters.push_back(letter);
  }
  return least_frequent_letters;
}