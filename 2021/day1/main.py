def read_file(filename: str) -> list[int]:
    lines = []
    with open(filename, 'r') as f:
        lines = [int(line) for line in f.readlines()]

    return lines

def part_one(lines: list[str]) -> int:
    count = 0
    for i in range(1, len(lines)):
        count += lines[i] > lines[i-1]

    return count


def part_two(lines: list[str]) -> int:
    count = 0
    for i in range(4, len(lines) + 3):
        lower = sum(lines[max(i-3-1, 0):max(i-1, 0)])
        upper = sum(lines[max(i-3, 0):max(i, 0)])

        count += lower < upper

    return count


if __name__ == "__main__":
    input_path = "./input.txt"
    input = read_file(input_path)

    print("---Part One---")
    print(part_one(input))

    print("---Part Two---")
    print(part_two(input))
