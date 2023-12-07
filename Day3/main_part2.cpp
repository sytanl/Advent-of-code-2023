#include <iostream>
#include <string>
#include <fstream>
#include <cctype>
#include <vector>
#include <sstream>

bool is_star(std::vector<std::vector<char>> character, int row, int col, int& h_row, int& h_col)
{
    if (character[row][col] == '*') 
    {   
        h_row = row;
        h_col = col;
        return true;
    }
    return false;
}

bool check_valid_for_top_left(std::vector<std::vector<char>> character, int& h_row, int& h_col)
{
    if (is_star(character, 0, 1, h_row, h_col) || is_star(character, 1, 0, h_row, h_col) || is_star(character, 1, 1, h_row, h_col))  return true;
    return false;
}

bool check_valid_for_top_right(std::vector<std::vector<char>> character, int& h_row, int& h_col)
{
    if (is_star(character, 0, character[0].size() - 3, h_row, h_col) || is_star(character, 1, character[0].size() - 3, h_row, h_col) || is_star(character, 1, character[0].size() - 2, h_row, h_col)) return true;
    return false;
}

bool check_valid_for_bottom_left(std::vector<std::vector<char>> character, int& h_row, int& h_col)
{
    if (is_star(character, character.size() - 2, 0, h_row, h_col) || is_star(character, character.size() - 2, 1, h_row, h_col) || is_star(character,character.size() - 1, 1, h_row, h_col)) return true;
    return false;
}

bool check_valid_for_bottom_right(std::vector<std::vector<char>> character, int& h_row, int& h_col)
{
    int row = character.size() - 1;
    int col = character[character.size() - 1].size() - 2;
    if (is_star(character, row - 1, col - 1, h_row, h_col) || is_star(character, row - 1, col, h_row, h_col) || is_star(character, row, col - 1, h_row, h_col)) return true;
    return false;
}

bool check_valid_for_top(std::vector<std::vector<char>> character, int col, int& h_row, int& h_col)
{
    if (is_star(character, 0, col - 1, h_row, h_col) || is_star(character, 0, col + 1, h_row, h_col) || is_star(character, 1, col - 1, h_row, h_col) || is_star(character, 1, col, h_row, h_col) || is_star(character, 1, col + 1, h_row, h_col)) return true;
    return false;
}

bool check_valid_for_left(std::vector<std::vector<char>> character, int row, int& h_row, int& h_col)
{
    if (is_star(character, row - 1, 0, h_row, h_col) || is_star(character, row + 1, 0, h_row, h_col) || is_star(character, row - 1, 1, h_row, h_col) || is_star(character, row, 1, h_row, h_col) || is_star(character, row + 1, 1, h_row, h_col)) return true;
    return false;
}

bool check_valid_for_right(std::vector<std::vector<char>> character, int row, int& h_row, int& h_col)
{
    int col = character[row].size() - 2;
    if (is_star(character, row - 1, col, h_row, h_col) || is_star(character,row + 1, col, h_row, h_col) || is_star(character, row - 1, col - 1, h_row, h_col) || is_star(character, row, col - 1, h_row, h_col) || is_star(character, row + 1, col - 1, h_row, h_col)) return true;
    return false;
}

bool check_valid_for_bottom(std::vector<std::vector<char>> character, int col, int& h_row, int& h_col)
{
    int row = character.size() - 1;
    if (is_star(character, row, col - 1, h_row, h_col) || is_star(character, row, col + 1, h_row, h_col) || is_star(character, row - 1, col - 1, h_row, h_col) || is_star(character, row - 1, col, h_row, h_col) || is_star(character, row - 1, col + 1, h_row, h_col)) return true;
    return false;
}

bool check_valid_for_middle(std::vector<std::vector<char>> character, int row, int col, int& h_row, int& h_col)
{
    if (is_star(character, row - 1, col - 1, h_row, h_col) || is_star(character, row - 1, col, h_row, h_col) || is_star(character, row - 1, col + 1, h_row, h_col) || is_star(character, row, col - 1, h_row, h_col) || is_star(character, row, col + 1, h_row, h_col) || is_star(character, row + 1, col - 1, h_row, h_col) || is_star(character, row + 1, col, h_row, h_col)|| is_star(character, row + 1, col + 1, h_row, h_col)) return true;
    return false;
}

void push_to_star_vector(std::vector<std::vector<int>> digit, int row, std::vector<std::vector<int>>& star, int h_row, int h_col)
{
    std::vector<int> star_line;
    star_line.push_back(digit[row][0]);
    star_line.push_back(h_row);
    star_line.push_back(h_col);
    star.push_back(star_line);
}

