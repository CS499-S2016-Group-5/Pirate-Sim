//=======================================================================
// Simulation class.  This class is responsible for interacting with the controller.  It provides the interface for the Model.
//
// Date:    Jan. 21, 2016
//=======================================================================

#include"Simulation.hpp"
#include"Ship_Type_Enum.hpp"
#include"Counts.hpp"
#include"Ship.hpp"
#include"Ships.hpp"

const int num_x = 35;
const int num_y = 20;


Simulation::Simulation(int PIRATE_PROB, int CARGO_PROB, int ESCORT_PROB)
    :   pirate_ships{&counters, Ship_Type::Pirate, PIRATE_PROB, CARGO_PROB, ESCORT_PROB},
        cargo_ships{&counters, Ship_Type::Cargo, PIRATE_PROB, CARGO_PROB, ESCORT_PROB},
        captured_ships{&counters, Ship_Type::Captured,PIRATE_PROB, CARGO_PROB, ESCORT_PROB},
        escort_ships{&counters, Ship_Type::Escort, PIRATE_PROB, CARGO_PROB, ESCORT_PROB}, 
        pirate_prob(PIRATE_PROB),
        cargo_prob(CARGO_PROB),
        escort_prob(ESCORT_PROB) {}

Simulation::~Simulation()
{
}

void Simulation::Move()
{
    pirate_ships.Move();
    cargo_ships.Move();
    captured_ships.Move();
    escort_ships.Move();
}

void Simulation::Generate()
{
    cargo_ships.Gen();
    pirate_ships.Gen();
    escort_ships.Gen();
}

void Simulation::Defeat()
{
    std::forward_list<Ship>::iterator e_begin = escort_ships.Begin();
    std::forward_list<Ship>::iterator e_end = escort_ships.End();
    std::forward_list<Ship>::iterator p_begin;
    std::forward_list<Ship>::iterator p_end;

    // iterate through escort ships and for each iterate through pirate ships
    // looking for the first adjacent pirate ship to delete.
    for ( ; e_begin != e_end; e_begin++){
        p_begin = pirate_ships.Begin();
        p_end = pirate_ships.End();
        for ( ; p_begin != p_end; p_begin++){
            if (p_begin->IsAdjacent(e_begin->Xpos(), e_begin->Ypos())){
                counters.IncPiratesDefeated();
                pirate_ships.RemoveShip(p_begin->Value());
                break;
            }
        }
    }
}

void Simulation::Update()
{
    Move();
    Generate();
    Defeat();
    Capture();
    Rescue();
}
    

void Simulation::Reset()
{
    for (int i = 0; i < num_x; i++)
    {
        for (int y = 0; y < num_y; y++)
        {
            for (int k=0; k < 4; k++){
                grid[i][y][k]=0;
            }
        }
    }
}

Simulation::gridXxYx4 Simulation::Grid()
{
    Reset();
    BuildGrid();
    return grid;
}

void Simulation::BuildGrid()
{
    // get iterator for each of the 4 forward_list member objects
    std::forward_list<Ship>::iterator p_list_begin = pirate_ships.Begin();
    std::forward_list<Ship>::iterator p_list_end = pirate_ships.End();
    std::forward_list<Ship>::iterator car_list_begin = cargo_ships.Begin();
    std::forward_list<Ship>::iterator car_list_end = cargo_ships.End();
    std::forward_list<Ship>::iterator e_list_begin = escort_ships.Begin();
    std::forward_list<Ship>::iterator e_list_end = escort_ships.End();
    std::forward_list<Ship>::iterator cap_list_begin = captured_ships.Begin();
    std::forward_list<Ship>::iterator cap_list_end = captured_ships.End();

    // iterate through each forward_list and increment the count for each ship 
    for ( ; p_list_begin != p_list_end; p_list_begin++)
    {
        grid[p_list_begin->Xpos()][p_list_begin->Ypos()][Ship_Type::Pirate]++;
    }

    // iterate through each forward_list and increment the count for each ship 
    for ( ; car_list_begin != car_list_end; car_list_begin++)
    {
        grid[car_list_begin->Xpos()][car_list_begin->Ypos()][Ship_Type::Cargo]++;
    }
  
    // iterate through each forward_list and increment the count for each ship 
    for ( ; e_list_begin != e_list_end; e_list_begin++)
    {
        grid[e_list_begin->Xpos()][e_list_begin->Ypos()][Ship_Type::Escort]++;
    }
    
    // iterate through each forward_list and increment the count for each ship 
    for ( ; cap_list_begin != cap_list_end; cap_list_begin++)
    {
        grid[cap_list_begin->Xpos()][cap_list_begin->Ypos()][Ship_Type::Captured]++;
    }
}

void Simulation::Capture()
{
    std::forward_list<Ship>::iterator p_begin = pirate_ships.Begin();
    std::forward_list<Ship>::iterator p_end = pirate_ships.End();
    std::forward_list<Ship>::iterator car_begin; 
    std::forward_list<Ship>::iterator car_end;

    // iterate through pirate ships and for each, iterate through cargo ships
    // looking for the first adjacent cargo ship to capture. Captured cargo
    // ships will be removed and in its place a captured ship will be created.
    // The capturing pirate ship will have its Ship.captured flag set.  
    for ( ; p_begin != p_end; p_begin++){
       car_begin = cargo_ships.Begin();
       car_end = cargo_ships.End();
       for ( ; car_begin != car_end; car_begin++){
            if (car_begin->IsAdjacent(p_begin->Xpos(), p_begin->Ypos())){
                p_begin->SetCaptured(true);
                counters.IncCargosCaptured();
                // create new captured ship in the same position as the cargo
                // ship
                captured_ships.AddCapturedShip(car_begin->Xpos(), car_begin->Ypos());
                // delete the captured cargo ship
                cargo_ships.RemoveShip(car_begin->Value());
                break;
            }
        }
    }
    // delete all pirate ships that captured on this turn
    pirate_ships.RemoveCaptured();
}

void Simulation::Rescue()
{
    std::forward_list<Ship>::iterator e_begin = escort_ships.Begin();
    std::forward_list<Ship>::iterator e_end = escort_ships.End();
    std::forward_list<Ship>::iterator cap_begin;
    std::forward_list<Ship>::iterator cap_end;

    // iterate through escort ships and for each iterate through captured ships
    // looking for the first adjacent captured ship to delete.
    for ( ; e_begin != e_end; e_begin++){
        cap_begin = captured_ships.Begin();
        cap_end = captured_ships.End();
        for ( ; cap_begin != cap_end; cap_begin++){
            if (cap_begin->IsAdjacent(e_begin->Xpos(), e_begin->Ypos())){
                // cap_begin points to an adjacent captured.  create cargo in
                // its place.  then remove captured
                counters.IncCapturedsRescued();
                cargo_ships.AddCargoShip(cap_begin->Xpos(), cap_begin->Ypos(), false);
                captured_ships.RemoveShip(cap_begin->Value());
                break;
            }
        }
    }
}

Counts* Simulation::GetCounters() 
{
    return &counters;
}

void Simulation::AddCargoShip(int x, int y, bool new_ship)
{
    cargo_ships.AddCargoShip(x, y, new_ship);
}

void Simulation::AddEscortShip(int x, int y)
{
    escort_ships.AddEscortShip(x, y);
}

void Simulation::AddPirateShip(int x, int y)
{
    pirate_ships.AddPirateShip(x, y);
}

void Simulation::AddCapturedShip(int x, int y)
{
    captured_ships.AddCapturedShip(x, y);
}
