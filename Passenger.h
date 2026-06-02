#ifndef PASSENGER_H
#define PASSENGER_H

#include <string>
#include <iostream>

class Passenger {
protected:
    std::string passengerID;
    std::string name;
    std::string email;

public:
    Passenger(std::string id, std::string nm, std::string em);
    virtual ~Passenger() = default;

    std::string getID() const { return passengerID; }
    std::string getName() const { return name; }
    std::string getEmail() const { return email; }

    // Pure virtual function requirements
    virtual std::string getPassengerType() const = 0;
    virtual double getRefundPercentage() const = 0; // Different rules per class

    virtual void displayDetails() const;
};

class EconomyPassenger : public Passenger {
public:
    using Passenger::Passenger;
    std::string getPassengerType() const override { return "Economy"; }
    double getRefundPercentage() const override { return 0.50; } // 50% refund
};

class BusinessPassenger : public Passenger {
public:
    using Passenger::Passenger;
    std::string getPassengerType() const override { return "Business"; }
    double getRefundPercentage() const override { return 0.80; } // 80% refund
};

class FirstClassPassenger : public Passenger {
public:
    using Passenger::Passenger;
    std::string getPassengerType() const override { return "FirstClass"; }
    double getRefundPercentage() const override { return 1.00; } // 100% refund
};

#endif
