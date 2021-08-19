#ifndef TUBE_H
#define TUBE_H

using namespace std;

struct tube_t{
    public:
        string getTopColor();
        bool   isTubeFull();
        bool   isTubeEmpty();
        bool   isTubeFinished();
        bool   oneParticalColor();
        int    numFreeSlots();
        int    amountTopColor();

        void setColor(int i, string s){colors[i] = s;}
        string getColor(int i){return colors[i];}
    private:
        string colors[4];
};


#endif