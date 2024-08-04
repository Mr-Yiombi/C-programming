#include<iostream>
#include<sstream>
#include<map>

using namespace std;

int add(int a, int b) {return a+b;}
int sub(int a, int b) {return a-b;}
int dvd(int a, int b) {if(b!=0) return a/b; else return 0;}
int mul(int a, int b) {return a*b;}

int get_int() {
    int x;
    string str;
    do{
        cout << "Enter an interger: ";
        getline(cin, str);
        try{
            x = stoi(str);
            break;
        }
        catch(invalid_argument& e){
            cerr << e.what() << "Retry" << endl;
        } 
    }while(true);
    return x;
    
}

pair <char, int> get_op(string opstr) {
    char op; 
    size_t x;
    do {
        stringstream ss;
        string str;
        cout << "Enter an operator( " << opstr << " ): ";
        getline(cin,str);
        ss << str;
        ss >> op;
        x = opstr.find(op);
    } while ( x == string::npos);
    return make_pair(op,x);
}

int main() {
    int (*fn[])(int, int) = {add, sub, mul,dvd};
    string opstr {"+-*/"};

    int a { get_int() };
    pair<char, int> op { get_op(opstr) };
    int b { get_int() };

   cout << a << " " << op.first << " " << b << " = " << fn[op.second](a,b) << endl;
    
    // g++ -std=c++11 Cal3.cpp -o Cal3


}