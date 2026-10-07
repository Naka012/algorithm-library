// (⁠◕⁠ᴗ⁠◕⁠✿⁠)
//905d7a24f
#include <bits/stdc++.h>
#define rep(i, n) for (ll i = 0; i < (n); i++)
using namespace std;
using ll = long long;

typedef string :: const_iterator State;
int expression(State &begin);
int term(State &begin);
int factor(State &begin);
int number(State &begin);
void consume(State &begin, set<char> expected);
class ParseError {};

int number(State &begin){
}

int term(State &begin){
}

int factor(State &begin){
}

int expression(State &begin){
}

void consume(State &begin, set<char> expected){
    if (expected.count(*begin)){
        begin++;
    }else{
        cout << "Expected ";
        for (auto it = expected.begin(); it != expected.end(); it++){
            if (it != expected.begin()) cout << " or ";
            cout << *it;
        }
        cout << " but got " << *begin << endl;
        cout << "rest : ";
        while (*begin){
            cout << *begin++;
        }
        cout << endl;
        throw ParseError();
    }
}

int main(){
    string S; cin >> S;
    State begin = S.begin();
    cout << expression(begin) << endl;
}
