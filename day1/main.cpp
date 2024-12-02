#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

int main() {
  vector<int> v1;
  vector<int> v2;
  int num;
  int i = 0;

  while (cin >> num) {
    if (i++ % 2 == 0) {
      v1.push_back(num);
    } else {
      v2.push_back(num);
    }
  }

  sort(v1.begin(), v1.end());
  sort(v2.begin(), v2.end());

  int totalDistance = 0;
  for (int i = 0; i < v1.size(); i++) {
    totalDistance += abs(v1.at(i) - v2.at(i));
  }
  cout << "Part One:\nTotal Distance: " << totalDistance << endl << endl;

  int similarityScore = 0;
  for (int i = 0; i < v1.size(); i++) {
    int dups = 0;
    for (int j = 0; j < v1.size(); j++) {
      if (v1.at(i) == v2.at(j)) {
        dups++;
      }
    }
    similarityScore += dups * v1.at(i);
  }

  cout << "Part Two:" << endl
       << "Similarity Score: " << similarityScore << endl;

  return 0;
}
