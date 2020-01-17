
//  Word Search Puzzle Solver

#include <iostream>
#include <string>
#include <cstdlib>

#include "wordPuzzle.h"

using namespace std;

int main(int argc, char *argv[])
{

// *****************************************************************
//  Headers...

	string		bars, stars;
	string		dictionaryFile;
	string		wordsFile;
	wordPuzzle	myWrdPzl;

	bars.append(65, '-');
	stars.append(65, '*');

// ------------------------------------------------------------------
//  Verify command line arguments.

	if (!myWrdPzl.getArguments(argc, argv, dictionaryFile, wordsFile))
		exit(1);

// ------------------------------------------------------------------
//  Start puzzle.

	cout << bars << endl << "CS 302 - Assignment #6" << endl;
	cout << "Word Search Puzzle Solver" << endl;
	cout << endl;

	if (!myWrdPzl.readDictionary(dictionaryFile)) {
		cout << "main: Read dictionary File, " <<
				dictionaryFile << " error." << endl;
		exit(1);
	}

	if (!myWrdPzl.readLetters(wordsFile)) {
		cout << "main: Read words file, " << wordsFile <<
				 " error." << endl;
		exit(1);
	}

	cout << bars << endl;
	myWrdPzl.showTitle();
	cout << endl;
	myWrdPzl.printLetters();

	myWrdPzl.findWords();
	myWrdPzl.showWords();

// ------------------------------------------------------------------
//  Show statistics.

	cout << endl;
	cout << "Stats:" << endl;
	myWrdPzl.showWordCount();
	cout << "Tree Max Height: " << myWrdPzl.height() << endl;
	cout << "Tree Node Count: " << myWrdPzl.countNodes() << endl;
	cout << endl;

// *****************************************************************
//  All done.

	cout << bars << endl << "Game Over, thank you for playing." << endl;

	return 0;
}

