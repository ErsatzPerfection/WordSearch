// WordSearchKata.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <string>
using namespace std;


vector<string> solver(vector<vector<char>> chars, int x, int y, int x_dir, int y_dir, int current_letter_pos, vector<string> possible_words)
{
    vector<string> solutions;
    if (x < 0 && y < 0 || x == chars[0].size() || y == chars.size()) return solutions;
    int i = possible_words.size();
    while (--i > -1)
    {
        if(possible_words[i][current_letter_pos] != chars[y][x])
        {
            possible_words.erase(possible_words.begin() + i);
        }
        else if(possible_words[i].length() == current_letter_pos + 1)
        {
            solutions.push_back(possible_words[i]);
            possible_words.erase(possible_words.begin() + i);

        }
    }
    vector<string> further_possible_solutions = solver(chars,x+ x_dir,y+y_dir,x_dir,y_dir, current_letter_pos+1, possible_words);
    solutions.insert(solutions.end(), further_possible_solutions.begin(), further_possible_solutions.end());
    return solutions;
}
void solveCharDirection(vector<vector<char>> chars, int x, int y, int x_dir, int y_dir, vector<string> words)
{
    vector<string> solutions = solver(chars, x, y, x_dir, y_dir, 0, words);
    for (int i = 0; i < solutions.size(); i++)
    {
        cout << solutions[i] << ": ";
        for (int c = 0; c < solutions[i].length(); c++)
        {
            cout << "(" << x + x_dir * c << "," << y + y_dir * c << ")";
        }
        cout << endl;
    }
}

int main()
{

    ifstream inputfile;
    string input_line;
    vector<string> words;
    vector<vector<char>> chars;
    bool first_run = true;
    inputfile.open("test1.txt");

    string word;

    while (getline(inputfile, input_line,'\n'))
    {
        stringstream current_line(input_line);
        vector<char> char_line;
        char c;
        if (first_run)
        {
            while (getline(current_line, word, ',')) words.push_back(word);
            first_run = false;
        }
        else 
        {
            while (getline(current_line, word, ','))
            {
                c = word[0];
                char_line.push_back(c);
            }
            chars.push_back(char_line);
        }

    }

    for (int i = 0; i < chars.size(); i++)
    {
        for (int c = 0; c < chars[0].size(); c++)
        {
            cout << chars[i][c];
        }
        cout << endl;
    }
    for (int y = 0; y < chars.size(); y++)
    {
        for (int x = 0; x < chars[0].size(); x++)
        {
            solveCharDirection(chars, x, y, 0, 1, words);

        }
        cout << endl;
    }

    inputfile.close();

   return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files 
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
