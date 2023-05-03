#include <iostream>
#include <stack>
using namespace std;

void error(string msg, char c){
    cout << "ERROR: " << msg << " " << c << endl;
}
bool is_balanced(string s){
    stack<char> note;
    for(int i = 0; i < s.length(); i++){
        if(note.empty()){
            note.push(s[i]);
        }
        else if ((note.top() == '(' && s[i] == ')') || 
                (note.top() == '[' && s[i] == ']') || 
                (note.top() == '{' && s[i] == '}') || 
                (note.top() == '<' && s[i] == '>')){
            note.pop();
        }
        else{
            note.push(s[i]);
        }
        if(note.empty()){
            return false;
        }
        return true;
    }
}
    
void test_is_balanced(){
    string test_cases[] = [ "({(())})((([({})])))(((((<>([{()}])(<>))))))()",
                           "({(<>)})((([({})])))(((((()([{()}])(())))))", 
                           "({(<>)})((([({})])))((((([]([{<>}])(()))))))()])"];
    for(val = 0; test_cases.length(); val ++){
        bool check = is_balanced(test_cases[val];
        cout << check << endl;
    }
