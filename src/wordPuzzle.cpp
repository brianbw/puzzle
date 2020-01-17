
#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <string>
#include <cstring>
#include <cstdlib>
#include "wordPuzzle.h"

using namespace std; 

// initialize class variables to empty state
wordPuzzle::wordPuzzle()
{
	title = "";
	order = 0;
	letters = NULL;
}

// delete the letters array
wordPuzzle::~wordPuzzle()
{
	for (int i = 0; i < order; i++)
		delete [] letters[i];
	delete [] letters; 
}

// read formatted letters grid from passed file name and
// store letters as strings in dynamic 2d array
// 1st line -> title line 
// 2nd line -> order 
// 3rd line on -> letters w/ order # of rows and order # of words per row
bool wordPuzzle::readLetters(const string fileName)
{
	ifstream in;
	string temp = "";

	in.open(fileName.c_str());
	
	if(!in.is_open())
		return false;

	getline(in, title);						// 1st line
	in >> order;  							// 2nd line

	letters = new string*[order];			// allocate

	for (int i = 0; i < order; i ++)
		letters[i] = new string[order];		// allocate 2d

	for (int i = 0; i < order; i ++)
		for (int j = 0; j < order; j ++)
		{
			in >> temp;
			letters[i][j] = temp;			// 3rd line on
		}

	in.close();
	return true;
}

// read the passed dictionary file name and
// store words in avlTree
// file read successful -> true, false otherwise
bool wordPuzzle::readDictionary(const string fileName)
{
	ifstream in;
	in.open(fileName.c_str());

	if(!in.is_open())
		return false;

	string temp = "";
	while (getline(in, temp))
	{
		insert(temp);
	}

	in.close();
	return true;
}

// read passed command line information
// if no args -> "Usage: ./findWords -d <dictFile> -w <wordsFile>"
// if invalid -> "Error, command line arguments are invalid."
bool wordPuzzle::getArguments(int c, char *v[], string &dfName, string &wfName)
{
	if (c == 1)
	{
		cout << "Usage: ./findWords -d <dictFile> -w <wordsFile>." << endl;
		return false;
	}

	if (c != 5)				
	{
		cout << "Error, command line arguments are invalid." <<endl;
		return false;
	}

	bool d = false;				
	int dIndex = 0;			

	bool w = false;
	int wIndex = 0;

	string errorMsg = "";

	for (int i = 1; i < c; i++)
	{
		if (string(v[i]) == "-d")
		{
			if (d == true)				// appear twice
			{
				d = false;
				errorMsg = "Error, invalid dictionary file specifier.";
			}

			else
			{
				d = true;				// appear once
				dIndex = i;				// get index
			}
		}

		else if (string(v[i]) == "-w")
		{	
			if (w == true)				// appear twice
			{
				w = false;
				errorMsg = "Error, invalid word file specifier.";
			}

			else
			{
				w = true;				// appear once
				wIndex = i;				// get index 
			}		
		}
	}

	if (!d || !w)
	{	
		if (errorMsg == "")				// arguments never existed
		{
			if (!d)
				errorMsg = "Error, invalid dictionary file specifier.";
			else if (!w)
				errorMsg = "Error, invalid word file specifier.";
		}

		cout << errorMsg << endl;
		return false;
	}

 	ifstream inDict;
 	ifstream inWord;

 	dfName = string(v[dIndex + 1]);		// next to "-d"
 	wfName = string(v[wIndex + 1]);		// next to "-w"

 	inDict.open(dfName.c_str());
 	inWord.open(wfName.c_str());

 	if (!inDict.is_open())
 	{
 		cout << "Error, unable to open input file: " << v[dIndex] << endl;
 		inDict.close();
 		return false; 
 	}


 	 if (!inWord.is_open())
 	{
 		cout << "Error, unable to open input file: " << v[wIndex] << endl;
 		inWord.close();
 		return false; 
 	}

 	return true; 
}

// find all words in letter grid (calls private)
void wordPuzzle::findWords()
{
	string wrd = "";
	for (int i = 0; i < order; i++)
		for (int j = 0; j < order; j++)
			findWords(i, j, wrd);

	return;
}

// find all words in letter grid
// word and location stored in AVL tree as string w/ starting location 
// word is considered different if path is different
// so same words may be found multiple times w/ different paths
void wordPuzzle::findWords(int i, int j, string wrd)
{
	string complete = ""; 
	if (i < order && i >= 0 && j < order && j >= 0)	// if inside playing board
	{

		wrd = wrd + letters[i][j];					// concatenate letters

		if (search(wrd))
		{
			complete = wrd + "     from: (" + to_string(i) + "," + to_string(j) + ")";
			wordsFound.insert(complete);

			if (isPrefix(wrd))						// if still possible word (after storage)
			{
				findWords(i - 1, j - 1, wrd);		// up left	
				findWords(i - 1, j, wrd);			// up
				findWords(i - 1, j + 1, wrd);		// up right

				findWords(i, j - 1, wrd);			// left
				findWords(i, j + 1, wrd);			// right

				findWords(i + 1, j - 1, wrd);		// down left
				findWords(i + 1, j, wrd);			// down
				findWords(i + 1, j + 1, wrd);		// down right
			}

			return; 
		}

		if (isPrefix(wrd))							// if possible word (not stored prev.)
		{
			findWords(i - 1, j - 1, wrd);			// up left	
			findWords(i - 1, j, wrd);				// up
			findWords(i - 1, j + 1, wrd);			// up right

			findWords(i, j - 1, wrd);				// left
			findWords(i, j + 1, wrd);				// right

			findWords(i + 1, j - 1, wrd);			// down left
			findWords(i + 1, j, wrd);				// down
			findWords(i + 1, j + 1, wrd);			// down right
		}	
	}

	return; 
}

// display puzzle title set by readLetters()
void wordPuzzle::showTitle() const
{
	cout << "Letter Set Title: " << title << endl;
}

// use appropriate avlTree function and display # of words found
void wordPuzzle::showWordCount() const
{
	cout << "Word Count: " << wordsFound.countNodes() << endl;
}

// display all words found in alphabetical
// appropriate avlTree print function should be used
void wordPuzzle::showWords() const
{
	wordsFound.printTree(INORDER2);
}

// display the title and formatted letter grids
void wordPuzzle::printLetters() const
{
	cout << "   ";
	for (int j = 0; j < order; j++)
		cout << " " << "___"; 								// very first row
	
	for (int i = 0; i < order; i ++)
	{
		cout << endl << "   " << "|"; 						// start 1st row

		for (int j = 0; j < order; j++)
			cout << "   " << "|"; 							// 1st row

		cout << endl << "   " << "|";						// start 2nd row

		for (int j = 0; j < order; j++)
			cout << " " << letters[i][j] << " " << "|";		// 2nd row 

		cout << endl << "   " << "|";						// start 3rd row

		for (int j = 0; j < order; j++)
			cout << "___" << "|"; 							// 3rd row
	}

	cout << endl << endl << endl;
}