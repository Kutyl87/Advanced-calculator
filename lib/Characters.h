#include <vector>

namespace swo {
namespace chars {

class Characters {
 public:
  void collect(char input);

  std::size_t count() const { return data.size(); }
  std::vector<char> getData() const { return data; }
  double letterFrequency() const;
  double frequencyCertainLetter(const char& letter) const;
  void checkIfEmpty() const;
  void checkIfLetterIsAlpha() const;
  std::vector<char> getLetters() const;
  double getLowestFrequency(const std::vector<char>& searchData) const;
  double getHighestFrequency(const std::vector<char>& searchData) const;
  std::vector<char> getLeastFrequentLetter() const;
  std::vector<char> getMostFrequentLetter() const;
  std::vector<char> getLetterWithFrequency(double frequency) const;

 private:
  std::vector<char> data;
};

}  // namespace chars
}  // namespace swo