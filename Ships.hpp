//=======================================================================
// File:  Ships class.  This is the container for all active ships.
//
// Date:    Feb. 21, 2016
//=======================================================================

#ifndef SHIPS_H
#define SHIPS_H 

#include"Ship_Type_Enum.hpp"
#include"Ship.hpp"
#include<forward_list>
#include"Counts.hpp"

class Ships
{
public:
    Ships(Counts* count, Ship_Type::Enum, int PIRATE_PROB, int CARGO_PROB, int ESCORT_PROB);
    Ships(Ship_Type::Enum ship_type, int PIRATE_PROB, int CARGO_PROB, int ESCORT_PROB);
    virtual ~Ships ();
    void Move();            // iterates through forward_list and calls Ship::Move() for each ship
    void Gen();               // Ship::Gen() methods handles random ship generation for each turn.  It will call Ships::Add*() after determining whether or not a Ship is generated and if so where it is generated. 
    void RemoveShip(int val); // removes ship.value == val from ship_list 
    // The following two methods will either be called by Simulation::Rescue(),
    // Simulation::Capture(), or Ships::Gen().
    void AddCargoShip(int x, int y, bool new_ship);        // adds cargo ship, bool is used to determine whether count needs to be inc
    void AddCapturedShip(int x, int y);     // adds captured ship
    void AddPirateShip(int x, int y);       // adds pirate ship
    void AddEscortShip(int x, int y);       // adds escort ship
    std::forward_list<Ship>::iterator Begin() ;      // return iterator
    std::forward_list<Ship>::iterator End() ;        // return last address
    void PrintList();                       // prints all elements to cout; [(x_pos, y_pos) value]
//    void SortList();                    // sort the list by Ship.x_pos
    void RemoveCaptured();  // removes all Ships with Ship.captured == true

private:
    Counts* count_ptr;
    Ship_Type::Enum type;           // holds the type of ship the forward_list contains
    int pirate_prob;
    int cargo_prob;
    int escort_prob;
    static const int num_x=35;
    static const int num_y=20;    // num of vertical cells
    static int num_cargos;      // num of cargos generated for unique ID (Ship::value)
    static int num_pirates;     // num of pirates generated for unique ID (Ship::value)
    static int num_escorts;     // num of escorts generated for unique ID
    static int num_captureds;    // num of captureds created for unique ID
    std::forward_list<Ship> ship_list;  // forward_list instead of vector for the constant time delete
   // the following four methods inc num_{cargos, pirates, escorts, captureds}
    bool IsOutOfBounds(Ship* ship_ptr); // return true if ship is out of the grid bounds
};






#endif /* ifndef SHIPS_H */
