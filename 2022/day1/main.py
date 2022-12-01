def read_file(filename: str) -> list[int]:
    lines = []
    calories = 0
    with open(filename, 'r') as f:
        for line in f.readlines():
            if not line.strip():
                lines.append(calories)
                calories = 0
                continue
            calories += int(line)

    return lines

def part_one(lines: list[int]) -> int:
    return max([lst for lst in lines])


def part_two(lines: list[int]) -> int:
    return sum(sorted([lst for lst in lines], reverse=True)[:3])


if __name__ == "__main__":
    input_path = "./input.txt"
    input = read_file(input_path)

    print("---Part One---")
    print(part_one(input))

    print("---Part Two---")
    print(part_two(input))
