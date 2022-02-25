#include <iostream>
//#include <string>
#include <sstream>
#include <fstream>
#include <ctime>
#include <algorithm>
#include <cstring>
//#include <ios>
//#include <limits>
#include<map>

using namespace std;

auto ReadList(int JDay)
{
   //load the text file and put it into a single string:
    std::ifstream in("words.txt");
    std::stringstream buffer;
    buffer << in.rdbuf();
    std::string WordList = buffer.str();
    //create variables that will act as "cursors". we'll take everything between them.
    size_t pos1 = 0;
    size_t pos2;
    //create the array to store the strings.
    std::string str[5757];
    for (int x=0; x<=5757; x++){
        pos2 = WordList.find("|", pos1); //search for the bar "|". pos2 will be where the bar was found.
        str[x] = WordList.substr(pos1, (pos2-pos1)); //make a substring, wich is nothing more 
                                              //than a copy of a fragment of the big string.
        pos1 = pos2+1; // sets pos1 to the next character after pos2. 
                         //so, it can start searching the next bar |.
    }
    std::string TodaysWord = str[JDay];
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
        int winner;
        map<char, int> alphaBet;
        string* BothRow = new string[10];
         for (char i = 'a'; i <= 'z'; i++)
                {
                alphaBet[i] = 0;
                }
        for (int counter = 0; counter < 5; ++counter) 
                {
                                for (char i = 'a'; i <= 'z'; i++)
                                {
                                        if (attempt[counter] == i)
                                        {
                                        alphaBet[i]++;

                                        }
                                }
                        if (tolower(attempt[counter]) == tolower(answer[counter]))
                        {
                                BothRow[counter] = tolower(attempt[counter]);
                                BothRow[counter+5] = "G";
                                winner++;
                        } 
                        else if (alphaBet[tolower(attempt[counter] ) ] > 0)
                                {
                                        for (int counter = 0; counter < 5; ++counter) 
                                        {
                                                
                                                if ((BothRow[counter+5] != "G") && ( alphaBet[tolower(attempt[counter]) ] > 0))
                                                {
                                                        BothRow[counter+5] = "Y";
                                                        attempt[counter]--;
                                                        BothRow[counter] = tolower(attempt[counter]);
                                                }
                                        }
                                }       
                        else {
                        BothRow[counter] = tolower(attempt[counter]);
                        BothRow[counter+5] = "B";
                        }
                         //BothRow[counter] = tolower(attempt[counter]);
                }
                if (winner == 5)
                {
                        cout << "You are a winner!" << endl;
                        exit(0);
                }
 

        return BothRow;
}

auto UserGuess () {
        //store guess given user input
        char* inputGuess = new char[5];
        std::cout << "Please enter your guess" << endl;
        cin >> inputGuess;
        //cout << "You have entered: " << inputGuess << endl;
        return inputGuess;
}

int main()
{
//Declare a variable to store a string
char* inputGuess ;
time_t now = time(0);
int MO,DY,JulianDay; //MO = months DY = days JulianDay = Julian Day Number
string* TwoRow = new string[10];
string* UsedLetters = new string[30];
string* Pattern =  new string[6];
string* Color = new string[6];
time_t ttime = time(0);
tm *local_time = localtime(&ttime);
MO = 1 + local_time->tm_mon;
DY = local_time->tm_mday;
JulianDay = JDate (MO,DY);
//cout << "JD is " << JulianDay ;
string TheWord = ReadList(JulianDay);
TheWord.pop_back();
TheWord.erase(std::remove(TheWord.begin(), TheWord.end(), '\n'), TheWord.end());
//cout << TheWord << " THE W " << endl;
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
        }
        UsedLetters[TryNum] = Pattern[TryNum] + UsedLetters[TryNum];
        for (int counter = 5; counter < 10; ++counter) 
        {
                Color[TryNum] = Color[TryNum] + TwoRow[counter];
        }
        UsedLetters[TryNum] = Color[TryNum] + UsedLetters[TryNum];
        //cout << Pattern[TryNum] << endl;
        //cout << Color[TryNum] << endl;
        cout << endl << "Guesses so far: " << endl;
        for (int counter = TryNum; counter >= 0; counter--)
        {
        cout << UsedLetters[counter].substr(5,10);
        cout << endl;
        cout << UsedLetters[counter].substr(0,5);
        cout << endl;
        }

}
return 0;
}