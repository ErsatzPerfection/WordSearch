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
    if (x < 0 || y < 0 || x == chars[0].size() || y == chars.size()) return solutions;
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

struct wordCoords
{
    string word;
    int x_start;
    int y_start;
    int x_dir;
    int y_dir;
};
vector<wordCoords> solveCharDirection(vector<vector<char>> chars, int x, int y, int x_dir, int y_dir, vector<string> words)
{
    vector<string> solutions = solver(chars, x, y, x_dir, y_dir, 0, words);
    vector<wordCoords> solutionCoords;
    for (int i = 0; i < solutions.size(); i++)
    {
        wordCoords word_coord;
        word_coord.word = solutions[i];
        word_coord.x_start = x;
        word_coord.y_start = y;
        word_coord.x_dir = x_dir;
        word_coord.y_dir = y_dir;
        solutionCoords.push_back(word_coord);
       
    }
    return solutionCoords;
}

int main()
{

    ifstream inputfile;
    string input_line;
    vector<string> words;
    vector<vector<char>> chars;
    bool first_run = true;
    inputfile.open("test2.txt");

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
    inputfile.close();
    //for (int i = 0; i < chars.size(); i++)
    //{
    //    for (int c = 0; c < chars[0].size(); c++)
    //    {
    //        cout << chars[i][c];
    //    }
    //    cout << endl;
    //}

    vector<wordCoords> solutionCoords;

    for (int y = 0; y < chars.size(); y++)
    {
        for (int x = 0; x < chars[0].size(); x++)
        {
            vector<wordCoords>s1 = solveCharDirection(chars, x, y, 0, 1, words);
            vector<wordCoords>s2 = solveCharDirection(chars, x, y, 1, 0, words);
            vector<wordCoords>s3 = solveCharDirection(chars, x, y, 1, 1, words);
            vector<wordCoords>s4 = solveCharDirection(chars, x, y, -1, 1, words);
            vector<wordCoords>s5 = solveCharDirection(chars, x, y, 1, -1, words);
            vector<wordCoords>s6 = solveCharDirection(chars, x, y, 0, -1, words);
            vector<wordCoords>s7 = solveCharDirection(chars, x, y, -1, 0, words);
            vector<wordCoords>s8 = solveCharDirection(chars, x, y, -1, -1, words);
            solutionCoords.insert(solutionCoords.end(), s1.begin(), s1.end());
            solutionCoords.insert(solutionCoords.end(), s2.begin(), s2.end());
            solutionCoords.insert(solutionCoords.end(), s3.begin(), s3.end());
            solutionCoords.insert(solutionCoords.end(), s4.begin(), s4.end());
            solutionCoords.insert(solutionCoords.end(), s5.begin(), s5.end());
            solutionCoords.insert(solutionCoords.end(), s6.begin(), s6.end());
            solutionCoords.insert(solutionCoords.end(), s7.begin(), s7.end());
            solutionCoords.insert(solutionCoords.end(), s8.begin(), s8.end());

        }
    }

    
    for (int n = 0; n < words.size(); n++)
    {
        for (int i = 0; i < solutionCoords.size(); i++)
        {
            if (words[n] == solutionCoords[i].word) {
                cout << solutionCoords[i].word << ": ";
                for (int c = 0; c < solutionCoords[i].word.length(); c++)
                {
                    cout << "(" << solutionCoords[i].x_start + solutionCoords[i].x_dir * c << "," << solutionCoords[i].y_start + solutionCoords[i].y_dir * c;
                    if (c == solutionCoords[i].word.length() - 1) cout << ")";
                    else cout << "),";
                }
                cout << endl;
                continue;
            }
        }
    }

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
