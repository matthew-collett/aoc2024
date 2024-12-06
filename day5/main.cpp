#include <iostream>
#include <map>
#include <sstream>

inline static auto split(const std::string& s, const char delim) {
  std::vector<std::string> result;
  std::stringstream ss(s);
  std::string item;

  while (getline(ss, item, delim)) {
    result.push_back(item);
  }
  return result;
}

inline static auto mapToInt(const std::vector<std::string>& v) {
  std::vector<int> v2;
  std::transform(v.begin(), v.end(), std::back_inserter(v2),
                 [](const auto& s) { return std::stoi(s); });
  return v2;
}

inline static auto getRules(std::string line) {
  std::map<int, std::vector<int>> rules;

  while (getline(std::cin, line)) {
    if (line.empty()) {
      break;
    }

    const auto& parts = mapToInt(split(line, '|'));
    const auto& key = parts[0];
    const auto& value = parts[1];

    if (!rules.count(key)) {
      rules.insert({key, std::vector<int>{value}});
      continue;
    }
    rules.at(key).push_back(value);
  }
  return rules;
}

inline static auto getUpdates(std::string line) {
  std::vector<std::vector<int>> updates;

  while (getline(std::cin, line)) {
    updates.push_back(mapToInt(split(line, ',')));
  }
  return updates;
}

inline static bool needsSwap(const std::map<int, std::vector<int>>& rules,
                             const int a, const int b) {
  if (!rules.count(b)) {
    return false;
  }
  const auto& rule = rules.at(b);
  return std::find(rule.begin(), rule.end(), a) != rule.end();
}

int main() {
  std::string line;
  const auto& rules = getRules(line);
  const auto& updates = getUpdates(line);

  int correctSum = 0;
  int incorrectFixedSum = 0;

  for (const auto& update : updates) {
    bool correct = true;
    bool swapped = true;

    auto currentUpdate = update;
    while (swapped) {
      swapped = false;
      for (size_t i = 0; i < currentUpdate.size() - 1; i++) {
        if (needsSwap(rules, currentUpdate[i], currentUpdate[i + 1])) {
          std::swap(currentUpdate[i], currentUpdate[i + 1]);
          swapped = true;
          correct = false;
        }
      }
    }

    (correct ? correctSum : incorrectFixedSum) +=
        currentUpdate[currentUpdate.size() / 2];
  }

  std::cout << "Part One:\nSum of Middle Pages in Correct Updates: "
            << correctSum << std::endl;
  std::cout << "Part One:\nSum of Middle Pages After Fixing Incorrect Updates: "
            << incorrectFixedSum << std::endl
            << std::endl;
  return 0;
}