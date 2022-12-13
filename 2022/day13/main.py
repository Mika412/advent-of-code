from ast import literal_eval
from itertools import zip_longest
from functools import cmp_to_key


def read_file(filename: str):
    pairs = []
    with open(filename, "r") as f:
        pair = []
        for line in f.readlines():
            if not line.strip():
                pairs.append(pair)
                pair = []
            else:
                pair.append(literal_eval(line.strip()))
    return pairs


def compare_pair(left, right) -> bool:
    if left is None:
        return -1

    if right is None:
        return 1

    elif isinstance(left, int) and isinstance(right, int):
        if left < right:
            return -1
        elif left > right:
            return 1
        else:
            return 0
    elif isinstance(left, int) and isinstance(right, list):
        return compare_pair([left], right)
    elif isinstance(left, list) and isinstance(right, int):
        return compare_pair(left, [right])
    else:
        for x, y in zip_longest(left, right):
            result = compare_pair(x, y)
            if result == 0:
                continue
            return result
    return 0


def part_one(input) -> int:
    count = []
    for idx, pair in enumerate(input):
        if compare_pair(pair[0], pair[1]) == -1:
            count.append(idx + 1)

    return sum(count)


def part_two(input) -> int:
    extra_pairs = [[[2]], [[6]]]
    flattened_pairs = []
    for pair in input:
        flattened_pairs.append(pair[0])
        flattened_pairs.append(pair[1])
    flattened_pairs += extra_pairs
    sorted_pairs = sorted(flattened_pairs, key=cmp_to_key(compare_pair))
    return (sorted_pairs.index(extra_pairs[0]) + 1) * (
        sorted_pairs.index(extra_pairs[1]) + 1
    )


if __name__ == "__main__":
    input_path = "./input.txt"
    input = read_file(input_path)

    print("---Part One---")
    print(part_one(input))

    print("---Part Two---")
    print(part_two(input))
