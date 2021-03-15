#include "Reservation.h"
#include <iostream>
#include <string>
using namespace std;

Reservation::Reservation(Flight f, int numPass, const int* sRow, const char* sCol) {
    flight = f;
    numPassengers = numPass;
    seatRow = sRow;
    seatCol = sCol;
    resCode = 0;
}

Reservation::Reservation() {
    Flight f(0,0,0);
    flight = f;
    numPassengers = 0;
    seatRow = 0;
    seatCol = 0;
    resCode = 0;
}

Reservation::~Reservation() {

}

void Reservation::setFlight(Flight f) {
    flight = f;
}

Flight Reservation::getFlight() {
    return flight;
}

int Reservation::getNumPass() {
    return numPassengers;
}

int* Reservation::getSeatRow() {
    return const_cast<int*> (seatRow);
}

char* Reservation::getSeatCol() {
    return const_cast<char*> (seatCol);
}

// By combining the resAmount and flightNo, create a unique reservation code
void Reservation::createAndSetResCode(int resAmount) {
    string str1 = to_string(flight.getFlightNo());
    string str2 = to_string(resAmount);
    resCode = stoi(str1 + "00" + str2);
}

int Reservation::getResCode() {
    return resCode;
}

Reservation& Reservation::operator=(Reservation& right) {
    if (&right != this) {
        flight = right.flight;
        seatRow = right.getSeatRow();
        seatCol = right.getSeatCol();
        resCode = right.getResCode();
        numPassengers = right.getNumPass();
    }
    return *this;
}
