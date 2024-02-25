#include <vector>

namespace swo {
namespace chars {

class Characters {
 public:
  void collect(char input);

  std::size_t count() const { return data.size(); }
  double letterFrequency() const;
  double frequencyCertainLetter(const char& letter) const;
  void checkIfEmpty() const;
  double getLowestFrequency() const;
  char getLeastFrequentLetter() const;

 private:
  std::vector<char> data;
};

}  // namespace chars
}  // namespace swo