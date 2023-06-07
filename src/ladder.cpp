#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <set>
#include <string>
using namespace std;

void error(string word1, string word2, string msg){
    cerr << "Error: " << msg << word1 << "->" << word2 << endl;
}

bool edit_distance_within(const std::string & str1, const std::string & str2, int d){
    int len1 = str1.length();
    int len2 = str2.length();
    vector<vector<int>> twoD(len1+1, vector<int>(len2+1,0));
    
    for(int i = 0; i<=len1; i++) twoD[i][0] = i;
    for(int i = 0; i<=len2; i++) twoD[0][i] = i;
    
    for(int i = 1; i<=len1; i++){
        for(int j = 1; j<=len2; j++){
            if(str1[i-1] == str2[j-1]){
                twoD[i][j] = twoD[i-1][j-1];
            }
            else{
                twoD[i][j] = min({twoD[i-1][j]+1, twoD[i][j-1]+1, twoD[i-1][j-1]+1});
            }
        }
    }
    return twoD[len1][len2] <= d;
}

bool is_adjacent(const string & word1, const string & word2){
    int len1 = word1.length();
    int len2 = word2.length();
    int c = 0;
    if(abs(len1-len2) > 1) return false;
    int small = 0;
    if(len2 > len1){
        small = len1;
    }
    else{
        small = len2;
    }
    for(int i = 0; i < small; i++){
        if(word1[i] != word2[i]){
            c++;
            //if(c>1)return false;
        }
    }
    if(len1!=len2) c=1;
    return c<=1;
}

void load_words(set<string> & word_list, const string & file_name){
    ifstream file(file_name);
    if(!file){
        error("-", "-", "File doesn't exist or is incorrect type: "); 
        return;
    }
    string w;
    while(file >> w)
        word_list.insert(w);
    file.close();
}

void print_word_ladder(const vector<string> & ladder){
    /*if(ladder.empty()){
        cout << "No word ladder found." << endl;
        return;
    }
    else{
        cout << "Word ladder found: ";
        for(const string& word : ladder){
            cout << word << " ";
        }
        cout << endl;
    }*/
    //cout << ladder;
    int c = 0;
    vector<string> store;
    for(const string & word : ladder){
        c++;
        store.push_back(word);
    }
    if(c==0){
        cout << "No word ladder found." << endl;
    }
    else{
        cout << "Word ladder found: ";
        for(const string & w: store){
            cout << w << " ";
        }
        cout << endl;
    }
    
}

vector<string> generate_word_ladder(const string& begin_word, const string& end_word, const set<string>& word_list) {
    if (begin_word == end_word) {
        return {begin_word};
    }
    vector<string> ladder;
    queue<vector<string>> ladder_queue;
    ladder_queue.push({begin_word});
    set<string> visited;
    visited.insert(begin_word);
    while (!ladder_queue.empty()) {
        vector<string> current_ladder = ladder_queue.front();
        ladder_queue.pop();
        string current_word = current_ladder.back();

        for (const string& word : word_list) {
            if (is_adjacent(current_word, word) && !visited.count(word)) {
                visited.insert(word);
                vector<string> new_ladder = current_ladder;
                new_ladder.push_back(word);
                if (word == end_word) {
                    return new_ladder;
                }
                ladder_queue.push(new_ladder);
            }
        }
    }

    return {};
}
