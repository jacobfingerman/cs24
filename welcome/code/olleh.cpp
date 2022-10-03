#include <iostream>
#include <cctype>

using namespace std;

char* flipSent(string sent);

int main()
{
    string sentence;

    getline(std::cin, sentence);
    cout << flipSent(sentence) << "\n";
    
    return 0;
}

char* flipSent(string sent) {
	int size = sent.size();
    int start = -1; // Marks punctuation

    char* flipped = nullptr;
    flipped = new char[size];

    for (int i = 0; i < size; i++) {
        // Punctuation test
        if (ispunct(sent[i]) || isspace(sent[i])) {

            // Adds punctuation at old start point
            if (start >= 0) flipped[start] = sent[start]; 

            // Loops backwards from current to last punctuation, flipping word
            for (int j = i - 1; j > start; j--) {
                flipped[start + (i - j)] = sent[j];
            }

            start = i; // Current punctuation becomes new start

            // Ending in punctuation case
            if (i == size - 1) flipped[i] = sent[i]; 
        }
        // Ending in word character case
        else if (i == size - 1) {
            
            // Adds last punctuation
            if (start >= 0) flipped[start] = sent[start]; 

            // Loops backwards to last punctuation, flipping word
            for (int j = i; j > start; j--) {
                flipped[start + 1 + (i - j)] = sent[j];
            }
        }
    }

    return flipped;

}