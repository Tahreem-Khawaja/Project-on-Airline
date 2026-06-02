#include "passenger.h"

Passenger::Passenger(std::string id, std::string nm, std::string em)
    : passengerID(id), name(nm), email(em) {}

void Passenger::displayDetails() const {
    std::cout << "ID: " << passengerID << " | Name: " << name << " | Type: " << getPassengerType();
}
