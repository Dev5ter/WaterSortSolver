#ifndef MOVE_H
#define MOVE_H

struct move_t{
    public:
       void setMove(int i, int x){source = i; dest = x;} 
       int  getS(){return source;}
       int  getD(){return dest;}
    private:
        int source;
        int dest;
};

#endif