/**********************************************************************
 * wordstats.cpp - CSCI251 - Ass3 - Contains WordsStats class definition
 * Mohammad Fawaz Siddiqi 5465163 mfs995 3/12/18
 **********************************************************************/
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <cstring>
#include "wordstats.h"
using namespace std;

WordStats::WordStats(){
	strcpy(Filename,"testdata.txt"); //copies testdata.txt into the filename variable
}

// Reads dictionary.txt into Dictionary
void WordStats::ReadDictionary(){
    ifstream fileInput; //file input variable to manipulate file
    string text;
    
    
    fileInput.open("dictionary.txt"); //opens the dictionary.txt
    
    if(!fileInput.good()) { //checks if the file iss opened or not
        cout<<"ERROR!! CAN NOT OPEN DICTIONARY.TXT!!"<<endl;
        exit(1);
    }
    while(!fileInput.eof()) {
        fileInput>>text; //reads text data into the fileInput variable
        Dictionary.insert(LowerCase(text)); //inserts the text in lower case into the dictionary
    }
    cout<<Dictionary.size()<<" words read from dictionary."<<endl<<endl; //gets the size of the dictionary
}

// Displays Dictwords 10 at a time
void WordStats::DisplayDictionary(){
    set<string>::iterator iterate = Dictionary.begin(); //an iterator of the STL set is initialized to the first element in the Dictionary
    int count = 0;
    cout<<"Displaying the first 20 words in the dictionary..."<<endl;
    for (iterate; iterate!=Dictionary.end(); ++iterate) { //for loop to use the iterator to manipulate the loop
        cout<<*iterate<<endl; //outputs the value in the iterator
        if (count++ == 19) { //breaks the loop once the certain count is reached
            break;
        }
    }
    cout<<endl;
    
}

// Reads textfile into KnownWords and UnknownWords
void WordStats::ReadTxtFile(){
   
    ifstream fileInput;
    string text;
    string cText;
    int position = 0;
    
    fileInput.open(Filename);
    
    if (!fileInput.good()) {
        cout<<"ERROR!! CAN NOT OPEN TESTDATA.TXT!!"<<endl;
        exit(1);
    }
    
    while(!fileInput.eof()) {
        fileInput>>text; //reads from testdata.txt
        if (text.size() == 1 && char(text[0]) == '-') { //checks if the read data size is equal to 1 and the character in the posoition of tet 0 is a hyphen then continues the program
            continue;
        }
        cText = NonAlpha(LowerCase(text)); //stores the value of text with non alphabetical characters and in lower case text
        
        // If the cText in Dictionary set
        set<string>::iterator dIter = Dictionary.find(cText); //a map STL iterator uses the dictionary  to find cText (iterator to element)
        if (dIter != Dictionary.end()) { //if the iterator is not equal to the value flund in the end of the dictionary
            WordMapIter kMapIter = KnownWords.find(cText); //it stores the known word in the kMapIter which is from WorldMap iterator
           
            // If cText in KnownWords

            if(kMapIter != KnownWords.end()) // if the word is already in map
                (*kMapIter).second.push_back(position); //it takes the second value in the pair and takes the position
            else {
                vector<int> vect(1, position); //initializes a vector with the position
                KnownWords.insert(kMapIter, pair<string,vector<int>>(cText, vect)); //inserts the text into the map
            }
        } else { //if not cText found
            WordMapIter uMapIter = UnknownWords.find(cText); //a map STL iterator uses the dictionary  to find cText (iterator to element)
            if(uMapIter != KnownWords.end())
                UnknownWords[cText].push_back(position); //array of cText in unknown word and pushes the element from the back
            else {
                vector<int> vect(1, position);//initializes a vector with the position
                KnownWords.insert(uMapIter, pair<string, vector<int> >(cText, vect));//inserts the text into the map
            }
        }
        
        position++; //increments position
    }
    
    cout<<KnownWords.size()<<" known words read."<<endl;
    cout<<UnknownWords.size()<<" unknown words read."<<endl<<endl;
    //finds the size of known and unknown words
}

