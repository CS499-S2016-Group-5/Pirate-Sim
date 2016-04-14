//=======================================================================
// File:  Ships class.  This is the container for all active ships.
//
// Date:    March 15, 2016
//=======================================================================

#include<forward_list>
#include"Ship_Type_Enum.hpp"
#include"Ships.hpp"
#include"Ship.hpp"
#include"RandomEvent.hpp"
#include<iostream>            
#include"Counts.hpp"

int Ships::num_cargos = 0;
int Ships::num_escorts=0;
int Ships::num_pirates=0;
int Ships::num_captureds=0;

Ships::Ships(Counts* count, Ship_Type::Enum ship_type, int PIRATE_PROB, int CARGO_PROB, int ESCORT_PROB) :    
        count_ptr(count),
        type(ship_type),
        pirate_prob(PIRATE_PROB),
        cargo_prob(CARGO_PROB),
        escort_prob(ESCORT_PROB){}

void Ships::Move() {
    Ship* ship_ptr;
    for (auto it = ship_list.begin(); it != ship_list.end(); it++)
    {
        it->Move();
        ship_ptr = &(*it);
        if (IsOutOfBounds(ship_ptr))
        {
            switch (type){
                case Ship_Type::Escort:
                    count_ptr->IncEscortsExited();
                    break;
                case Ship_Type::Pirate:
                    count_ptr->IncPiratesExited();
                    break;
                case Ship_Type::Cargo:
                    count_ptr->IncCargosExited();
                    break;
                case Ship_Type::Captured:
                    break;
            }
           RemoveShip(it->Value()); 
        }
    }
}

bool Ships::IsOutOfBounds(Ship* ship_ptr)
{
    switch (type) {
        case Ship_Type::Escort:
            if (ship_ptr->Xpos() < 0) return true;
            break;
        case Ship_Type::Pirate:
            if (ship_ptr->Ypos() < 0) return true;
            break;
        case Ship_Type::Cargo:
            if (ship_ptr->Xpos() > (num_x - 1)) return true;
            break;
        case Ship_Type::Captured:
            if (ship_ptr->Ypos() > (num_y - 1)) return true;
            break;
    }
    return false;
}

void Ships::Gen() {
//    std::cout<<"Ship_Type: " <<type<<std::endl;
    int x_grid;
    int y_grid;
    switch (type) {
        case Ship_Type::Captured:
            break;
        case Ship_Type::Cargo:
            if (IsShipSpawned(cargo_prob)) 
            {
                x_grid = 0;
                y_grid = GetNode(num_y);
                AddCargoShip(x_grid, y_grid, true);
            }
            break;
         case Ship_Type::Escort:
            if (IsShipSpawned(escort_prob)) 
            {
                x_grid = num_x - 1;
                y_grid = GetNode(num_y);
                AddEscortShip(x_grid, y_grid);                              
            }
            break;
         case Ship_Type::Pirate:
            if (IsShipSpawned(pirate_prob)) 
            {
                x_grid = GetNode(num_x);
                y_grid = num_y - 1;
                AddPirateShip(x_grid, y_grid);               
            }
            break;
    }
}

Ships::Ships(Ship_Type::Enum ship_type, int PIRATE_PROB, int CARGO_PROB, int ESCORT_PROB){
    type = ship_type;
    std::forward_list<Ship> ship_list;
    pirate_prob = PIRATE_PROB;
    cargo_prob = CARGO_PROB;
    escort_prob = ESCORT_PROB;
    count_ptr = NULL;
}

Ships::~Ships()
{
}

void Ships::AddCargoShip(int x, int y, bool new_ship) {
    Ship ship = Ship(x, y, num_cargos, Ship_Type::Cargo);
    ship_list.push_front (ship);
    num_cargos++;
    if (new_ship){
        count_ptr->IncCargosEntered();
    }
}
   
void Ships::AddPirateShip(int x, int y) {
    Ship ship = Ship(x, y, num_pirates, Ship_Type::Pirate);
    ship_list.push_front (ship);
    num_pirates++;
    count_ptr->IncPiratesEntered();
}

void Ships::AddEscortShip(int x, int y) {
    Ship ship = Ship(x, y, num_escorts, Ship_Type::Escort);
    ship_list.push_front (ship);
    num_escorts++;
    count_ptr->IncEscortsEntered();
}
 
void Ships::AddCapturedShip(int x, int y) {
    Ship ship = Ship(x, y, num_captureds, Ship_Type::Captured);
    ship_list.push_front (ship);
    num_captureds++;
    
}

bool remove_val(Ship& ship) {return (ship.Value() == 0);}

void Ships::RemoveShip(int val) {
    /*
    Ship* ship_ptr;
    auto prev_it = ship_list.before_begin();
    for (auto it = ship_list.begin(); it != ship_list.end(); it++) {
        if (it->Value() == val) {
            it = ship_list.erase_after(prev_it);
            break;
        }
        prev_it++;
    }
    */
    ship_list.remove_if(remove_val);
}

std::forward_list<Ship>::iterator Ships::Begin() 
{
    return ship_list.begin();
}

std::forward_list<Ship>::iterator Ships::End() 
{
    return ship_list.end();
}
/*
void Ships::SortList()
{
    ship_list.sort();
}
*/
void Ships::PrintList()
{
    for (auto it = ship_list.begin(); it != ship_list.end(); it++)
    {
        std::cout << "("<<it->Xpos()<<", "<<it->Ypos()<<")\t\t\tValue: "<< it->Value()<<std::endl;
    }
}

bool remove_captured(Ship& ship){ return (ship.GetCaptured());}

void Ships::RemoveCaptured() {
    ship_list.remove_if(remove_captured); 
} 
