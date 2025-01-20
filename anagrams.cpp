
#include <iostream>
#include <fstream>
#include <istream>
#include <string>
#include <cstring>

using namespace std;
const int MAXRESULTS = 20; // Max matches that can be found
const int MAXDICTWORDS = 10; // Max words that can be read in
// Reads words from the dictionary file into the 'dict' array
int readWords(istream& dictfile, string dict[], int index)
{

	if (index >= MAXDICTWORDS)
		return index;
	// Reads a word from the file into the 'dict' array at the current index
	// if we reach the end of the file/stream
	if ((dictfile >> dict[0]).eof())
	{

		return (++index);
	}
	return readWords(dictfile, dict + 1, ++index);
}
//puts each string in dictfile into the array dict
int vocabularyCreator(istream &dictfile, string dict[]) {
	int returnVal = 0;
	return readWords(dictfile, dict, returnVal);
}
//************************************************************
// Declarations:
// this will generate permutations of string and store valid results in 'results' array
void printPermutation(string pre, string remaining, const string dict[], int size, string results[], int& num_res);
// will check if a given word is a valid match and not already in 'results'. prevent repeat
bool checkdictfunc(std::string word, string results[], int& num_res, const string dict[], int size);

//recursive helper
void printPermutationLoop(string pre, string remaining, int remainingSize, const string dict[], int size, string results[], int& num_res, int tracker) {
	if (remainingSize == tracker) {
		return;
	}
	string npre = pre + remaining[tracker];
	string nremaining = remaining.substr(0, tracker) + remaining.substr(tracker + 1);
	printPermutation(npre, nremaining, dict, size, results, num_res);
	printPermutationLoop(pre, remaining, remaining.size(), dict, size, results, num_res, tracker + 1);
}
//implemtation of printPermutation
void printPermutation(string pre, string remaining, const string dict[], int size, string results[], int& num_res) {
	if (num_res >= MAXRESULTS) {
		num_res = MAXRESULTS;
		return;
	}
	if (remaining == "") {//base case: empty
		if (checkdictfunc(pre, results, num_res, dict, size)) {
			results[num_res] = pre;
			num_res++;// Tail recursion optimization
		}
		return; // Tail recursion optimization: no need to continue
	}
	int tracker = 0;
	printPermutationLoop(pre, remaining, remaining.size(), dict, size, results, num_res, tracker);
}
// searches if a given word is in the array of a size 
bool SearchInArray(std::string word, const string arr[], int size) {
	if (size == 0) {
		return false;

	}
	if (arr[size - 1] == word) {
		return true;
	}
	return SearchInArray(word, arr, size - 1);
}

//implementation of checkdictfun
bool checkdictfunc(std::string word, string results[], int& num_res, const string dict[], int size) {
	return (SearchInArray(word, dict, size) && !SearchInArray(word, results, num_res));
}
//puts all possibilities of words found in dict into results
int potentialSequences(string word, const string dict[], int
	size, string results[]) {
	int num_res = 0;
	printPermutation("", word, dict, size, results, num_res);
	if (num_res >= MAXRESULTS) {
		num_res = MAXRESULTS;
		return num_res;
	}
	return num_res;
}
//*******************************************************************
// Recursive helper function
void outcomeDisclosureHelper(const string results[], int& size, int index) {
	// Base case: if index goes beyond the array size, return
	if (index >= size) {
		return;
	}

	cout << results[index] << endl;

	outcomeDisclosureHelper(results, size, index + 1);
}
void outcomeDisclosure(const string results[], int size) {
	// Displays size number of strings from results. The results can be
	// printed in any order.

	outcomeDisclosureHelper(results, size, 0);
}

