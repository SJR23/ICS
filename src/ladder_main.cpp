#include <iostream>
#include <fstream>
#include "ladder.h"
#include <vector>
#include <set>
using namespace std;

int main(){
    set<string> word_list;
    string begin, end;
    cout << "Begin word: ";
    cin >> begin;
    cout << endl << "End word: ";
    cin >> end;
    cout <<endl;
    load_words(word_list, "small.txt");
    vector<string> ladder = generate_word_ladder(begin, end, word_list);
    print_word_ladder(ladder);
    return 0;
}

/*void verify_word_ladder() {
    set<string> word_list;

    load_words(word_list, "words.txt");
    my_assert(generate_word_ladder("cat", "dog", word_list).size() == 4);
    my_assert(generate_word_ladder("marty", "curls", word_list).size() == 6);
    my_assert(generate_word_ladder("code", "data", word_list).size() == 6);
    my_assert(generate_word_ladder("work", "play", word_list).size() == 6);
    my_assert(generate_word_ladder("sleep", "awake", word_list).size() == 8);
    my_assert(generate_word_ladder("car", "cheat", word_list).size() == 4);
}*/