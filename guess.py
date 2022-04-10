#!/usr/bin/env python3
#
#This program is free software: you can redistribute it and/or modify it under the terms 
#of the GNU General Public License as published by the Free Software Foundation, either 
#version 3 of the License, or (at your option) any later version.

#This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; 
#without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. 
#See the GNU General Public License for more details. 

#You should have received a copy of the GNU General Public License along with this program. 
#If not, see <https:#www.gnu.org/licenses/>.
#

from argparse import ArgumentDefaultsHelpFormatter
from fileinput import filename
import os
import sys
from datetime import date
import datetime

def ReadList():
    fileName='words.txt'
    words = []
    with open(fileName) as my_file:
        for line in my_file:
            line = line.replace("|", "")
            line = line.strip()
            words.append(line)
    return words

def wordMatch(inputGuess,TodaysWord):
    winner = 0
    howmany = 0
    ColorRow = []
    NewAnswer = []
    NewAttempt = []
    thisdict = { }
    checked_dict = {}
    for value in range(0,5):
        NewAnswer.append(TodaysWord[value])
        NewAttempt.append(inputGuess[value])
        ColorRow.insert(value,'_')
    for value in range(0,5):
            checked_dict[NewAnswer[value]]=False
            newkey2 =  NewAttempt[value]
            thisdict[newkey2] = sum(char == NewAttempt[value] for char in NewAnswer)
    for value in range(0,5):
        howmanyAns = sum(char == NewAnswer[value] for char in NewAnswer)
        newkey2 =  NewAttempt[value]
        if NewAttempt[value] in NewAnswer:
            if (NewAnswer[value] == NewAttempt[value]):
                winner=winner+1
                ColorRow.pop(value)
                ColorRow.insert(value,'G')
                thisdict[newkey2] = thisdict[newkey2]-1
            if (thisdict[newkey2] > 0) and (ColorRow[value] != 'G'):
                ColorRow.pop(value)
                ColorRow.insert(value,'Y')
                thisdict[newkey2] = thisdict[newkey2]-1
            if (ColorRow[value] != ('Y') and ColorRow[value] != 'G'):
                ColorRow.pop(value)
                ColorRow.insert(value,'B')
        else: 
            ColorRow.pop(value)
            ColorRow.insert(value,'B')
    if winner >= 5:
        print("Congratulations! You solved today's game!\n")
        print("Today's word is ", TodaysWord, "\n")
        exit()
    return ColorRow

def isWord(keybd):
    if keybd.isalpha() and len(keybd) == 5:
        return True
    else:
        print('Please enter 5 letter word.\n')
        return False

def UserGuess():
    userg = input('What is your guess?\n')
    while not isWord(userg):
        userg = input('What is your guess?\n')
    return userg

current_time = datetime.datetime.now()
jul = current_time.strftime('%j')
jday=int(jul)
words = ReadList()
TodaysWord=words[jday]
#print (TodaysWord)
Attempt = []
ColorRow = []
for tryNum in range(1,7):
    inputGuess = UserGuess()
    ColorRow = wordMatch(inputGuess,TodaysWord)
    for value in range(0,5):
        Attempt.append(inputGuess[value])
    Attempt.append("\n")
    for value in range(0,5):
        Attempt.append(ColorRow[value])
    Attempt.append("\n")
    print ("\nYou have ", 6-tryNum, " plays remaining.\n\nPlays so far: ")
    print(''.join(Attempt))
    print ("Try again!")