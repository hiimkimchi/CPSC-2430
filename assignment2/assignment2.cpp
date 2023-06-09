// Bryan Kim
// assignment2.cpp
// This code tests multiple recursive functions

#include <iostream>
#include <string>
#include <cmath>

using namespace std;

//desc: prints menu
//pre : none
//post: none
void printMenu();

//desc: recursively finds the value of mystery sequence for input value
//pre : -value is a nonnegative int
//post: -returns the value found at the end of the stack frame
int mysterySequence(int value);

//desc: recursively finds the number of tennis balls at input height
//pre : -value is a nonnegative int
//post: -returns the value found at the end of the stack frame
int tennisBalls(int height);

//desc: recursively converts a input decimal num into a binary number
//pre : -num is a nonnegative int
//post: -returns the value found at the end of the stack frame
string decToBase2(int num);

//desc: recursively checks if input num is divisible by 7
//pre : -num is a nonnegative int
//post: -returns the value found at the end of the stack frame
bool isDivisibleBy7(int num);

//desc: recursively finds the result of the ramanujan series at input depth maxDepth
//pre : -maxDepth is a nonnegative int
//      -depth always starts at 0 for correct implementation
//post: -returns the value found at the end of the stack frame
double ramanujan(int depth, int maxDepth);

//desc: changes results of isDivisibleBy7 to a readable result
//pre : none
//post: -if parameter is true, return "divisible"
//      -if false, return "not divisible"
string boolToString(bool isDivisible);

//desc: prints the test cases provided in assignment details
//pre : none
//post: none
void printTests();

int main() {
    int option = 0, n = 0, result = 0;
    string binaryConvert;
    bool isDivisible;
    double ramaResult = 0.0, infiniteRamaResult = 0.0;

    //menu
    while (option != 7) {
        printMenu();
        cin >> option;
        switch (option) {
            case 1:
                cout << endl << "Mystery Sequence. Please enter n to compute the nth number in the sequence: ";
                cin >> n;
                result = mysterySequence(n);
                cout << endl << "The " << n << "th number in Mystery Sequence is " << result << endl;
                break;
            case 2:
                cout << endl << "Tennis Balls. Please enter the height of the pyramid: ";
                cin >> n;
                result = tennisBalls(n);
                cout << endl << "A pyramid with a height of " << n << " has " << result << " tennis balls." << endl;
                break;
            case 3:
                cout << endl << "Decimal to Binary. Please enter a number in base 10: ";
                cin >> n;
                binaryConvert = decToBase2(n);
                cout << endl << n << " in binary is " << binaryConvert << "." << endl; 
                break;
            case 4:
                cout << endl << "Is Divisible by 7. Please enter a number: ";
                cin >> n;
                isDivisible = isDivisibleBy7(n);
                if (isDivisible) {
                    cout << endl << n << " is divisible by 7." << endl;
                } else {
                    cout << endl << n << " is not divisible by 7." << endl;
                }
                break;
            case 5:
                cout << endl << "Ramanujan. Please enter integer depth: " << endl;
                cin >> n;
                ramaResult = ramanujan(0, n);
                infiniteRamaResult = ramanujan (0, 100);
                cout << endl << "Result at depth " << n << " is " << ramaResult;
                cout << endl << "Result at infinite depth is " <<  infiniteRamaResult << endl;
                break;
            case 6:
                printTests();
                break;
            case 7:
                cout << "Thank you for accessing the recursion assignment." << endl;
                return 0;
            default:
                cout << "Invalid entry, please try again." << endl << endl; 
        }
    }
}

void printMenu() {
    cout << endl << "Welcome to the recursion assignment. What would you like to test?" << endl
         << "1. Mystery Sequence" << endl
         << "2. Tennis Balls" << endl
         << "3. Decimal to Binary" << endl
         << "4. Is Divisible by 7" << endl
         << "5. Ramanujan" << endl
         << "6. Run Tests" << endl
         << "7. Exit" << endl << endl;
}

int mysterySequence(int value) {
    if (value == 0 || value == 1) {
        return value + 2;
    } else {
        return (mysterySequence(value - 1) * mysterySequence(value - 2));
    }
}

int tennisBalls(int height) {
    if (height == 1 || height == 0) {
        return height;
    } else {
        return (height * height + tennisBalls(height - 1));
    }
}

string decToBase2(int num) {
    if (num == 0) {
        return "0";
    }
    if (num == 1) {
        return "1";
    }

    //add remainder of num / 2 to next recursion
    return decToBase2(num / 2) + to_string(num % 2);
}

bool isDivisibleBy7(int num) {
    //return true if the number is two digits and = 0 or 7
    if ((num == 0 || num % 7 == 0) && num < 100) {
        return true;
    }
    //return false if its two digits and not = 0 or 7
    if (num % 7 != 0 && num < 100) {
        return false;
    }

    //remove last digit and subtract double of the last digit
    int lastDigit = num % 10;
    int doubledLastDigit = lastDigit * 2;
    return isDivisibleBy7(num / 10 - doubledLastDigit);
}

double ramanujan(int depth, int maxDepth) {
    if (depth == maxDepth) {
        return (depth + 1) * sqrt(6 + depth);
    //increment (not decrement) the depth inside recursive statement
    } else {
        return (depth + 1) * sqrt((6 + depth) + ramanujan(depth + 1, maxDepth));
    }
}

string boolToString(bool isDivisible) {
    if (isDivisible) {
        return "divisible";
    } else {
        return "not divisible";
    }
} 

void printTests() {
    cout << endl << "Mystery Sequence with n = 0, 1, 4, 7:" << endl;
    cout << mysterySequence(0) << ", " << mysterySequence(1) << ", " << mysterySequence(4)
         << ", " << mysterySequence(7) << endl;

    cout << endl << "Tennis Balls with height = 0, 1, 3, 10:" << endl;
    cout << tennisBalls(0) << ", " << tennisBalls(1) << ", " << tennisBalls(3)
         << ", " <<tennisBalls(10) << endl;

    cout << endl << "Decimal to Binary with inputs = 0, 1, 13, 32, 321:" << endl;
    cout << decToBase2(0) << ", " << decToBase2(1) << ", " << decToBase2(13) << ", "
         << decToBase2(32) << ", " << decToBase2(321) << endl;
    
    cout << endl << "Is Divisible by 7 with inputs = 1, 7, 31, 1073, 1729:" << endl
         << boolToString(isDivisibleBy7(1)) << ", " << boolToString(isDivisibleBy7(7)) << ", " << boolToString(isDivisibleBy7(31))
         << ", " << boolToString(isDivisibleBy7(1073)) << ", " << boolToString(isDivisibleBy7(1729)) << endl;

    cout << endl << "Ramanujan with depths = 1, 3, 10:" << endl
         << ramanujan(0,1) << ", " << ramanujan(0,3) << ", " << ramanujan(0,10) << endl
         << "Ramanujan converges to " << ramanujan(0,100) << " at infinity" << endl;
}

