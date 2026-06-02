#include "airline.h"
#include "exceptions.h"
#include <fstream>
#include <sstream>

Airline::Airline() : ticketCounter(1000) {}

Airline::~Airline() {
    for (auto f : flights) delete f;       // Deep memory cleanup [cite: 48]
    for (auto p : passengers) delete p;
    for (auto t : tickets) delete t;
}

void Airline::addFlight(Flight* f) { flights.push_back(f); }
void Airline::registerPassenger(Passenger* p) { passengers.push_back(p); }

void Airline::listFlights() const {
    std::cout << "\n--- Scheduled System Flights ---\n";
    for (auto f : flights) {
        std::cout << *f << " | Type: " << f->getFlightType() << " | Base Fare: $" << f->calculateBaseFare() << "\n";
    }
}

Flight* Airline::findFlight(const std::string& flightNum) const {
    for (auto f : flights) {
        if (f->getFlightNumber() == flightNum) return f;
    }
    return nullptr;
}

Passenger* Airline::findPassenger(const std::string& passengerID) const {
    for (auto p : passengers) {
        if (p->getID() == passengerID) return p;
    }
    return nullptr;
}

void Airline::bookTicket(const std::string& passengerID, const std::string& flightNum, const std::string& seatNum) {
    Passenger* p = findPassenger(passengerID);
    Flight* f = findFlight(flightNum);

    if (!p) throw std::runtime_error("Passenger profile record not found.");
    if (!f) throw std::runtime_error("Flight profile schedule not found.");

    // Check if flight is full [cite: 35]
    if (!f->allocateSeat()) {
        throw FlightFullException("Capacity Exhausted: Flight " + flightNum + " has no open seats.");
    }

    double finalFare = f->calculateBaseFare();
    ticketCounter++;
    std::string tid = "TX" + std::to_string(ticketCounter);

    Ticket* newTicket = new Ticket(tid, p, f, seatNum, finalFare);
    tickets.push_back(newTicket);
    std::cout << "Successfully booked! Ticket Reference: " << tid << "\n";
}

void Airline::cancelBooking(const std::string& ticketID, int hoursBeforeDeparture) {
    Ticket* targetTicket = nullptr;
    for (auto t : tickets) {
        if (t->getTicketID() == ticketID) {
            targetTicket = t;
            break;
        }
    }

    if (!targetTicket) throw std::runtime_error("Ticket reference details not found.");
    if (targetTicket->getStatus() == "Cancelled") throw InvalidCancellationException("Ticket is already cancelled.");

    Passenger* p = targetTicket->getPassenger();
    Flight* f = targetTicket->getFlight();

    double refundRate = p->getRefundPercentage();
    if (hoursBeforeDeparture < 24) {
        refundRate -= 0.20; // 24-hour proximity penalty rule [cite: 36, 37]
        if (refundRate < 0) refundRate = 0;
    }

    double refundAmount = targetTicket->getFarePaid() * refundRate;
    targetTicket->cancelTicket();
    f->freeSeat();

    std::cout << "Ticket Cancelled! Total refund returned to customer: $" << refundAmount << "\n";
}

void Airline::viewPassengerHistory(const std::string& passengerID) const {
    std::cout << "\n--- Booking Archive for ID: " << passengerID << " ---\n";
    bool zeroRecords = true;
    for (auto t : tickets) {
        if (t->getPassenger()->getID() == passengerID) {
            std::cout << *t << "\n";
            zeroRecords = false;
        }
    }
    if (zeroRecords) std::cout << "No past bookings recorded for this passenger.\n";
}

void Airline::generateDailyDeparturesReport(const std::string& date) const {
    std::cout << "\n--- Departures Scheduled For: " << date << " ---\n";
    for (auto f : flights) {
        if (f->getDepartureTime().substr(0, 10) == date) {
            std::cout << *f << "\n";
        }
    }
}

void Airline::generateOccupancyReport() const {
    std::cout << "\n--- Flight Distribution Loading Factor ---\n";
    for (auto f : flights) {
        double currentOccupancy = ((double)(f->getTotalSeats() - f->getAvailableSeats()) / f->getTotalSeats()) * 100.0;
        std::cout << "Flight: " << f->getFlightNumber() << " | Capacity: " << currentOccupancy << "% Filled.\n";
    }
}

void Airline::saveData(const std::string& fFile, const std::string& pFile, const std::string& tFile) const {
    std::ofstream fOut(fFile);
    for (auto f : flights) {
        fOut << f->getFlightType() << "," << f->getFlightNumber() << "," << f->getOrigin() << ","
             << f->getDestination() << "," << f->getDepartureTime() << "," << f->getTotalSeats() << ","
             << f->getBasePrice() << "\n";
    }

    std::ofstream pOut(pFile);
    for (auto p : passengers) {
        pOut << p->getPassengerType() << "," << p->getID() << "," << p->getName() << "," << p->getEmail() << "\n";
    }

    std::ofstream tOut(tFile);
    for (auto t : tickets) {
        tOut << t->getTicketID() << "," << t->getPassenger()->getID() << "," << t->getFlight()->getFlightNumber() << ","
             << t->getStatus() << "," << t->getFarePaid() << "\n";
    }
}

void Airline::loadData(const std::string& fFile, const std::string& pFile, const std::string& tFile) {
    std::ifstream fIn(fFile);
    std::string line;
    while (fIn && std::getline(fIn, line)) {
        if (line.empty()) continue;
        std::stringstream ss(line);
        std::string type, num, orig, dest, time, seatsStr, priceStr;
        std::getline(ss, type, ','); std::getline(ss, num, ','); std::getline(ss, orig, ',');
        std::getline(ss, dest, ','); std::getline(ss, time, ','); std::getline(ss, seatsStr, ',');
        std::getline(ss, priceStr, ',');

        int seats = std::stoi(seatsStr);
        double price = std::stod(priceStr);

        if (type == "Domestic") flights.push_back(new DomesticFlight(num, orig, dest, time, seats, price));
        else if (type == "International") flights.push_back(new InternationalFlight(num, orig, dest, time, seats, price));
        else if (type == "Charter") flights.push_back(new CharterFlight(num, orig, dest, time, seats, price));
    }

    std::ifstream pIn(pFile);
    while (pIn && std::getline(pIn, line)) {
        if (line.empty()) continue;
        std::stringstream ss(line);
        std::string type, id, name, email;
        std::getline(ss, type, ','); std::getline(ss, id, ','); std::getline(ss, name, ','); std::getline(ss, email, ',');

        if (type == "Economy") passengers.push_back(new EconomyPassenger(id, name, email));
        else if (type == "Business") passengers.push_back(new BusinessPassenger(id, name, email));
        else if (type == "FirstClass") passengers.push_back(new FirstClassPassenger(id, name, email));
    }

    std::ifstream tIn(tFile);
    while (tIn && std::getline(tIn, line)) {
        if (line.empty()) continue;
        std::stringstream ss(line);
        std::string tid, pid, fnum, status, fareStr;
        std::getline(ss, tid, ','); std::getline(ss, pid, ','); std::getline(ss, fnum, ',');
        std::getline(ss, status, ','); std::getline(ss, fareStr, ',');

        Passenger* p = findPassenger(pid);
        Flight* f = findFlight(fnum);
        if (p && f) {
            Ticket* t = new Ticket(tid, p, f, "Auto", std::stod(fareStr));
            if (status == "Cancelled") t->cancelTicket();
            else f->allocateSeat();
            tickets.push_back(t);
        }
    }
}
