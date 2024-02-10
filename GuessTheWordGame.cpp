


#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstdlib>
#include <algorithm>
#include <cctype>
#include <cwctype>
#include<ctime>
#include <random>
using namespace std;
inline bool caseInsCharCompareN(char a, char b) {
    return(toupper(a) == toupper(b));
}
bool caseInsCompare(const string& s1, const string& s2) {
         return((s1.size() == s2.size()) &&
                    equal(s1.begin(), s1.end(), s2.begin(), caseInsCharCompareN));
    
}
vector<string> readDataFromFile(const string& filename) {
    ifstream inputFile(filename);
    if (!inputFile.is_open()) {
        cout << "Error opening file for reading." << endl;
        return vector<string>();
    }

    vector<string> loadedWords;
    string loadedWord;

    while (inputFile >> loadedWord) {
        loadedWords.push_back(loadedWord);
    }

    inputFile.close();
    return loadedWords;
}

string generateUnguessableWord(const string& word) {
    int wordLength = word.length();
    string unguessableWord = word;
    int totalReplaceableChars = (wordLength > 3) ? wordLength / 3 : 1;

    for (int i = 0; i < totalReplaceableChars; ++i) {
        int index = rand() % wordLength;
        char randomChar = '_';
        unguessableWord[index] = randomChar;
    }

    return unguessableWord;
}

int main() {
    const string filename = "dummy_words.txt";
    vector<string> loadedWords = readDataFromFile(filename);

    if (loadedWords.empty()) {
        cout << "Error reading data from file." << endl;
        return 1;
    }

    int size = loadedWords.size();
    bool run = true;
    int score = 0;
    int choice;
    string guessWord;
    srand(static_cast<unsigned int>(time(0)));
    while (run) {
        cout << "Press 1 to guess a word." << endl;
        cout << "Press 2 to exit." << endl;
        cout << "Enter Choice: ";
        cin >> choice;

        if (choice == 1) {
            int randomIndex = rand() % size;
            //random_device rd;
            //mt19937 gen(rd());
            //uniform_int_distribution<int> distribution(0, size - 1);
            //int randomIndex = distribution(gen);

            string unguessableResult = generateUnguessableWord(loadedWords[randomIndex]);
            string correctWord = loadedWords[randomIndex];
            cout << "Word: " << unguessableResult << endl;
            cout << "Guess word: ";
            cin >> guessWord;
            if(caseInsCompare(guessWord, correctWord)){
                cout << "Wow, you guessed the right word...!" << endl;
                score += 1;
                cout << "Score: " << score << endl;
            }
            else {
                cout << "You guessed the wrong word...!" << endl;
                cout << "Right word is " << correctWord << endl;
                score = (score > 0) ? score - 1 : score;
                cout << "Score: " << score << endl;
            }
        }
        else if (choice == 2) {
            run = false;
        }
        else {
            cout << "You entered a wrong choice...!" << endl;
        }
        cout << "_____________________________________________________________________________________________________________________" << endl;
    }

    return 0;
}

