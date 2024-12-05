#include <algorithm>
#include <iostream>
#include <map>
#include <sstream>

inline static std::vector<std::string> split(const std::string& s,
                                             const char delim) {
  std::vector<std::string> result;
  std::stringstream ss(s);
  std::string item;

  while (getline(ss, item, delim)) {
    result.push_back(item);
  }

  return result;
}

inline static std::vector<int> mapToInt(const std::vector<std::string> v) {
  std::vector<int> v2;
  std::transform(v.begin(), v.end(), std::back_inserter(v2),
                 [](const std::string& s) { return std::stoi(s); });
  return v2;
}

inline static std::map<int, std::vector<int>> getRules(std::string line) {
  std::map<int, std::vector<int>> rules;
  while (getline(std::cin, line)) {
    if (line == "") {
      break;
    }
    const std::vector<int> parts = mapToInt(split(line, '|'));
    const int key = parts[0];
    const int value = parts[1];
    if (!rules.count(key)) {
      rules.insert({key, std::vector<int>{value}});
      continue;
    }
    rules.at(key).push_back(value);
  }
  return rules;
}

inline static std::vector<std::vector<int>> getUpdates(std::string line) {
  std::vector<std::vector<int>> updates;
  while (getline(std::cin, line)) {
    updates.push_back(mapToInt(split(line, ',')));
  }
  return updates;
}

inline static bool needsSwap(const std::map<int, std::vector<int>>& rules,
                             int a, int b) {
  const std::vector<int> rule = rules.at(b);
  return rules.count(b) && std::find(rule.begin(), rule.end(), a) != rule.end();
}

int main() {
  std::string line;
  const std::map<int, std::vector<int>> rules = getRules(line);
  const std::vector<std::vector<int>> updates = getUpdates(line);

  int correctSum = 0;
  int incorrectFixedSum = 0;
  for (auto update : updates) {
    bool correct = true;
    bool swapped = true;
    while (swapped) {
      swapped = false;
      for (unsigned long i = 0; i < update.size() - 1; i++) {
        if (needsSwap(rules, update[i], update[i + 1])) {
          std::swap(update[i], update[i + 1]);
          swapped = true;
          correct = false;
        }
      }
    }
    (correct ? correctSum : incorrectFixedSum) += update[update.size() / 2];
  }

  std::cout << "Part One:\nSum of Middle Pages in Correct Updates: "
            << correctSum << std::endl;
  std::cout << "Part One:\nSum of Middle Pages After Fixing Incorrect Updates: "
            << incorrectFixedSum << std::endl
            << std::endl;
}