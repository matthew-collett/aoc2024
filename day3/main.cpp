#include <iostream>
#include <regex>
#include <sstream>

static const auto r = std::regex(R"(mul\(\d{1,3}\,\d{1,3}\))");

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

inline static int doMul(const std::string input) {
  int results = 0;
  std::sregex_iterator begin =
      std::sregex_iterator(input.begin(), input.end(), r);

  for (std::sregex_iterator i = begin; i != std::sregex_iterator(); ++i) {
    std::string ms = i->str();
    ms.erase(ms.begin(), ms.begin() + 4);
    ms.erase(ms.size() - 1);
    std::vector<std::string> parts = split(ms, ',');
    std::vector<int> factors;
    std::transform(parts.begin(), parts.end(), std::back_inserter(factors),
                   [](const std::string& s) { return std::stoi(s); });
    results += factors[0] * factors[1];
  }
  return results;
}

int main() {
  std::string input = std::string(std::istreambuf_iterator<char>(std::cin), {});
  std::cout << "Part One:\nResults of Instructions: " << doMul(input)
            << std::endl;

  int enabledSum = 0;
  bool enabled = true;
  size_t pos = 0;

  while (pos < input.length()) {
    size_t doPos = input.find("do()", pos);
    size_t dontPos = input.find("don't()", pos);
    size_t next = input.length();

    if (doPos != std::string::npos || dontPos != std::string::npos) {
      next = std::min(doPos != std::string::npos ? doPos : input.length(),
                      dontPos != std::string::npos ? dontPos : input.length());
    }

    if (enabled) {
      enabledSum += doMul(input.substr(pos, next - pos));
    }

    if (next == input.length()) {
      break;
    }

    enabled = (next == doPos);
    pos = next + (enabled ? 4 : 6);
  }

  std::cout << "Part Two:\nResults of Enabled Instructions: " << enabledSum
            << std::endl;
  return 0;
}