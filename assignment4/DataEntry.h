// Bryan Kim
// DataEntry.h

#include <string>

using namespace std;

class DataEntry {
    private:
        string date;
        string country;
        int c_cases;
        int c_deaths;
    public:
        DataEntry();
        DataEntry(string date, string country, int c_cases, int c_deaths);
        void setDate(string date);
        void setCountry(string country);
        void setCases(int cases);
        void setDeaths(int deaths);
        string getDate();
        string getCountry();
        int getCases();
        int getDeaths();
};