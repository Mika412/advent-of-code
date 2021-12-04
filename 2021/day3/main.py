def read_file(filename: str) -> list[int]:
    lines = []
    with open(filename, 'r') as f:
        for line in f.readlines():
            line = line.strip()
            lines.append(line)

    return lines

def part_one(lines: list[int]) -> int:
    n_bits = len(lines[0])
    gamma_rate = ""
    epsilon_rate = ""
    for bit_pos in range(n_bits):
        bit_count = 0
        for line in lines:
            if line[bit_pos] == '1':
                bit_count += 1

        if bit_count > (len(lines) - bit_count):
            gamma_rate += "1"
            epsilon_rate += "0"
        else:
            gamma_rate += "0"
            epsilon_rate += "1"

    return int(gamma_rate, 2) * int(epsilon_rate, 2)


def part_two(lines: list[str]) -> int:
    n_bits = len(lines[0])
    oxigen = lines
    co2 = lines
    for bit_pos in range(n_bits):
        pos_list = []
        neg_list = []
        for line in oxigen:
            if line[bit_pos] == '1':
                pos_list.append(line)
            else:
                neg_list.append(line)

        if len(pos_list) >= len(neg_list):
            oxigen = pos_list
        else:
            oxigen = neg_list
        if len(co2) == 1:
            break

    for bit_pos in range(n_bits):
        pos_list = []
        neg_list = []
        for line in co2:
            if line[bit_pos] == '1':
                pos_list.append(line)
            else:
                neg_list.append(line)

        if len(pos_list) < len(neg_list):
            co2 = pos_list
        else:
            co2 = neg_list

        if len(co2) == 1:
            break
    return int(oxigen[0], 2) * int(co2[0], 2)


if __name__ == "__main__":
    input_path = "./input.txt"
    input = read_file(input_path)

    print("---Part One---")
    print(part_one(input))

    print("---Part Two---")
    print(part_two(input))
