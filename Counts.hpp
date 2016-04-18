


#ifndef COUNTS_H
#define COUNTS_H 

class Counts {
        unsigned int cargos_exited;
        unsigned int cargos_entered;
        unsigned int escorts_exited;
        unsigned int escorts_entered;
        unsigned int pirates_exited;
        unsigned int pirates_entered;
        unsigned int pirates_defeated;
        unsigned int captureds_rescued;
        unsigned int cargos_captured; 
        unsigned int num_cargos;
        unsigned int num_captureds;
        unsigned int num_escorts;
        unsigned int num_pirates;

    public:
        Counts() : cargos_exited(0),
                    cargos_entered(0),
                    escorts_exited(0),
                    escorts_entered(0),
                    pirates_exited(0),
                    pirates_entered(0),
                    pirates_defeated(0),
                    captureds_rescued(0),
                    cargos_captured(0),
                    num_cargos(0),
                    num_captureds(0),
                    num_escorts(0),
                    num_pirates(0) {}
        void IncCargosCaptured() { cargos_captured++;}   // increment cargos_captured
        void IncPiratesDefeated() {pirates_defeated++;}  // increment pirates_defeated
        void IncEscortsExited() {escorts_exited++;}    // increment escorts_exited
        void IncCargosExited() {cargos_exited++;}     // increment cargos_exited
        void IncCargosEntered() {cargos_entered++;}     // increment cargos_entered
        void IncPiratesExited() {pirates_exited++;}    // increment pirates_exited
        void IncEscortsEntered() {escorts_entered++;}   // increment escorts_entered
        void IncPiratesEntered() {pirates_entered++;}   // increment pirates_entered   
        void IncCapturedsRescued() {captureds_rescued++;} // increment captureds_rescued
        unsigned int CargosExited() {return cargos_exited;}
        unsigned int CargosEntered() {return cargos_entered;}
        unsigned int EscortsExited() {return escorts_exited;}
        unsigned int EscortsEntered() {return escorts_entered;}
        unsigned int PiratesExited() {return pirates_exited;}
        unsigned int PiratesEntered() {return pirates_entered;}
        unsigned int PiratesDefeated() {return pirates_defeated;}
        unsigned int CapturedsRescued() {return captureds_rescued;}
        unsigned int CargosCaptured() {return cargos_captured;}
        void SetCargos(unsigned int n) { num_cargos = n;}
        unsigned int Cargos() {return num_cargos;}
        unsigned int Captureds() {return num_captureds;}
        unsigned int Pirates() {return num_pirates;}
        unsigned int Escorts() {return num_escorts;}
        void SetCaptureds(unsigned int n){ num_captureds = n;}
        void SetEscorts(unsigned int n) {num_escorts = n;}
        void SetPirates(unsigned int n) { num_pirates = n;}
        virtual ~Counts() {}
};



#endif /* ifndef COUNTS_H */ 
