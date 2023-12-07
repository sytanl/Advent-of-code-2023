#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <iostream>
#include <cmath>

void cal_sum_instance(std::vector<std::vector<int>> left_side, 
                    std::vector<std::vector<int>> right_side,
                    std::vector<int> & instance)
{
    for (int i = 0; i < left_side.size(); i++)
    {
        int expo = 0;
        for (int j = 0; j < left_side[i].size(); j++)
        {
            for (int k = 0; k < right_side[i].size(); k++)
            {
                if (left_side[i][j] == right_side[i][k]) expo++;
            }
        }
        for (int h = i + 1; h <= i + expo; h++)
        {
            instance[h] += instance[i];
        }
    }
}

void read_file(std::ifstream & fin, std::string file_name,
               std::vector<std::vector<int>> & left_side, 
               std::vector<std::vector<int>> & right_side)
{
    fin.open(file_name);

    //Card 1: 41 48 83 86 17 | 83 86  6 31 17  9 48 53

    std::string line, comma;

    while (!fin.eof())
    {
        std::getline(fin, line);
        std::stringstream ss(line);
        std::getline(ss, comma,':');

        std::string left_string;
        std::string right_string;

        std::getline(ss, left_string, '|');
        std::getline(ss, right_string);

        if (left_string[left_string.size() - 1] == ' ') left_string.erase(left_string.size() - 1);


        std::stringstream ss_left(left_string);
        std::stringstream ss_right(right_string);

        std::vector<int> left_vec;
        std::vector<int> right_vec;

        int num;

        while (!ss_left.eof())
        {
            ss_left >> num;
            left_vec.push_back(num); 
        }

        left_side.push_back(left_vec);

        while (!ss_right.eof())
        {
            ss_right >> num;
            right_vec.push_back(num);
        }

        right_side.push_back(right_vec);
    }

}

int main()
{
    std::ifstream fin;
    std::string file_name = "input.txt";

    std::vector<std::vector<int>> left_side;
    std::vector<std::vector<int>> right_side;

    read_file(fin, file_name, left_side, right_side);
    std::vector<int> instance(left_side.size(), 1);


    // for (int i = 0; i < left_side.size(); i++)
    // {
    //     for (int j = 0; j < left_side[i].size(); j++)
    //     {
    //         std::cout << left_side[i][j] << " ";
    //     }
    //     std::cout << "\n";
    // }

    // for (int i = 0; i < instance.size(); i++)
    // {
    //    std::cout << instance[i] << " ";
    // }

    cal_sum_instance(left_side, right_side, instance);

    int sum = 0;

    for (int i = 0; i < instance.size(); i++)
    {
        sum += instance[i];
    }

    std::cout << sum;

    return 0;
}