// Displays stats of words in KnownWords
void WordStats::DisplayKnownWordStats(){
    //display
    cout<<setw(15)<<right<<"Word"<<'\t';
    cout<<setw(6)<<right<<"Count"<<'\t';
    cout<<setw(25)<<left<<"Positions"<<endl;
    
    for (WordMapIter iterator = KnownWords.begin(); iterator != KnownWords.end(); ++iterator)
        //a for loop initialized with the iterator of the known words, and increments accordingly
    {
        vector<int> vector = (*iterator).second;//takes the second position in the iterator and stores it in a vector
        cout<<setw(15)<<right<<(*iterator).first<<'\t'; //it takes the first value in the iterator
        cout<<setw(4)<<right<<vector.size()<<'\t'; //displays the size
        cout<<setw(3)<<left;
        copy(vector.begin(), vector.end(), ostream_iterator<int>(cout, " ")); //copies the value from the beginning of the vector to the end and then outputs it using the ostream_iterator
        cout<<endl;
    }
    cout<<endl;
}

// Displays stats of words in Unknownwords
void WordStats::DisplayUnknownWordStats(){
    cout<<setw(15)<<right<<"Word"<<'\t';
    cout<<setw(6)<<right<<"Count"<<'\t';
    cout<<setw(25)<<left<<"Positions";
    cout<<endl;
    
    for (WordMapIter iterator = UnknownWords.begin(); iterator != UnknownWords.end(); ++iterator)
    //a for loop initialized with the iterator of the unknown words, and increments accordingly
    {
        vector<int> vector = (*iterator).second;//takes the second position in the iterator and stores it in a vector
        
        cout<<setw(15)<<right<<(*iterator).first<<'\t'; //it displays the first value in the iterator
        cout<<setw(4)<<right<<vector.size()<<'\t';//displays the size
        cout<<setw(3)<<left;
        copy(vector.begin(), vector.end(), ostream_iterator<int>(cout, " "));
        //copies the value from the beginning of the vector to the end and then outputs it using the ostream_iterator
        cout<<endl;
    }
    cout<<endl;
}

// Displays 20 most frequent words in KnownWords
void WordStats::DisplayMostFreqKnownWords(){
    multimap<int,string> knownFreqWords; //multimap initialized for known words
    multimap<int,string>::reverse_iterator revIteratorMap; //reversed iterator initialized
    int count = 0;
    
    for (WordMapIter iterator = KnownWords.begin(); iterator != KnownWords.end(); ++iterator)
     //a for loop initialized with the iterator of the known words, and increments accordingly
    {
        vector<int> vector = (*iterator).second;//takes the second position in the iterator and stores it in a vector
        knownFreqWords.insert(pair<int,string>(vector.size(), (*iterator).first));
        //inserts value into the multimap by pairing the vector size and the first value in the iterator
    }
    
    cout<<right<<setw(15)<<"Word";
    cout<<setw(8)<<"Count"<<endl;
    for (revIteratorMap = knownFreqWords.rbegin(); revIteratorMap != knownFreqWords.rend();
         ++revIteratorMap)
    //a for loop initialized by the first element in the reverse iterator, which continues till it reaches the end of the reversered iterator, increments accordingly
    {
        cout<<setw(15)<<(*revIteratorMap).second; //returns the second value in the reversed iterator map
        cout<<right;
        cout<<setw(6)<<(*revIteratorMap).first<<endl;//returns the first value in the reversed iterator map
        if (count++ == 19) { //breaks the loop once the certain count is reached
            break;
        }
    }
    cout<<endl;
}

