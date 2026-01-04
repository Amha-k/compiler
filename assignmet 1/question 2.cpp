/*Write a C++ function that evaluates a string containing a simple arithmetic expression with + only.*/


#include <iostream>
#include <string>
using namespace std;

int evaluateExpression(const string& expr) {
    int sum = 0;           
    int currentNumber = 0;   
    for (char ch : expr) {
        if (ch >= '0' && ch <= '9') {
            currentNumber = currentNumber * 10 + (ch - '0');
        } else if (ch == '+') {
           
            sum += currentNumber;
            currentNumber = 0; 
        }
       
    }
    
    sum += currentNumber;
    return sum;
}
int main() {
    string expr = "2+34+7";
    cout << "Result: " << evaluateExpression(expr) << endl;
    return 0;
}
