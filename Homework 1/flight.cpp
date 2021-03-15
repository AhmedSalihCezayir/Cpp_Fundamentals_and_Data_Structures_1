#include "Flight.h"
#include <iostream>
using namespace std;

Flight::Flight(int fNo, int rNo, int sNo) {
    setFlightNo(fNo);
    setRowNo(rNo);
    setSeatNo(sNo);
    setAvailable(rNo * sNo);

    // Create a 2d array for seat plan
    seatPlan = new string * [rNo + 1];
    for (int i = 0; i < rNo + 1; i++) {
        seatPlan[i] = new string[sNo + 1];
    }

    //Initialize the seat plan
    initializeSeatPlan(rNo, sNo);
}

Flight::Flight(const Flight& f) {
    setFlightNo(f.getFlightNo());
    setRowNo(f.getRowNo());
    setSeatNo(f.getSeatNo());
    setAvailable(f.getAvailable());
    
    // Create a 2d array for seat plan
    seatPlan = new string * [f.getRowNo() + 1];
    for (int i = 0; i < f.getRowNo() + 1; i++) {
        seatPlan[i] = new string[f.getSeatNo() + 1];
    }

    // Copy the seat plan
    for (int i = 0; i < getRowNo() + 1; i++) {
        for (int k = 0; k < getSeatNo() + 1; k++) {
            seatPlan[i][k] = f.seatPlan[i][k];
        }
    }
}

Flight::Flight() {
    setFlightNo(0);
    setRowNo(0);
    setSeatNo(0);
    setAvailable(0);

    // Create a 2d array for the seat plan
    seatPlan = new string * [getRowNo() + 1];
    for (int i = 0; i < getRowNo() + 1; i++) {
        seatPlan[i] = new string[getSeatNo() + 1];
    }

    // First element of the array must be ' ' so that it will look nice when printed
    seatPlan[0][0] = " ";
}

Flight::~Flight() {
    for (int k = 0; k < getRowNo() + 1; k++) {
        delete[] seatPlan[k];
    }
    delete[] seatPlan;
}

void Flight::setFlightNo(int fNo) {
    flightNo = fNo;
}

void Flight::setRowNo(int rNo) {
    rowNo = rNo;
}

void Flight::setSeatNo(int sNo) {
    seatNo = sNo;
}

void Flight::setAvailable(int av) {
    available = av;
}

int Flight::getRowNo() const {
    return rowNo;
}

int Flight::getFlightNo() const {
    return flightNo;
}

int Flight::getSeatNo() const {
    return seatNo;
}

int Flight::getNumPassengers() const {
    return rowNo * seatNo;
}

int Flight::getAvailable() const {
    return available;
}

string** Flight::getSeatPlan() const {
    return seatPlan;
}

// A method for initializing the seat plan for a flight. Rows are shown using numbers while collums are shown using letters.
// Available seats are represented using 'o'.
void Flight::initializeSeatPlan(int rNo, int sNo) {

    const string alphabet[26] = { "A","B","C","D","E","F","G","H","I","J",
                    "K","L","M","N","O","P","Q","R",
                    "S","T","U","V","W","X","Y","Z" };

    seatPlan[0][0] = " ";

    // Initialize the first row by using letters 
    for (int i = 1; i < sNo + 1; i++) {
        seatPlan[0][i] = alphabet[i - 1];
    }

    // Initialize the first collumn by using numbers
    for (int i = 1; i < rNo + 1; i++) {
        seatPlan[i][0] = i + '0';
    }

    // Initialize the rest with 'o'
    for (int i = 1; i < rNo + 1; i++) {
        for (int j = 1; j < sNo + 1; j++) {
            seatPlan[i][j] = "o";
        }
    }
}

Flight& Flight::operator=( Flight& right ) {
    if (&right != this) {
        // Delete the current seat plan
        for (int k = 0; k < rowNo + 1; k++) {
            delete[] seatPlan[k];
        }
        delete[] seatPlan;
        
        // Create a 2d array for seat plan
        seatPlan = new string*[right.getRowNo() + 1];
        for (int i = 0; i < right.getRowNo() + 1; i++) {
            seatPlan[i] = new string[right.getSeatNo() + 1];
        }

        // Copy the seat plan
        for (int i = 0; i < right.getRowNo() + 1; i++) {
            for (int k = 0; k < right.getSeatNo() + 1; k++) {
                seatPlan[i][k] = right.seatPlan[i][k];
            }
        }

        // Copy the rest of the data
        flightNo = right.getFlightNo();
        rowNo = right.getRowNo();
        seatNo = right.getSeatNo();
        available = right.getAvailable();
    }
    return* this;
}

