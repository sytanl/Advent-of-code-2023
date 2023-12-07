#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
#include <vector>



void read_file(std::ifstream &fin,std::string file_name, std::vector<std::string> &lines)
{
    fin.open(file_name);
    std::string line;

    while (!fin.eof())
    {
        fin >> line;
        lines.push_back(line);
    }

    fin.close();
}

int find_number_in_line(std::vector<std::string> lines, int row, int position)
{
    if (lines[row][position] == 'o' && lines[row].substr(position, 3) == "one") return 1;
    else if (lines[row][position] == 't')
    {
        if (lines[row].substr(position, 3) == "two") return 2;
        else if (lines[row].substr(position, 5) == "three") return 3;
    } 
    else if (lines[row][position] == 'f')
    {
        if (lines[row].substr(position, 4) == "four") return 4;
        else if (lines[row].substr(position, 4) == "five") return 5;
    }
    else if (lines[row][position] == 's')
    {
        if (lines[row].substr(position, 3) == "six") return 6;
        else if (lines[row].substr(position, 5) == "seven") return 7;
    }
    else if (lines[row][position] == 'e' && lines[row].substr(position, 5) == "eight") return 8;
    else if (lines[row][position] == 'n' && lines[row].substr(position, 4) == "nine") return 9;

    return 0;
}

int cal_sum(std::vector<std::string> lines)
{
    int sum = 0;
    for (int i = 0; i < lines.size(); i++)
    {
        int num = 0, num1 = 0, num2 = 0;
        int flag[2] = {0, 0};
        for (int j = 0; j < lines[i].length(); j++)
        {
            if (num1 == 0 && isdigit(lines[i][j])) 
            {
                num1 = lines[i][j] - '0';
                flag[0] = 1;
            }

            if (num1 == 0 && find_number_in_line(lines, i, j) != 0)
            {
                num1 = find_number_in_line(lines, i, j);
                flag[0] = 1;
            }

            if (num1 != 0 && isdigit(lines[i][j]))
            {
                num2 = lines[i][j] - '0';

                flag[1] = 1;
            }
            
            if (num1 != 0 && find_number_in_line(lines, i, j) != 0)
            {
                num2 = find_number_in_line(lines, i, j);
                flag[1] = 1;
            }

        }

        if (flag[0] + flag[1] == 2) num += num1 * 10 + num2;
        else num += num1 * 10 + num1; 
        sum += num;
    }

    return sum;
}

int main()
{
    std::ifstream fin;
    std::string file_name = "input.txt";
    std::vector<std::string> lines;


    read_file(fin, file_name, lines);

    std::cout << cal_sum(lines);

    return 0;
}