void cal_sum_valid_for_one_digit(std::vector<std::vector<char>> character, std::vector<std::vector<int>> one_digit, std::vector<std::vector<int>>& star)
{
    int end_col = character[0].size() - 2;
    int end_row = character.size() - 1;
    for (int i = 0; i < one_digit.size(); i++)
    {
        int h_row = 0, h_col = 0;
        if (one_digit[i][1] == 0 && one_digit[i][2] == 0 && check_valid_for_top_left(character, h_row, h_col)) push_to_star_vector(one_digit, i, star, h_row, h_col);
        else if (one_digit[i][1] == 0 && one_digit[i][2] != 0 && one_digit[i][2] != end_col && check_valid_for_top(character, one_digit[i][2], h_row, h_col)) push_to_star_vector(one_digit, i, star, h_row, h_col);
        else if (one_digit[i][1] == 0 && one_digit[i][2] == end_col && check_valid_for_top_right(character, h_row, h_col)) push_to_star_vector(one_digit, i, star, h_row, h_col);
        else if (one_digit[i][1] != 0 && one_digit[i][1] != end_row && one_digit[i][2] == 0 && check_valid_for_left(character, one_digit[i][1], h_row, h_col)) push_to_star_vector(one_digit, i, star, h_row, h_col);
        else if (one_digit[i][1] != 0 && one_digit[i][1] != end_row && one_digit[i][2] == end_col && check_valid_for_right(character, one_digit[i][1], h_row, h_col)) push_to_star_vector(one_digit, i, star, h_row, h_col);
        else if (one_digit[i][1] == end_row && one_digit[i][2] == 0 && check_valid_for_bottom_left(character, h_row, h_col)) push_to_star_vector(one_digit, i, star, h_row, h_col);
        else if (one_digit[i][1] == end_row && one_digit[i][2] != 0 && one_digit[i][2] != end_col && check_valid_for_bottom(character, one_digit[i][2], h_row, h_col)) push_to_star_vector(one_digit, i, star, h_row, h_col);
        else if (one_digit[i][1] == end_row && one_digit[i][2] == end_col && check_valid_for_bottom_right(character, h_row, h_col)) push_to_star_vector(one_digit, i, star, h_row, h_col);
        else if (one_digit[i][1] != 0 && one_digit[i][1] != end_row && one_digit[i][2] != 0 && one_digit[i][2] != end_col)
        {
            if (check_valid_for_middle(character, one_digit[i][1], one_digit[i][2], h_row, h_col)) push_to_star_vector(one_digit, i, star, h_row, h_col);
        }

    }
}

void cal_sum_valid_for_two_digit(std::vector<std::vector<char>> character, std::vector<std::vector<int>> two_digit, std::vector<std::vector<int>>& star)
{
    int end_col = character[0].size() - 2;
    int end_row = character.size() - 1;
    for (int i = 0; i < two_digit.size(); i++)
    {
        int h_row = 0, h_col = 0;
        if (two_digit[i][1] == 0 && two_digit[i][2] == 0 && (check_valid_for_top_left(character, h_row, h_col) || check_valid_for_top(character, two_digit[i][3], h_row, h_col))) push_to_star_vector(two_digit, i, star, h_row, h_col);
        else if (two_digit[i][1] == 0 && two_digit[i][2] != 0 && two_digit[i][3] != end_col && (check_valid_for_top(character, two_digit[i][2], h_row, h_col) || check_valid_for_top(character, two_digit[i][3], h_row, h_col))) push_to_star_vector(two_digit, i, star, h_row, h_col);
        else if (two_digit[i][1] == 0 && two_digit[i][3] == end_col && (check_valid_for_top_right(character, h_row, h_col) || check_valid_for_top(character, two_digit[i][2], h_row, h_col))) push_to_star_vector(two_digit, i, star, h_row, h_col);
        else if (two_digit[i][1] != 0 && two_digit[i][1] != end_row && two_digit[i][2] == 0 && (check_valid_for_left(character, two_digit[i][1], h_row, h_col) || check_valid_for_middle(character, two_digit[i][1], two_digit[i][3], h_row, h_col))) push_to_star_vector(two_digit, i, star, h_row, h_col);
        else if (two_digit[i][1] != 0 && two_digit[i][1] != end_row && two_digit[i][3] == end_col && (check_valid_for_right(character, two_digit[i][1], h_row, h_col) || check_valid_for_middle(character, two_digit[i][1], two_digit[i][2], h_row, h_col))) push_to_star_vector(two_digit, i, star, h_row, h_col);
        else if (two_digit[i][1] == end_row && two_digit[i][2] == 0 && (check_valid_for_bottom_left(character, h_row, h_col) || check_valid_for_bottom(character, two_digit[i][3], h_row, h_col))) push_to_star_vector(two_digit, i, star, h_row, h_col);
        else if (two_digit[i][1] == end_row && two_digit[i][2] != 0 && two_digit[i][3] != end_col && (check_valid_for_bottom(character, two_digit[i][2], h_row, h_col) || check_valid_for_bottom(character, two_digit[i][3], h_row, h_col))) push_to_star_vector(two_digit, i, star, h_row, h_col);
        else if (two_digit[i][1] == end_row && two_digit[i][3] == end_col && (check_valid_for_bottom_right(character, h_row, h_col) || check_valid_for_bottom(character, two_digit[i][2], h_row, h_col))) push_to_star_vector(two_digit, i, star, h_row, h_col);
        else if (two_digit[i][1] != 0 && two_digit[i][1] != end_row && two_digit[i][2] != 0 && two_digit[i][3] != end_col)
        {
            if (check_valid_for_middle(character, two_digit[i][1], two_digit[i][2], h_row, h_col) || check_valid_for_middle(character, two_digit[i][1], two_digit[i][3], h_row, h_col)) push_to_star_vector(two_digit, i, star, h_row, h_col);
        }
       
    }
}


