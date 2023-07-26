#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>

using namespace std;

// Flight class to store flight information
class Flight {
public:
    string flightNumber;
    string source;
    string destination;
    string date;
    int totalSeats;
    int bookedSeats;

    Flight(const string& flightNumber, const string& source, const string& destination, const string& date, int totalSeats)
        : flightNumber(flightNumber), source(source), destination(destination), date(date), totalSeats(totalSeats), bookedSeats(0) {}
};

// Function to load flights from a file
vector<Flight> loadFlightsFromFile(const string& filename) {
    vector<Flight> flights;
    ifstream infile(filename);

    if (!infile) {
        cerr << "Error: Could not open the file." << endl;
        return flights;
    }

    string line;
    while (getline(infile, line)) {
        stringstream ss(line);
        string flightNumber, source, destination, date;
        int totalSeats;

        ss >> flightNumber >> source >> destination >> date >> totalSeats;
        flights.push_back(Flight(flightNumber, source, destination, date, totalSeats));
    }

    infile.close();
    return flights;
}

// Function to save flights to a file
void saveFlightsToFile(const vector<Flight>& flights, const string& filename) {
    ofstream outfile(filename);

    if (!outfile) {
        cerr << "Error: Could not open the file." << endl;
        return;
    }

    for (const Flight& flight : flights) {
        outfile << flight.flightNumber << " " << flight.source << " " << flight.destination << " " << flight.date << " " << flight.totalSeats << endl;
    }

    outfile.close();
}

// Function to search for flights based on source, destination, and date
vector<Flight> searchFlights(const vector<Flight>& flights, const string& source, const string& destination, const string& date) {
    vector<Flight> result;
    for (const Flight& flight : flights) {
        if (flight.source == source && flight.destination == destination && flight.date == date && flight.bookedSeats < flight.totalSeats) {
            result.push_back(flight);
        }
    }
    return result;
}

// Function to book a seat on a flight
void bookFlightSeat(vector<Flight>& flights, const string& flightNumber) {
    for (Flight& flight : flights) {
        if (flight.flightNumber == flightNumber && flight.bookedSeats < flight.totalSeats) {
            flight.bookedSeats++;
            break;
        }
    }
}

int main() {
    // Load flights from a file or create your own
    vector<Flight> flights = loadFlightsFromFile("flights.txt");

    int choice;
    do {
        cout << "Airline Booking System" << endl;
        cout << "1. Search Flights" << endl;
        cout << "2. Book a Flight" << endl;
        cout << "3. View Bookings" << endl;
        cout << "4. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                string source, destination, date;
                cout << "Enter source: ";
                cin >> source;
                cout << "Enter destination: ";
                cin >> destination;
                cout << "Enter date (DD-MM-YYYY): ";
                cin >> date;

                vector<Flight> availableFlights = searchFlights(flights, source, destination, date);
                if (availableFlights.empty()) {
                    cout << "No flights available for the given details." << endl;
                } else {
                    cout << "Available Flights:" << endl;
                    for (const Flight& flight : availableFlights) {
                        cout << flight.flightNumber << " " << flight.source << " -> " << flight.destination << " Date: " << flight.date << " Seats: " << flight.totalSeats - flight.bookedSeats << endl;
                    }
                }
                break;
            }
            case 2: {
                string flightNumber;
                cout << "Enter the Flight Number to book: ";
                cin >> flightNumber;

                bookFlightSeat(flights, flightNumber);
                cout << "Flight seat booked successfully." << endl;
                break;
            }
            case 3: {
                cout << "Your Bookings:" << endl;
                for (const Flight& flight : flights) {
                    if (flight.bookedSeats > 0) {
                        cout << flight.flightNumber << " " << flight.source << " -> " << flight.destination << " Date: " << flight.date << " Seat: " << flight.bookedSeats << endl;
                    }
                }
                break;
            }
            case 4: {
                // Save flights to a file before exiting
                saveFlightsToFile(flights, "flights.txt");
                cout << "Thank you for using the Airline Booking System. Goodbye!" << endl;
                break;
            }
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    } while (choice != 4);

    return 0;
}
