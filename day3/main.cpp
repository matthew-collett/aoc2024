#include <iostream>
#include <regex>
#include <sstream>

static const auto r = std::regex(R"(mul\(\d{1,3}\,\d{1,3}\))");

inline static auto split(const std::string& s, const char delim) {
  std::vector<std::string> result;
  std::stringstream ss(s);
  std::string item;

  while (getline(ss, item, delim)) {
    result.push_back(item);
  }

  return result;
}

inline static int doMul(const std::string input) {
  int results = 0;
  auto begin = std::sregex_iterator(input.begin(), input.end(), r);

  for (auto& i = begin; i != std::sregex_iterator(); ++i) {
    auto ms = i->str();
    ms.erase(ms.begin(), ms.begin() + 4);
    ms.erase(ms.size() - 1);
    const auto& parts = split(ms, ',');
    std::vector<int> factors;
    std::transform(parts.begin(), parts.end(), std::back_inserter(factors),
                   [](const auto& s) { return std::stoi(s); });
    results += factors[0] * factors[1];
  }
  return results;
}

int main() {
  const auto& input = std::string(std::istreambuf_iterator<char>(std::cin), {});
  std::cout << "Part One:\nResults of Instructions: " << doMul(input)
            << std::endl;

  int enabledSum = 0;
  bool enabled = true;
  size_t pos = 0;

  while (pos < input.length()) {
    size_t doPosition = input.find("do()", pos);
    size_t dontPosition = input.find("don't()", pos);
    size_t next = input.length();

    if (doPosition != std::string::npos) {
      next = doPosition;
    }

    if (dontPosition != std::string::npos && dontPosition < next) {
      next = dontPosition;
    }

    if (enabled) {
      enabledSum += doMul(input.substr(pos, next - pos));
    }

    enabled = next == doPosition;
    pos = next + (enabled ? 4 : 6);
  }

  std::cout << "Part Two:\nResults of Enabled Instructions: " << enabledSum
            << std::endl
            << std::endl;
  return 0;
}