/*
This program is free software: you can redistribute it and/or modify it under the terms 
of the GNU General Public License as published by the Free Software Foundation, either 
version 3 of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; 
without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. 
See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License along with this program. 
If not, see <https://www.gnu.org/licenses/>.
*/

#include <iostream>
#include <sstream>
#include <fstream>
#include <ctime>
#include <algorithm>
#include <cstring>
#include<map>

using namespace std;

string readsFileString(string path) {
    ifstream word_file(path);
    word_file.clear();
    if (!word_file.is_open()) {
        cerr << "Could not open the file - '"
             << path << "'" << endl;
        exit(EXIT_FAILURE);
    }
    std::string ReadData = string((std::istreambuf_iterator<char>(word_file)), std::istreambuf_iterator<char>());
    word_file.close();
    return ReadData;
}

auto ReadList(int JDay)
{
   //Load the text file in a single string:
    //std::ifstream inputs("words.txt");
    std::string WordList = readsFileString("words.txt");
    int sizes = WordList.size();
    cout.flush();
    //create variables for cursors. 
    size_t position1 = 0;
    size_t position2 = 0;
    //create the array to store
    std::string string_list[sizes]={"O"};
    for (int counter=0; counter<sizes; counter++){
        position2 = WordList.find("|", position1);                     //search for the pipe. position2 will be where the bar was found
        string_list[counter] = WordList.substr(position1, (position2-position1)); //now a substring
                                                                        //than a copy of a word of the string
        position1 = position2+1; // sets position1 to the next char after position2 
                                     //start searching the next pipe
    }
    std::string TodaysWord = string_list[JDay];
    //cout << " " << TodaysWord << endl;
return TodaysWord;
}

auto JDate ( int M, int D) 
{
        int JDN;
        if (M == 0) JDN = D;
        if (M == 1) JDN = D + 31;
        if (M == 2) JDN = D + 59;
        if (M == 3) JDN = D + 90;
        if (M == 4) JDN = D + 120;
        if (M == 5) JDN = D + 151;
        if (M == 6) JDN = D + 181;
        if (M == 7) JDN = D + 212;
        if (M == 8) JDN = D + 243;
        if (M == 9) JDN = D + 273;
        if (M == 10) JDN = D + 304;
        if (M == 11) JDN = D + 334;
        return JDN;
}

auto wordMatch (char attempt[5], char answer[5])
{
        int winner = 0;
        string* BothRow = new string[10];
        string NewAnswer;
        string NewAttempt;
        size_t foundAnsw1;
        size_t foundAnsw2;
        size_t foundAnsw3;
        size_t foundAnsw4;
        size_t foundAnsw5;
        int howmany;
        int sizes;
        int IntTimes=0;

        for (int counter=0; counter < 5; counter++) {
                NewAnswer = NewAnswer + answer[counter];
        }
        
        for (int counter=0; counter < 5; counter++) {
                NewAttempt = NewAttempt + attempt[counter];
        }
        for (int counter=0; counter <5; counter++) {
                BothRow[counter] = attempt[counter];
        }
       for (int counter=0; counter < 5; counter++)
                {   
                        if (answer[counter] == attempt[counter]) { BothRow[counter+5] = "G"; winner++;  }

                        foundAnsw1 = NewAnswer.find(attempt[counter]);

                        if ((foundAnsw1  != string::npos)) {
                        
                        foundAnsw1 = NewAnswer.substr(0,1).find(attempt[counter]); 
                        if ((foundAnsw1  != string::npos) && (BothRow[counter+5] != "G") ) BothRow[counter+5] = "Y"; IntTimes++;

                        foundAnsw2 = NewAnswer.substr(1,1).find(attempt[counter]);
                        if ((foundAnsw2 != string::npos) && (BothRow[counter+5] != "G") ) BothRow[counter+5] = "Y";  IntTimes++;

                        foundAnsw3 = NewAnswer.substr(2,1).find(attempt[counter]);
                        if ((foundAnsw3 != string::npos) && (BothRow[counter+5] != "G") ) BothRow[counter+5] = "Y";  IntTimes++;

                        foundAnsw4 = NewAnswer.substr(3,1).find(attempt[counter]);
                        if ((foundAnsw4 != string::npos) && (BothRow[counter+5] != "G") ) BothRow[counter+5] = "Y";  IntTimes++;

                        foundAnsw5 = NewAnswer.substr(4,1).find(attempt[counter]);
                        if ((foundAnsw5 != string::npos) && (BothRow[counter+5] != "G") ) BothRow[counter+5] = "Y";  IntTimes++;
                                
                        }

                        else BothRow[counter+5] = "B";
                }
        if (winner == 5)
                {
                cout << "Congratulations! You solved today's game!"<< endl;
                cout << "Today's word is " << NewAnswer << "." << endl;
                exit(0);
                }

        return BothRow;
}

auto UserGuess () {
        //store guess given user input
        char* inputGuess = new char[5];
        std::cout << "To play today's game. Please enter a 5 letter word." << endl;
        cin >> inputGuess;
        cout << "Your entry is: " << inputGuess << endl;
        return inputGuess;
}

int main()
{
//Declare a variable to store a string
char* inputGuess ;
time_t now = time(0);
int MO,DY,JulianDay; //MO = months DY = days JulianDay = Julian Day Number
string* TwoRow = new string[10];
string* Pattern =  new string[6];
string* Color = new string[6];
time_t ttime = time(0);
map<string, string> letterMap;
tm *local_time = localtime(&ttime);
MO = 1 + local_time->tm_mon;
DY = local_time->tm_mday;
JulianDay = JDate (MO,DY);
//cout << "JD is " << JulianDay ;
string TheWord = ReadList(JulianDay);
TheWord.pop_back();
TheWord.erase(std::remove(TheWord.begin(), TheWord.end(), '\n'), TheWord.end());
// declaring character array
// copying the contents of the
// string to char array
int numlen = TheWord.length();
// declaring character array
char* newWord = new char [numlen + 1];
// copying the contents of the
// string to char array
strcpy(newWord, TheWord.c_str());
//cout << "Today's word is " << newWord ;
for (int TryNum=0; TryNum < 6; TryNum++ ) 
{
       inputGuess = UserGuess();
       TwoRow = wordMatch(inputGuess,newWord);
        for (int counter = 0; counter < 5; ++counter) 
        {
                Pattern[TryNum] = Pattern[TryNum] + TwoRow[counter];
                //cout << TwoRow[counter] << " 1st ";
        }
        for (int counter = 5; counter < 10; ++counter) 
        {
                Color[TryNum] = Color[TryNum] + TwoRow[counter];
                //cout << TwoRow[counter] << " 2nd ";
        }
        letterMap.insert({Pattern[TryNum], Color[TryNum]});
        //cout << Pattern[TryNum] << endl;
        //cout << Color[TryNum] << endl;
        cout << "Try again! " << endl;
        cout << endl << "You have " << 5-TryNum << " plays remaining." << endl << endl << "Plays so far: " << endl << endl;
        for (auto i = letterMap.begin(); i != letterMap.end(); ++i) {
        cout << i->first << ' ' << i->second << '\n';
        }
}
return 0;
}