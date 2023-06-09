// Bryan Kim
// lab5.cpp
// This code tests the run time of heap sort, merge sort, and quick sort

#include <iostream>
#include <chrono>

using namespace std;
using namespace std::chrono;

//desc: sorts an array using the heap sort method (max heap, push back)
//pre : -A = array, n = size
//post: -A of size n has sorted values
void heapSort (int* A, int n);

//desc: sifts the key value down until it is in the correct location
//pre : -A = array, index = index, n = size
//post: -element at index is in the correct location in the heap
void percolateDown(int* A, int index, int n);

//desc: sorts an array using the merge sort method (divide all, merge group by group)
//pre : -A = array, n = size
//post: -A of size n has sorted values
void mergeSort (int* A, int n);

//desc: overloaded function used to recursively split the array
//pre : -A = array, i = start, j = end
//post: -A of size n has sorted values
void mergeSort (int* A, int i, int j);

//desc: helper function for mergeSort; take two sorted subarrays and merge them
//pre : -p = beginning index, q = middle index, r = end index
//post: -A has sorted values in p through r
void merge(int* A, int p, int q, int r);

//desc: sorts an array using the quick sort method (pivot, partition)
//pre : -A = array, n = size
//post: -A of size n has sorted values
void quickSort (int* A, int n);

//desc: overloaded function for quickSort; take 
//pre : -A = array, i = pivot, j = end
//post: -A has sorted values between i and j
void quickSort (int* A, int i, int j);

//desc: helper function for quickSort; process unknown from the pivot, update pivot
//pre : -A = array, i = pivot, j = end
//post: -A has sorted values between i and j
int partition (int* A, int i, int j);

//desc: helper function for quickSort; pick random from unknown and swap with j
//pre : -A = array, i = pivot, j = end
//post: none
int randPartition (int* A, int i , int j);

//desc: prints an array of SIZE 10 ONLY
//pre : -to be called before and after a sort 
//post: none
void print (int* A, int n);

//desc: covers the runtime for a sorting algo and displays a random array of size 10
//pre : -parameter is a function* that passes paramaters of (int*, int)
//post: none
void measureSorts (void (*sortingFunction)(int*, int));

int main () {
    //function pointer to be changed per iteration
    void (*sortingFunction)(int*, int);

    //seeds randomizer
    srand(time(0));

    sortingFunction = &heapSort;
    cout << endl << "HEAP SORT TEST" << endl;
    measureSorts(sortingFunction);

    sortingFunction = &mergeSort;
    cout << endl << "MERGE SORT TEST" << endl;
    measureSorts(sortingFunction);

    sortingFunction = &quickSort;
    cout << endl << "QUICK SORT TEST" << endl;
    measureSorts(sortingFunction);

    return 0;
}

void heapSort (int* A, int n) {
    //create the initial heap using the percolateDown
    for (int i = n / 2 - 1; i >= 0; i--) {
        percolateDown(A, i, n);
    }
    
    //swap the max and the last element in the current heap
    for (int i = n - 1; i >= 0; i--) {
        swap(A[0],A[i]);
        percolateDown(A, 0, i);
    }
}

void percolateDown(int* A, int index, int n) {
    int leftChildIndex = 2 * index + 1;
    int rightChildIndex = 2 * index + 2;

    int largest = index;

    if (leftChildIndex < n && A[leftChildIndex] > A[largest]) {
        largest = leftChildIndex;
    }

    if (rightChildIndex < n && A[rightChildIndex] > A[largest]) {
        largest = rightChildIndex;
    }

    if (largest != index) {
        swap(A[index], A[largest]);
        percolateDown(A, largest, n);
    }

}

void mergeSort(int* A, int n) {
    mergeSort(A, 0, n - 1);
}

void mergeSort(int* A, int i, int j) {
    if (i < j) {
        int mid = (i + j) / 2;
        mergeSort(A, i, mid);
        mergeSort(A, mid + 1, j);
        merge(A, i, mid, j);
    }
}

void merge(int* A, int p, int q, int r) {
    //initialize
    int size = r - p + 1;
    int* temp = new int[size];
    int i = 0;
    int j = p;
    int k = q + 1;

    //until all elements have been traversed in BOTH subarrays
    while (j <= q && k <= r && i < size) {
        //if value in first subarray is less than or equal to, put in temp
        if (A[j] <= A[k]) {
            temp[i] = A[j];
            i++;
            j++;

        //if value in second subarray is less than, put in temp
        } else {
            temp[i] = A[k];
            i++;
            k++;
        }
    }
    
    //check if there are leftover values, and add them to the temp array afterwards
    while (j <= q) {
        temp[i] = A[j];
        i++;
        j++;
    }
    while (k <= r) {
        temp[i] = A[k];
        i++;
        k++;
    }

    //set all the values we changed into A and delete
    for (int i = 0; i < size; i++) {
        A[i + p] = temp[i];
    }

    delete[] temp;
}

void quickSort(int* A, int n) {
    quickSort(A, 0, n - 1);
}

void quickSort(int* A, int i, int j) {
    if (i < j) {
        int pivotIndex = randPartition(A, i ,j);
        quickSort(A, i, pivotIndex - 1);
        quickSort(A, pivotIndex + 1, j);
    }
}

int partition (int* A, int i, int j) {
	int p = A[i];
	int m = i;
    int k;
	for(k = i + 1; k <= j; k++) {
		if(A[k] <= p) {
			m++;
			swap(A[m],A[k]);
		}
	}
	swap(A[m], A[i]);
	return m;
}

int randPartition (int* A, int i , int j){
    int pos = i + rand() % (j - i + 1);
    swap(A[j], A[pos]);
    return partition(A, i, j);
}

void print(int* A, int n) {
    for (int i = 0; i < n; i++) {
        cout << A[i] << ' ';
    }
    cout << endl;
}

void measureSorts (void (*sortingFunction)(int*, int)) {
    int size[] = {10,100,1000,10000,100000};
    

    for(int i = 0; i < 5; i ++){

        //allocate memory for the array
        int* array = new int[size[i]];

        //fill in array with random numbers
        for(int j=0; j<size[i]; j++){
            array[j] = rand() % 100000;
        }

        //display
        if (size[i] == 10){
            cout << "Random array: " << endl;
            print(array, size[i]);
        }

        //measure the execution time here
        auto start = high_resolution_clock::now();
        sortingFunction(array, size[i]);
        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<nanoseconds>(stop - start);

        //display size 10 sorted array
        if (size[i] == 10){
            cout << "Sorted array: " << endl;
            print (array, size[i]);
        }
        //display the time measurement with units
        cout << "Array size " << size[i] << " duration: ";
        cout << duration.count() << " ns." << endl;
    }
}
