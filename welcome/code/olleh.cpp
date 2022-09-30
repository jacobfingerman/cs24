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
    int start = -1;

    char* flipped = nullptr;
    flipped = new char[sent.size()];

    for (int i = 0; i < sent.size(); i++) {
        if (ispunct(sent[i]) || isspace(sent[i])) {

            if (start >= 0) flipped[start] = sent[start];

            for (int j = i - 1; j > start; j--) {
                flipped[start + (i - j)] = sent[j];
            }

            start = i;

            if (i == sent.size() - 1) flipped[i] = sent[i];
        }
        else if (i == sent.size() - 1) {

            if (start >= 0) flipped[start] = sent[start];

            for (int j = i; j > start; j--) {
                flipped[start + 1 + (i - j)] = sent[j];
            }
        }
    }

    return flipped;

}