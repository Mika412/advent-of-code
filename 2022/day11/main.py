import math
import copy


def read_file(filename: str):
    monkeys = []
    with open(filename, "r") as f:
        cur_monkey = {}
        for line in f.readlines():
            line = line.strip()
            if "Monkey " in line:
                _, m_num = line.split("Monkey ")
                cur_monkey = {"num": int(m_num[:-1])}
            elif "Starting items:" in line:
                _, items = line.split("Starting items: ")
                cur_monkey["items"] = [int(item) for item in items.split(",")]
            elif "Operation: " in line:
                _, operations = line.split("Operation: new = ")
                cur_monkey["operations"] = operations
            elif "Test: " in line:
                _, divisible_by = line.split("Test: divisible by ")
                cur_monkey["divisible_by"] = int(divisible_by)
            elif "If true: " in line:
                _, divisible_true = line.split("If true: throw to monkey ")
                cur_monkey["divisible_true"] = int(divisible_true)
            elif "If false: " in line:
                _, divisible_false = line.split("If false: throw to monkey ")
                cur_monkey["divisible_false"] = int(divisible_false)
            elif "If false: " in line:
                _, divisible_false = line.split("If false: throw to monkey ")
                cur_monkey["divisible_false"] = int(divisible_false)
            else:
                cur_monkey["worry_level"] = []
                monkeys.append(cur_monkey)
    return monkeys


def get_top_monkeys(monkeys, rounds, should_worry, use_lcm=False) -> int:
    lcm = math.lcm(*[monkey["divisible_by"] for monkey in monkeys])
    monkey_count = [0] * len(monkeys)

    for i in range(rounds):
        for i, monkey in enumerate(monkeys):
            while len(monkey["items"]) > 0:
                item = monkey["items"].pop(0)
                monkey_count[i] += 1

                # Perform operation
                item = eval(monkey["operations"].replace("old", str(item)))

                # Reduce worry
                if should_worry:
                    item /= 3

                item = math.floor(item)

                # LCM optimisation
                if use_lcm:
                    if item > lcm:
                        item = lcm + item % lcm

                # Check divisible
                if item % monkey["divisible_by"] == 0:
                    monkeys[monkey["divisible_true"]]["items"].append(item)
                else:
                    monkeys[monkey["divisible_false"]]["items"].append(item)
    count = sorted(monkey_count, reverse=True)
    return count[0] * count[1]


def part_one(input) -> int:
    return get_top_monkeys(input, 20, True)


def part_two(input) -> int:
    return get_top_monkeys(input, 10000, False, True)


if __name__ == "__main__":
    input_path = "./input.txt"
    input = read_file(input_path)

    print("---Part One---")
    print(part_one(copy.deepcopy(input)))

    print("---Part Two---")
    print(part_two(input))
