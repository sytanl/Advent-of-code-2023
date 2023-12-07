#include <iostream>
#include <string>
#include <fstream>
#include <cctype>
#include <vector>
#include <sstream>

bool check_valid_for_top_left(std::vector<std::vector<char>> character)
{
    if (!isalnum(character[0][1]) || !isalnum(character[1][0]) || !isalnum(character[1][1])) return true;
    return false;
}

bool check_valid_for_top_right(std::vector<std::vector<char>> character)
{
    if (!isalnum(character[0][character[0].size() - 3]) || !isalnum(character[1][character[0].size() - 3]) || !isalnum(character[1][character[0].size() - 2])) return true;
    return false;
}

bool check_valid_for_bottom_left(std::vector<std::vector<char>> character)
{
    if (!isalnum(character[character.size() - 2][0]) || !isalnum(character[character.size() - 2][1]) || !isalnum(character[character.size() - 1][1])) return true;
    return false;
}

bool check_valid_for_bottom_right(std::vector<std::vector<char>> character)
{
    int row = character.size() - 1;
    int col = character[character.size() - 1].size() - 2;
    if (!isalnum(character[row - 1][col - 1]) || !isalnum(character[row - 1][col]) || !isalnum(character[row][col - 1])) return true;
    return false;
}

bool check_valid_for_top(std::vector<std::vector<char>> character, int col)
{
    if (!isalnum(character[0][col - 1]) || !isalnum(character[0][col + 1]) || !isalnum(character[1][col - 1]) || !isalnum(character[1][col]) || !isalnum(character[1][col + 1])) return true;
    return false;
}

bool check_valid_for_left(std::vector<std::vector<char>> character, int row)
{
    if (!isalnum(character[row - 1][0]) || !isalnum(character[row + 1][0]) || !isalnum(character[row - 1][1]) || !isalnum(character[row][1]) || !isalnum(character[row + 1][1])) return true;
    return false;
}

bool check_valid_for_right(std::vector<std::vector<char>> character, int row)
{
    int col = character[row].size() - 2;
    if (!isalnum(character[row - 1][col]) || !isalnum(character[row + 1][col]) || !isalnum(character[row - 1][col - 1]) || !isalnum(character[row][col - 1]) || !isalnum(character[row + 1][col - 1])) return true;
    return false;
}

bool check_valid_for_bottom(std::vector<std::vector<char>> character, int col)
{
    int row = character.size() - 1;
    if (!isalnum(character[row][col - 1]) || !isalnum(character[row][col + 1]) || !isalnum(character[row - 1][col - 1]) || !isalnum(character[row - 1][col]) || !isalnum(character[row - 1][col + 1])) return true;
    return false;
}

bool check_valid_for_middle(std::vector<std::vector<char>> character, int row, int col)
{
    if (!isalnum(character[row - 1][col - 1]) || !isalnum(character[row - 1][col]) || !isalnum(character[row - 1][col + 1]) || !isalnum(character[row][col - 1]) || !isalnum(character[row][col + 1]) || !isalnum(character[row + 1][col - 1]) || !isalnum(character[row + 1][col])|| !isalnum(character[row + 1][col + 1])) return true;
    return false;
}

int cal_sum_valid_for_one_digit(std::vector<std::vector<char>> character, std::vector<std::vector<int>> one_digit)
{
    int sum = 0;
    int end_col = character[0].size() - 2;
    int end_row = character.size() - 1;
    for (int i = 0; i < one_digit.size(); i++)
    {
        if (one_digit[i][1] == 0 && one_digit[i][2] == 0 && check_valid_for_top_left(character) == true) sum += one_digit[i][0];
        else if (one_digit[i][1] == 0 && one_digit[i][2] != 0 && one_digit[i][2] != end_col && check_valid_for_top(character, one_digit[i][2])) sum += one_digit[i][0];
        else if (one_digit[i][1] == 0 && one_digit[i][2] == end_col && check_valid_for_top_right(character)) sum += one_digit[i][0];
        else if (one_digit[i][1] != 0 && one_digit[i][1] != end_row && one_digit[i][2] == 0 && check_valid_for_left(character, one_digit[i][1])) sum += one_digit[i][0];
        else if (one_digit[i][1] != 0 && one_digit[i][1] != end_row && one_digit[i][2] == end_col && check_valid_for_right(character, one_digit[i][1])) sum += one_digit[i][0];
        else if (one_digit[i][1] == end_row && one_digit[i][2] == 0 && check_valid_for_bottom_left(character)) sum += one_digit[i][0];
        else if (one_digit[i][1] == end_row && one_digit[i][2] != 0 && one_digit[i][2] != end_col && check_valid_for_bottom(character, one_digit[i][2])) sum += one_digit[i][0];
        else if (one_digit[i][1] == end_row && one_digit[i][2] == end_col && check_valid_for_bottom_right(character)) sum+= one_digit[i][0];
        else if (one_digit[i][1] != 0 && one_digit[i][1] != end_row && one_digit[i][2] != 0 && one_digit[i][2] != end_col)
        {
            if (check_valid_for_middle(character, one_digit[i][1], one_digit[i][2])) sum+= one_digit[i][0];
        }

    }
    return sum;
}

