import copy


def read_file(filename: str) -> tuple[list[list[str]], list[str]]:
    crates = {}
    instructions = []
    with open(filename, "r") as f:
        for line in f.readlines():
            if "[" in line:
                for i in range(0, int(len(line) / 4)):
                    crate = line[i * 4 + 1: i * 4 + 2]
                    if i not in crates:
                        crates[i] = []

                    if not crate == " ":
                        crates[i].append(crate)

            elif "move" in line:
                line = line.split("move ")[1]
                many, line = line.split(" from ")
                frm, to = line.split(" to ")
                instructions.append([int(many), int(frm) - 1, int(to) - 1])

    return crates, instructions


def part_one(crates: list[str], instructions: list[str]) -> str:
    for many, frm, to in instructions:
        for i in range(many):
            item = crates[frm].pop(0)
            crates[to].insert(0, item)

    return "".join([values[0] for values in crates.values()])


def part_two(crates: list[str], instructions: list[str]) -> str:
    for many, frm, to in instructions:
        item = crates[frm][:many]
        del crates[frm][:many]
        crates[to] = item + crates[to]
    return "".join([values[0] for values in crates.values()])


if __name__ == "__main__":
    input_path = "./input.txt"
    crates, instructions = read_file(input_path)

    print("---Part One---")
    print(part_one(copy.deepcopy(crates), instructions))

    print("---Part Two---")
    print(part_two(copy.deepcopy(crates), instructions))
