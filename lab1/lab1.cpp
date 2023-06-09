//Bryan Kim
//lab1.cpp
//This code finds the binomial coefficient of a location in pascal's triangle

#include <iostream>

using namespace std;

//desc: finds the coefficient from a desired location in a binomial
//pre : -gets parameters from user input
//post: -all dynamic memory is deallocated
//      -returns 1 if n is 0 and i is 0
//      -returns -1 if i > n
int bico (int n, int i);

//desc: prints the pascal's triangle
//pre : -gets parameters from an allocated 2D array
//post: none
void pascalPrint (int** triangle, int size);

int main() {
    int n, i, result;
    cout << "Please insert the degree of the binomial: ";
    cin >> n;
    cout << "Please insert the index of the coefficient: ";
    cin >> i;
    result = bico(n,i);
    if (result == -1) {
        cout << "Index out of bounds" << endl;
    } else {
        cout << "The result is " << result << endl;
    }
    return 0;
}

int bico (int n, int i) {
    //check if n is 0 or if the index exceeds the max
    if (n == 0 && i == 0) {
        return 1;
    } else if (i > n) {
        return -1;
    }

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
    for (int iter = 1; iter < n + 1; iter++) {
        for (int j = 0; j < iter + 1; j++) {
            if (j == 0) {
                pascal[iter][0] = 1;
            } else if (j == iter) {
                pascal[iter][iter] = 1;
            } else {
                pascal[iter][j] = pascal[iter - 1][j - 1] + pascal[iter - 1][j];
            }
        }
    }

    //save return value
    int coef = pascal[n][i];

    pascalPrint(pascal, n + 1);

    //deallocate
    for (int iter = 0; iter < n; iter++) {
        delete[] pascal[iter];
    }
    delete[] pascal;
    
    return coef;
}

void pascalPrint (int** triangle, int size) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j <= i; j++) {
            cout << triangle[i][j] << ' ';
        }
        cout << endl;
    }
}