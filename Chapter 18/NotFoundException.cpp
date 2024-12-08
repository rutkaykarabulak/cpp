#ifndef NotFoundException_cpp
#define NotFoundException_cpp

#include <exception>
#include <string>

class NotFoundException : public std::exception {
private:
    std::string message;

public:
    // Default constructor
    NotFoundException();

    // Constructor with custom message
    explicit NotFoundException(const std::string& customMessage);

    // Destructor
    virtual ~NotFoundException() noexcept;

    // Override the what() function from std::exception
    virtual const char* what() const noexcept override;
};

#endif

NotFoundException::NotFoundException() : message("Item not found.") {}

NotFoundException::NotFoundException(const std::string& customMessage) : message(customMessage) {}

NotFoundException::~NotFoundException() noexcept = default;

// Override what() function
const char* NotFoundException::what() const noexcept {
    return message.c_str();
}
