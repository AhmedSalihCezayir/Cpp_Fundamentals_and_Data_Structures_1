#include "ReservationSystem.h"
#include <iostream>
using namespace std;

ReservationSystem::ReservationSystem() {
    resAmount = 0;
    totalResAmount = 0;
    flightAmount = 0;
    reservations = new Reservation[resAmount];
    flights = new Flight[flightAmount];
}

ReservationSystem::~ReservationSystem() {
    delete[] reservations;
    delete[] flights;
}

// Add a flight with the given flight properties to the flights array
void ReservationSystem::addFlight(const int flightNo, const int rowNo, const int seatNo) {
    // Check whether this flight exists or not
    if (flightNoExist(flightNo) != -1) {
        cout << "Flight " << flightNo << " already exists" << endl;
    }
    else if (rowNo <= 0) {
        cout << "Invalid Row Number " << rowNo << "!" << endl;
    }
    else if (seatNo <= 0) {
        cout << "Invalid Seat Number!" << seatNo << "!" << endl;
    }
    else {
        // Everything is ok. Create a flight with the given properties
        // Also create an array with flightAmount+1 size. This array will be the new flights array
        Flight f(flightNo, rowNo, seatNo);
        Flight* tmp = new Flight[flightAmount + 1];
        
        //Copy the data
        for (int i = 0; i < flightAmount; i++) {
            tmp[i] = flights[i];
        }
        
        // Add the new flight
        tmp[flightAmount] = f;

        flights = NULL;
        delete[] flights;

        flights = tmp;
        flightAmount++;

        tmp = NULL;
        delete[] tmp;

        cout << "Flight " << flightNo << " has been added" << endl;
    }
}

// Delete the element with the given flightNo from the flights array
void ReservationSystem::cancelFlight(const int flightNo) {
    int k = flightNoExist(flightNo);

    // Check the existence of the flight
    if (k == -1) {
        cout << "Flight " << flightNo << " does not exist!" << endl;
    }
    else {
        // First cancel all the reservations of this flight
        cancelReservationsOfFlight( flightNo );

        // Create an array with flightAmount-1 size. This array will be the new flights array
        Flight* tmp = new Flight[flightAmount - 1];

        // Copy the data until the element we want to delete
        for (int i = 0; i < k; i++) {
            tmp[i] = flights[i];
        }

        // Copy the data after the element we want to delete
        for (int i = k; i < flightAmount - 1; i++) {
            tmp[i] = flights[i + 1];
        }

        flights = NULL;
        delete[] flights;

        flights = tmp;
        flightAmount = flightAmount - 1;

        tmp = NULL;
        delete[] tmp;

        cout << "Flight " << flightNo << " and all of its reservations are cancelled" << endl;
    }
}

// Print the elements of the flights array
void ReservationSystem::showAllFlights() {
    if (flightAmount == 0) {
        cout << "No flights exist" << endl;
    }
    else {
        cout << "Flights currently operated: " << endl;
        for (int i = 0; i < flightAmount; i++) {
            cout << "Flight " << flights[i].getFlightNo() << " (" << flights[i].getAvailable() << " available seats)" << endl;
        }
    }
}

// Show spesific data about a flight including its seating plan
void ReservationSystem::showFlight(const int flightNo) {
    if (flightNoExist(flightNo) == -1) {
        cout << "Flight " << flightNo << " does not exist" << endl;
    }
    else {
        int index = flightNoExist(flightNo);
        cout << "Flight " << flightNo << " has " << flights[index].getAvailable() << " available seats" << endl;
        printSeatPlan(index);
    }
}

int ReservationSystem::makeReservation(const int flightNo, const int numPassengers, const int* seatRow, const char* seatCol) {
    int notAvailable[100];
    int nSize = 0;
    int resCode = -1;
    int index = flightNoExist(flightNo);

    // Check the existence of this flight
    if (index == -1) {
        cout << "Flight " << flightNo << " does not exist" << endl;
        return -1;
    }
    else {
        // Get the seat plan of the wanted flight
        string** seatPlan = flights[index].getSeatPlan();

        // Check if the wanted seats have already occupied or not. If occupied add their index to the notAvailable array
        // Also increase the nSize variable for each wanted seat that is occupied. This shows the size of notAvailable array
        for (int i = 0; i < numPassengers; i++) {
            if (seatPlan[seatRow[i]][(int)(seatCol[i]) - 64] == "x") {
                notAvailable[nSize] = i;
                nSize++;
            }
        }

        // If notAvailable array is not empty, print the seats that are not available
        if (nSize != 0) {
            for (int i = 0; i < nSize; i++) {
                cout << seatRow[notAvailable[i]] << seatCol[notAvailable[i]] << " ";
            }
            cout << "is not available" << endl;
            return -1;
        }
        else {
            // If all the seats wanted are available change the available seats variable
            flights[index].setAvailable(flights[index].getAvailable() - numPassengers);

            // Change the seat plan so that the newly taken seats are now shown by 'x'.
            for (int i = 0; i < numPassengers; i++) {
                seatPlan[seatRow[i]][(int)(seatCol[i]) - 64] = "x";
            }

            // Create a reservation object and create a reservation code for this reservation
            Flight f(flightNo, 0, 0);
            Reservation r(f, numPassengers, seatRow, seatCol);
            r.createAndSetResCode(totalResAmount);

            // Update the reservations array
            Reservation* tmp = new Reservation[resAmount + 1];
            for (int i = 0; i < resAmount; i++) {
                tmp[i] = reservations[i];
            }
            // Add the new reservation
            tmp[resAmount] = r;

            reservations = NULL;
            delete[] reservations;

            reservations = tmp;
            resAmount++;
            totalResAmount++;

            tmp = NULL;
            delete[] tmp;

            return reservations[resAmount - 1].getResCode();
        }
    }
}

