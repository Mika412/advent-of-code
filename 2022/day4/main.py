def read_file(filename: str) -> list[str]:
    lines = []
    with open(filename, "r") as f:
        for line in f.readlines():
            line = line.replace(",", " ").replace("-", " ")
            left_btm, left_up, right_btm, right_up = [
                int(item) for item in line.split(" ")
            ]
            lines.append([[left_btm, left_up], [right_btm, right_up]])
    return lines


def calc_char_priority(item: str) -> int:
    return ord(item) - 38 if item.isupper() else ord(item) - 96


def part_one(lines: list[int]) -> int:
    count = 0
    for left, right in lines:
        count += (left[0] >= right[0] and left[1] <= right[1]) or (
            right[0] >= left[0] and right[1] <= left[1]
        )
    return count


def part_two(lines: list[int]) -> int:
    count = 0
    for left, right in lines:
        count += (left[0] <= right[0] and left[1] >= right[0]) or (
            right[0] <= left[0] and right[1] >= left[0]
        )
    return count


if __name__ == "__main__":
    input_path = "./input.txt"
    input = read_file(input_path)

    print("---Part One---")
    print(part_one(input))

    print("---Part Two---")
    print(part_two(input))
