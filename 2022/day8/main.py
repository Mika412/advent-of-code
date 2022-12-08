def read_file(filename: str) -> dict[str, int]:
    trees = []
    with open(filename, "r") as f:
        for line in f.readlines():
            trees.append(list(map(int, line.strip())))
    return trees


def part_one(input: list[list[int]]) -> int:
    count = len(input) * 2 + len(input[0]) * 2 - 4
    for i in range(1, len(input) - 1):
        for j in range(1, len(input[0]) - 1):
            val = input[i][j]

            visible = False
            visible |= max(input[i][0:j]) < val
            visible |= max(input[i][j + 1 :]) < val
            visible |= max([row[j] for row in input[0:i]]) < val
            visible |= max([row[j] for row in input[i + 1 :]]) < val

            count += visible
    return count


def count_scenic(value: int, row: list[int]) -> int:
    for i in range(len(row)):
        if value <= row[i]:
            return i + 1
            break
    return len(row)


def part_two(input: list[list[int]]) -> int:
    max_count = 0
    for i in range(1, len(input) - 1):
        for j in range(1, len(input[0]) - 1):
            count = 1
            value = input[i][j]

            row_left = list(reversed(input[i][0:j]))
            row_right = input[i][j + 1 :]
            col_top = list(reversed([row[j] for row in input[0:i]]))
            col_bottom = [row[j] for row in input[i + 1 :]]

            count *= count_scenic(value, row_left)
            count *= count_scenic(value, row_right)
            count *= count_scenic(value, col_top)
            count *= count_scenic(value, col_bottom)
            max_count = max(max_count, count)
    return max_count


if __name__ == "__main__":
    input_path = "./input.txt"
    input = read_file(input_path)

    print("---Part One---")
    print(part_one(input))

    print("---Part Two---")
    print(part_two(input))
