#include "ticket.h"

Ticket::Ticket(std::string id, Passenger* p, Flight* f, std::string seat, double fare)
    : ticketID(id), passenger(p), flight(f), seatNumber(seat), farePaid(fare), bookingStatus("Active") {}

void Ticket::cancelTicket() {
    bookingStatus = "Cancelled";
}

std::ostream& operator<<(std::ostream& os, const Ticket& ticket) {
    os << "Ticket ID: " << ticket.ticketID << " | Passenger: " << ticket.passenger->getName() 
       << " | Flight: " << ticket.flight->getFlightNumber() << " | Seat: " << ticket.seatNumber 
       << " | Fare: $" << ticket.farePaid << " | Status: " << ticket.bookingStatus;
    return os;
}
