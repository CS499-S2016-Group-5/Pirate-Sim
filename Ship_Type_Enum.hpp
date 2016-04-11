





#ifndef SHIP_TYPE
#define SHIP_TYPE 
namespace Ship_Type
{
    enum Enum { Captured, Cargo, Escort, Pirate};
} /* ship_type */ 

namespace State{
    enum Enum {SINGLE_STEP, RUNNING, STOP, CLOSE};
}
#endif /* ifndef SHIP_TYPE */
