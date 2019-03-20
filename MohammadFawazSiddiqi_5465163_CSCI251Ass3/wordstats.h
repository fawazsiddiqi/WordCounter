/**********************************************************************
 * wordstats.h - CSCI251 - Ass3 - Contains WordStats class declaration
 * Mohammad Fawaz Siddiqi 5465163 mfs995 3/12/18
 **********************************************************************/
#ifndef WORDSTATS_H_
#define WORDSTATS_H_

#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <set>
using namespace std;

// Definition of data contained in BinaryTree


typedef map<string, vector<int>> WordMap;
typedef WordMap::iterator WordMapIter;

class WordStats
{
	public:
		WordStats();
		void ReadDictionary();
		void DisplayDictionary();
		void ReadTxtFile();
		void DisplayKnownWordStats();
		void DisplayUnknownWordStats();
		void DisplayMostFreqKnownWords();
		void DisplayMostFreqUnknownWords();
		void DisplayOriginalText();
	private:
		WordMap KnownWords;
		WordMap UnknownWords;
		set<string> Dictionary;
		char Filename[256];
		
		//add your private fns here
    string LowerCase(string); //private function to concert to lower case
    string NonAlpha(string); //
};

#endif

