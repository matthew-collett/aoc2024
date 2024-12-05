#include <algorithm>
#include <iostream>
#include <map>
#include <sstream>

void printVec(const std::vector<int>& vec) {
  std::cout << "[ ";
  for (int x : vec)
    std::cout << x << " ";
  std::cout << "]\n";
}

void printMap(const std::map<int, std::vector<int>>& m) {
  std::cout << "{\n";
  for (const auto& [key, vec] : m) {
    std::cout << "  " << key << ": ";
    printVec(vec);
  }
  std::cout << "}\n";
}

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

inline static bool followsRule(const std::vector<int> rule, const int page) {
  return std::find(rule.begin(), rule.end(), page) != rule.end();
}

inline static bool needsSwap(const std::map<int, std::vector<int>>& rules,
                             int a, int b) {
  if (rules.count(b) && followsRule(rules.at(b), a)) {
    return true;
  }
  return false;
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