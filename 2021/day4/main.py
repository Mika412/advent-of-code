def read_file(filename: str) -> list[int]:
    nums = []
    boards = []
    new_board = []
    with open(filename, 'r') as f:
        nums = list(map(int, f.readline().strip().split(',')))
        for line in f.readlines():
            line = line.strip()
            if line == "":
                boards.append(new_board)
                new_board = []
                continue

            line = list(map(int, filter(None, line.split(' '))))
            new_board.append(line)
    return nums, boards

def find_board_rows(input_nums, input_boards):
    selected_items = []
    for new_num in input_nums:
        selected_items.append(new_num)
        for board in input_boards:
            for row in board:
                if all(elem in selected_items for elem in row):
                    return selected_items, board

    return None, None

def find_board_rows_cols(input_nums, input_boards):
    selected_items = []
    for new_num in input_nums:
        selected_items.append(new_num)
        for board in input_boards:
            for row in board:
                if all(elem in selected_items for elem in row):
                    return selected_items, board

            for col_idx in range(5):
                col = []
                for row in board:
                    col.append(row[col_idx])

                if all(elem in selected_items for elem in col):
                    return selected_items, board
    return None, None

def part_one(input_nums: list[int], input_boards: list[list[int]]) -> int:
    selected_items, selected_board = find_board_rows(input_nums, input_boards)
    unmarked_nums = []
    for row in selected_board:
        unmarked_nums.extend(list(set(row) - set(selected_items)))

    return sum(unmarked_nums) * selected_items[-1]


def part_two(input_nums: list[int], input_boards: list[list[int]]) -> int:
    selected_items = []
    won_board = []
    won_items = []
    while selected_items != input_nums:
        selected_items, selected_board = find_board_rows_cols(input_nums, input_boards)

        if selected_board is None or selected_items is None:
            break

        won_board.append(selected_board)
        won_items.append(selected_items)
        input_boards.remove(selected_board)

    unmarked_nums = []
    for row in won_board[-1]:
        unmarked_nums.extend(list(set(row) - set(won_items[-1])))
    return sum(unmarked_nums) * won_items[-1][-1]


if __name__ == "__main__":
    input_path = "./input.txt"
    input_nums, input_boards = read_file(input_path)

    print("---Part One---")
    print(part_one(input_nums, input_boards))

    print("---Part Two---")
    print(part_two(input_nums, input_boards))
