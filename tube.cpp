#include <iostream>

#include "tube.h"

string tube_t::getTopColor(){
    for(int i=0; i<4; i++){
        if(colors[i] != "Em") return colors[i];
    }
    return "NULL";
}

bool tube_t::isTubeFull(){
    for(int i=0; i<4; i++){
        if(colors[i] == "Em") return false;
    }
    return true;
}

bool tube_t::isTubeEmpty(){
    for(int i=0; i<4; i++){
        if(colors[i] != "Em") return false;
    }
    return true;
}

bool tube_t::isTubeFinished(){
    if(colors[3] == "Em") return false;
    if((colors[0] == colors[1]) &&
       (colors[1] == colors[2]) &&
       (colors[2] == colors[3])){
           return true;
       }else{
           return false;
       }
}

bool tube_t::oneParticalColor(){
    if(isTubeEmpty() || isTubeFull()) return false;
    for(int i=0; i<3-numFreeSlots(); i++){
        if(colors[3-i] != colors[2-i]) return false;
    }
    return true;
}

int tube_t::numFreeSlots(){
    int nfs = 0;
    for(int i=0; i<4; i++){
        if(colors[i] == "Em"){
            nfs++;
        }else{
            return nfs;
        }
    }
    return nfs;
}

int tube_t::amountTopColor(){
    if(numFreeSlots() == 4) return 0;
    int atc = 1;
    for(int i=numFreeSlots()+1; i<4; i++){
        if(colors[numFreeSlots()] == colors[i]){ 
            atc++;
        }else{
            return atc;
        }
    }
    return atc;
}