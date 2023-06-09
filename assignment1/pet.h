//Bryan Kim
//pet.h
//Pet class header

#include <string>

using namespace std;

class Pet {
    private:
        int type;
        string name;
    
    public:
        Pet(int type, string name);
        void setType(int type);
        void setName(string name);
        int getType();
        string getName();
};