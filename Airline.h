#ifndef AIRLINE_H
#define AIRLINE_H

#include <vector>
#include <string>
#include "flight.h"
#include "passenger.h"
#include "ticket.h"

class Airline {
private:
    std::vector<Flight*> flights;       // Using basic STL vectors [cite: 47]
    std::vector<Passenger*> passengers;
    std::vector<Ticket*> tickets;
    int ticketCounter;

public:
    Airline();
    ~Airline(); // Cleans up dynamic memory allocation to prevent memory leaks [cite: 48]

    void addFlight(Flight* f);
    void registerPassenger(Passenger* p);
    
    void listFlights() const;
    Flight* findFlight(const std::string& flightNum) const;
    Passenger* findPassenger(const std::string& passengerID) const;

    void bookTicket(const std::string& passengerID, const std::string& flightNum, const std::string& seatNum);
    void cancelBooking(const std::string& ticketID, int hoursBeforeDeparture);
    void viewPassengerHistory(const std::string& passengerID) const;

    void generateDailyDeparturesReport(const std::string& date) const;
    void generateOccupancyReport() const;

    void saveData(const std::string& fFile, const std::string& pFile, const std::string& tFile) const;
    void loadData(const std::string& fFile, const std::string& pFile, const std::string& tFile);
};

#endif
