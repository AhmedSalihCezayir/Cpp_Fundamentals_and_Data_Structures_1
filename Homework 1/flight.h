#ifndef _FLIGHT_H
#define _FLIGHT_H
#include <string>
using namespace std;

class Flight {
public:
    Flight(int fNo, int rNo, int sNo);
    Flight(const Flight&);
    Flight();
    ~Flight();

    void setFlightNo(int);
    void setRowNo(int);
    void setSeatNo(int);
    void setAvailable(int);
    void initializeSeatPlan(int, int);

    int getRowNo() const;
    int getFlightNo() const;
    int getSeatNo() const;
    int getNumPassengers() const;
    int getAvailable() const;

    string** getSeatPlan() const;
    
    Flight& operator=( Flight& );

private:
    string** seatPlan;
    int flightNo;
    int rowNo;
    int seatNo;
    int available;
};

#endif // _FLIGHT_H
