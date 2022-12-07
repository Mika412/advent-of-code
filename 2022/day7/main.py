def calculate_upper_dirs(input: list[str]) -> list[str]:
    output = []
    for i in range(0, len(input)):
        output.append("/".join(input[: i + 1]))
    return output


def read_file(filename: str) -> dict[str, int]:
    directories = {}
    current_dir = []
    with open(filename, "r") as f:
        for line in f.readlines():
            com = line.strip().split(" ")
            if "$ cd /" in line:
                current_dir = ["/"]
            if "$ cd .." in line:
                current_dir.pop()
            elif "$ cd " in line:
                current_dir.append(com[2])
            elif com[0].isdigit():
                for val in calculate_upper_dirs(current_dir):
                    directories[val] = directories.get(val, 0) + int(com[0])
    return directories


def part_one(input: dict[str, int]) -> int:
    return sum([value for value in input.values() if value <= 100000])


def part_two(input: dict[str, int]) -> int:
    unused_space = 70_000_000 - input["/"]
    make_space = 30_000_000 - unused_space
    sorted_input = [value for value in input.values() if value >= make_space]
    return sorted(sorted_input)[0]


if __name__ == "__main__":
    input_path = "./input.txt"
    input = read_file(input_path)

    print("---Part One---")
    print(part_one(input))

    print("---Part Two---")
    print(part_two(input))
