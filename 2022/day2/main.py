def read_file(filename: str) -> list[list[str]]:
    lines = []
    calories = 0
    with open(filename, "r") as f:
        for line in f.readlines():
            lines.append(line.split())

    return lines

score_map = {'X':1, 'Y':2, 'Z':3}
winning_comb = [['A', 'Y'], ['B','Z'], ['C','X']]
draw_comb = [['A', 'X'], ['B','Y'], ['C','Z']]
def part_one(lines: list[list[str]]) -> int:
    score = 0
    for line in lines:
        score += (line in draw_comb) * 3
        score += (line in winning_comb) * 6
        score += score_map[line[1]]
    return score


winning_map = {'A': 'Y', 'B':'Z', 'C':'X'}
draw_map = {'A': 'X', 'B':'Y', 'C':'Z'}
lose_map = {'A': 'Z', 'B':'X', 'C':'Y'}
def part_two(lines: list[list[str]]) -> int:
    for i, line in enumerate(lines):
        act, choice = line 
        if choice == 'X':
            lines[i][1] = lose_map[act]
        elif choice == 'Y':
            lines[i][1] = draw_map[act]
        elif choice == 'Z':
            lines[i][1] = winning_map[act]
    return part_one(lines)

if __name__ == "__main__":
    input_path = "./input.txt"
    input = read_file(input_path)
    print("---Part One---")
    print(part_one(input))

    print("---Part Two---")
    print(part_two(input))
