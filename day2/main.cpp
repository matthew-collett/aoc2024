#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

bool isSafe(const vector<int> nums) {
  char dir = nums[1] > nums[0] ? 'a' : 'd';

  for (int i = 1; i < nums.size(); i++) {
    int curr = nums[i];
    int prev = nums[i - 1];
    int diff = abs(curr - prev);

    if ((!(curr > prev && dir == 'a') &&
         !(curr < prev && dir == 'd')) || // wrong direction
        !(diff >= 1 && diff <= 3))        // wrong difference
    {
      return false;
    }
  }
  return true;
}

bool isSafeWithDampener(const vector<int> &original) {
  if (isSafe(original))
    return true;

  for (int skip = 0; skip < original.size(); skip++) {
    vector<int> modified;

    for (int i = 0; i < original.size(); i++) {
      if (i != skip) {
        modified.push_back(original[i]);
      }
    }

    if (isSafe(modified)) {
      return true;
    }
  }

  return false;
}

int main() {
  string line;
  int safeReports = 0;
  int safeReportsWithDampener = 0;

  while (getline(cin, line)) {
    vector<int> report;
    stringstream ss(line);
    int num;

    while (ss >> num) {
      report.push_back(num);
    }

    if (isSafe(report)) {
      safeReports++;
    }

    if (isSafeWithDampener(report)) {
      safeReportsWithDampener++;
    }
  }

  cout << "Part One:\nSafe Reports: " << safeReports << endl << endl;
  cout << "Part Two:\nSafe Reports with Dampener: " << safeReportsWithDampener
       << endl;
  return 0;
}
