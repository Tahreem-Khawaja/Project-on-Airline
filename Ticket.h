#ifndef TICKET_H
#define TICKET_H

#include <string>
#include <iostream>
#include "flight.h"
#include "passenger.h"

class Ticket {
private:
    std::string ticketID;
    Passenger* passenger;
    Flight* flight;
    std::string seatNumber;
    double farePaid;
    std::string bookingStatus; // "Active" or "Cancelled" [cite: 30]

public:
    Ticket(std::string id, Passenger* p, Flight* f, std::string seat, double fare);

    std::string getTicketID() const { return ticketID; }
    Passenger* getPassenger() const { return passenger; }
    Flight* getFlight() const { return flight; }
    double getFarePaid() const { return farePaid; }
    std::string getStatus() const { return bookingStatus; }
    
    void cancelTicket();

    // Comparing tickets by ID using overloaded operator [cite: 44]
    bool operator==(const Ticket& other) const { return this->ticketID == other.ticketID; }

    friend std::ostream& operator<<(std::ostream& os, const Ticket& ticket);
};

#endif
