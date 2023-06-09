// Bryan Kim
// assignment5.cpp
// This code is a revision of assignment4 for extra credit: it includes a rehash function

#include <iostream>
#include <fstream>
#include <sstream>
#include "CovidDB.h"

using namespace std;

//desc: displays menu
//pre : none
//post: none
void displayMenu();

//desc: reads in a file and creates a hashtable based on the data
//pre : -table is initialized in main
//post: -table is created according to the csv file
void createTable(CovidDB &table);

int main () {
    CovidDB table;
    int option = -1;
    string date;
    string country;
    int cases;
    int deaths;
    DataEntry* retreieved;
    cout << endl << endl << "Welcome to Covid Tracker";
    while (option != 0) {
        displayMenu();
        cin >> option;
        switch(option) {
            case 1:
                //create
                cout << "Please wait a moment as the file reads in..." << endl;
                createTable(table);
                break;
            case 2:
                //add new entry
                cout << endl << "Please enter the country of this entry: ";
                cin.ignore();
                getline(cin, country);
                cout << endl << "Please enter the date of this entry: ";
                cin >> date;
                cout << endl << "Please enter the number of new cases: ";
                cin >> cases;
                cout << endl << "Please enter the number of new deaths: ";
                cin >> deaths;
                table.add(new DataEntry(date, country, cases, deaths));
                break;
            case 3:
                //get entry
                cout << endl << "Please enter the country you want to retreive: ";
                cin.ignore();
                getline(cin, country);

                retreieved = table.get(country);
                if (retreieved != nullptr) {
                    cout << retreieved->getDate() << ", " << retreieved->getCountry() << ", " 
                         << retreieved->getCases() << ", " << retreieved->getDeaths() << endl;
                }
                break;
            case 4:
                //remove entry
                cout << endl << "Please enter the country you want to delete from the hashtable: ";
                cin.ignore();
                getline(cin, country);
                table.remove(country);
                break;
            case 5:
                //display
                table.display();
                break;
            case 6:
                //rehash
                table.rehash();
                createTable(table);
                cout << endl << "Table has been rehashed.";
                break;
            case 0:
                //exit
                cout << endl << "Thank you for accessing Covid Tracker." << endl << endl;
                return 0;
            default:
                cout << endl << "Command not recognized";
        }
    }
    return 0;
}

void displayMenu() {
    cout << endl << endl << "Please choose the operation you want to apply:"
         << endl << endl << "1. Create the initial hashtable"
         << endl << "2. Add a new data entry"
         << endl << "3. Get a data entry" 
         << endl << "4. Remove a data entry"
         << endl << "5. Display hashtable"
         << endl << "6. Rehash the table"
         << endl << "0. Exit system" << endl << endl;
}

void createTable(CovidDB &table) {
    //open the file
    ifstream inFile;
    inFile.open("WHO-COVID-data.csv");
    string line;
    getline(inFile, line);

    //read it in
    while (getline(inFile, line)) {
        stringstream ss(line);
        string token;
        DataEntry* currentEntry = new DataEntry();
        
        //use stringstream and a comma as a delimiter to read in all the entries from the file
        //convert the strings to ints using stoi
        getline(ss, token, ',');
        currentEntry->setDate(token);

        getline(ss, token, ',');
        currentEntry->setCountry(token);

        getline(ss, token, ',');
        currentEntry->setCases(stoi(token));
        
        getline(ss, token);
        currentEntry->setDeaths(stoi(token));

        //add the entry
        table.add(currentEntry);
    }
    inFile.close();
}