// Bryan Kim
// CovidDB.cpp

#include "CovidDB.h"
#include <iostream>

//desc: default constructor
//pre : none
//post: none
CovidDB::CovidDB() {
    hashtable = vector<vector<DataEntry*>>(17);
}

//desc: destructor
//pre : none
//post: none
CovidDB::~CovidDB() {
    //delete the DataEntry s by iterating through them
    for (int i = 0; i < (int)hashtable.size(); i++) {
        for (int j = 0; j < (int)hashtable[i].size(); j++) {
            delete hashtable[i][j];
        }
    }
}

//desc: hash function
//pre : none
//post: hash will be returned to determine location in the table
int CovidDB::hash(string country) {
    int sum = 0;
    char letter = ' ';
    for (int i = 0; i < (int)country.length(); i++) {
        letter  = country[i];
        sum += ((i + 1) * letter);
    }
    sum %= 17;
    return sum;
}

//desc: helper function to find if one date is greater than another
//pre : -both strings must represent a date MM/DD/YYYY
//post: -returns true if current is larger than compared, false if vice versa
bool CovidDB::isDateGreater (string current, string compared) {
    //initialize day, month, and year for both dates
    int currentMonth;
    int currentDay;
    int currentYear;
    int comparedMonth;
    int comparedDay;
    int comparedYear;
    
    stringstream ssOld(compared);
    stringstream ssNew(current);
    string token;
    
    
    getline(ssOld, token, '/');
    comparedMonth = stoi(token);

    getline(ssOld,token, '/');
    comparedDay = stoi(token);

    getline(ssOld, token);
    comparedYear = stoi(token);

    getline(ssNew, token, '/');
    currentMonth = stoi(token);

    getline(ssNew, token, '/');
    currentDay = stoi(token);

    getline(ssNew, token);
    currentYear = stoi(token);


    //check year
    if (currentYear > comparedYear) {
        return true;
    }

    //if year is the same, check month
    if (currentYear == comparedYear) {
        if (currentMonth > comparedMonth) {
            return true;
        //if month is the same, check day
        } else if (currentMonth == comparedMonth) {
            if (currentDay > comparedDay) {
                return true;
            }
        } else {
            return false;
        }
    } else {
        return false;
    }
    return false;
}

//desc: adds or updates an entry in the hash table
//pre : -entry must have all members initialized
//post: returns true if add or update is successful, false if unsuccessful
bool CovidDB::add(DataEntry* entry) {
    //set current values (including the hash value)
    string currentCountry = entry->getCountry();
    string currentDate = entry->getDate();
    int currentCases = entry->getCases();
    int currentDeaths = entry->getDeaths();
    int currentHash = hash(currentCountry);

    //iterate through the seperate chain of the hashtable[currentHash]
    for (int i = 0; i < (int)hashtable[currentHash].size(); i++) {

        //if same country and greater date, update all members except for country
        //else, return false
        if (hashtable[currentHash][i]->getCountry() == currentCountry) {
            
            DataEntry *archived = hashtable[currentHash][i];
            string archivedDate = hashtable[currentHash][i]->getDate();
            bool compareDates = isDateGreater(currentDate, archivedDate);
            if (compareDates && hashtable[currentHash][i] != nullptr) {
                hashtable[currentHash][i]->setDate(currentDate);
                hashtable[currentHash][i]->setCases(currentCases + archived->getCases());
                hashtable[currentHash][i]->setDeaths(currentDeaths + archived->getDeaths());
                return true;
            } else {
                cout << "Entry's date is less than the previous date of this country.";
                return false;
            }
        }
    }

    //if country isnt found in the table, add the country as a new entry
    hashtable[currentHash].push_back(new DataEntry(currentDate, currentCountry, currentCases, currentDeaths));
    return true;
}

//desc: gets a DataEntry from the hashtable
//pre : none
//post: -returns the DataEntry if found
//      -returns nullptr if not found
DataEntry* CovidDB::get(string country) {
    //search for country
    int currentHash = hash(country);


    //traverse
    for (int i = 0; i < (int)hashtable[currentHash].size(); i++) {
        //if it exists, return it
        if (hashtable[currentHash][i]->getCountry() == country) {
            return hashtable[currentHash][i];
        }
    }
    //else return nullptr
    cout << "Country not found.";
    return nullptr;
}

//desc: removes a DataEntry from the hashtable
//pre : -key country must exist in the hashtable to function properly
//post: -removes the DataEntry containing key country
void CovidDB::remove(string country) {
    //find the country to remove
    int currentHash = hash(country);
    for (int i = 0; i < (int)hashtable[currentHash].size(); i++) {

        //if you find it delete it
        if (hashtable[currentHash][i]->getCountry() == country) {
            
            delete hashtable[currentHash][i];

            hashtable[currentHash].erase(hashtable[currentHash].begin() + i);
            cout << country << " is deleted.";

        }
    }
}

//desc: displays all elements in the hashtable
//pre : -at least one element must exist in the hashtable to function properly
//post: none
void CovidDB::display() {
    cout << endl <<"Each displayed as Date, Country, Cases, Deaths: " << endl << endl;
    for (int i = 0; i < (int)hashtable.size(); i++) {
        int currSize = (int)hashtable[i].size();
        cout << endl << "Index " << i << " in the hashtable" << endl << endl;
        for (int j = 0; j < currSize; j++) {
            string date = hashtable[i][j]->getDate();
            string country = hashtable[i][j]->getCountry();
            int cases = hashtable[i][j]->getCases();
            int deaths = hashtable[i][j]->getDeaths();
            cout << date << ", " << country << ", " << cases << ", "
                 << deaths << endl;
        }

    }
    cout << endl << endl;
}