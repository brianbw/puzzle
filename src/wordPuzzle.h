
#include "avlTree.h"

class wordPuzzle : public avlTree<string>
{
	public:
		wordPuzzle();	// constructor
		~wordPuzzle();	// destructor

		bool readLetters(const string);
		bool readDictionary(const string);
		bool getArguments(int, char *[], string &, string &);
		void findWords();
		void showTitle() const;
		void showWordCount() const;
		void showWords() const; 
		void printLetters() const;

	private:
		string title;	
		int order;
		string **letters;
		avlTree<string> wordsFound;
		void findWords(int, int, string);
};
