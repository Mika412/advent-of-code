import math
import copy


def read_file(filename: str):
    map = []
    end = (0, 0)
    with open(filename, "r") as f:
        for line in f.readlines():
            row = []
            for idx, char in enumerate(list(line.strip())):
                if char == "S":
                    row.append(-1)
                elif char == "E":
                    row.append(26)
                    end = (idx, len(map))
                else:
                    row.append(ord(char) - 97)
            map.append(row)
    return map, end


def get_valid_neighbours(grid, x, y) -> int:
    neighbours = []
    possible_neighbours = [(x - 1, y), (x + 1, y), (x, y - 1), (x, y + 1)]
    for i, j in possible_neighbours:
        if (
            i in range(0, len(grid[0]))
            and j in range(0, len(grid))
            and (grid[j][i] >= grid[y][x] or (grid[j][i] + 1 == grid[y][x]))
        ):
            neighbours.append((i, j))

    return neighbours


def find_shortest_path(grid, start, target) -> int:
    visited = []
    to_visit = [start]
    visited_map = [[0] * len(grid[0]) for _ in range(len(grid))]

    while len(to_visit):
        x, y = to_visit.pop(0)

        if grid[y][x] in target:
            return visited_map[y][x]

        for i, j in get_valid_neighbours(grid, x, y):
            if (i, j) not in visited:
                to_visit.append((i, j))
                visited_map[j][i] = visited_map[y][x] + 1
                visited.append((i, j))


def part_one(grid, end) -> int:
    return find_shortest_path(grid, end, [-1])


def part_two(grid, end) -> int:
    return find_shortest_path(grid, end, [-1, 0])


if __name__ == "__main__":
    input_path = "./input.txt"
    grid, end = read_file(input_path)

    print("---Part One---")
    print(part_one(grid, end))

    print("---Part Two---")
    print(part_two(grid, end))
