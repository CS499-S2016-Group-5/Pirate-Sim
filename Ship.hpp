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
private:
    int x_pos;
    int y_pos;
    int d_x;                        // Change of the x-cord per time unit
    int d_y;                        // Change of the y-cord per time unit
    Ship_Type::Enum type;           // The ship type {Captured, Cargo, Escort, Pirate}
    int value;                      // Unique value (eg. nth cargoe ship created) used for Ships::Remove(value)
};




#endif /* ifndef SHIP_H */  
