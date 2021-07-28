#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
//#include <string>
using namespace std;

//x and y correspond to the letter the solver is starting from, x_dir and y_dir are how much those coordinates are incremented to get to the next letter
vector<string> solver(vector<vector<char>> chars, int x, int y, int x_dir, int y_dir, int current_letter_pos, vector<string> possible_words)
{
    vector<string> solutions;
    if (x < 0 || y < 0 || x == chars[0].size() || y == chars.size()) return solutions;
    int i = possible_words.size();
    while (--i > -1)
    {
        if(possible_words[i][current_letter_pos] != chars[y][x])
        {
            possible_words.erase(possible_words.begin() + i); //remove word from consideration in future iterations of recursive loop if not a possible answer
        }
        else if(possible_words[i].length() == current_letter_pos + 1)
        {
            solutions.push_back(possible_words[i]); //add solution to vector of words that can be found in this direction with this starting point
            possible_words.erase(possible_words.begin() + i); //remove word from consideration in future iterations of recursive loop if already a known answer

        }
    }
    vector<string> further_possible_solutions = solver(chars,x+ x_dir,y+y_dir,x_dir,y_dir, current_letter_pos+1, possible_words);
    solutions.insert(solutions.end(), further_possible_solutions.begin(), further_possible_solutions.end());
    return solutions;
}

struct wordCoords
{
    string word;
    int x;
    int y;
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
        word_coord.x = x;
        word_coord.y = y;
        word_coord.x_dir = x_dir;
        word_coord.y_dir = y_dir;
        solutionCoords.push_back(word_coord);
       
    }
    return solutionCoords;
}

int main(int argc, char** argv)
{
    string filename;
    if (argc > 1) filename = argv[1];
    else {
        cout << "Please enter name of input file" << endl;
        cin >> filename;
    }
    ifstream inputfile;
    string input_line;
    vector<string> words;
    vector<vector<char>> chars;
    bool first_run = true;
    inputfile.open(filename);

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

    vector<wordCoords> solutionCoords;
    for (int y = 0; y < chars.size(); y++)
    {
        for (int x = 0; x < chars[0].size(); x++)
        {
            //solves clockwise starting from 12 o'clock position
            vector<wordCoords>s1 = solveCharDirection(chars, x, y, 0, 1, words);
            vector<wordCoords>s2 = solveCharDirection(chars, x, y, 1, 1, words);
            vector<wordCoords>s3 = solveCharDirection(chars, x, y, 1, 0, words);
            vector<wordCoords>s4 = solveCharDirection(chars, x, y, 1, -1, words);
            vector<wordCoords>s5 = solveCharDirection(chars, x, y, 0, -1, words);
            vector<wordCoords>s6 = solveCharDirection(chars, x, y, -1, -1, words);
            vector<wordCoords>s7 = solveCharDirection(chars, x, y, -1, 0, words);
            vector<wordCoords>s8 = solveCharDirection(chars, x, y, -1, 1, words);
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
                    cout << "(" << solutionCoords[i].x + solutionCoords[i].x_dir * c << "," << solutionCoords[i].y + solutionCoords[i].y_dir * c;
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

