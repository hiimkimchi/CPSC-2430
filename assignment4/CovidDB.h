// Bryan Kim
// CovidDB.h

#include <string>
#include <vector>
#include <sstream>
#include "DataEntry.h"

using namespace std;

class CovidDB {
    private:
        vector<vector<DataEntry*>> hashtable;
        int hash(string country);
        bool isDateGreater(string current, string compared);
    public:
        CovidDB();
        ~CovidDB();
        bool add(DataEntry* entry);
        DataEntry* get(string country);
        void remove(string country);
        void display();
};