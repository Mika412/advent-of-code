import math


def read_file(filename: str) -> list[str]:
    moves = []
    with open(filename, "r") as f:
        for line in f.readlines():
            dir, times = line.strip().split()
            moves += [dir] * int(times)
    return moves


directions = {"U": [1, 0], "D": [-1, 0], "L": [0, -1], "R": [0, 1]}


def simulate_rope(input: list[str], head: list[int], tails: list[list[int]]) -> int:
    visited_pos = set()
    for dir in input:
        head[0] += directions[dir][0]
        head[1] += directions[dir][1]

        target = head
        for idx, tail in enumerate(tails):
            distance = math.sqrt(
                (target[0] - tail[0]) ** 2 + (target[1] - tail[1]) ** 2
            )
            if distance >= 2:
                tail[0] += max(min(target[0] - tail[0], 1), -1)
                tail[1] += max(min(target[1] - tail[1], 1), -1)

                if idx == len(tails) - 1:
                    visited_pos.add(tuple(tail))

            target = tail

    return len(visited_pos) + 1


def part_one(input: list[str]) -> int:
    head = [0, 0]
    tails = [[0, 0]]
    return simulate_rope(input, head, tails)


def part_two(input: list[str]) -> int:
    head = [0, 0]
    tails = [[0, 0] for i in range(9)]
    return simulate_rope(input, head, tails)


if __name__ == "__main__":
    input_path = "./input.txt"
    input = read_file(input_path)

    print("---Part One---")
    print(part_one(input))

    print("---Part Two---")
    print(part_two(input))
