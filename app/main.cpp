#include <Characters.h>

#include <cmath>
#include <iostream>

int main() {
  swo::chars::Characters a;

  char x;
  std::cin >> x;
  while (std::cin) {
    a.collect(x);
    std::cin >> x;
  }

  std::cout << "Count: " << a.count() << '\n';
  std::cout << "Letter frequency: "
            << static_cast<int>(std::round(a.letterFrequency() * 100)) << "%\n";
}
