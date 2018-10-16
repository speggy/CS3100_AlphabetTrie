#include "stdafx.h"
#include "Trie.h"
#include <vector>
#include <string>
//#include <array>
#include <fstream>
#include <iostream>

using namespace std;

/*Space Complexity: Each trie has a root, and a nodeCount. The root can have n amount of pointers so if we take the space complexity of the TrieNode 
times the space complexity of the Trie itself, we have 2pn(2pn)*/
Trie::Trie()
{
	root = new TrieNode("ROOT -- NULL PAYLOAD");
	nodeCount = 1;
}

/*Adds a new word to the trie.
Returns true if the word was added, false otherwise.
Time Complexity: Thete(1)*/
bool Trie::insert(string word)
{
	return insertHelper(root, word);
}

/*Used as a helper function for insert; handles recursion and node creation.
Returns the result of the word addition. If word couldn't be added, return false, true otherwise.
Time Complexity: Theta(length-Of-Word)*/
bool Trie::insertHelper(TrieNode* current, string word)
{
	string firstLetter = word.substr(0, 1); // Peel the first letter off of the word
	TrieNode* tmp = nullptr;
	for (auto &indexPointer : current->children) // iterate through the current node's vector to see if the letter already exists
	{
		if (indexPointer->payload.compare(firstLetter) == 0) // Check to see if the letter exists already 
		{
			tmp = indexPointer; // set tmp to the index of the letter that already exists for recursion 
		}
	}
	if (!tmp) // Checks to see if tmp was set to anything to signify if a letter exists or not
	{
		tmp = new TrieNode(firstLetter); // create a new node with the current payload
		current->children.push_back(tmp); // Push the new node into the vector 
		nodeCount++; // increment the number of nodes in the trie
	}
	if (word.length() > 1) // check to see if the word has been exhausted
	{
		return insertHelper(tmp, word.substr(1)); // recurse one the existing letter index and the rest of the word
	}
	else
	{
		tmp->isEndOfWord = true; // word has been added and set the end of word value to true
	}
	return true; 
}

/*Gets the number of complete words in the trie. 
Time Complexity: Theta(1)*/
int Trie::count()
{
	return countHelper(root);
}

/*Handles all the recursion and logic for the count function 
Time Complexity: Theta(n)*/
int Trie::countHelper(TrieNode * current)
{
	int wordCount = 0;
	if (current->isEndOfWord) //initial check to see if the word has an end of word flag
	{
		wordCount++; // increment
	}
	for (auto &index : current->children) // iterate through the current node's children
	{
		wordCount += countHelper(index); // add the result of the recursion to the word count 
	}	
	return wordCount; 
}

/*Return the total number of nodes in the trie. 
Time Complexity: Theta(1)*/
int Trie::getSize()
{
	return nodeCount;
}

/*Returns the result of the functions ability to find a given word.
Time Complexity: Theta(1)*/
bool Trie::find(string word)
{
	if (findHelper(root, word)) // pass the helper function the root anad the word that way the search starts at the top
	{
		return true;
	}
	else
		return false;
}

/*Handles all the recursion for finding nodes in the trie
Time Complexity: Theta(length-of-word)*/
bool Trie::findHelper(TrieNode* currentNode, string findMe)
{
	string firstLetter = findMe.substr(0, 1); // peel off the first letter 
	TrieNode* tmp = nullptr;
	for (auto &index : currentNode->children)
	{
		if (index->payload.compare(firstLetter) == 0) // check if the first letter of the word is in the current node's vector
		{
			tmp = index; // record tmp for later recursion
		}
	}
	if (!tmp) // letter was not found in the current vector
	{
		return false;
	}
	if (findMe.length() > 1) // makes sure there is still word to recurse on 
	{
		return findHelper(tmp, findMe.substr(1)); // recurse on the index that we want and pass the rest of the word
	}
	return true;
}

