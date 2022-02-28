#include <iostream>
#include <sstream>
#include <fstream>
#include <ctime>
#include <algorithm>
#include <cstring>
#include<map>

using namespace std;

auto ReadList(int JDay)
{
   //Load the text file in a single string:
    std::ifstream inputs("words.txt");
    std::stringstream buffer;
    buffer << inputs.rdbuf();
    std::string WordList = buffer.str();
    //create variables for cursors. 
    size_t position1 = 0;
    size_t position2 = 0;
    //create the array to store
    std::string string_list[5757];
    for (int counter=0; counter<=5757; counter++){
        position2 = WordList.find("|", position1); //search for the bar "|". pos2 will be where the bar was found.
        string_list[counter] = WordList.substr(position1, (position2-position1)); //make a substring, wich is nothing more 
                                              //than a copy of a fragment of the big string.
        position1 = position2+1; // sets pos1 to the next character after pos2. 
                         //so, it can start searching the next bar |.
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
        int winner;
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
                        if ((foundAnsw1  != string::npos) && (BothRow[counter+5] != "G") ) {BothRow[counter+5] = "Y"; IntTimes++; cout << foundAnsw1 << "times" << IntTimes << endl; }

                        foundAnsw2 = NewAnswer.substr(1,1).find(attempt[counter]);
                        if ((foundAnsw2 != string::npos) && (BothRow[counter+5] != "G") ) {BothRow[counter+5] = "Y";  IntTimes++; cout << foundAnsw2  << "times" << IntTimes << endl; }

                        foundAnsw3 = NewAnswer.substr(2,1).find(attempt[counter]);
                        if ((foundAnsw3 != string::npos) && (BothRow[counter+5] != "G") ) {BothRow[counter+5] = "Y";  IntTimes++; cout << foundAnsw3 << "times" << IntTimes << endl; }

                        foundAnsw4 = NewAnswer.substr(3,1).find(attempt[counter]);
                        if ((foundAnsw4 != string::npos) && (BothRow[counter+5] != "G") ) {BothRow[counter+5] = "Y";  IntTimes++; cout << foundAnsw4 << "times" << IntTimes << endl; }

                        foundAnsw5 = NewAnswer.substr(4,1).find(attempt[counter]);
                        if ((foundAnsw5 != string::npos) && (BothRow[counter+5] != "G") ) {BothRow[counter+5] = "Y";  IntTimes++; cout << foundAnsw5 << "times" << IntTimes  << endl; }
                                
                        }

                        else BothRow[counter+5] = "B";
                }

        if (winner == 5)
                {
                cout << "Congratulations! You solved today's game!"<< endl;
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
// declaring character array
// copying the contents of the
// string to char array
int numlen = TheWord.length();
// declaring character array
char* newWord = new char [numlen + 1];
// copying the contents of the
// string to char array
strcpy(newWord, TheWord.c_str());
cout << "Today's word is " << newWord ;
for (int TryNum=0; TryNum < 6; TryNum++ ) 
{
       inputGuess = UserGuess();
       TwoRow = wordMatch(inputGuess,newWord);
        for (int counter = 0; counter < 5; ++counter) 
        {
                Pattern[TryNum] = Pattern[TryNum] + TwoRow[counter];
                //cout << TwoRow[counter] << " 1st ";
        }
        UsedLetters[TryNum] = Pattern[TryNum] + UsedLetters[TryNum];
        for (int counter = 5; counter < 10; ++counter) 
        {
                Color[TryNum] = Color[TryNum] + TwoRow[counter];
                //cout << TwoRow[counter] << " 2nd ";
        }
        UsedLetters[TryNum] = Color[TryNum] + UsedLetters[TryNum];
        //cout << Pattern[TryNum] << endl;
        //cout << Color[TryNum] << endl;
        cout << "Try again! " << endl;
        cout << endl << "You have " << TryNum + 5 << " plays remaining." << endl << "Plays so far: " << endl;
        for (int counter = 0; counter < TryNum; counter++)
        {
        cout << UsedLetters[counter].substr(5,10);
        cout << endl;
        cout << UsedLetters[counter].substr(0,5);
        cout << endl;
        }

}
return 0;
}