void ReservationSystem::cancelReservation(const int resCode) {
    bool exist = false;
    int index;

    // Check whether the reservation with the given resCode exists
    // Index variable will holds the index of it in the reservations array
    for (int i = 0; i < resAmount; i++) {
        if (reservations[i].getResCode() == resCode) {
            exist = true;
            index = i;
            break;
        }
    }
    if (exist) {
        // Get the flights index no in the flights array
        int flightNoIndex = flightNoExist(reservations[index].getFlight().getFlightNo());
        int numPass = reservations[index].getNumPass();

        string** seatPlan = flights[flightNoIndex].getSeatPlan();

        // Change the seating plan so that now canceled seats are shown by 'o'
        for (int i = 0; i < numPass; i++) {
            seatPlan[(reservations[index].getSeatRow())[i]]
                [(int)((reservations[index].getSeatCol())[i]) - 64] = "o";
        }

        cout << "Reservation for the seats ";
        for (int i = 0; i < numPass; i++) {
            cout << (reservations[index].getSeatRow())[i] << "" << (reservations[index].getSeatCol())[i] << " ";
        }
        cout << "is cancelled in Flight " << flights[flightNoIndex].getFlightNo() << endl;

        // Update the reservations array
        Reservation* tmp = new Reservation[resAmount];
        for (int i = 0; i < index; i++) {
            tmp[i] = reservations[i];
        }
        for (int i = index; i < resAmount - 1; i++) {
            tmp[i + 1] = reservations[i];
        }
        reservations = NULL;
        delete[] reservations;

        reservations = tmp;
        resAmount = resAmount - 1;
        flights[flightNoIndex].setAvailable(flights[flightNoIndex].getAvailable() + numPass);

        tmp = NULL;
        delete[] tmp;
    }
    else {
        cout << "No reservations under Code " << resCode << endl;
    }
}

void ReservationSystem::showReservation(const int resCode) {
    bool exist = false;
    int index = -1;

    // Check whether the reservation with the given resCode exists
    for (int i = 0; i < resAmount; i++) {
        if (reservations[i].getResCode() == resCode) {
            exist = true;
            index = i;
            break;
        }
    }
    if (!exist) {
        cout << "No reservations under Code " << resCode << endl;
    }
    else {
        cout << "Reservations under Code " << resCode << " in flight " <<
            reservations[index].getFlight().getFlightNo() << ": ";

        for (int i = 0; i < reservations[index].getNumPass(); i++) {
            cout << (reservations[index].getSeatRow())[i] << "" << (reservations[index].getSeatCol())[i] << " ";
        }
        cout << endl;
    }
}

void ReservationSystem::printSeatPlan(int index) {
    string** seatPlan = flights[index].getSeatPlan();

    for (int i = 0; i < flights[index].getRowNo() + 1; i++) {
        for (int j = 0; j < flights[index].getSeatNo() + 1; j++) {
            cout << seatPlan[i][j];
        }
        cout << endl;
    }
}

// A method for checking existence of an flight in the flights array
// If the flight exist, return the index of the flight in the flights array
// If it does not exist, return -1
int ReservationSystem::flightNoExist(const int flightNo) {
    int a = -1;
    for (int i = 0; i < flightAmount; i++) {
        if (flights[i].getFlightNo() == flightNo) {
            a = i;
            break;
        }
    }
    return a;
}

// A method for cancelling all the reservation of a spesific flight
void ReservationSystem::cancelReservationsOfFlight(const int flightNo) {
    // This array will hold all the reservations except the ones we want to cancel due to its flight
    // j will be the new resAmount
    int indexes[100];
    int j = 0;

    for (int i = 0; i < resAmount; i++) {
        if (reservations[i].getFlight().getFlightNo() != flightNo) {
            indexes[j] = i;
            j++;
        }
    }

    Reservation* tmp = new Reservation[j];

    for (int i = 0; i < j; i++) {
        tmp[i] = reservations[indexes[i]];
    }
    reservations = NULL;
    delete[] reservations;

    reservations = tmp;
    resAmount = j;

    tmp = NULL;
    delete[] tmp;
}
