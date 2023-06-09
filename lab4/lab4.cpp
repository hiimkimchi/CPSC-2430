// Bryan Kim
// lab4.cpp
// This code implements a min heap that represents a priority queue of Pet memebers

#include <vector>
#include <string>
#include <iostream>
#include <string>

using namespace std;

struct Pet {
    string name;
    int arrival;
    Pet(string name, int arrival) {
        this->name = name;
        this->arrival = arrival;
    }
};

class PetHeap {
    private:
        vector<Pet*> petHeap;
        void percolateUp(int index);
        void percolateDown(int index);
        void deleteMin();
        Pet* peekMin();
    public:
        PetHeap(){
            petHeap = vector<Pet*>();
        }
        ~PetHeap() {
            petHeap.clear();
        }
        void insert(Pet* pet);
        Pet* adoptOldestPet();
        int numPets();
        void displayPets();
};

//desc: sifts nodes up in a way they are sorted min->max
//pre : -index must be inbounds of the vector
//post: -restructures the heap so that it is sorted
void PetHeap::percolateUp(int index) {
    //find parent
    Pet* parent = petHeap[(index - 1)/2];
    //if index = 0, stop
    if (index == 0) {
        return;
    }
    //if current node > parent, stop
    if (petHeap[index]->arrival > parent->arrival) {
        return;
    //else swap parent and current and recursively call again
    } else {
        Pet* temp = parent;
        petHeap[(index - 1)/2] = petHeap[index];
        petHeap[index] = temp;
        percolateUp((index - 1)/2);
    }
}

//desc: sifts nodes down in a way they are sorted min->max
//pre : -index must be in bounds of the vector
//post: -restructures the heap so that it is sorted
void PetHeap::percolateDown(int index){
    //BASE CASES
    //no children
    if (petHeap[2 * index + 1] == nullptr && petHeap[2 * index + 2] == nullptr) {
        return;
    }
    //1 left child
    if (petHeap[2 * index + 1] != nullptr && petHeap[2 * index + 2] == nullptr) {
        if (petHeap[index]->arrival < petHeap[2 * index + 1]->arrival) {
            return;
        }
    }
    //1 right child
    if (petHeap[2 * index + 1] == nullptr && petHeap[2 * index + 2] != nullptr) {
        if (petHeap[index]->arrival < petHeap[2 * index + 2]->arrival) {
            return;
        }
    }
    //2 children
    if (petHeap[2 * index + 1] != nullptr && petHeap[2 * index + 2] != nullptr) {
        if (petHeap[index]->arrival < petHeap[2 * index + 1]->arrival 
            && petHeap[index]->arrival < petHeap[2 * index + 2]->arrival) {
            return;
        }
    }

    //RECURSIVE CASE
    if (petHeap[index]->arrival > petHeap[2 * index + 1]->arrival 
        || petHeap[index]->arrival > petHeap[2 * index + 2]->arrival) {
        //swap with the smaller of the two
        //call recursively with the index of the swapped child
        int childDecider = 0;
        if (petHeap[2 * index + 1]->arrival < petHeap[2 * index + 2]->arrival) {
            childDecider = 1;
        } else {
            childDecider = 2;
        }
        Pet* temp = petHeap[2 * index + childDecider];
        petHeap[2 * index + childDecider] = petHeap[index];
        petHeap[index] = temp;
        percolateUp(2 * index + childDecider);
    }
}

//desc: returns the oldest pet
//pre : -vector is at least size 1
//post: -returns Pet* in the first index
Pet* PetHeap::peekMin(){
    return petHeap[0];
}

//desc: deletes the root of the heap
//pre : -vector is at least size 1
//post: -heap is ordered correctly
void PetHeap::deleteMin(){
    // remove the oldest Pet (by arrival) from the heap
    // and reconstruct the heap after deletion
    if (petHeap.size() == 0) {
        return;
    }
    Pet* last = petHeap[petHeap.size() - 1];
    Pet* root = peekMin();
    Pet* temp = last;
    last = root;
    root = temp;
    petHeap.pop_back();
    percolateDown(0);
}