int cal_sum_valid_for_two_digit(std::vector<std::vector<char>> character, std::vector<std::vector<int>> two_digit)
{
    int sum = 0;
    int end_col = character[0].size() - 2;
    int end_row = character.size() - 1;
    for (int i = 0; i < two_digit.size(); i++)
    {
        if (two_digit[i][1] == 0 && two_digit[i][2] == 0 && (check_valid_for_top_left(character) || check_valid_for_top(character, two_digit[i][3]))) sum += two_digit[i][0];
        else if (two_digit[i][1] == 0 && two_digit[i][2] != 0 && two_digit[i][3] != end_col && (check_valid_for_top(character, two_digit[i][2]) || check_valid_for_top(character, two_digit[i][3]))) sum += two_digit[i][0];
        else if (two_digit[i][1] == 0 && two_digit[i][3] == end_col && (check_valid_for_top_right(character) || check_valid_for_top(character, two_digit[i][2]))) sum += two_digit[i][0];
        else if (two_digit[i][1] != 0 && two_digit[i][1] != end_row && two_digit[i][2] == 0 && (check_valid_for_left(character, two_digit[i][1]) || check_valid_for_middle(character, two_digit[i][1], two_digit[i][3]))) sum += two_digit[i][0];
        else if (two_digit[i][1] != 0 && two_digit[i][1] != end_row && two_digit[i][3] == end_col && (check_valid_for_right(character, two_digit[i][1]) || check_valid_for_middle(character, two_digit[i][1], two_digit[i][2]))) sum += two_digit[i][0];
        else if (two_digit[i][1] == end_row && two_digit[i][2] == 0 && (check_valid_for_bottom_left(character) || check_valid_for_bottom(character, two_digit[i][3]))) sum += two_digit[i][0];
        else if (two_digit[i][1] == end_row && two_digit[i][2] != 0 && two_digit[i][3] != end_col && (check_valid_for_bottom(character, two_digit[i][2]) || check_valid_for_bottom(character, two_digit[i][3]))) sum += two_digit[i][0];
        else if (two_digit[i][1] == end_row && two_digit[i][3] == end_col && (check_valid_for_bottom_right(character) || check_valid_for_bottom(character, two_digit[i][2]))) sum+= two_digit[i][0];
        else if (two_digit[i][1] != 0 && two_digit[i][1] != end_row && two_digit[i][2] != 0 && two_digit[i][3] != end_col)
        {
            if (check_valid_for_middle(character, two_digit[i][1], two_digit[i][2]) || check_valid_for_middle(character, two_digit[i][1], two_digit[i][3])) sum+= two_digit[i][0];
        }
       
    }
    return sum;
}

int cal_sum_valid_for_three_digit(std::vector<std::vector<char>> character, std::vector<std::vector<int>> three_digit)
{
    int sum = 0;
    int end_col = character[0].size() - 2;
    int end_row = character.size() - 1;
    for (int i = 0; i < three_digit.size(); i++)
    {
        if (three_digit[i][1] == 0 && three_digit[i][2] == 0 && (check_valid_for_top_left(character) || check_valid_for_top(character, three_digit[i][4]))) sum += three_digit[i][0];
        else if (three_digit[i][1] == 0 && three_digit[i][2] != 0 && three_digit[i][4] != end_col && (check_valid_for_top(character, three_digit[i][2]) || check_valid_for_top(character, three_digit[i][4]))) sum += three_digit[i][0];
        else if (three_digit[i][1] == 0 && three_digit[i][4] == end_col && (check_valid_for_top_right(character) || check_valid_for_top(character, three_digit[i][2]))) sum += three_digit[i][0];
        else if (three_digit[i][1] != 0 && three_digit[i][1] != end_row && three_digit[i][2] == 0 && (check_valid_for_left(character, three_digit[i][1]) || check_valid_for_middle(character, three_digit[i][1], three_digit[i][4]))) sum += three_digit[i][0];
        else if (three_digit[i][1] != 0 && three_digit[i][1] != end_row && three_digit[i][4] == end_col && (check_valid_for_right(character, three_digit[i][1]) || check_valid_for_middle(character, three_digit[i][1], three_digit[i][2]))) sum += three_digit[i][0];
        else if (three_digit[i][1] == end_row && three_digit[i][2] == 0 && (check_valid_for_bottom_left(character) || check_valid_for_bottom(character, three_digit[i][4]))) sum += three_digit[i][0];
        else if (three_digit[i][1] == end_row && three_digit[i][2] != 0 && three_digit[i][4] != end_col && (check_valid_for_bottom(character, three_digit[i][2]) || check_valid_for_bottom(character, three_digit[i][4]))) sum += three_digit[i][0];
        else if (three_digit[i][1] == end_row && three_digit[i][4] == end_col && (check_valid_for_bottom_right(character) || check_valid_for_bottom(character, three_digit[i][2]))) sum+= three_digit[i][0];
        else if (three_digit[i][1] != 0 && three_digit[i][1] != end_row && three_digit[i][2] != 0 && three_digit[i][4] != end_col)
        {
            if (check_valid_for_middle(character, three_digit[i][1], three_digit[i][2]) || check_valid_for_middle(character, three_digit[i][1], three_digit[i][4])) sum+= three_digit[i][0];
        }

    }
    return sum;
}