/*A function to get the last letter in a string represented as a node
Time Complexity: Theta(length-of-remaining-word)*/
Trie::TrieNode* Trie::findNode(TrieNode* current, string substr)
{
	string firstLetter = substr.substr(0, 1); // peel off the first letter for comparisons
	TrieNode* tmp = nullptr;
	for (auto &index : current->children)
	{
		if (index->payload.compare(firstLetter) == 0) // check if the first letter of the word is in the current node's vector
		{
			tmp = index; // record the index for later recursion
		}
	}
	if (!tmp) // letter was not found in the current vector
	{
		return nullptr;
	}
	if (substr.length() > 1) // makes sure there is still word to recurse on 
	{
		return findNode(tmp, substr.substr(1)); // recurse on the index and pass the rest of the word 
	}
	return tmp;
}

/*Returns the total number of existing words that begin with a given prefix
Time Complexity: Theta(n*length-of-words)*/
int Trie::completeCount(string prefix)
{
	TrieNode* lastLetterNode = findNode(root, prefix); // get the last node in the substrng 
	if (lastLetterNode)
	{
		return countHelper(lastLetterNode); // get the count of words
	}
	else
		return 0; // no complete words exist
}

/*Handles all the recursion for the completeCount function
Time Complexity: Theta(length of word)*/
int Trie::completeCountHelper(TrieNode* current)
{
	int prefixWordCount = 0; 
	if (current->isEndOfWord) // initial check to see if and end of word key has been reached 
	{
		prefixWordCount++;
	}
	for (auto &index : current->children) // iterate through node's children and recurse 
	{
		prefixWordCount += completeCountHelper(index);
	}
	return prefixWordCount;
}

/*Returns the complete words in a vector that start with a given prefix
Time Complexity: Theta(1)*/
vector<string> Trie::complete(string prefix)
{
	// get the last node that exists in the prefix
	TrieNode *lastLetterNode = findNode(root, prefix);
	vector<string> *wordSuggestions = new vector<string>;

	autoComplete(lastLetterNode, wordSuggestions, prefix.substr(0, prefix.length()-1)); // I peel off the last letter of the prefix to account for duplicates when adding to the prefix in the helper function

	printVector(wordSuggestions);
	return  *wordSuggestions;
}

/*Handles all the recursion for the complete function 
Time Complexity: Theta(length of word)*/
void Trie::autoComplete(TrieNode *current, vector<string> *wordSuggestions, string prefix)
{
	if (current->isEndOfWord) //initial check to see if the word has an end of word flag
	{
		wordSuggestions->push_back(prefix + current->payload); // Add the contents of the current node to the prefix then add that to the vector since there is a complete word
	}
	for (auto &index : current->children) // iterate through the current node's children
	{
		autoComplete(index, wordSuggestions, prefix + current->payload); // recurse on the children and add the current node's payload so there are no duplicates upon recursion 
	}
}

/*Just a function that prints out all the information about a node. Nothing to see here. */
void Trie::printNode(TrieNode* printMe)
{
	if (!printMe)
	{
		cout << "Node does not exist." << endl;
	}
	else
	{
		cout << "Payload: " << printMe->payload << endl;
		cout << "List of pointers: " << endl;
		for (auto &indexPointer : printMe->children)
		{
			cout << indexPointer->payload << ", ";
		}
		cout << "\n";
		if (printMe->isEndOfWord)
		{
			cout << "isEndOfWord: True" << endl;
		}
		else
			cout << "isEndOfWord: False" << endl;
		cout << "\n";
	}
}

/*Also another fucntion that prints out the contents of the string vector for the complete function 
Time Complexity: Theta(n)*/
void Trie::printVector(vector<string>* printMe)
{
	for (auto indexPointer : *printMe)
	{
		cout << indexPointer << endl;
	}
}

/*Reads in the .txt file that we were supplied and inserts each word into the trie
Time Complexity: Theta(n)*/
bool Trie::read(string filename)
{
	ifstream readMe(filename);

	if (!readMe.is_open()) // Checks to see if the file exists and exits if it does not 
	{
		cerr << "File cound not be opened." << endl;
		return false;
	}
	else // File can be opened and is readable
	{
		string word;
		while (readMe.peek() != EOF)
		{
			getline(readMe, word); // get the whole line since there is only one word per line 
			insert(word);
		} 
		readMe.close();
	}
	return true; // file was successfully read
}

Trie::~Trie()
{

}
