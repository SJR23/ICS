#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <set>
#include <string>
#include <stack>
#include <algorithm>

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

bool is_adjacent(const string& word1, const string& word2) {
    int len1 = word1.length();
    int len2 = word2.length();
    int editDistance = abs(len1 - len2);

    if (editDistance > 1)
        return false;

    if (len1 == len2) {
        int diffCount = 0;
        for (int i = 0; i < len1; i++) {
            if (word1[i] != word2[i]) {
                diffCount++;
                if (diffCount > 1)
                    return false;
            }
        }
        return true;
    } else {
        int i = 0, j = 0;
        int diffCount = 0;
        while (i < len1 && j < len2) {
            if (word1[i] != word2[j]) {
                diffCount++;
                if (diffCount > 1)
                    return false;
                if (len1 < len2)
                    j++;
                else
                    i++;
            } else {
                i++;
                j++;
            }
        }
        return true;
    }
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
        return {};
    }
    
    if(word_list.find(end_word) == word_list.end()){
        return {};
    }
    
    if(word_list.find(begin_word) == word_list.end()){
        return {};
    }
    
    //vector<string> ladder;
    /*queue<stack<string>> ladder_queue;
    set<string> visited;
    
    stack<string> lad;
    lad.push(begin_word);
    ladder_queue.push(lad);
    //visited.insert(begin_word);
    
    while (!ladder_queue.empty()) {
        stack<string> current_ladder = ladder_queue.front();
        ladder_queue.pop();
        string current_word = current_ladder.top();
        
        if(current_word == end_word){
            vector<string> word_lad;
            while(!current_ladder.empty()){
                word_lad.push_back(current_ladder.top());
                current_ladder.pop();
            }
            reverse(word_lad.begin(), word_lad.end());
            return word_lad;
        }
        
        visited.insert(current_word);
        for (const string& word : word_list){
            if (is_adjacent(current_word, word) && !visited.count(word)){
                //visited.insert(word);
                stack<string> new_ladder = current_ladder;
                new_ladder.push(word);
                ladder_queue.push(new_ladder);
            }
        }
    }*/
    
    queue<vector<string>> ladder_queue;
    ladder_queue.push({begin_word});
    set<string> visited;
    visited.insert(begin_word);
    
    while(!ladder_queue.empty()){
        vector<string> ladder = ladder_queue.front();
        ladder_queue.pop();
        string last_word = ladder.back();
        
        for(const string& word : word_list){
            if(is_adjacent(last_word, word) && visited.find(word)==visited.end()){
                visited.insert(word);
                vector<string> new_ladder = ladder;
                new_ladder.push_back(word);
                if(word == end_word){
                    return new_ladder;}
                ladder_queue.push(new_ladder);
            }
        }
    }
    return vector<string>();
}