// Displays 20 most frequent words in UnknownWords
void WordStats::DisplayMostFreqUnknownWords(){
    multimap<int,string> unknownFreqWords;//multimap initialized for unknown words
    multimap<int,string>::reverse_iterator revIteratorMap;//reversed iterator initialized
    int count = 0;
    
    for (WordMapIter iterator = UnknownWords.begin(); iterator != UnknownWords.end(); ++iterator)
   //a for loop initialized with the iterator of the known words, and increments accordingly
    {
        vector<int> vector = (*iterator).second;//takes the second position in the iterator and stores it in a vector
        unknownFreqWords.insert(pair<int,string>(vector.size(), (*iterator).first));
        //inserts value into the multimap by pairing the vector size and the first value in the iterator
    }
    
    cout<<right<<setw(15)<<"Word";
    cout<<setw(8)<<"Count"<<endl;
    for (revIteratorMap = unknownFreqWords.rbegin(); revIteratorMap != unknownFreqWords.rend();
         ++revIteratorMap)
    //a for loop initialized by the first element in the reverse iterator, which continues till it reaches the end of the reversered iterator, increments accordingly
    {
        cout<<setw(15)<<(*revIteratorMap).second; //returns the second value in the reversed iterator
        cout<<right;
        cout<<setw(6)<<(*revIteratorMap).first<<endl; //returns the first value in the reversed
        if (count++ == 19) { //breaks the loop once the certain count is reached
            break;
        }
    }
    cout<<endl;
}

// Displays original text from KnownWords & UnknownWords
void WordStats::DisplayOriginalText(){
    map<int,string> TextMap; //mapping initialized
    map<int,string>::iterator textMapIter; //map iterator initialized
    WordMapIter kWordsIterator; //known words iterator initialized
    WordMapIter uWordsIterator; //unknown words iterator initialized
    
    for (kWordsIterator = KnownWords.begin(); kWordsIterator != KnownWords.end(); ++kWordsIterator)
      //a for loop initialized with the iterator of the known words, and increments accordingly
    {
        vector<int>::iterator vectorIterator; //vector iteratoe initialized
        vector<int> vector = (*kWordsIterator).second; //takes in the second value in the kwordsiterator and stores it in the vector
        
        for (vectorIterator = vector.begin(); vectorIterator != vector.end(); ++vectorIterator)
        //a for loop initialized with the iterator vector , and increments accordingly
        {
            TextMap.insert(pair<int,string>((*vectorIterator),(*kWordsIterator).first));
            //inserts value into the multimap by pairing the vector size and the first value in the iterator
        }
    }
    
    for (uWordsIterator = UnknownWords.begin(); uWordsIterator != UnknownWords.end();
         ++uWordsIterator)
         //a for loop initialized by the first element in the Unkownwords vector, which continues till it reaches the end of the Unkownwords vector, increments accordingly
    {
        vector<int>::iterator vectorIterator;
        //vector iteratoe initialized
        vector<int> vector = (*uWordsIterator).second;
        //takes in the second value in the uwordsiterator and stores it in the vector
        
        for (vectorIterator = vector.begin();vectorIterator != vector.end(); ++vectorIterator)
        //a for loop initialized with the iterator vector , and increments accordingly
        {
            TextMap.insert(pair<int, string>((*vectorIterator), (*uWordsIterator).first));
            //inserts value into the multimap by pairing the vector size and the first value in the iterator
        }
    }
    
    // prints the entire text in order by keeping the textMapIter to the value in text map begin, and loops till the end accordingly incrementing.
    for (textMapIter = TextMap.begin(); textMapIter != TextMap.end(); ++textMapIter) {
        cout<<(*textMapIter).second<<" ";
    }
    
    cout<<endl;
}

// ============ Private Fns ========================
string WordStats::LowerCase(string text) //private function fo covert to lower case
{
    for (int i=0; i<text.length(); i++) text[i] = tolower(text[i]);
    return text;
}

string WordStats::NonAlpha(string text) //private fuction to remove all non-alphabetic characters except hyphen and '
{
    string cText;
    for (int i=0; i<text.length(); ++i) {
        if (isalpha(text[i])){
            cText += text[i];
        }
        else if (char(text[i]) == '\''){
            cText += text[i];
        }
        else if (char(text[i]) == '-') {
            cText += text[i];
        }
    }
    return cText;
}