void cal_sum_valid_for_three_digit(std::vector<std::vector<char>> character, std::vector<std::vector<int>> three_digit, std::vector<std::vector<int>>& star)
{
    int end_col = character[0].size() - 2;
    int end_row = character.size() - 1;
    for (int i = 0; i < three_digit.size(); i++)
    {
        int h_row = 0, h_col = 0;
        // std::cout << three_digit[i][1] << " " << three_digit[i][2] << "\n";
        // std::cout << check_valid_for_top(character, three_digit[i][4], h_row, h_col) << "\n";
        if (three_digit[i][1] == 0 && three_digit[i][2] == 0 && (check_valid_for_top(character, three_digit[i][4], h_row, h_col) || check_valid_for_top_left(character, h_row, h_col))) 
        {
            push_to_star_vector(three_digit, i, star, h_row, h_col);
        }
        else if (three_digit[i][1] == 0 && three_digit[i][2] != 0 && three_digit[i][4] != end_col && (check_valid_for_top(character, three_digit[i][2], h_row, h_col) || check_valid_for_top(character, three_digit[i][4], h_row, h_col))) push_to_star_vector(three_digit, i, star, h_row, h_col);
        else if (three_digit[i][1] == 0 && three_digit[i][4] == end_col && (check_valid_for_top_right(character, h_row, h_col) || check_valid_for_top(character, three_digit[i][2], h_row, h_col))) push_to_star_vector(three_digit, i, star, h_row, h_col);
        else if (three_digit[i][1] != 0 && three_digit[i][1] != end_row && three_digit[i][2] == 0 && (check_valid_for_left(character, three_digit[i][1], h_row, h_col) || check_valid_for_middle(character, three_digit[i][1], three_digit[i][4], h_row, h_col))) push_to_star_vector(three_digit, i, star, h_row, h_col);
        else if (three_digit[i][1] != 0 && three_digit[i][1] != end_row && three_digit[i][4] == end_col && (check_valid_for_right(character, three_digit[i][1], h_row, h_col) || check_valid_for_middle(character, three_digit[i][1], three_digit[i][2], h_row, h_col))) push_to_star_vector(three_digit, i, star, h_row, h_col);
        else if (three_digit[i][1] == end_row && three_digit[i][2] == 0 && (check_valid_for_bottom_left(character, h_row, h_col) || check_valid_for_bottom(character, three_digit[i][4], h_row, h_col))) push_to_star_vector(three_digit, i, star, h_row, h_col);
        else if (three_digit[i][1] == end_row && three_digit[i][2] != 0 && three_digit[i][4] != end_col && (check_valid_for_bottom(character, three_digit[i][2], h_row, h_col) || check_valid_for_bottom(character, three_digit[i][4], h_row, h_col))) push_to_star_vector(three_digit, i, star, h_row, h_col);
        else if (three_digit[i][1] == end_row && three_digit[i][4] == end_col && (check_valid_for_bottom_right(character, h_row, h_col) || check_valid_for_bottom(character, three_digit[i][2], h_row, h_col))) push_to_star_vector(three_digit, i, star, h_row, h_col);
        else if (three_digit[i][1] != 0 && three_digit[i][1] != end_row && three_digit[i][2] != 0 && three_digit[i][4] != end_col)
        {
            if (check_valid_for_middle(character, three_digit[i][1], three_digit[i][2], h_row, h_col) || check_valid_for_middle(character, three_digit[i][1], three_digit[i][4], h_row, h_col)) push_to_star_vector(three_digit, i, star, h_row, h_col);
        }
       
    }
}

int cal_sum_star_adj(std::vector<std::vector<int>> star)
{
    int sum = 0;
    for (int i = 0; i < star.size() - 1; i++)
    {
        for (int j = i + 1; j < star.size(); j++)
        {
            if (star[i][1] == star[j][1] && star[i][2]  == star[j][2]) sum += star[i][0] * star[j][0];
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
    std::vector<std::vector<int>> star;


    read_file(fin, file_name, character, one_digit, two_digit, three_digit);
    cal_sum_valid_for_one_digit(character, one_digit, star);
    cal_sum_valid_for_two_digit(character, two_digit, star);
    cal_sum_valid_for_three_digit(character, three_digit, star);

    // for (int i = 0; i < star.size(); i++)
    // {
    //     for (int j = 0; j < star[i].size(); j++)
    //     {
    //         std::cout << star[i][j] << " ";
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

    //std::cout << cal_sum_valid_for_one_digit(character, one_digit) + cal_sum_valid_for_two_digit(character, two_digit) + cal_sum_valid_for_three_digit(character, three_digit); 
    std::cout << cal_sum_star_adj(star);
    return 0;

}