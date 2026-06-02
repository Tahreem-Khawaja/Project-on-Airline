#include <iostream>
#include "airline.h"
#include "exceptions.h"

void menu() {
    std::cout << "\n======================================\n";
    std::cout << "      SKYLINK AIRWAYS CONSOLE SYSTEM  \n";
    std::cout << "======================================\n";
    std::cout << "1. Add New Flight Profile Record\n";
    std::cout << "2. Register New Passenger Profile\n";
    std::cout << "3. Display All Available Flights\n";
    std::cout << "4. Process Seat Booking & Issue Ticket\n";
    std::cout << "5. Process Flight Ticket Cancellation\n";
    std::cout << "6. Check Customer History Logs\n";
    std::cout << "7. Print Daily Departures Schedule\n";
    std::cout << "8. Print Occupancy Load Report\n";
    std::cout << "9. Save Changes and Exit Application\n";
    std::cout << "Enter Choice (1-9): ";
}

int main() {
    Airline skyLink;
    
    // Auto-load state from file system database context if existing [cite: 39]
    skyLink.loadData("flights.txt", "passengers.txt", "tickets.txt");

    int selection = 0;
    while (true) {
        menu();
        std::cin >> selection;

        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            std::cout << "Invalid Option. Please use numerical selection flags.\n";
            continue;
        }

        try {
            if (selection == 1) {
                std::string num, orig, dest, time;
                int seats, fType;
                double price;

                std::cout << "Enter Flight Number: "; std::cin >> num;
                std::cout << "Enter Origin Airport Location: "; std::cin >> orig;
                std::cout << "Enter Destination Airport Location: "; std::cin >> dest;
                std::cout << "Enter Departure Date-Time (YYYY-MM-DD): "; std::cin >> time;
                std::cout << "Enter Airframe Total Capacity Seats: "; std::cin >> seats;
                std::cout << "Enter Standard Ticket Base Price: "; std::cin >> price;
                std::cout << "Select Type Classification (1: Domestic, 2: International, 3: Charter): "; std::cin >> fType;

                if (fType == 1) skyLink.addFlight(new DomesticFlight(num, orig, dest, time, seats, price));
                else if (fType == 2) skyLink.addFlight(new InternationalFlight(num, orig, dest, time, seats, price));
                else if (fType == 3) skyLink.addFlight(new CharterFlight(num, orig, dest, time, seats, price));
                else std::cout << "Invalid Classification. Flight Entry Dropped.\n";
            }
            else if (selection == 2) {
                std::string id, name, email;
                int pType;

                std::cout << "Enter Profile Registration ID: "; std::cin >> id;
                std::cout << "Enter Full Legal Identity Name: "; std::cin.ignore(); std::getline(std::cin, name);
                std::cout << "Enter Customer Email Address: "; std::cin >> email;
                std::cout << "Select Tier Class Structure (1: Economy, 2: Business, 3: First Class): "; std::cin >> pType;

                if (pType == 1) skyLink.registerPassenger(new EconomyPassenger(id, name, email));
                else if (pType == 2) skyLink.registerPassenger(new BusinessPassenger(id, name, email));
                else if (pType == 3) skyLink.registerPassenger(new FirstClassPassenger(id, name, email));
                else std::cout << "Invalid Classification. Passenger Entry Aborted.\n";
            }
            else if (selection == 3) {
                skyLink.listFlights();
            }
            else if (selection == 4) {
                std::string pid, fnum, seat;
                std::cout << "Enter Target Passenger ID Profile: "; std::cin >> pid;
                std::cout << "Enter Target Flight Code Allocation: "; std::cin >> fnum;
                std::cout << "Enter Requested Cabin Seat Number: "; std::cin >> seat;
                skyLink.bookTicket(pid, fnum, seat);
            }
            else if (selection == 5) {
                std::string tid;
                int hours;
                std::cout << "Enter Active Ticket Transaction Reference ID: "; std::cin >> tid;
                std::cout << "Enter Expected Hours Remaining Prior To Departure: "; std::cin >> hours;
                skyLink.cancelBooking(tid, hours);
            }
            else if (selection == 6) {
                std::string pid;
                std::cout << "Enter Passenger Profile Reference ID: "; std::cin >> pid;
                skyLink.viewPassengerHistory(pid);
            }
            else if (selection == 7) {
                std::string date;
                std::cout << "Enter Search Target Date (YYYY-MM-DD): "; std::cin >> date;
                skyLink.generateDailyDeparturesReport(date);
            }
            else if (selection == 8) {
                skyLink.generateOccupancyReport();
            }
            else if (selection == 9) {
                std::cout << "Writing operations state out to non-volatile tracking files...\n";
                skyLink.saveData("flights.txt", "passengers.txt", "tickets.txt");
                std::cout << "Data transaction backup saved cleanly. Halting system threads.\n";
                break;
            }
            else {
                std::cout << "Selection out of valid execution boundaries (Range: 1-9).\n";
            }
        }
        catch (const FlightFullException& e) {
            std::cout << "\n[BOOKING ERROR]: " << e.what() << "\n";
        }
        catch (const InvalidCancellationException& e) {
            std::cout << "\n[CANCELLATION ERROR]: " << e.what() << "\n";
        }
        catch (const std::exception& e) {
            std::cout << "\n[SYSTEM MESSAGE]: " << e.what() << "\n";
        }
    }
    return 0;
}
