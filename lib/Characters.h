#include <vector>

namespace swo::chars {

class Characters {
 public:
  void collect(char input);

  std::size_t count() const { return data.size(); }
  double letterFrequency() const;

 private:
  std::vector<char> data;
};

}  // namespace swo::chars
