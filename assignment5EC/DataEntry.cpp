// Bryan Kim
// DataEntry.cpp

#include "DataEntry.h"

DataEntry::DataEntry() {
    date = "";
    country = "";
    c_cases = -1;
    c_deaths = -1;
}

DataEntry::DataEntry(string date, string country, int c_cases, int c_deaths) {
    this->date = date;
    this->country = country;
    this->c_cases = c_cases;
    this->c_deaths = c_deaths;
}

void DataEntry::setDate(string date) {
    this->date = date;
}

void DataEntry::setCountry(string country) {
    this->country = country;
}

void DataEntry::setCases(int cases) {
    this->c_cases = cases;
}

void DataEntry::setDeaths(int deaths) {
    this->c_deaths = deaths;
}

string DataEntry::getDate() {
    return date;
}

string DataEntry::getCountry() {
    return country;
}

int DataEntry::getCases() {
    return c_cases;
}

int DataEntry::getDeaths() {
    return c_deaths;
}