#include <Characters.h>

#include <cmath>
#include <iostream>

int main() {
  swo::chars::Characters a;

  while (std::cin) {
    char x = 0;
    std::cin >> x;
    a.collect(x);
  }

  std::cout << "Count: " << a.count() << '\n';
  std::cout << "Letter frequency: "
            << static_cast<int>(std::round(a.letterFrequency() * 100)) << "%\n";
}
