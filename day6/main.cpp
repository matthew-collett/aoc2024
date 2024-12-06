#include <iostream>
#include <set>

struct Position {
  size_t x, y;

  bool operator<(const Position& other) const {
    if (x != other.x)
      return x < other.x;
    return y < other.y;
  }

  bool operator==(const Position& other) const {
    return x == other.x && y == other.y;
  }
};

struct PathResult {
  size_t numPositions;
  bool isLoop;
};

enum Direction { UP = 0, RIGHT = 1, DOWN = 2, LEFT = 3 };

const int dx[] = {-1, 0, 1, 0};
const int dy[] = {0, 1, 0, -1};

inline static auto getInputMap() {
  std::string line;
  std::vector<std::vector<char>> map;
  while (getline(std::cin, line)) {
    std::vector<char> row(line.begin(), line.end());
    map.push_back(row);
  }
  return map;
}

inline static bool inBounds(const std::vector<std::vector<char>>& map,
                            const Position& pos) {
  return pos.x < map.size() && pos.y < map[0].size();
}

inline static Position getStartPosition(
    const std::vector<std::vector<char>>& map) {
  for (size_t i = 0; i < map.size(); i++) {
    const auto& it = find(map[i].begin(), map[i].end(), '^');
    if (it != map[i].end()) {
      return {i, static_cast<size_t>(it - map[i].begin())};
    }
  }
  return {0, 0};
}

inline static Position nextPosition(const Position& pos, int direction) {
  return {pos.x + dx[direction], pos.y + dy[direction]};
}

inline static PathResult runPath(const std::vector<std::vector<char>>& map,
                                 Position pos, int direction,
                                 std::set<Position>& visited) {
  std::set<std::pair<Position, int>> seenStates;
  visited.insert(pos);

  while (true) {
    auto state = std::make_pair(pos, direction);
    if (!seenStates.insert(state).second) {
      return {visited.size(), true};
    }

    Position next = nextPosition(pos, direction);
    if (!inBounds(map, next)) {
      return {visited.size(), false};
    }

    for (int i = 0; i < 4 && inBounds(map, next) && map[next.x][next.y] == '#';
         ++i) {
      direction = (direction + 1) % 4;
      next = nextPosition(pos, direction);
    }

    if (!inBounds(map, next) || map[next.x][next.y] == '#') {
      return {visited.size(), false};
    }

    visited.insert(next);
    pos = next;
  }
}

inline static int findStuckPositions(
    const std::vector<std::vector<char>>& map) {
  int stuckPositions = 0;
  const Position& start = getStartPosition(map);

  for (size_t i = 0; i < map.size(); i++) {
    for (size_t j = 0; j < map[0].size(); j++) {
      const Position& currentPos = {i, j};
      if (currentPos == start || map[i][j] == '#') {
        continue;
      }

      auto tempMap = map;
      tempMap[i][j] = '#';
      std::set<Position> visited;
      const auto& result = runPath(tempMap, start, UP, visited);
      if (result.isLoop) {
        stuckPositions++;
      }
    }
  }
  return stuckPositions;
}

int main() {
  const auto& map = getInputMap();
  const Position& start = getStartPosition(map);
  std::set<Position> visited;
  const PathResult& result = runPath(map, start, UP, visited);

  std::cout << "Part One:\nNumber of Distinct Positions: "
            << result.numPositions << std::endl;

  const int& stuckPositions = findStuckPositions(map);
  std::cout << "Part Two:\nNumber of Different Positions for Obstacles: "
            << stuckPositions << std::endl;
}
