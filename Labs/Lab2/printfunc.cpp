// C++ for C Coders & Data Structures
#include "printfunc.h"
#include <iostream>
#include <vector>

using namespace std;

void printfunc(int n, char *names[]) {
	for (int i = 0; i < n; i++)      // do not change i = 0 to i = 1.
		cout << "Hello " << names[i] << "!" << endl;
}

void printfunc(std::vector<std::string>& names) {
    for (std::string& name : names) {
        std::cout << "Hello " << name << "!" << std::endl;
    }
}