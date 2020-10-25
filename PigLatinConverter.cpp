#include <iostream>
#include <string>
#include <cctype>
using namespace std;

struct Word
{
	string language;
	string translation;
};

string removePunctuation (string);
Word * splitsentence (const string, int &);
void convertToPigLatin(Word [], int);
void convertToEnglish (Word [], int);
void displayTranslation(const Word [], int);


int main()
{
	int mySize = 0;
	string mySentence;
	char convertTo;
	Word *myWords = nullptr;

	cout << "Enter a sentence to convert to pig latin, then press enter: " << endl;
	getline(cin, mySentence);

	cout << "Do you want to convert to English (E) or Pig Latin (P)? Type E or P then press enter:" << endl;
	cin >> convertTo;
	convertTo = toupper(convertTo);

	while (!(convertTo == 'E' || convertTo == 'P'))
	{
		cout << "The only options are pig latin or english. please enter E or P then press enter:" << endl;
		cin >> convertTo;
		convertTo = toupper(convertTo);
	}

	mySentence = removePunctuation(mySentence);

	myWords = splitsentence(mySentence, mySize);

	if (convertTo == 'P')
		convertToPigLatin(myWords, mySize);
	else if (convertTo == 'E')
		convertToEnglish(myWords, mySize);

	displayTranslation(myWords, mySize);

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
			separateWords[wordCount].language = wordAccum;
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
		separateWords[wordCount].language = wordAccum;

	return separateWords;

}

/******************************************************************************
*  Stores a pig latin word in the translation member of each Word in the Word array
 ******************************************************************************/
void convertToPigLatin (Word wordarr[], int size)
{
	for (int wordCount = 0; wordCount < size; wordCount++) // for each word in the word array
	{
		string originalWord = wordarr[wordCount].language;

		if (originalWord != "")
		{
			char firstLetter = originalWord.front();

			if (firstLetter == 'a'|| firstLetter == 'e' || firstLetter == 'i' || firstLetter == 'o' || firstLetter == 'u')
				wordarr[wordCount].translation = originalWord + "way";
			else
				wordarr[wordCount].translation = originalWord.substr(1, originalWord.length() - 1) + firstLetter + "ay";
		}
	}
}

/******************************************************************************
*  Stores an english word in the translation member of each Word in the Word array
 ******************************************************************************/
void convertToEnglish (Word wordarr[], int size)
{
	for (int wordCount = 0; wordCount < size; wordCount++) // for each word in the word array
	{
		string originalWord = wordarr[wordCount].language;

		if (originalWord != "")
		{
			if (originalWord.substr(originalWord.length() - 3, 3) == "way")
				wordarr[wordCount].translation = originalWord.substr(0, originalWord.length() - 3);
			else
				wordarr[wordCount].translation = originalWord[originalWord.length() - 3] + originalWord.substr(0, originalWord.length() - 3);
		}
	}
}
/********************************
* Displays the translated sentence
 ********************************/
void displayTranslation(const Word wordArr[], int size)
{
	cout << "*************************************" << endl;
	cout << "Here is the translation: " << endl;
	for (int i = 0; i < size; i++)
				cout << wordArr[i].translation << " ";
			cout << endl;
}
