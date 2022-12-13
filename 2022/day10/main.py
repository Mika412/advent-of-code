import math


def read_file(filename: str) -> list[list[object]]:
    instructions = []
    with open(filename, "r") as f:
        for line in f.readlines():
            instr = line.strip().split()
            act = 0
            if len(instr) >= 2:
                act = instr[1]
            instructions.append([instr[0], int(act)])
    return instructions


def part_one(input: list[list[object]]) -> int:
    strength = 0
    total_cycles = 0
    X_reg = 1
    last_cycles = 0

    for instr, act in input:
        if not last_cycles:
            if instr == "noop":
                last_cycles = 1
            elif instr == "addx":
                last_cycles = 2

        while last_cycles:
            total_cycles += 1
            last_cycles -= 1
            if total_cycles == 20 or (total_cycles - 20) % 40 == 0:
                strength += total_cycles * X_reg

        X_reg += act

    return strength


def part_two(input: list[str]) -> int:
    head = [0, 0]
    tails = [[0, 0] for i in range(9)]
    return 0


if __name__ == "__main__":
    input_path = "./input.txt"
    input = read_file(input_path)

    print(input)
    print("---Part One---")
    print(part_one(input))

    # print("---Part Two---")
    # print(part_two(input))
