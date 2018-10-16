#include "stdafx.h"
#include <iostream>
#include "Trie.h"

using namespace std;

int main()
{
	Trie t1, dictionary;
	cout << "Loading..." << endl;
	if (dictionary.read("wordlist.txt"))
	{
		cout << "Dictionary was added successfully." << endl;
	}
	else
		cout << "Dictionary could not be added." << endl;
	// test insert
	//if (t1.insert("cat"))
	//	cout << "Word was successfully added." << endl;
	//else
	//	cout << "Word could not be added" << endl;

	//if (t1.insert("car"))
	//	cout << "Word was successfully added." << endl;
	//else
	//	cout << "Word could not be added" << endl;
	//t1.insert("cart");
	//cout << "\n";
	//// test getSize
	//cout << "Total amount of nodes in the Trie: " << t1.getSize() << endl;
	//// test count
	//cout << "Total of complete words: " << t1.count() << endl;
	//cout << "\n";
	// test find
	//if (t1.find("cat"))
	//{
	//	cout << " was found!" << endl;
	//}
	//else
	//	cout << " was not found!" << endl;

	//if (t1.find("car"))
	//{
	//	cout << " was found!" << endl;
	//}
	//else
	//	cout << " was not found!" << endl;

	//if (t1.find("cart"))
	//{
	//	cout << " was found!" << endl;
	//}
	//else
	//	cout << " was not found!" << endl;

	//cout << "\n";



	//cout << "Number of complete words starting with 'ca': " << t1.completeCount("ca") << endl; 
	//cout << "Number of complete words starting with 'addr': " << dictionary.completeCount("addr") << endl;

	//t1.complete("ca");
	//dictionary.complete("addr");
	
	cout << "Done. " << endl;
	while (1)
	{
		string input = "";
		cout << "Enter a word prefix, all lower case, no spaces (Or type 'STOP' to exit): ";
		getline(cin, input);
		if (input.compare("STOP") == 0)
		{
			cout << "Exiting..." << endl;
			exit(0);
		}
		else if (dictionary.completeCount(input) == 0)
		{
			cout << "There were no words that can be completed with that prefix." << endl;
		}
		else
		{
			cout << "There are " << dictionary.completeCount(input) << " words that can be completed, would you like to see them?" << endl;

			string yesNo = "";
			getline(cin, yesNo);
			if (yesNo.compare("yes") == 0)
			{
				cout << "Completions are as follows \n ==========" << endl;
				dictionary.complete(input);
			}
			else if (yesNo.compare("no") == 0)
			{
				cout << "Are you sure?" << endl;
				getline(cin, yesNo);
				if (yesNo.compare("yes") == 0)
				{
					cout << "Ok :(" << endl;
					exit(0);
				}
				else if (yesNo.compare("no") == 0)
				{
					cout << "Exiting anway sucka! " << endl;
					exit(0);
				}
				else
				{
					cout << "Oops! This program isn't smart enough to detect alpha characters, misspelled words, or spaces! Killing myself!" << endl;
					exit(0);
				}
			}
			else
			{
				cout << "Oops! This program isn't smart enough to detect alpha characters, misspelled words, or spaces! Please enter 'yes' or 'no' as displayed :)" << endl;
			}
		}
	}


	system("pause");
    return 0;
}

