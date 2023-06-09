//Bryan Kim
//lab2.cpp
//This code is similar to lab1, but there is a recursive implementation as well.
//Run time is measured and compared between the two implementations.

#include <iostream>
#include <chrono>

using namespace std;
using namespace std::chrono;

//desc: ITERATIVELY creates a pascal's triangle
//pre : -gets parameter from user input
//post: -all dynamic memory is deallocated
int** iterativePascal (int n);

//desc: RECURSIVELY creates a pascal's triangle
//pre : -gets parameters from user input
//post: -all dynamic memory is deallocated
int recursivePascal (int n, int i);

//desc: prints the pascal's triangle
//pre : -gets parameters from an allocated 2D array
//post: none
void pascalPrint (int** triangle, int size);

//desc: finds the binomial coefficient of a given triangle at [n][i]
//pre : -triangle must exist
//post: -returns its value if exists, -1 if it is out of bounds
int findValue (int** triangle, int n, int i);

//desc: deallocates the respective triangle
//pre : -triangle exists and n represents its size
//post: -no memory leaks exist
void deletePascal (int** triangle, int n);

int main() {
    int n, i, iResult, rResult;
    cout << "Please insert the degree of the binomial: ";
    cin >> n;
    cout << "Please insert the index of the coefficient: ";
    cin >> i;

    auto iterStart = high_resolution_clock::now();
    int** iterTriangle = iterativePascal(n);
    iResult = findValue(iterTriangle, n, i);
    auto iterStop = high_resolution_clock::now();
    
    auto recurStart = high_resolution_clock::now();
    //create recursive triangle
    int** recurTriangle = new int*[n + 1];
    for (int i = 0; i < n + 1; i++) {
        recurTriangle[i] = new int[i + 1];
    }

    //initialize each value using recursive function
    for (int i = 0; i < n + 1; i++) {
        for (int j = 0; j < i + 1; j++) {
            recurTriangle[i][j] = recursivePascal(i, j);
        }
    }
    rResult = findValue(recurTriangle, n, i);
    auto recurStop = high_resolution_clock::now();

    pascalPrint(iterTriangle, n + 1);
    if (iResult == -1) {
        cout << "Iterative index out of bounds" << endl;
    } else {
        cout << "Iterative result is " << iResult << endl;
    }

    pascalPrint(recurTriangle, n + 1);
    if (iResult == -1) {
        cout << "Recursive index out of bounds" << endl;
    } else {
        cout << "Recursive result is " << rResult << endl;
    }
    
    auto duration = iterStop - iterStart;
    auto iterDuration = duration_cast<nanoseconds>(duration);
    duration = recurStop - recurStart;
    auto recurDuration = duration_cast<nanoseconds>(duration);

    cout << "Iterative runtime (nanoseconds): " << iterDuration.count() << endl;
    cout << "Recursive runtime (nanoseconds): " << recurDuration.count() << endl;
    //deallocate
    deletePascal(iterTriangle, n);
    deletePascal(recurTriangle, n);
    return 0;
}

int** iterativePascal (int n) {
    //allocate array
    int** pascal = new int*[n + 1];
    for (int iter = 0; iter < n + 1; iter++) {
        pascal[iter] = new int[iter + 1];
    }
    
    //hardcoding the first two rows
    pascal[0][0] = 1;
    pascal[0][1] = 1;
    pascal[1][1] = 1;

    //use for loop to create the rest
    for (int i = 1; i < n + 1; i++) {
        for (int j = 0; j < i + 1; j++) {
            if (j == 0) {
                pascal[i][0] = 1;
            } else if (j == i) {
                pascal[i][i] = 1;
            } else {
                pascal[i][j] = pascal[i - 1][j - 1] + pascal[i - 1][j];
            }
        }
    }

    return pascal;
}

int recursivePascal(int n, int i) {
    //base case
    if (n == 0 || i == 0 || n == i) {
        return 1;
    //recursive case
    } else {
        return (recursivePascal(n - 1, i - 1) + recursivePascal(n - 1, i));
    }
}

void pascalPrint (int** triangle, int size) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j <= i; j++) {
            cout << triangle[i][j] << ' ';
        }
        cout << endl;
    }
}

int findValue (int** triangle, int n, int i) {
    if (i > n) {
        return -1;
    } else {
        return triangle[n][i];
    }
}

void deletePascal (int** triangle, int n) {
    for (int iter = 0; iter < n; iter++) {
        delete[] triangle[iter];
    }
    delete[] triangle;
}