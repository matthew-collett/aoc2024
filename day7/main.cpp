#include <iostream>
#include <sstream>
#include <string>

struct Operation {
  const long testValue;
  const std::vector<long> numbers;
};

inline static auto split(const std::string& s, const char delim) {
  std::vector<std::string> result;
  std::stringstream ss(s);
  std::string item;

  while (getline(ss, item, delim)) {
    result.push_back(item);
  }

  return result;
}

inline static auto mapToLong(const std::vector<std::string>& v) {
  std::vector<long> v2;
  std::transform(v.begin(), v.end(), std::back_inserter(v2),
                 [](const auto& s) { return std::stol(s); });
  return v2;
}

inline static auto getInput() {
  std::string line;
  std::vector<Operation> operations;
  while (getline(std::cin, line)) {
    const auto& parts = split(line, ':');
    auto numbers = split(parts[1], ' ');
    numbers.erase(numbers.begin());
    operations.push_back(Operation{std::stol(parts[0]), mapToLong(numbers)});
  }
  return operations;
}

inline static auto operatorCombinations(const size_t& numOps) {
  std::vector<std::vector<char>> combinations;
  for (int i = 0; i < 1 << numOps; i++) {
    std::vector<char> ops;
    for (int bit = numOps - 1; bit >= 0; bit--) {
      ops.push_back((i & (1 << bit)) ? '*' : '+');
    }
    combinations.push_back(ops);
  }
  return combinations;
}

inline static auto operatorCombinationsPartTwo(const size_t& numOps) {
  std::vector<std::vector<char>> combinations;
  int total = pow(3, numOps);

  for (int i = 0; i < total; i++) {
    std::vector<char> ops;
    int num = i;
    for (size_t j = 0; j < numOps; j++) {
      int remainder = num % 3;
      if (remainder == 0) {
        ops.push_back('+');
      } else {
        ops.push_back(remainder == 1 ? '*' : '|');
      }
      num /= 3;
    }
    combinations.push_back(ops);
  }
  return combinations;
}

inline static long evaluateLeftToRight(const std::vector<long>& testValues,
                                       const std::vector<char>& operators) {
  long result = testValues[0];
  for (size_t i = 0; i < operators.size(); i++) {
    if (operators[i] == '+') {
      result += testValues[i + 1];
      continue;
    }

    if (operators[i] == '*') {
      result *= testValues[i + 1];
      continue;
    }

    if (operators[i] == '|') {
      std::string concat =
          std::to_string(result) + std::to_string(testValues[i + 1]);
      result = std::stol(concat);
      continue;
    }
  }
  return result;
}

inline static long calcCalibration(const std::vector<Operation>& operations) {
  long calibrationResult = 0;
  for (const auto& op : operations) {
    for (const auto& opCombinations :
         operatorCombinations(op.numbers.size() - 1)) {
      if (op.testValue == evaluateLeftToRight(op.numbers, opCombinations)) {
        calibrationResult += op.testValue;
        break;
      }
    }
  }
  return calibrationResult;
}

inline static long calcCalibrationPartTwo(
    const std::vector<Operation>& operations) {
  long calibrationResult = 0;
  for (const auto& op : operations) {
    for (const auto& opCombinations :
         operatorCombinationsPartTwo(op.numbers.size() - 1)) {
      if (op.testValue == evaluateLeftToRight(op.numbers, opCombinations)) {
        calibrationResult += op.testValue;
        break;
      }
    }
  }
  return calibrationResult;
}

int main() {
  const auto& operations = getInput();
  std::cout << "Part One:\nCalibration Result: " << calcCalibration(operations)
            << std::endl;
  std::cout << "Part Two:\nCalibration Result: "
            << calcCalibrationPartTwo(operations) << std::endl
            << std::endl;
  return 0;
}