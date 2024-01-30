def read_file(file_name):
    move = []
    location = {}
    first_goal = None

    with open(file_name, 'r') as fin:
        first_line = fin.readline().rstrip('\n')
        #print(first_line)
        move = [1 if i == 'L' else 2 for i in first_line]
        # # move = []
        # for i in first_line:
        #     if i == 'L':
        #         move.append(1)
        #     else:
        #         move.append(2)


        fin.readline()

        for line in fin:
            parts = line.strip().split(' = (')
            if len(parts) == 2:
                location_key = parts[0]
                if first_goal is None:
                    first_goal = location_key

                location_val = [value.strip() for value in parts[1].rstrip(')\n').split(',')]
                location[location_key] = location_val

    return move, location, first_goal

def count_step(move, location, goal):
    count = 0
    i = 0
    completed = False

    while completed == False:
        # print(goal)
        if move[i] == 1: goal = location[goal][0]
        elif move[i] == 2: goal = location[goal][1]

        if (goal[-1] == 'Z'): completed = True

        count += 1
        i += 1
        if (i == len(move)): i = 0

    return count

def get_end_with(location):
    end_A = []
    end_Z = []

    for value in location:
        if value[-1] == 'A':
            end_A.append(value)
        elif value[-1] == 'Z':
            end_Z.append(value)

    return end_A, end_Z
        
def cal_GCD(num1, num2):
    if num2 == 0: return num1
    else: return cal_GCD(num2, num1 % num2)

def cal_LCM(num1, num2):
    return (num1 * num2) // cal_GCD(num1, num2)

def get_step(arr_A, move, location):
    num_step = []
    for i in range(len(arr_A)):
        num_step.append(count_step(move, location, arr_A[i]))

    # print(num_step)

    result = cal_LCM(num_step[0], num_step[1])
    for i in range (2, len(num_step)):
        result = cal_LCM(result, num_step[i])

    return result 


file_name = 'input_day8.txt'
move, location, first_goal = read_file(file_name)
end_A, end_Z = get_end_with(location)


# print("Move:", move)
# print("Location:", location)
# print(end_Z)
# print(end_A)

print("Number step to end Z is: ", get_step(end_A, move, location))
