#ifndef _RESERVATION_H
#define _RESERVATION_H

#include "Flight.h"

class Reservation {
public:
    Reservation(Flight f, int numPassengers, const int* seatRow, const char* seatCol);
    Reservation();
    ~Reservation();

    void setFlight(Flight);

    Flight getFlight();
    int* getSeatRow();
    char* getSeatCol();
    int getNumPass();
    int getResCode();
    void createAndSetResCode(int);
    
    Reservation& operator=( Reservation& );

private:
    Flight flight;
    const int* seatRow;
    const char* seatCol;
    int resCode;
    int numPassengers;
};

#endif // _RESERVATION_H

