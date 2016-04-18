//=======================================================================
// File:  Ship class.  The Ship class is used for all four types of Ships.
//
// Date:    Feb. 21, 2016
//=======================================================================

#include"Ship_Type_Enum.hpp"
#include"Ship.hpp"
#include<iostream>

void Ship::Move() {
    x_pos += d_x;
    y_pos += d_y;
}

Ship::Ship(int x, int y, int val, Ship_Type::Enum ship_type)
{
    x_pos = x;
    captured = false;
    y_pos = y;
    value = val;
    type = ship_type;
    d_x = 0;
    d_y = 0;
    remove_flag = false;

    if (type == Ship_Type::Pirate)  d_y = -1;
    else if ( type == Ship_Type::Cargo) d_x = 1;
    else if ( type == Ship_Type::Escort) d_x = -2;
    else
        d_y = 1;
       // std::cout << "Error!  Invalid Ship_type::Enum ship_type passed to Ship::Ship()" << std::endl;
}

int Ship::Xpos() {
    return x_pos;
}

int Ship::Ypos()
{
    return y_pos;
}

void Ship::SetType(Ship_Type::Enum ship_type) {
   type = ship_type;
   switch (type)
   {
       case Ship_Type::Pirate:{
                        d_x = 0;
                        d_y = -1;
                        break;
                   }
       case Ship_Type::Cargo:{    d_x = 1;
                        d_y = 0;
                        break;
                   }
       case Ship_Type::Captured:{   d_x = 0;
                          d_y = 1;
                          break;
                      }
       case Ship_Type::Escort:{   d_x = -2;
                        d_y = 0;
                        break;
                    }
        default: break;
   }
}

Ship_Type::Enum Ship::Type()
{
    return type;
}

Ship::~Ship()
{
}

int Ship::Value()
{
    return value;
}

bool Ship::operator < (Ship& ship)
{
    return (x_pos < ship.Xpos());
}

bool Ship::IsAdjacent(int x, int y)
{
    // check to see if (this.x_pos, this.y_pos) is adjacent to (x, y)
    // check x value first
    if (x_pos >= (x-1) && x_pos <= (x+1)) {
        // check y value
        if (y_pos >= (y-1) && y_pos <= (y+1)) {
            return true;
        }
    }
    return false;
}

void Ship::SetCaptured(bool flag)
{
    captured = flag;
}

bool Ship::GetCaptured()
{
    return captured;
}

void Ship::SetRemoveFlag()
{
    remove_flag = true;
}

bool Ship::RemoveFlag()
{
    return remove_flag;
}

