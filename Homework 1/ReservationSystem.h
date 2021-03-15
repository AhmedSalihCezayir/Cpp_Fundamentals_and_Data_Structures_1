#ifndef _RESERVATIONSYSTEM_H
#define _RESERVATIONSYSTEM_H

#include "Reservation.h"
class ReservationSystem {
public:
    ReservationSystem();
    ~ReservationSystem();

    void addFlight(const int flightNo, const int rowNo, const int seatNo);
    void cancelFlight(const int flightNo);

    void showAllFlights();
    void showFlight(const int flightNo);
    int makeReservation(const int flightNo, const int numPassengers,
        const int* seatRow, const char* seatCol);
    void cancelReservation(const int resCode);
    void showReservation(const int resCode);
    int flightNoExist(int flightNo);
    void printSeatPlan(int index);
    void cancelReservationsOfFlight(const int flightNo);
    

private:
    Flight* flights;
    Reservation* reservations;
    int totalResAmount;
    int resAmount; //size of reservations array
    int flightAmount; //size of flights array
};

#endif // _RESERVATIONSYSTEM_H

