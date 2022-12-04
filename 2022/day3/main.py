def read_file(filename: str) -> list[str]:
    lines = []
    with open(filename, "r") as f:
        for line in f.readlines():
            lines.append(line.strip())
    return lines


def calc_char_priority(item: str) -> int:
    return ord(item) - 38 if item.isupper() else ord(item) - 96


def part_one(lines: list[str]) -> int:
    score = 0
    for rucksack in lines:
        chars = len(rucksack) // 2
        existing_chars = set(rucksack[:chars]).intersection(rucksack[chars:])
        for item in existing_chars:
            score += calc_char_priority(item)
    return score


def part_two(rucksacks: list[str]) -> int:
    score = 0
    for i in range(0, len(rucksacks), 3):
        existing_chars = set(rucksacks[i]).intersection(rucksacks[i + 1])
        existing_chars = set(existing_chars).intersection(rucksacks[i + 2])
        score += calc_char_priority(list(existing_chars)[0])
    return score


if __name__ == "__main__":
    input_path = "./input.txt"
    input = read_file(input_path)
    print("---Part One---")
    print(part_one(input))

    print("---Part Two---")
    print(part_two(input))
