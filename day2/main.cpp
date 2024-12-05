#include <iostream>
#include <sstream>

inline static bool isSafe(const std::vector<int> nums) {
  auto dir = nums[1] > nums[0] ? 'a' : 'd';

  for (size_t i = 1; i < nums.size(); i++) {
    int curr = nums[i];
    int prev = nums[i - 1];
    int diff = abs(curr - prev);

    if ((!(curr > prev && dir == 'a') &&
         !(curr < prev && dir == 'd')) ||  // wrong direction
        !(diff >= 1 && diff <= 3))         // wrong difference
    {
      return false;
    }
  }
  return true;
}

inline static bool isSafeWithDampener(const std::vector<int>& original) {
  if (isSafe(original))
    return true;

  for (size_t skip = 0; skip < original.size(); skip++) {
    std::vector<int> modified;

    for (size_t i = 0; i < original.size(); i++) {
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
  std::string line;
  int safeReports = 0;
  int safeReportsWithDampener = 0;

  while (getline(std::cin, line)) {
    std::vector<int> report;
    std::stringstream ss(line);
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

  std::cout << "Part One:\nSafe Reports: " << safeReports << std::endl;
  std::cout << "Part Two:\nSafe Reports with Dampener: "
            << safeReportsWithDampener << std::endl
            << std::endl;
  return 0;
}
