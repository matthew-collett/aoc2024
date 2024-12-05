#include <algorithm>
#include <iostream>

int main() {
  std::vector<int> v1;
  std::vector<int> v2;
  int num;
  int i = 0;

  while (std::cin >> num) {
    if (i++ % 2 == 0) {
      v1.push_back(num);
    } else {
      v2.push_back(num);
    }
  }

  sort(v1.begin(), v1.end());
  sort(v2.begin(), v2.end());

  int totalDistance = 0;
  for (size_t i = 0; i < v1.size(); i++) {
    totalDistance += abs(v1[i] - v2[i]);
  }
  std::cout << "Part One:\nTotal Distance: " << totalDistance << std::endl;

  int similarityScore = 0;
  for (size_t i = 0; i < v1.size(); i++) {
    int dups = 0;
    for (size_t j = 0; j < v1.size(); j++) {
      if (v1[i] == v2[j]) {
        dups++;
      }
    }
    similarityScore += dups * v1[i];
  }

  std::cout << "Part Two:" << std::endl
            << "Similarity Score: " << similarityScore << std::endl
            << std::endl;

  return 0;
}
