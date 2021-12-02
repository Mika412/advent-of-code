def read_file(filename: str) -> list[int]:
    lines = []
    with open(filename, 'r') as f:
        for line in f.readlines():
            line = line.strip()
            spl_line = line.split()
            lines.append([spl_line[0], int(spl_line[1])])

    return lines

def part_one(lines: list) -> int:
    horizontal = 0
    depth = 0
    for pair in lines:
        if pair[0] == "forward":
            horizontal += pair[1]
        elif pair[0] == "down":
            depth += pair[1]
        elif pair[0] == "up":
            depth -= pair[1]

    return horizontal * depth


def part_two(lines: list[str]) -> int:
    horizontal = 0
    depth = 0
    aim = 0
    for pair in lines:
        if pair[0] == "forward":
            horizontal += pair[1]
            depth += aim * pair[1]
        elif pair[0] == "down":
            aim += pair[1]
        elif pair[0] == "up":
            aim -= pair[1]

    return horizontal * depth


if __name__ == "__main__":
    input_path = "./input.txt"
    input = read_file(input_path)

    print("---Part One---")
    print(part_one(input))

    print("---Part Two---")
    print(part_two(input))
