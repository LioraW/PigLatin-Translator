#include <iostream>
#include <string>
#include <cctype>
using namespace std;

struct Word
{
	string english;
	string pigLatin;
};

string removePunctuation (string);
Word * splitsentence (const string, int &);
void convertToPigLatin(Word [], int);
void displayPigLatin(const Word [], int);


int main()
{
	int mySize = 0;
	string mySentence;
	Word *myWords = nullptr;

	cout << "Enter a string to convert to pig latin: " << endl;
	getline(cin, mySentence);

	mySentence = removePunctuation(mySentence);

	myWords = splitsentence(mySentence, mySize);

	convertToPigLatin(myWords, mySize);

	displayPigLatin(myWords, mySize);

	//garbage collection
	delete [] myWords;
	myWords = nullptr;

	return 0;
}

/**********************************************************
 * Removes punctuation and capital letters from the sentence
 **********************************************************/
string removePunctuation(string sentence){

	string cleanSentence = "";

	for (unsigned int i = 0; i <= sentence.length(); i++)
	{
		if (isspace(sentence[i]) || (isalpha(sentence[i])))
			cleanSentence += tolower(sentence[i]);
	}

	return cleanSentence;
}

/********************************************************************************************
* Splits the sentence into separate strings which are stored in an array of Words
*********************************************************************************************/
Word * splitsentence(const string words, int &size)
{
	//Go through the string and count the number of words.
	for (unsigned int i = 0; i <= words.length(); i++)
	{
		if (isspace(words[i]) && !(isspace(words[i+1])))
			size++;
	}
	size++; //there is usually one more word than the number of separations between words.


	//dynamically allocate an array of Words
	Word *separateWords = nullptr;
	separateWords = new Word[size];

	//Split the sentence
	bool isWord= false;
	string wordAccum = "";
	int wordCount = 0;

	for (unsigned int i = 0; i < words.length(); i++)
	{
		if (isWord && isalpha(words[i])) 	//loop was just in a word and the current position is a letter
		{
			wordAccum += words[i];
		}
		else if (isWord && !(isalpha(words[i])))//loop was just in a word and the current position is not a letter
		{
			separateWords[wordCount].english = wordAccum;
			wordAccum = "";
			wordCount++;
			isWord = false;
		}
		else if (!(isWord) && isalpha(words[i])) // the loop was not just in a word and the current position is now a letter
		{
			wordAccum = words[i];
			isWord = true;
		}

		//else (the loop was not just in a word and the current position is not a letter): do nothing.
	}

	if (wordAccum != "")//there are more letters left then add what's left in the accumulator to the Word array
		separateWords[wordCount].english = wordAccum;

	return separateWords;

}

/******************************************************************************
*  Stores a pig latin word in the pigLatin member of each Word in the Word array
 ******************************************************************************/
void convertToPigLatin (Word wordarr[], int size)
{
	for (int wordCount = 0; wordCount < size; wordCount++) // for each word in the word array
	{
		string englishWord = wordarr[wordCount].english;

		if (englishWord != "")
		{
			char firstLetter = englishWord.front();

			if (firstLetter == 'a'|| firstLetter == 'e' || firstLetter == 'i' || firstLetter == 'o' || firstLetter == 'u')
				wordarr[wordCount].pigLatin = englishWord + "way";
			else
				wordarr[wordCount].pigLatin = englishWord.substr(1, englishWord.length() - 1) + firstLetter + "ay";
		}
	}
}

/********************************
* Displays the pig Latin sentence
 ********************************/
void displayPigLatin(const Word wordArr[], int size)
{
	cout << "*************************************" << endl;
	cout << "Pig Latin translation: " << endl;
	for (int i = 0; i < size; i++)
				cout << wordArr[i].pigLatin << " ";
			cout << endl;
}
