import copy


def read_file(filename: str):
    paths = []
    max_x, max_y = float("-inf"), float("-inf")
    min_x = float("inf")
    with open(filename, "r") as f:
        for line in f.readlines():
            path = []
            for trace in line.strip().split(" -> "):
                x, y = trace.split(",")
                max_x = max(int(x), max_x)
                max_y = max(int(y), max_y)
                min_x = min(int(x), min_x)
                path.append([int(x), int(y)])
            paths.append(path)

    # Create board
    board = [[0 for x in range(max_x - min_x + 1)] for _ in range(max_y)]
    for path in paths:
        for i in range(1, len(path)):
            x_start = min(path[i - 1][0], path[i][0])
            x_end = max(path[i - 1][0], path[i][0])
            y_start = min(path[i - 1][1], path[i][1])
            y_end = max(path[i - 1][1], path[i][1])

            for x in range(x_start - min_x, x_end - min_x + 1):
                for y in range(y_start - 1, y_end):
                    board[y][x] = "#"
    return board, 500 - min_x


def add_sand_particle(board, cur_x, cur_y):
    while True:
        # Check bottom
        if cur_y <= len(board) and not board[cur_y + 1][cur_x]:
            cur_y += 1
            continue

        # Check bottom left
        if cur_y < len(board) and cur_x > 0 and not board[cur_y + 1][cur_x - 1]:
            cur_y += 1
            cur_x -= 1
            continue

        # Check bottom right
        if (
            cur_y < len(board)
            and cur_x < len(board[0]) - 1
            and not board[cur_y + 1][cur_x + 1]
        ):
            cur_y += 1
            cur_x += 1
            continue

        # Check for overflow
        if cur_x == 0 or cur_x == len(board[0]) - 1:
            return board, True

        board[cur_y][cur_x] = "o"
        return board, False


def part_one(board, start_x) -> int:
    overflowed = False
    counter = -1

    while not overflowed:
        board, overflowed = add_sand_particle(board, start_x, 0)
        counter += 1

    return counter


def part_two(board, start_x) -> int:
    # board.insert(0, [0] * len(board[0]))
    board.insert(0, [0] * len(board[0]))
    board.append([0] * len(board[0]))
    board.append(["#"] * len(board[0]))

    counter = 0
    while not board[0][start_x]:
        board, overflowed = add_sand_particle(board, start_x, 0)
        if overflowed:
            start_x += 1

            # Expand board
            for y in range(len(board) - 1):
                board[y].insert(0, 0)
                board[y].append(0)

            board[-1].insert(0, "#")
            board[-1].append("#")
        else:
            counter += 1

    return counter


if __name__ == "__main__":
    input_path = "./input.txt"
    input, start_x = read_file(input_path)

    print("---Part One---")
    print(part_one(copy.deepcopy(input), start_x))

    print("---Part Two---")
    print(part_two(input, start_x))
