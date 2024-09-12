#ifndef SHIP_H
#define SHIP_H 

#include <iostream>
#include <map>
#include <vector>
#include <string>
#include <random>
#include <functional>
#include <algorithm>

using std::vector;
using std::map;

class Ship{
    protected:
    int size = 0;
    int health = 0;
    int og_health = 0;
    

    public:
    vector<map<int, char>> placement;


    //constructor for giving ships their size which is also their health
    Ship(int given_numbers);
    Ship(){ size = 0; health = 0;};

    //Assigns the coordinates they recieve
    void AssignCoords(std::vector<std::vector<char>> &usable_coords, int seed);
    void TestAssign(std::vector<std::vector<char>> &usable_coords, int num, int num_letter, int direction);
    
    //What happens when they get hit
    int Hit();

};

class T_Ship : public Ship{

    public:
    T_Ship(int given_numbers);
    void AssignCoords(std::vector<std::vector<char>> &usable_coords, int seed);

};


#endif