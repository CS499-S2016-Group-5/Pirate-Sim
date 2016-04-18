//=======================================================================
// File:  Ship class.  The Ship class is used for all four types of Ships.
//
// Date:    Feb. 21, 2016
//=======================================================================


#ifndef SHIP_H
#define SHIP_H 

#include"Ship_Type_Enum.hpp"


class Ship
{
public:
    Ship (int x, int y, int val, Ship_Type::Enum ship_type);    // Will need to set d_x, d_y based on Ship_Type::Enum ship_type.  Eg. (ship_type == Pirate) d_x = 0; d_y = -1;  Pirate ships move 1 grid North each time unit.
    virtual ~Ship ();
    void Move();                    // Changes the Ship location by the following: x_pos += d_x; y_pos += d_y;
    int Xpos() ;                    // Returns x_pos
    int Ypos() ;                    // Returns y_pos
    void SetType(Ship_Type::Enum ship_type);    // Changes Ship_Type::Enum type
    Ship_Type::Enum Type();         // returns the Ship.type
    int Value();                    // returns the Ship.value
    bool operator < (Ship& ship);
    bool IsAdjacent(int x, int y);  // returns bool: (this adjacent to (x, y))
    void SetCaptured(bool flag);    // sets the captured flag
    bool GetCaptured();             // returns Ship.captured
    void SetRemoveFlag();           // sets remove_flag to true
    bool RemoveFlag();              // return remove_flag
private:
    int x_pos;
    int y_pos;
    int d_x;                        // Change of the x-cord per time unit
    int d_y;                        // Change of the y-cord per time unit
    Ship_Type::Enum type;           // The ship type {Captured, Cargo, Escort, Pirate}
    int value;                      // Unique value (eg. nth cargoe ship created) used for Ships::Remove(value)
    bool captured;                  // boolean flag used to signify that a Ship_Type::Pirate ship has                                    // captured a cargo on this time step.
    bool remove_flag;               // flag that will be used to identify ships that need to be removed
};




#endif /* ifndef SHIP_H */  
