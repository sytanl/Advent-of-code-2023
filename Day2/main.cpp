#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>

void increase_color(std::string color, int no, std::vector<int>& num_color, int count)
{
    if (color.length() == 0) return;

    if (color[0] == 'r')
        num_color[no * 3 - 3] += count;
    else if (color[0] == 'g')
        num_color[no * 3 - 2] += count;
    else if (color[0] == 'b') num_color[no * 3 - 1] += count;
}

void increase_color_round(std::string comma_line, std::vector<int>& count_color_round, int num_round)
{
    std::string first_col, sec_col, thi_col;
    std::stringstream ss1(comma_line);
    int ele_1 = 0, ele_2 = 0, ele_3 = 0;
    ss1 >> ele_1;
    ss1 >> first_col;
    if (!ss1.eof())
    {
        ss1 >> ele_2;
        ss1 >> sec_col;
        if (!ss1.eof())
        {
            ss1 >> ele_3;
            ss1 >> thi_col;
        }
    }

    //std::cout << first_col << " " << sec_col << " " << thi_col << "\n";

    increase_color(first_col, num_round, count_color_round, ele_1);
    increase_color(sec_col, num_round, count_color_round, ele_2);
    increase_color(thi_col, num_round, count_color_round, ele_3);
}

void read_file(std::ifstream & fin, std::string file_name, std::vector<std::vector<int>> &count_color)
{
    fin.open(file_name);

    if (!fin.is_open())
    {
        std::cout << "File not found!\n";
        return;
    }

    std::string line;
    std::string comma, new_id_str, comma_line1, comma_line2, comma_line3, comma_line4, comma_line5, comma_line6, first_col, sec_col, thi_col;
    int new_id;

    while (!fin.eof())
    {
        std::getline(fin, line);
        std::stringstream ss(line);
        ss >> comma;
        std::getline(ss, new_id_str, ':');
        std::getline(ss, comma_line1, ';');
        if (!ss.eof())
        {
            std::getline(ss, comma_line2, ';');
            if (!ss.eof())
            {
                std::getline(ss, comma_line3, ';');
                if (!ss.eof())
                {
                    std::getline(ss, comma_line4, ';');
                    if (!ss.eof())
                    {
                        std::getline(ss, comma_line5, ';');
                        if (!ss.eof())
                        {
                            std::getline(ss, comma_line6);
                        } 
                    } 
                } 
            } 
        }

        //std::cout << comma_line1 << " " << comma_line2 << " " << comma_line3 << "\n";

        std::vector<int> count_color_round(18, 0);

        increase_color_round(comma_line1, count_color_round, 1);
        increase_color_round(comma_line2, count_color_round, 2);
        increase_color_round(comma_line3, count_color_round, 3);  
        increase_color_round(comma_line4, count_color_round, 4);  
        increase_color_round(comma_line5, count_color_round, 5);  
        increase_color_round(comma_line6, count_color_round, 6);  

        // for (int i = 0; i < 9; i++) std::cout << count_color_round[i] << " ";
        // std::cout << "\n";

        count_color.push_back(count_color_round);     

        comma_line1 = "";   
        comma_line2 = "";   
        comma_line3 = "";   
        comma_line4 = "";   
        comma_line5 = "";   
        comma_line6 = "";   
    }

    fin.close();
}

int sum_game_possible(std::vector<std::vector<int>> count_color)
{
    int sum = 0;


    for (int i = 0; i < count_color.size(); i++)
    {
        int max_red = 0, max_green = 0, max_blue = 0;
        for (int j = 0; j < 18; j++)
        {
            if (j % 3 == 0)
            {
                if (count_color[i][j] > max_red)
                {
                    max_red = count_color[i][j];
                }
            }
            else if (j % 3 == 1)
            {
                if (count_color[i][j] > max_green)
                {
                    max_green = count_color[i][j] ;
                }
            }
            else if (j % 3 == 2)
            {
                if (count_color[i][j] > max_blue)
                {
                    max_blue = count_color[i][j];
                }
            }
        }

        sum += max_red * max_green * max_blue;
    }

    return sum;
}

int main()
{
    std::string file_name = "input.txt";

    std::ifstream fin;

    std::vector<std::vector<int>> count_color;

    read_file(fin, file_name, count_color);

    // for (int i = 0; i < count_color.size(); i++)
    // {
    //     for (int j = 0; j < count_color[i].size(); j++)
    //     {
    //         std::cout << count_color[i][j] << " ";
    //     }

    //     std::cout << "\n";
    // }


    std::cout << sum_game_possible(count_color);

    return 0;    
}