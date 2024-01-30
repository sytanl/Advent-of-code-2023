#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <cmath>
#include <unordered_map>

int count_step(std::vector<int> direct, std::unordered_map<std::string, std::vector<std::string>> locations, std::string des, std::string first_goal)
{
    std::string goal = first_goal;
    int count = 0;
    int i = 0;

    while (goal != des)
    {
        if (direct[i] == 1) goal = locations[goal][0];
        else if (direct[i] == 2) goal = locations[goal][1];
        std::cout << goal << "\n";

        count++;
        i++;
        if (i == direct.size()) i = 0;
    }

    return count;
}

void read_file(std::ifstream& fin, std::string file_name, std::vector<int>& direct, std::unordered_map  <std::string, std::vector<std::string>>& locations, std::string& first_goal)
{
    fin.open(file_name);

    std::string line;
    std::getline(fin, line);    

    for (int i = 0; i < line.size(); i++)
    {
        if (line[i] == 'L') direct.push_back(1);
        else if (line[i] == 'R') direct.push_back(2);
    }

    std::getline(fin, line);    
    int flag = 0;

    while (std::getline(fin, line))
    {
        std::string ele1, ele2, ele3, comma, comma2;
        std::stringstream ss(line);

        std::getline(ss, ele1, ' ');
        std::getline(ss, comma, '(');
        std::getline(ss, ele2, ',');
        std::getline(ss, comma2, ' ');
        std::getline(ss, ele3, ')');


        if (flag == 0)
        {
            first_goal = ele1;
            flag = 1;
        }

        std::vector<std::string> location;
        location.push_back(ele2);
        location.push_back(ele3);

        locations.insert(make_pair(ele1, location));
    }   

    fin.close();
}

int main()
{
    std::ifstream fin;
    std::string file_name = "input.txt";
    std::string first_goal;

    std::vector<int> direct;
    std::unordered_map<std::string, std::vector<std::string>> locations;

    read_file(fin, file_name, direct, locations, first_goal);

    //for (int i = 0; i < direct.size(); i++) std::cout << direct[i] << " ";

    std:: unordered_map<std::string, std::vector<std::string>>::iterator itr; 
    // for (itr = locations.begin(); itr != locations.end(); itr++)  
    // { 
    //     std::cout << itr->first << " " << itr->second[0] << " " << itr->second[1] << "\n";
    // } 

    std::cout << count_step(direct, locations, first_goal , "ZZZ");

    return 0;
}