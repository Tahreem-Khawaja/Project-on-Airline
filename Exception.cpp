#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include <stdexcept>
#include <string>

// Custom Exception 1: Flight Full
class FlightFullException : public std::runtime_error {
public:
    explicit FlightFullException(const std::string& msg) : std::runtime_error(msg) {}
};

// Custom Exception 2: Invalid Cancellation
class InvalidCancellationException : public std::runtime_error {
public:
    explicit InvalidCancellationException(const std::string& msg) : std::runtime_error(msg) {}
};

#endif
