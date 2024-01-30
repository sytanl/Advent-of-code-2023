def read_file(file_name):
    history = []

    with open(file_name, 'r') as fin:
        for line in fin:
            value = line.strip().split()
            history.append(value)
    
    return history

def analysis_history(history_line, sum):
    new_history = []
    sum += int(history_line[-1])

    for i in range(0, len(history_line) - 1):
        value = int(history_line[i + 1]) - int(history_line[i])
        new_history.append(value)

    flag = all(element == 0 for element in new_history)
    if flag: return sum

    return analysis_history(new_history, sum)

def count_sum_history(history):
    result = 0
    for line in history:
        sum = 0
        result += int(analysis_history(line, sum))

    return result

file_name = 'input.txt'
history = read_file(file_name)

print("Result: ", count_sum_history(history))