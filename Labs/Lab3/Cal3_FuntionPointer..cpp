#include<iostream>
#include<map>
#include<sstream>


using namespace std;

int add(int a, int b) {return a+b;}
int sub(int a, int b) {return a-b;}
int dvd(int a, int b) {if(b!=0) return a/b; else return 0;}
int mul(int a, int b) {return a*b;}

int get_int(){
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

char get_op ( map<char, int(*)(int,int)> fp_map ){
    string opstr;
    char op;
    for(auto x : fp_map) opstr += x.first;
    
    
    do{
        cout << "Enter an operator( " << opstr << " ): ";

        stringstream ss;
        string str;
        getline(cin, str);
        ss << str;
        ss >> op;
        if(fp_map.find(op) != fp_map.end()) break; // if not found. find() return fp_map.end()
    } while(true);                                       // if found, op is valid
    return op;
}

int main() {
    
    map<char, int(*)(int,int)> fp_map { make_pair('-',sub), make_pair('*',mul),
                                        make_pair('+',add), make_pair('/', dvd)};

    int a { get_int() };
    char op { get_op(fp_map) }; 
    int b { get_int() };
    
    cout<<a << " " << op << " " << b << " = " << fp_map[op](a,b) << endl;
}