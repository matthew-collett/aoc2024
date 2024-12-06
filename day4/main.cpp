#include <iostream>

inline static auto getInput() {
  std::vector<std::vector<char>> wordSearch;
  std::string line;
  while (std::cin >> line) {
    std::vector<char> row;
    for (const auto& ch : line) {
      row.push_back(ch);
    }
    wordSearch.push_back(row);
  }
  return wordSearch;
}

inline static bool inBounds(const std::vector<std::vector<char>>& wordSearch,
                            const unsigned long x, const unsigned long y) {
  return x >= 0 && x < wordSearch.size() && y >= 0 && y < wordSearch[0].size();
}

inline static bool findWord(unsigned long i, const std::string word,
                            const std::vector<std::vector<char>>& wordSearch,
                            int x, int y, int dx, int dy) {
  if (i == word.length()) {
    return true;
  }

  if (inBounds(wordSearch, x, y) && word[i] == wordSearch[x][y]) {
    return findWord(i + 1, word, wordSearch, x + dx, y + dy, dx, dy);
  }
  return false;
}

inline static int countXMAS(const std::vector<std::vector<char>> wordSearch) {
  const std::vector<std::pair<int, int>> directions = {
      {-1, -1},  // northwest
      {-1, 0},   // north
      {-1, 1},   // northeast
      {0, -1},   // west
      {0, 1},    // east
      {1, -1},   // southwest
      {1, 0},    // south
      {1, 1}     // southeast
  };

  int count = 0;
  for (size_t i = 0; i < wordSearch.size(); i++) {
    for (size_t j = 0; j < wordSearch[0].size(); j++) {
      for (const auto& dir : directions) {
        if (findWord(0, "XMAS", wordSearch, i, j, dir.first, dir.second)) {
          count++;
        }
      }
    }
  }
  return count;
}

int countXShapeXMAS(const std::vector<std::vector<char>>& grid) {
  int count = 0;
  for (size_t i = 1; i < grid.size() - 1; i++) {
    for (size_t j = 1; j < grid[0].size() - 1; j++) {
      if (grid[i][j] != 'A') {
        continue;
      }

      char nw = grid[i - 1][j - 1];  // northwest
      char ne = grid[i - 1][j + 1];  // northeast
      char sw = grid[i + 1][j - 1];  // southwest
      char se = grid[i + 1][j + 1];  // southeast

      if (((nw == 'M' && se == 'S') || (nw == 'S' && se == 'M')) &&
          ((ne == 'M' && sw == 'S') || (ne == 'S' && sw == 'M'))) {
        count++;
      }
    }
  }
  return count;
}

int main() {
  const auto& wordSearch = getInput();
  std::cout << "Part One:\nNumber of XMAS Occurrences: "
            << countXMAS(wordSearch) << std::endl;
  std::cout << "Part Two:\nNumber of X Shape XMAS Occurrences: "
            << countXShapeXMAS(wordSearch) << std::endl
            << std::endl;
  return 0;
}