void read_character(std::string line, int row, std::vector<std::vector<char>>& character, std::vector<std::vector<int>>& one_digit, std::vector<std::vector<int>>& two_digit, std::vector<std::vector<int>>& three_digit)
{
    std::vector<char> new_line;
    for (int i = 0; i < line.size(); i++)
    {
        if (line[i]  == '.') new_line.push_back('a');
        else new_line.push_back(line[i]);
    }
    new_line.push_back('\0');

    character.push_back(new_line);


    for (int i = 0; i < character[row].size() - 1; i++)
    {
        if (isdigit(character[row][i]))
        {
            if (isdigit(character[row][i + 1]) && character[row][i + 1] != '\0')
            {
                if (isdigit(character[row][i + 2]) && character[row][i + 2] != '\0')
                {
                    int num_1 = character[row][i] - '0';
                    int num_2 = character[row][i + 1] - '0';
                    int num_3 = character[row][i + 2] - '0';
                    std::vector<int> digit;
                    digit.push_back(num_1 * 100 + num_2 * 10 + num_3);
                    digit.push_back(row);
                    digit.push_back(i);
                    digit.push_back(i + 1);
                    digit.push_back(i + 2);
                    three_digit.push_back(digit);
                    i += 2;
                }
                else
                {
                    int num_1 = character[row][i] - '0';
                    int num_2 = character[row][i + 1] - '0';
                    std::vector<int> digit;
                    digit.push_back(num_1 * 10 + num_2);
                    digit.push_back(row);
                    digit.push_back(i);
                    digit.push_back(i + 1);
                    two_digit.push_back(digit);
                    i++;
                }       
            }
            else
            {
                std::vector<int> digit;
                digit.push_back(character[row][i] - '0');
                digit.push_back(row);
                digit.push_back(i);
                one_digit.push_back(digit);

            }
        }
    }

}

void read_file(std::ifstream & fin, std::string file_name, std::vector<std::vector<char>>& character, std::vector<std::vector<int>>& one_digit, std::vector<std::vector<int>>& two_digit, std::vector<std::vector<int>>& three_digit)
{
    fin.open(file_name);

    std::string line;
    int row = 0;

    while (!fin.eof())
    {
        std::getline(fin, line);
        //std::cout << line << "\n";
        read_character(line, row, character, one_digit, two_digit, three_digit);
        row++;        
    }

    fin.close();
}

int main()
{
    std::ifstream fin;
    std::string file_name = "input.txt";

    std::vector<std::vector<char>> character;
    std::vector<std::vector<int>> one_digit; // 3 elements for each vector
    std::vector<std::vector<int>> two_digit; // 4 elements for each vector
    std::vector<std::vector<int>> three_digit; // 5 elements for each vector

    read_file(fin, file_name, character, one_digit, two_digit, three_digit);

    // for (int i = 0; character.size(); i++)
    // {
    //     for (int j = 0; j < character[i].size(); j++)
    //     {
    //         std::cout << character[i][j] << ' ';
    //     }

    //     std::cout << "\n";
    // }

    // for (int i = 0; two_digit.size(); i++)
    // {
    //     for (int j = 0; j < two_digit[i].size(); j++)
    //     {
    //         std::cout << two_digit[i][j] << " ";
    //     }

    //     std::cout << "\n";
    // }

    // for (int i = 0; three_digit.size(); i++)
    // {
    //     for (int j = 0; j < three_digit[i].size(); j++)
    //     {
    //         std::cout << three_digit[i][j] << " ";
    //     }

    //     std::cout << "\n";
    // }

    // for (int i = 0; one_digit.size(); i++)
    // {
    //     for (int j = 0; j < one_digit[i].size(); j++)
    //     {
    //         std::cout << one_digit[i][j] << " ";
    //     }

    //     std::cout << "\n";
    // }

    //std::cout << cal_sum_valid_for_three_digit(character, three_digit);

    std::cout << cal_sum_valid_for_one_digit(character, one_digit) + cal_sum_valid_for_two_digit(character, two_digit) + cal_sum_valid_for_three_digit(character, three_digit); 
    return 0;

}