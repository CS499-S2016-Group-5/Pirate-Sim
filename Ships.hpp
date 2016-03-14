//=======================================================================
// File:  Ships class.  This is the container for all active ships.
//
// Date:    Feb. 21, 2016
//=======================================================================

#ifndef SHIPS_H
#define SHIPS_H 

#include"Ship_Type_Enum.hpp"
#include"Ship.hpp"

class Ships
{
public:
    Ships::Ships(double prob, Ship_Type::Enum type)
    virtual ~Ships ();
    void Move();            // iterates through forward_list and calls Ship::Move() for each ship
    void Gen();               // Ship::Gen() methods handles random ship generation for each turn.  It will call Ships::Add*() after determining whether or not a Ship is generated and if so where it is generated. 
    void RemoveShip(int val); // removes ship.value == val from ship_list 
    // The following two methods will either be called by Simulation::Rescue(),
    // Simulation::Capture(), or Ships::Gen().
    void AddCargoShip(Ship ship);        // adds cargo ship
    void AddCapturedShip(Ship ship);     // adds captured ship

private:
    Ship_Type::Enum type;           // holds the type of ship the forward_list contains
    forward_list<Ship> ship_list;  // forward_list instead of vector for the constant time delete
    double probability;       // 0 <= x < 1; value used in gen method
    // The following two methods will be called by Ships::Gen() in the event a
    // Ship is to be generated.
    void AddPirateShip(Ship ship);       // adds pirate ship
    void AddEscortShip(Ship ship);       // adds escort ship

};






#endif /* ifndef SHIPS_H */
