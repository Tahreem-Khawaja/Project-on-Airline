#include "flight.h"

Flight::Flight(std::string num, std::string orig, std::string dest, std::string time, int seats, double price)
    : flightNumber(num), origin(orig), destination(dest), departureTime(time), totalSeats(seats), availableSeats(seats), basePrice(price) {}

bool Flight::allocateSeat() {
    if (availableSeats > 0) {
        availableSeats--;
        return true;
    }
    return false;
}

void Flight::freeSeat() {
    if (availableSeats < totalSeats) {
        availableSeats++;
    }
}

void Flight::displayDetails(std::ostream& os) const {
    os << "Flight: " << flightNumber << " | " << origin << " -> " << destination 
       << " | Date: " << departureTime << " | Available Seats: " << availableSeats << "/" << totalSeats;
}

std::ostream& operator<<(std::ostream& os, const Flight& flight) {
    flight.displayDetails(os);
    return os;
}