/*int main()
{
	string results[MAXRESULTS];
	string dict[MAXDICTWORDS];
	ifstream dictfile; // file containing the list of words
	int nwords; // number of words read from dictionary
	string word;
	dictfile.open("words.txt");
	if (!dictfile) {
		cout << "File not found!" << endl;
		return (1);
	}
	nwords = vocabularyCreator(dictfile, dict);
	cout << "Please enter a string for an anagram: ";
	cin >> word;
	int numMatches = potentialSequences(word, dict, nwords, results);
	if (!numMatches) {
		cout << "No matches found" << endl;
	}
	else {
		outcomeDisclosure(results, numMatches);
	}
	

	return 0;}*/void testone(int n)
	{
		string dictionary[MAXDICTWORDS];
		string results[MAXRESULTS];
		switch (n)
		{
		default: {
			cout << "Bad argument" << endl;
		} break; case 1: {
			istringstream iss("dog\ncat\nrat\neel\ntar\nart\nlee\nact\ngod");
			int numResults = vocabularyCreator(iss, dictionary);
			sort(dictionary, dictionary + numResults);
			assert(numResults == 9 && dictionary[0] == "act" && dictionary[1] ==
				"art");
		} break; case 2: {
			// File is empty, checks that file is empty and vocabularyCreator
			//returns 0.
				istringstream iss("");
			int numResults = vocabularyCreator(iss, dictionary);
			assert(numResults == 0 && dictionary[0] == "");
		} break; case 3: {
			// Dictionary has been read properly
			istringstream iss("dog\ncat\nrat\neel\ntar\nart\nlee\nact\ngod");
			int numResults = vocabularyCreator(iss, dictionary);
			sort(dictionary, dictionary + numResults);
			assert(numResults == 9 && dictionary[0] == "act" &&
				dictionary[numResults - 1] == "tar");
		} break; case 4: {
			// Input file is larger than the dictionary size
			istringstream iss("dog\ncat\nrat\neel\ntar\nart\nlee\nact\ngod\ntoo\
nmany\nwords");
			int numResults = vocabularyCreator(iss, dictionary);
			sort(dictionary, dictionary + numResults);
			assert(numResults == 10 && dictionary[MAXDICTWORDS - 1] == "too");
		} break; case 5: {
			// If a certain word with repeated letter is shown in results more than
			once - still accept.
				string dictionary[] = { "one", "oone", "ne", "e", "too" };
			int numResults = potentialSequences("oto", dictionary, 5, results);
			assert((numResults == 1 || numResults == 2) && results[0] == "too");
		} break; case 6: {
			// Doesn't check numResults nor duplicates.
			string dictionary[] = { "one", "oone", "ne", "e", "too" };
			potentialSequences("oto", dictionary, 5, results);
			assert(results[0] == "too");
		} break; case 7: {
			// If word wasn't found, numResults = 0 and results array is empty.
			string dictionary[] = { "one", "oone", "ne", "e" };
			int numResults = potentialSequences("look", dictionary, 4, results);
			assert(numResults == 0 && results[0] == "" && results[1] == "");
		} break; case 8: {
			// No fraction of a permutation is being searched in dictionary
			string dictionary[] = { "one", "oone", "non", "oon" };
			int numResults = potentialSequences("on", dictionary, 4, results);
			assert(numResults == 0 && results[0] == "" && results[1] == "");
		} break; case 9: {
			// No fraction of a permutation is being searched in dictionary
			string dictionary[] = { "one", "oone", "ne", "e", "neoo", "oneo" };
			int numResults = potentialSequences("neo", dictionary, 6, results);
			assert(numResults == 1 && results[0] == "one" && results[1] == "");
		} break; case 10: {
			// Checking that no error occurs if more than MAXRESULTS are found.
			string dictionary[] = { "true", "treu", "teru", "teur", "ture",
			"tuer", "rtue", "rteu", "retu","reut", "ruet", "rute", "utre",
			"uter", "uetr", "uert", "urte", "uret", "etru", "etur", "ertu",
			"erut", "eurt", "eutr" };
			// All 24 permutations
			int numResults = potentialSequences("true", dictionary, 24, results);
			assert(numResults == MAXRESULTS);
		} break; case 11: {
			// Checking one word was found, no duplicates.
			string dictionary[] = { "ppp" };
			int numResults = potentialSequences("ppp", dictionary, 1, results);
			assert(numResults == 1 && results[0] == "ppp" && results[1] == "");
		} break; case 12: {
			string dictionary[] = { "run", "dodge", "break", "urn", "defeat" };
			int numResults = potentialSequences("nru", dictionary, 5, results);
			sort(results, results + numResults);
			assert(numResults == 2 && results[0] == "run" && results[1] == "urn");
		} break; case 13: {
			streambuf* oldCoutStreamBuf = cout.rdbuf();
			ostringstream strCout;
			cout.rdbuf(strCout.rdbuf());
			string results[] = { "cat", "act" };
			outcomeDisclosure(results, 2);
			cout.rdbuf(oldCoutStreamBuf);
			string temp = strCout.str();
			bool match1 = temp.find("act") != string::npos;
			bool match2 = temp.find("cat") != string::npos;
			assert(match1 && match2);
		} break; case 14: {
			istringstream iss("tier\nrite\nbate\ntire\nttir");
			int numWords = vocabularyCreator(iss, dictionary);
			sort(dictionary, dictionary + numWords);
			assert(numWords == 5 && dictionary[0] == "bate");
			int numResults = potentialSequences("tier", dictionary, numWords,
				results);
			assert(numResults == 3 && (results[2] == "tire" || results[2] == "tier"
				|| results[2] == "rite"));
		} break; case 15: {
			string example[] = { "kool", "moe", "dee" };
			int numResults = potentialSequences("look", example, 3, results);
			assert(numResults == 1 && results[0] == "kool");
		} break;
		}
	}
	int main()
	{
		for (int n = 1; n <= 15; n++) {
			testone(n);
			cout << n << " passed" << endl;
		}
		return 0;
	}
