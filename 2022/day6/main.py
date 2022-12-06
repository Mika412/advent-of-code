def read_file(filename: str) -> str:
    with open(filename, "r") as f:
        for line in f.readlines():
            return line

    return ""


def get_sequence_count(input: str, n_chars: int) -> int:
    for i in range(n_chars, len(input)):
        if len(set(input[i - n_chars : i])) == n_chars:
            return i
    return -1


def part_one(input: str) -> int:
    return get_sequence_count(input, 4)


def part_two(input: str) -> int:
    return get_sequence_count(input, 14)


if __name__ == "__main__":
    input_path = "./input.txt"
    input = read_file(input_path)

    print(input)
    print("---Part One---")
    print(part_one(input))

    print("---Part Two---")
    print(part_two(input))
