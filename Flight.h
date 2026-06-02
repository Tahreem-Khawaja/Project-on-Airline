#ifndef FLIGHT_H
#define FLIGHT_H

#include <string>
#include <iostream>

class Flight {
protected:
    std::string flightNumber;
    std::string origin;
    std::string destination;
    std::string departureTime;
    int totalSeats;
    int availableSeats;
    double basePrice;

public:
    Flight(std::string num, std::string orig, std::string dest, std::string time, int seats, double price);
    virtual ~Flight() = default;

    std::string getFlightNumber() const { return flightNumber; }
    std::string getOrigin() const { return origin; }
    std::string getDestination() const { return destination; }
    std::string getDepartureTime() const { return departureTime; }
    int getAvailableSeats() const { return availableSeats; }
    int getTotalSeats() const { return totalSeats; }
    double getBasePrice() const { return basePrice; }

    bool allocateSeat();
    void freeSeat();

    virtual std::string getFlightType() const = 0;
    virtual double calculateBaseFare() const = 0; // Pure virtual [cite: 27]
    virtual void displayDetails(std::ostream& os) const;

    // Operator Overloading for displaying Flight objects [cite: 44]
    friend std::ostream& operator<<(std::ostream& os, const Flight& flight);
};

class DomesticFlight : public Flight {
public:
    using Flight::Flight;
    std::string getFlightType() const override { return "Domestic"; }
    double calculateBaseFare() const override { return basePrice + 15.0; } // flat tax rate [cite: 28]
};

class InternationalFlight : public Flight {
public:
    using Flight::Flight;
    std::string getFlightType() const override { return "International"; }
    double calculateBaseFare() const override { return basePrice + 50.0; } // international tariff [cite: 28]
};

class CharterFlight : public Flight {
public:
    using Flight::Flight;
    std::string getFlightType() const override { return "Charter"; }
    double calculateBaseFare() const override { return basePrice * 1.30; } // 30% premium rate [cite: 28]
};

#endif