//desc: inserts a node into the heap
//pre : none
//post: -size += 1
//      -node is placed in the correct location
void PetHeap::insert(Pet* pet){
    //push back
    petHeap.push_back(pet);
    int maxIndex = petHeap.size() - 1;
    //percolate up
    percolateUp(maxIndex);
}

//desc: adopts the first pet in the heap
//pre : none
//post: -returns the oldest pet
Pet* PetHeap::adoptOldestPet(){
    if (petHeap.size() == 0) {
        cout << "No pets availible to adopt" << endl << endl;
        return nullptr;
    }
    //find oldest
    Pet* oldest = peekMin();
    //delete oldest
    deleteMin();
    return oldest;
}

//desc: returns the number of pets in the heap
//pre : none
//post: -return the size of the vector
int PetHeap::numPets(){
    return petHeap.size();
}

//desc: prints all of the pets in sequential order
//pre : none
//post: none
void PetHeap::displayPets() {
    cout << endl << endl;
    if (petHeap.size() > 0) {
        int maxIndex = petHeap.size() - 1;
        for (int i = 0; i <= maxIndex; i++) {
            cout << petHeap[i]->name << ", " << petHeap[i]->arrival << "  ";
        }
        cout << endl << endl;
    } else {
        cout << "No pets to display." << endl << endl;
    }
}

//desc: prints menu
//pre : none 
//post: none
void printMenu() {
    cout << endl << "Welcome to my lab4 implementation. Please select an option:" << endl
         << endl << "1. Insert Pet\n2. Adopt Pet\n3. Number of Pets\n4. Display Pets" << endl
         << "5. Run Tests\n6. Exit" << endl << endl; 
}

//desc: runs tests
//pre : none
//post: none
void runTests() {
    PetHeap testShelter; 

    //insert 10 pets
    testShelter.insert(new Pet("Jooj", 2));
    testShelter.insert(new Pet("Pickles", 7));
    testShelter.insert(new Pet("Emily", 1));
    testShelter.insert(new Pet("Daniel", 3));
    testShelter.insert(new Pet("Elliott", 4));
    testShelter.insert(new Pet("Sam", 11));
    testShelter.insert(new Pet("Kirby", 9));
    testShelter.insert(new Pet("Leel", 20));
    testShelter.insert(new Pet("Geeg", 11));
    testShelter.insert(new Pet("Foof", 10));

    //display the heap
    testShelter.displayPets();

    //adopt 3 pets
    testShelter.adoptOldestPet();
    testShelter.adoptOldestPet();
    testShelter.adoptOldestPet();

    //display the heap again
    testShelter.displayPets();

    //adopt the rest
    testShelter.adoptOldestPet();
    testShelter.adoptOldestPet();
    testShelter.adoptOldestPet();
    testShelter.adoptOldestPet();
    testShelter.adoptOldestPet();
    testShelter.adoptOldestPet();
    testShelter.adoptOldestPet();

    //attempt an extra adoption
    testShelter.adoptOldestPet();
}

int main() {
    PetHeap shelter;
    int option = 0, num = 0;
    string name;
    Pet* oldestPet = nullptr;
    while (option != 6) {
        printMenu();
        cin >> option;
        switch (option) {
            case 1:
                //insert pet
                int time;
                cout << "Please input a name: ";
                cin >> name;
                cout << endl << "Please input an arrival time: ";
                cin >> time;
                shelter.insert(new Pet(name, time));
                break;
            case 2:
                //adopt pet
                oldestPet = shelter.adoptOldestPet();
                cout << endl << "You have adopted " << oldestPet->name << ".";
                break;
            case 3:
                //num pets
                num = shelter.numPets();
                cout << "There are " << num << " pets in the shelter heap." << endl << endl;
                break;
            case 4:
                //display pets
                shelter.displayPets();
                break;
            case 5:
                //run tests
                runTests();
                break;
            case 6:
                cout << endl << "Thank you for accessing my lab4." << endl;
                return 0;
            default:
                cout << endl << "Command not found." << endl;
        }
    }
    return 0;
}