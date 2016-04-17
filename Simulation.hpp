//=======================================================================
// Simulation class.  This class is responsible for interacting with the controller.  It provides the interface
// for the Model.
//
// Date:    Jan. 21, 2016
//=======================================================================
#include"Ship_Type_Enum.hpp"
#include"Counts.hpp"
#include"Ship.hpp"
#include"Ships.hpp"

const int X = 35;
const int Y = 20;

class Simulation
{
  private:
    Ships captured_ships;
    Ships pirate_ships;
    Ships escort_ships;
    Ships cargo_ships;
    Counts counters;        // Struct that holds the 9 Counts
    int pirate_prob;
    int cargo_prob;
    int escort_prob;
//    enum Enum { Captured, Cargo, Escort, Pirate};
    int grid[X][Y][4];          // dynamically allocated 3-D array.  grid[1][1][1] represents the number of Cargo ships are at (1, 1). Captured==0, Cargo==1, Escort==2, Pirate==3
    // The following 5 methods execute 1 time unit of the simulation and should be called in order by
    // Simulation::Update();
    void Generate();        // Randomly generates ships for Cargos, Pirates, Escorts
    void BuildGrid();      
    int Cargos();           // Return the number of Cargos
    int Captureds();        // Return the number of Captureds
    int Escorts();          // Return the number of Escorts
    int Pirates();          // Return the number of Pirates
   
  public:
    typedef int (&gridXxYx4)[X][Y][4];
    Simulation(int PIRATE_PROB, int CARGO_PROB, int ESCORT_PROB);
    virtual ~Simulation();
    Counts* GetCounters();     // returns reference to the counters struct
    Simulation::gridXxYx4 Grid();     // return pointer to grid of Map (location of all the ships)
    void Update();          // Runs one time unit of Simulation
    void Reset();		// clears 2-D grid
    // the following four functions are added for testing purposes
    void AddCargoShip(int x, int y, bool new_ship);
    void AddEscortShip(int x, int y);
    void AddPirateShip(int x, int y);
    void AddCapturedShip(int x, int y);
    // the following should be private (moved to public for testing purposes)
    void Defeat();          // Determines if any Defeat actions occur
    void Capture();         // Determines if any Capture actions occur
    void Rescue();          // Determines if any Rescue actions occur
    void Move();            // Moves all active ships
};
