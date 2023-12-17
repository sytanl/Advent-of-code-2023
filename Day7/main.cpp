#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <cctype>

int convert_letter(char c)
{
    if (c == 'A') return 5;
    else if (c == 'K') return 4;
    else if (c == 'Q') return 3;
    else if (c == 'J') return 0;
    else if (c == 'T') return 1;
}

long long cal_total_winning(std::vector<std::vector<std::string>> cards)
{   
    long long total_win = 0;

    for (int i = 0; i < cards.size() - 1; i++)
    {
       for (int j = i + 1; j <cards.size(); j++)
       {
            if (cards[j][2] < cards[i][2])
            {
                std::swap(cards[j], cards[i]);
            }
            else if (cards[j][2] == cards[i][2])
            {
                for (int h = 0; h < 5; h++)
                {
                    if (isdigit(cards[j][0][h]) && isdigit(cards[i][0][h]) && (cards[j][0][h] < cards[i][0][h]))
                    {
                        std::swap(cards[j], cards[i]);
                        break;
                    }
                    else if (isdigit(cards[j][0][h]) && isalpha(cards[i][0][h]))
                    {
                        if (cards[i][0][h] == 'J') break; 
                        std::swap(cards[j], cards[i]);
                        break;
                    }
                    else if (isalpha(cards[j][0][h]) && isalpha(cards[i][0][h]))
                    {
                        int num_j = convert_letter(cards[j][0][h]);
                        int num_i = convert_letter(cards[i][0][h]);
                        if (num_j < num_i)
                        {
                            std::swap(cards[j], cards[i]);
                            break;
                        }
                        else if (num_j == num_i) continue;
                        else if (num_j > num_i) break;
                    }
                    else if (cards[j][0][h] == cards[i][0][h])
                    {
                        //continue;
                    }
                    else if (cards[j][0][h] == 'J' && isdigit(cards[i][0][h]))
                    {
                        std::swap(cards[j], cards[i]);
                        break;
                    }
                    else break;
                }
            }
       }

    //    for (int j = 0; j < cards[i].size(); j++)
    //     {
    //         std::cout << cards[i][j] << " ";
    //     }

    //     std::cout << "\n";

    }

    //  for (int i = 0; i < cards.size(); i++)
    // {
    //     for (int j = 0; j < cards[i].size(); j++)
    //     {
    //         std::cout << cards[i][j] << " ";
    //     }

    //     std::cout << "\n";
    // }
    
    for (int i = 0; i < cards.size(); i++)
    {
        total_win += std::stoi(cards[i][1]) * (i + 1);
    }

    return total_win;
}

void read_file(std::ifstream& fin, std::string file_name, std::vector<std::vector<std::string>>& cards)
{
    fin.open(file_name);
    std::string line;

    while(std::getline(fin, line))
    {
        std::stringstream ss(line);
        std::string hand;
        std::string hand_fake;
        std::string bid;

        ss >> hand;
        ss >> bid;

        hand_fake = hand;

        std::unordered_map<char, int> count_letter_real;
        std::unordered_map<char, int> count_letter;
        std::vector<std::string> card;

        for (char c : hand)
        {
            count_letter_real[c]++;
        }

        int max = 0;
        char max_char = 'J';
        for (auto pair : count_letter_real)
        {
            if (pair.second >= max && pair.first != 'J')
            {
                max = pair.second;
                max_char = pair.first;
            }
        }


        if (hand.find('J') != std::string::npos)
        {
            for (int i = 0; i < hand.size(); i++)
            {
                if (hand[i] == 'J') 
                {
                    hand_fake[i] = max_char;
                }
                else hand_fake[i] = hand[i];
            }
        }


        for (char c : hand_fake)
        {
            count_letter[c]++;
        }

        if (count_letter.size() == 1)
        {
            card.push_back(hand);
            card.push_back(bid);
            card.push_back("7");
        }
        else if (count_letter.size() == 2)
        {
            auto first_ele = *(count_letter.begin());
            if (first_ele.second == 1 || first_ele.second == 4)
            {
                card.push_back(hand);
                card.push_back(bid);
                card.push_back("6");
            }
            else
            {
                card.push_back(hand);
                card.push_back(bid);
                card.push_back("5");
            }
        }
        else if (count_letter.size() == 3)
        {
            int flag = 0;
            for (auto pair : count_letter)
            {
                if (pair.second == 3)
                {
                    flag = 1;
                    break;
                }
            }

            if (flag == 1)
            {
                card.push_back(hand);
                card.push_back(bid);
                card.push_back("4");
            }
            else
            {
                card.push_back(hand);
                card.push_back(bid);
                card.push_back("3");
            }
        }
        else if (count_letter.size() == 4)
        {
            card.push_back(hand);
            card.push_back(bid);
            card.push_back("2");
        }
        else if (count_letter.size() == 5)
        {
            card.push_back(hand);
            card.push_back(bid);
            card.push_back("1");
        }

        cards.push_back(card);
    }

    fin.close();
}

int main()
{
    std::ifstream fin;
    std::string file_name = "input.txt";

    std::vector<std::vector<std::string>> cards;

    read_file(fin, file_name, cards);

    // for (int i = 0; i < cards.size(); i++)
    // {
    //     for (int j = 0; j < cards[i].size(); j++)
    //     {
    //         std::cout << cards[i][j] << " ";
    //     }

    //     std::cout << "\n";
    // }

    std::cout << cal_total_winning(cards);

    return 0;
}