//Bryan Kim
//assignment1.cpp
//This code simulates a pet adoption center using STL containers (queues)

#include <iostream>
#include <string>
#include <queue>
#include <list>
#include "pet.h"

using namespace std;

//desc: prints the menu to show options
//pre : none
//post: none
void printMenu();

//desc: enqueues a pet of desired type into the shelter queue
//pre : -function will only be accessed with the first two cases of the switch statement
//post: -one and only one pet will be enqueued into shelter
void enqueuePet(int option, queue<Pet*> &shelter, list<Pet*> &list);

//desc: dequeues the last pet
//pre : -function will be accessed only at the 5th switch statement
//post: -queue's size - 1
void adopt(queue<Pet*> &cats, queue<Pet*> &dogs, list<Pet*> &list);

//desc: dequeues the last of a certain type of pet
//pre : -function will be accessed only at the 3rd and 4th switch statement
//post: -queue's size - 1
void adopt(int type, queue<Pet*> &shelter, list<Pet*> &list);


int main() {
    int option = 0;
    string name = "";
    queue<Pet*> cats;
    queue<Pet*> dogs;
    list<Pet*> list;

    while (option != 6) {
        printMenu();
        cin >> option;
        switch (option) {
            case 1:
                enqueuePet(option, cats, list);
                break;
            case 2:
                enqueuePet(option, dogs, list);
                break;
            case 3:
                adopt(0, cats, list);
                break;
            case 4:
                adopt(1, dogs, list);
                break;
            case 5:
                adopt(cats, dogs, list);
                break;
            case 6:
                cout << "Thank you for coming to the animal shelter." << endl;
                return 0;
            default:
                cout << "Invalid entry, please try again." << endl << endl; 
        }
    }
    return 0;
}

void printMenu() {
    cout << "Welcome to the animal shelter. What would you like to do?" << endl
         << "1. Add a CAT to the shelter." << endl
         << "2. Add a DOG to the shelter." << endl
         << "3. Adopt a CAT from the shelter." << endl
         << "4. Adopt a DOG from the shelter." << endl
         << "5. Adopt any animal from the shelter." << endl
         << "6. Exit." << endl;
}

void enqueuePet(int option, queue<Pet*> &shelter, list<Pet*> &list) {
    string name, animal;
    int animalType;
    //differentiate if cat or dog
    if (option == 1) {
        animal = "CAT";
        animalType = 0;
    } else {
        animal = "DOG";
        animalType = 1;
    }
    //enqueue into queue and list using user input
    cout << "Please enter the " << animal << "\'s name: ";
    cin >> name;
    shelter.push(new Pet(animalType, name));
    list.push_back(new Pet(animalType, name));
    cout << endl;
}

void adopt(queue<Pet*> &cats, queue<Pet*> &dogs, list<Pet*> &list) {
    if (cats.empty() && dogs.empty()) {
        //error check
        cout << "Sorry, there are no pets left in the shelter." << endl << endl;
    } else {
        //deallocate memory representing adopted pet in the list
        Pet* adoptee = list.front();
        string name = adoptee->getName(), animal;
        int type = adoptee->getType();
        list.pop_front();

        //deallocate in the queue
        if (adoptee->getType() == 0) {
            Pet* removedPet = cats.front();
            cats.pop();
            delete removedPet;
        } else {
            Pet* removedPet = dogs.front();
            dogs.pop();
            delete removedPet;
        }
        delete adoptee;

        //print message to user
        if (type == 0) {
            animal = "CAT";
        } else {
            animal = "DOG";
        }
        cout << "Congrats on adopting a " << animal << ", their name is: " << name << endl << endl;
    }
}

void adopt(int type, queue<Pet*> &shelter, list<Pet*> &list) {
    string animal;
    if (type == 0) {
        animal = "CAT";
    } else {
        animal = "DOG";
    }

    if (shelter.empty()) {
        //error check
        cout << "Sorry, there are no " << animal << "s left in the shelter." << endl << endl;
    } else {
        //deallocate memory representing adopted pet in the queue
        Pet* adoptee = shelter.front();
        string name = adoptee->getName();
        shelter.pop();

        //deallocate in the list
        std::list<Pet*>::iterator iter = list.begin();
        while (iter != list.end() && name != (*iter)->getName() && type != (*iter)->getType()) {
            iter++;
        }
        list.erase(iter);

        cout << "Congrats on adopting a " << animal << ", their name is: " << name << endl << endl;

    }
    
}