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
