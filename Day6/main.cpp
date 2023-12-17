#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <cmath>

void merge_to_one(std::vector<std::vector<int>> race, std::vector<long long int>& new_race)
{
    std::string one = "";
    std::string two = "";

    for (int i = 0; i < race[0].size(); i++)
    {
        one += std::to_string(race[0][i]);
        two += std::to_string(race[1][i]);
    }

    new_race.push_back(std::stoll(one));
    new_race.push_back(std::stoll(two));
}

long long  beat_winner(std::vector<long long int> race)
{
    long long  total = 1;
    float delta = pow(race[0], 2) - 4 * 1 * race[1];
    int x1 = ceil((race[0] + sqrt(delta))/ 2) - 1; 
    int x2 = (race[0] - sqrt(delta))/ 2 + 1;

    total = x1 - x2 + 1; 

    return total;
}

void read_file(std::ifstream& fin, std::string file_name, std::vector<std::vector<int>> &race)
{
    fin.open(file_name);

    std::string line;

    while (std::getline(fin, line))
    {
        std::stringstream ss(line);
        std::string comma;
        std::vector<int> number;

        ss >> comma;
        int num;

        while (!ss.eof())
        {
            ss >> num;
            number.push_back(num);
        }

        race.push_back(number);
        number.clear();
    }

    fin.close();
}

int main()
{
    std::ifstream fin;
    std::string file_name = "input.txt";
    std::vector<std::vector<int>> race;

    read_file(fin, file_name, race);


    // for (int i = 0; i < race.size(); i++)
    // {
    //     for (int j = 0; j < race[i].size(); j++)
    //     {
    //         std::cout << race[i][j] << " ";
    //     }

    //     std::cout << "\n";
    // }

    std::vector<long long int> new_race;



    merge_to_one(race, new_race);

    std::cout << beat_winner(new_race);


    return 0;
}