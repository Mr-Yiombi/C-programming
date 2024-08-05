// postfix.cpp :
//
// The program evaluates a given postfix expression and produces a fully
// parenthesized infix expression. If the postfix expression may be 
// evaluated to a numeric value if it is expressed using numerically.
// For simplicity of coding, however, the postfix expression consists
// of single character operands and operators only and may have spaces.
//

//
#include <iostream>
#include <stack>
#include <cassert>
#include <string>
using namespace std;

// change the printStack to use template once you finish part 1 in step 1.
// prints the stack contents from the bottom. 
template <typename T>
void printStack(stack<T> orig) {
	stack<T> bot;
	while (!orig.empty()) {
        cout << orig.top() << endl;
        bot.push(orig.top());
        orig.pop();
    }
    while (!bot.empty()) {
        orig.push(bot.top());
        bot.pop();
    }

}


// returns a fully parenthesized infix expression in string after postfix evaluation.
string evaluate(string tokens) {
	stack<string> st;

    for (char token : tokens) {
        if (isspace(token)) continue;  // if token is whitespace, skip it.

        if (token == '+' || token == '-' || token == '*' || token == '/')  {
            if (st.size() < 2) {
                assert(st.size()< 2);
                cout << "Assertion failed: st.size()>=2\n";
                return "Error";
            }
            string op2 = st.top();
            st.pop();
            string op1 = st.top();
            st.pop();

            string result = "(" + op1 + " " + token + " " + op2 + ")";
            st.push(result);
        } else {  // push the operand
            // convert token (char type) to a string type and push it to the stack
            st.push(string(1, token));
        }
    }
	if (st.size() != 1) {
        assert(st.size()!=1);
        cout << "Assertion failed: st.size()==1\n";
        return "Error";
    }
    //cout << "prosfix expr: "+tokens << endl;
    //cout << "Infix: " << st.top() << endl;
    return st.top();
}

// returns true if the tokens consist of '+', '-', '*', '/', spaces, and 
// digits (0 ~ 9), false otherwise.
bool is_numeric(string tokens) {
	int op_count =0;
	int va_count =0;
	int al_count = 0;
	for(char token : tokens){
		if (token == '+' || token == '-' || token == '*' || token == '/'){
			op_count++;
		}
		if(token == '0' || token == '1' || token == '2' || token == '3' ||token == '4' || token == '5' || token == '6' || token == '7'|token == '8' || token == '9'){
			va_count++;
		}
		if(token >= 'a'&& token <='z')
			al_count++;
	}
	if(op_count>0 && va_count>1&&al_count==0)
		return true;
	return false;
}

// returns a numeric value after evaluating the postfix evaluation.
double evaluate_numeric(string tokens) {
	stack<double> st;
	double cal;

	for (char token : tokens) {
		if (isspace(token)) continue;  // if token is a whitespace, skip it.

		// if token is a operator, evaluate; if a digit(or operand), push it to st.
		if (token == '+' || token == '-' || token == '*' || token == '/') {
			// checking the stack top() for right operand 
			// checking the stack top() for left oprand 
			// compute the expression and push the result
            if (st.size() < 2) {
                assert(st.size()< 2);
                cout << "Assertion failed: st.size()>=2\n";
                return 0;
            }
			double op1 = st.top();
			st.pop(); 
			double op2 = st.top();
			st.pop();
			if(token == '+'){
				cal = op2 + op1;
			}
			else if(token == '-'){
				cal = op2 - op1;
			}
			else if(token == '*'){
				cal = op2 * op1;
			}
			else {
				if (op1 != 0)
                    cal = op2 / op1;
                else
                    return 0;
			}
			st.push(cal);
		}
		else{ // push the operand (digit) in a value to the stack
			   // convert token to a numeric data type and push it the stack
			int num = token - '0';
            st.push(num);
        }
	}
    
    
	//cout << "token exhausted: check the stack, its size() should be 1.\n";
	//printStack(st);
	double expr = st.top();
    //cout << "prosfix expr: "+tokens << endl;
    //cout << "  Infix expr: " << st.top() << endl;
	//cout << "    evaluate: " << expr << endl;
	return expr;
}