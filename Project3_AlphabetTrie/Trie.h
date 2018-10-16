#pragma once
#include <string>
#include <iostream>
#include <vector>

using namespace std;

class Trie
{
public:
	class TrieNode
	{
	public:
		string payload;
		vector<TrieNode*> children;
		bool isEndOfWord;

		/*Space Complexity: Each trieNode has a payload and a vector of variable size of pointer. 2pn - 2 being the vector and payload, p being the 
		number of bytes needed, and n being the number of pointers in the vector*/
		TrieNode(string newPayload) // Each node will hava a payload which represents the letter in the word and a vector holding pointers to the next node in the word
		{
			payload = newPayload;
			isEndOfWord = false;
		}
	private:
	};
	
	Trie();

	bool insert(string);
	bool insertHelper(TrieNode*, string);

	int count();
	int countHelper(TrieNode*);
	
	int getSize();
	
	bool find(string);
	bool findHelper(TrieNode*, string);

	TrieNode* findNode(TrieNode*,string);

	bool read(string);

	int completeCount(string);
	int completeCountHelper(TrieNode*);
	vector<string> complete(string);
	void autoComplete(TrieNode*, vector<string>*, string);

		void printNode(TrieNode*);
	void printVector(vector<string>*);

	~Trie();

private:
	TrieNode *root;
	int nodeCount;                       
};

