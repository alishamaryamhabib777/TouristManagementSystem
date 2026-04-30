#include <iostream>
#include <vector>
#include <map>
#include <cmath>
#include <string>
#include <iomanip>
#include <fstream>
#include <algorithm>
#include <limits> 

using namespace std;

#ifndef M_PI
// Define PI if it's not already defined by the math library
#define M_PI 3.14159265358979323846
#endif
// ======================================================
// MODULE 1: TOUR DISTANCE CALCULATION
// A structure to hold the name and geographical coordinates of a place.
struct Location {
    string name;
    double latitude;
    double longitude;
};
//This class handles logic related to calculating the distance between two points on Earth.
class TourDistanceModule {
private:
    // Lists of various tourist places in Pakistan
    vector<Location> historicalPlaces;
    vector<Location> urbanPlaces;
    vector<Location> modernPlaces;
    vector<Location> ruralPlaces;
    vector<Location> northernPlaces;
    // A map to store the main cities of Pakistan 
    map<string, Location> pakistanCities;
    // A map for case-insensitive city lookups.
    map<string, Location> standardizedCities;
    void line() {
        cout << "====================================================\n";
    }
    // function to print a section title.
    void title(string text) {
        line();
        cout << "   " << text << endl;
        line();
    }
    // Fills up the lists of tourist places with their names and coordinates.
    void initializePlaces() {

        historicalPlaces = {
            {"Mohenjo-Daro", 27.3290, 68.1380},
            {"Taxila", 33.6000, 72.8333},
            {"Lahore Fort", 31.5820, 74.3294},
            {"Badshahi Mosque", 31.5820, 74.3087},
            {"Rohtas Fort", 32.9333, 72.6500},
            {"Makli Necropolis", 24.7333, 68.3833},
            {"Shalimar Gardens", 31.5820, 74.3294},
            {"Wazir Khan Mosque", 31.5820, 74.3087},
            {"Khanpur Dam", 33.0000, 72.5000},
            {"Katas Raj Temples", 32.9333, 72.6500}
        };
        urbanPlaces = {
            {"Karachi", 24.8607, 67.0011},
            {"Lahore", 31.5497, 74.3436},
            {"Islamabad", 33.6844, 73.0479},
            {"Faisalabad", 31.4184, 74.1108},
            {"Rawalpindi", 33.6007, 72.6774},
            {"Multan", 30.1575, 71.5249},
            {"Peshawar", 34.0151, 71.5249},
            {"Quetta", 30.1798, 66.9750},
            {"Hyderabad", 25.3960, 68.3693},
            {"Gujranwala", 32.1614, 74.1882}
        };
        modernPlaces = {
            {"Centaurus Mall", 33.6844, 73.0551},
            {"Dolmen Mall", 24.8607, 67.0011},
            {"Emporium Mall", 31.5497, 74.3436},
            {"LuckyOne Mall", 24.8607, 67.0011},
            {"Sapphire Mall", 31.5497, 74.3436},
            {"Mall of Lahore", 31.5497, 74.3436},
            {"Giga Mall", 33.6844, 73.0551},
            {"Al-Fatah Mall", 31.5497, 74.3436},
            {"Park Towers", 24.8607, 67.0011},
            {"Bahria Town", 33.6844, 73.0551}
        };
        ruralPlaces = {
            {"Skardu", 35.3333, 75.5489},
            {"Hunza", 36.3133, 74.6342},
            {"Fairy Meadows", 35.3294, 73.6880},
            {"Naran", 34.0200, 73.6530},
            {"Kaghan", 34.0200, 73.6530},
            {"Neelum Valley", 34.0000, 73.7500},
            {"Swat Valley", 35.2225, 72.2750},
            {"Murree", 33.9094, 73.3922},
            {"Khanaspur", 33.9080, 73.3920},
            {"Ayubia", 33.9111, 73.3922}
        };
        northernPlaces = {
            {"Naltar Valley", 36.0000, 73.5000},
            {"Ratti Gali Lake", 34.0000, 73.5000},
            {"Ratti Gali", 34.0000, 73.5000},
            {"Fairy Meadows", 35.3294, 73.6880},
            {"Kaghan Valley", 34.0200, 73.6530},
            {"Hunza Valley", 36.3133, 74.6342},
            {"Skardu", 35.3333, 75.5489},
            {"Neelum Valley", 34.0000, 73.7500},
            {"Swat Valley", 35.2225, 72.2750},
            {"Murree", 33.9094, 73.3922}
        };
    }

    void initializeCities() {
        // Fills up the map of major cities in Pakistan with their coordinates.
        pakistanCities = {
            {"Karachi", {"Karachi", 24.8607, 67.0011}},
            {"Lahore", {"Lahore", 31.5204, 74.3587}},
            {"Islamabad", {"Islamabad", 33.6844, 73.0479}},
            {"Rawalpindi", {"Rawalpindi", 33.5651, 73.0169}},
            {"Peshawar", {"Peshawar", 34.0151, 71.5249}},
            {"Quetta", {"Quetta", 30.1798, 66.9750}},
            {"Faisalabad", {"Faisalabad", 31.4180, 73.0790}},
            {"Multan", {"Multan", 30.1575, 71.5249}},
            {"Hyderabad", {"Hyderabad", 25.3960, 68.3578}},
            {"Sialkot", {"Sialkot", 32.4927, 74.5313}},
            {"Gujranwala", {"Gujranwala", 32.1877, 74.1945}},
            {"Bahawalpur", {"Bahawalpur", 29.3956, 71.6836}},
            {"Sukkur", {"Sukkur", 27.7139, 68.8363}},
            {"Larkana", {"Larkana", 27.5589, 68.2090}},
            {"Mardan", {"Mardan", 34.1989, 72.0400}},
            {"Swat", {"Swat", 34.7717, 72.3600}},
            {"Gilgit", {"Gilgit", 35.9208, 74.3089}},
            {"Skardu", {"Skardu", 35.2979, 75.6333}},
            {"Hunza", {"Hunza", 36.3167, 74.6500}},
            {"Muzaffarabad", {"Muzaffarabad", 34.3700, 73.4711}},
            {"Gwadar", {"Gwadar", 25.1264, 62.3225}},
            {"Abbottabad", {"Abbottabad", 34.1688, 73.2215}},
            {"Chitral", {"Chitral", 35.8511, 71.7864}},
            {"Khuzdar", {"Khuzdar", 27.8110, 66.6100}},
            {"DeraGhaziKhan", {"DeraGhaziKhan", 30.0322, 70.6403}},
            {"DeraIsmailKhan", {"DeraIsmailKhan", 31.8333, 70.9000}},
            {"RahimYarKhan", {"RahimYarKhan", 28.4202, 70.2952}},
            {"Jhelum", {"Jhelum", 32.9400, 73.7300}}
        };

        //case-insensitive lookup for cities
        for (const auto& pair : pakistanCities) {
            string upperCaseKey = pair.first;
            transform(upperCaseKey.begin(), upperCaseKey.end(), upperCaseKey.begin(), ::toupper);
            standardizedCities[upperCaseKey] = pair.second;
        }
    }
    // Calculates the distance between the user's city and the selected spot using the Haversine formula.
    void calculateDistance(double userLat, double userLong, Location spot) {
        const double earthRadiusKm = 6371.0;

        // Convert latitude and longitude differences to radians.
        double dLat = (spot.latitude - userLat) * M_PI / 180.0;
        double dLong = (spot.longitude - userLong) * M_PI / 180.0;
        // Haversine formula
        double a = sin(dLat / 2) * sin(dLat / 2) +
            cos(userLat * M_PI / 180.0) *
            cos(spot.latitude * M_PI / 180.0) *
            sin(dLong / 2) * sin(dLong / 2);

        double c = 2 * atan2(sqrt(a), sqrt(1 - a));
        double distance = earthRadiusKm * c;
        // Display the result
        title("TRAVEL DETAILS");
        cout << "Destination : " << spot.name << endl;
        cout << "Distance    : " << fixed << setprecision(2) << distance << " km" << endl;
        line();
    }

public:
    TourDistanceModule() {
        initializePlaces(); // Load all the tourist spots.
        initializeCities(); // load all city data
    }

    void runTourDistanceCalculator() {
        title("WELCOME TO DISTANCE CALCULATOR");
        // Ask the user to choose a category.
        cout << "Select your favorite category:\n";
        cout << "1. Historical\n";
        cout << "2. Urban\n";
        cout << "3. Modern\n";
        cout << "4. Rural\n";
        cout << "5. Northern\n";
        cout << "Enter choice: ";

        int choice;
        cin >> choice;

        vector<Location> selectedPlaces;
        // Use a switch to select the correct list of places based on user input.
        switch (choice) {
        case 1: selectedPlaces = historicalPlaces; break;
        case 2: selectedPlaces = urbanPlaces; break;
        case 3: selectedPlaces = modernPlaces; break;
        case 4: selectedPlaces = ruralPlaces; break;
        case 5: selectedPlaces = northernPlaces; break;
        default:
            cout << "Invalid choice!\n";
            return;
        }
        // Display all the available places in the chosen category.
        title("AVAILABLE PLACES");
        for (size_t i = 0; i < selectedPlaces.size(); ++i) {
            cout << i + 1 << ". " << selectedPlaces[i].name << endl;
        }

        cout << "Select place number: ";
        int placeChoice;
        cin >> placeChoice;
        // Check if the place choice is valid.
        if (placeChoice < 1 || placeChoice > selectedPlaces.size()) {
            cout << "Invalid choice.\n";
            return;
        }

        string userCity;
        cout << "Enter your current city: ";
        cin >> userCity;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        string standardizedInput = userCity;
        transform(standardizedInput.begin(), standardizedInput.end(), standardizedInput.begin(), ::toupper);
        // Look up the city coordinates in the standardized map.
        if (standardizedCities.find(standardizedInput) == standardizedCities.end()) {
            cout << "City not found in Pakistan list. Please try again with exact spelling.\n";
            return;
        }

        Location userLocation = standardizedCities[standardizedInput];
        Location selectedSpot = selectedPlaces[placeChoice - 1];
        // Calculate and display the distance between the user's city and the tourist spot.
        calculateDistance(userLocation.latitude,
            userLocation.longitude,
            selectedSpot);
    }
};
// =====================================================
// MODULE 2: HOTEL BOOKING

// Structure to hold all the details of a single hotel booking.
struct bookingsummary {
    string name;
    string city;
    int occupancy;
    string roomtype;
    int noofdays;
    int roomno;
    bool meals;
    string currency;
    double total_bill;
};
// Structure to hold all the data about a single hotel.
struct hotel {
    string name;
    string city;
    int star;
    double priceUSDstan;
    double pricePKRstan;
    double pricedeluxe;
    double pricesuite;
    bool roomService;
    double mealprice;
    int availroom;
    vector<bool> BookedRooms;
};
// This class handles hotel management, booking, and bill calculation.
class HotelBookingModule {
private:
    vector<hotel> Hotels;
    vector<bookingsummary> allBookings;// In-memory list of current session bookings.
    // room assignment function which finds available rooms and marks them as booked.
    vector<int> assignrooms(hotel& h, int roomsRequested) {
        vector<int> assigned;
        for (int i = 0; i < h.BookedRooms.size() && assigned.size() < roomsRequested; i++) {
            if (!h.BookedRooms[i]) {// If the room is not booked
                h.BookedRooms[i] = true;
                assigned.push_back(i + 1);
            }
        }
        return assigned;
    }
    // Calculates the total cost for the stay based on room type, days, and currency.
    double calculatebill(const hotel& h, int roomType, int rooms, int days, int occupancy, bool meals, string currency) {
        double roomprice = 0;
        double usdToPkrRate = h.pricePKRstan / h.priceUSDstan;
        // Determine the base room price based on type and desired currency.
        if (roomType == 1) roomprice = (currency == "USD") ? h.priceUSDstan : h.pricePKRstan;
        else if (roomType == 2) roomprice = (currency == "USD") ? h.pricedeluxe : h.pricedeluxe * usdToPkrRate;
        else if (roomType == 3) roomprice = (currency == "USD") ? h.pricesuite : h.pricesuite * usdToPkrRate;

        double total = roomprice * rooms * days;
        // Add the cost for meals if requested 
        if (meals && !h.roomService)
            total += h.mealprice * occupancy * days * ((currency == "USD") ? 1.0 : usdToPkrRate);
        return total;
    }
    // Fills up the list of hotels with their details and initializes their room availability.
    void initializeHotels() {
        Hotels = {
            {"PC Hotel", "Rawalpindi", 5, 87.00, 24400.00, 120.00, 200.00, true, 0, 54},
            {"Best Western Hotel", "Rawalpindi", 3, 70.00, 19600.00, 100.00, 150.00, false, 15.00, 100},
            {"Hotel Khursheed Palace", "Rawalpindi", 3, 40.00, 11200.00, 60.00, 100.00, false, 10.00, 30},
            {"Pearl Continental Hotel", "Lahore", 5, 100.00, 28000.00, 150.00, 250.00, true, 0, 32},
            {"Grand Royal Hotel", "Lahore", 3, 32.00, 5500.00, 50.00, 80.00, false, 12.00, 15},
            {"Faletti's Hotel", "Lahore", 5, 90.00, 25200.00, 130.00, 220.00, true, 0, 40},
            {"Embassy Inn Hotel", "Karachi", 3, 27.00, 7500.00, 45.00, 70.00, false, 8.00, 40},
            {"Avari Towers", "Karachi", 5, 107.00, 29960.00, 160.00, 280.00, true, 0, 120},
            {"Pearl Continental Hotel", "Karachi", 5, 97.00, 27160.00, 150.00, 250.00, true, 0, 200},
            {"Mövenpick Hotel", "Karachi", 5, 120.00, 33600.00, 180.00, 300.00, true, 0, 80},
            {"Islamabad Serena Hotel", "Islamabad", 5, 209.00, 58400.00, 300.00, 500.00, true, 0, 120},
            {"Islamabad Marriott Hotel", "Islamabad", 5, 130.00, 36400.00, 200.00, 350.00, true, 0, 288},
            {"Hotel One Jinnah", "Islamabad", 3, 25.00, 7000.00, 40.00, 70.00, false, 10.00, 50},
            {"Reina Boutique Hotel", "Islamabad", 5, 75.00, 21000.00, 120.00, 200.00, true, 0, 25},
            {"Ramada by Wyndham", "Multan", 3, 112.00, 31360.00, 150.00, 200.00, false, 20.00, 90},
            {"Hotel One", "Multan", 3, 35.00, 9800.00, 50.00, 80.00, false, 12.00, 45},
            {"Al-Hamra Hotel", "Multan", 5, 95.00, 26600.00, 140.00, 220.00, true, 0, 50}
        };
        // For every hotel, initialize all its rooms as available (false).
        for (auto& h : Hotels) {
            h.BookedRooms = vector<bool>(h.availroom, false);
        }
    }
    // Reads and displays all saved bookings from the "bookings.txt" file.
    void viewAllBookings() {
        cout << "\n********** ALL BOOKINGS **********\n";
        ifstream fin("bookings.txt");

        if (!fin) {
            cout << "No bookings file found.\n";
        }
        else {
            string line;
            while (getline(fin, line)) {
                cout << line << endl;
            }
            fin.close();
        }
    }

public:// runs when the HotelBookingModule object is created.
    HotelBookingModule() {
        initializeHotels();// Load all the hotel data.
    }

    void runHotelBooking() {
        cout << "\n********** HOTEL MANAGEMENT SYSTEM **********\n";
        cout << "1. Book a room\n";
        cout << "2. View bookings\n";
        cout << "3. Back to Main Menu\n";
        cout << "Choice: ";
        int mainoption;
        cin >> mainoption;

        if (mainoption == 3) return;
        // Option 1: Book a room 
        if (mainoption == 1) {
            bookingsummary Booking;
            // Get city choice.
            cout << "which city are you planning to stay in? select one:\n";
            string cities[] = { "Lahore", "Islamabad", "Rawalpindi", "Karachi","Multan" };
            for (int i = 0;i <= 4;i++) {
                cout << i + 1 << "." << cities[i] << endl;
            }
            int choice;
            cin >> choice;

            if (choice < 1 || choice > 5) {
                cout << "Invalid city choice.\n";
                return;
            }
            Booking.city = cities[choice - 1];
            //Display available hotels in the selected city.
            vector<hotel*> hotelsInCity;
            for (auto& h : Hotels)
                if (h.city == Booking.city) hotelsInCity.push_back(&h);
            if (hotelsInCity.empty()) {
                cout << "No hotels found in this city.\n";
                return;
            }
            //  Select currency.
            cout << "Select currency:\n1. USD\n2. PKR\nChoice: ";
            int curChoice;
            cin >> curChoice;
            Booking.currency = (curChoice == 1) ? "USD" : "PKR";

            cout << "Select a hotel:\n";
            int num = 1;
            for (auto* h : hotelsInCity) {
                double price = (Booking.currency == "USD") ? h->priceUSDstan : h->pricePKRstan;
                cout << num << ". " << h->name << " | " << h->star << "stars | "
                    << price << " " << Booking.currency << " per night" << endl;
                num++;
            }
            int hotelChoice;
            cin >> hotelChoice;

            if (hotelChoice < 1 || hotelChoice > hotelsInCity.size()) {
                cout << "Invalid hotel choice.\n";
                return;
            }

            hotel* selectHotel = hotelsInCity[hotelChoice - 1];
            Booking.name = selectHotel->name;
            //Select room type(Standard, Deluxe, Suite).
            int roomtype;
            cout << "select type of room:\n";
            cout << "1.Standard\n2.Deluxe\n3.Suite\n";
            cin >> roomtype;
            switch (roomtype) {
            case 1: Booking.roomtype = "Standard"; break;
            case 2: Booking.roomtype = "Deluxe"; break;
            case 3: Booking.roomtype = "Suite"; break;
            default: cout << "Invalid room type.\n"; return;
            }
            // number of rooms requested.
            cout << "Enter number of rooms to be booked: ";
            cin >> Booking.roomno;

            vector<int> assigned = assignrooms(*selectHotel, Booking.roomno);
            if (assigned.size() < Booking.roomno) {
                cout << "Sorry, not enough rooms available in this hotel. Only " << assigned.size() << " rooms booked.\n";

                return;
            }
            else {
                cout << "Your assigned rooms are: ";
                for (int r : assigned) cout << r << " ";
                cout << endl;
            }

            cout << "Number of days: ";
            cin >> Booking.noofdays;

            cout << "Occupancy in one room: ";
            cin >> Booking.occupancy;
            //choose meal plan.
            cout << "Are you planning to eat out or do you want meals in hotel?\n";
            cout << "1.Meals in hotel (room service)\n";
            cout << "2.Planning to eat out\n";
            int choosemeal;
            cin >> choosemeal;
            Booking.meals = (choosemeal == 1);

            Booking.total_bill = calculatebill(*selectHotel, roomtype, Booking.roomno, Booking.noofdays, Booking.occupancy, Booking.meals, Booking.currency);

            cout << fixed << setprecision(2);
            cout << "Total cost: " << Booking.total_bill << " " << Booking.currency << endl;

            // -------------------- Save booking --------------------
            allBookings.push_back(Booking);
            ofstream fout("bookings.txt", ios::app);

            fout << "Hotel: " << Booking.name << ", "
                << "City: " << Booking.city << ", "
                << "Room Type: " << Booking.roomtype << ", "
                << "Rooms: " << Booking.roomno << ", "
                << "Days: " << Booking.noofdays << ", "
                << "Total: " << Booking.total_bill << " "
                << Booking.currency << endl;

            fout.close();

            // Display Summary
            cout << "\n********** BOOKING SUMMARY **********\n";
            cout << "Hotel: " << Booking.name << endl;
            cout << "City: " << Booking.city << endl;
            cout << "Room Type: " << Booking.roomtype << endl;
            cout << "Number of Rooms: " << Booking.roomno << endl;
            cout << "Number of Days: " << Booking.noofdays << endl;
            cout << "Occupancy per Room: " << Booking.occupancy << endl;
            cout << "Meals Included: " << (Booking.meals ? "Yes" : "No") << endl;
            cout << "Assigned Room Numbers: ";
            for (int r : assigned) cout << r << " ";
            cout << endl;
            cout << fixed << setprecision(2);
            cout << "Total Bill: " << Booking.total_bill << " " << Booking.currency << endl;
            cout << "***********************************\n";
        }
        else if (mainoption == 2) {
            viewAllBookings();
        }
        else {
            cout << "Invalid choice.\n";
        }
    }
};

// ===================================================
// MODULE 3: TRANSPORT BOOKING


// Structure to hold details of an available vehicle.
struct Vehicle {
    int id;
    string type;
    string model;
    int capacity;
    double baseFare;
    string driverName;
    bool available;
};
// Structure to hold details of a completed transport booking.

struct BookingTransport {
    int bookingId;
    int vehicleId;
    string customerName;
    string date;
    int seatsBooked;
    double totalCost;
};
// This class manages the vehicle list and handles transport booking.

class TransportSystemModule {
private:
    vector<Vehicle> vehicles;
    vector<BookingTransport> bookings;
    int nextBookingId = 1;

    void initializeVehicles() {
        vehicles.push_back({ 1, "Bus", "Volvo 9700", 40, 15.0, "Ali Akbar", true });
        vehicles.push_back({ 2, "Car", "Cultus Alto", 4, 10.0, "Ahmad Khalil", true });
        vehicles.push_back({ 3, "Van", "Ford Transit", 12, 12.0, "Mutahar kiani", true });
    }
    // Displays the entire list of vehicles in a nice, formatted table.

    void listVehicles() {
        cout << "\n===== AVAILABLE VEHICLES =====\n";
        cout << left << setw(6) << "ID" << setw(10) << "Type" << setw(12)
            << "Model" << setw(9) << "Capacity" << setw(12) << "BaseFare"
            << setw(16) << "Driver" << "Available\n";
        cout << string(70, '-') << "\n";
        for (auto& v : vehicles) {
            cout << left << setw(6) << v.id << setw(10) << v.type << setw(12)
                << v.model << setw(9) << v.capacity << setw(12) << fixed << setprecision(2) << v.baseFare
                << setw(16) << v.driverName << (v.available ? "Yes" : "No") << "\n";
        }
        cout << "==============================\n";
    }
    // Prints a detailed invoice for a successful booking.

    void printInvoice(const BookingTransport& b, const Vehicle& v) {
        cout << "\n===== TRANSPORT INVOICE =====\n";
        cout << "Booking ID: " << b.bookingId << "\n";
        cout << "Customer: " << b.customerName << "\n";
        cout << "Vehicle: " << v.type << " (" << v.model << ")\n";
        cout << "Driver: " << v.driverName << "\n";
        cout << "Date: " << b.date << "\n";
        cout << "Seats: " << b.seatsBooked << "\n";
        cout << fixed << setprecision(2);
        cout << "Total cost: " << b.totalCost << "\n";
        cout << "=============================\n\n";
    }

    // Helper function to safely read an integer from the user, handling bad input (like letters).

    static int readInt(const string& prompt) {
        while (true) {
            cout << prompt;
            string line;
            if (!getline(cin, line)) return -1;
            try { return stoi(line); }
            catch (...) { cout << "Invalid input. Enter a number.\n"; }
        }
    }
    // Calculates the final cost: BaseFare * Seats * 1.10 (for a 10% fee/tax).

    static double computeCost(const Vehicle& v, int seats) {
        return v.baseFare * seats * 1.10;
    }

public:
    // Constructor: runs when the TransportSystemModule object is created.

    TransportSystemModule() {
        initializeVehicles(); // Load all vehicle data.
    }

    void bookTransport() {

        listVehicles();
        int vehicleId = readInt("Enter vehicle ID to book: ");
        if (vehicleId == -1) return;

        // Find the selected vehicle in the list
        auto it = find_if(vehicles.begin(), vehicles.end(), [&](Vehicle& v) { return v.id == vehicleId; });
        if (it == vehicles.end()) { cout << "Invalid vehicle ID.\n"; return; }
        Vehicle& v = *it;
        if (!v.available) { cout << "Vehicle currently unavailable.\n"; return; }

        // Get booking details from the user.
        cout << "Enter your name: ";
        string cname; getline(cin, cname);
        cout << "Enter date (YYYY-MM-DD): "; string date; getline(cin, date);
        int seats = readInt("Enter number of seats to book: ");
        if (seats <= 0 || seats > v.capacity) { cout << "Invalid number of seats.\n"; return; }


        // Calculate cost and create the booking record.
        double cost = computeCost(v, seats);
        BookingTransport b = { nextBookingId++, v.id, cname, date, seats, cost };
        bookings.push_back(b);
        // If all seats are booked, mark the entire vehicle as unavailable.
        if (seats == v.capacity) v.available = false;

        cout << "Booking successful! Booking ID: " << b.bookingId << "\n";
        printInvoice(b, v);
    }

    void runTransportSystem() {
        while (true) {
            cout << "\n=== Transport Booking System ===\n";
            cout << "1. View Vehicles\n";
            cout << "2. Book Transport\n";
            cout << "0. Back to Main Menu\n";
            cout << "Select option: ";
            int opt;

            if (!(cin >> opt)) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid input. Please enter a number.\n";
                continue;
            }
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            if (opt == 1) listVehicles();
            else if (opt == 2) bookTransport();
            else if (opt == 0) break;
            else cout << "Invalid option.\n";
        }
    }
};

// =============================================
// MODULE 4: SIGN UP/LOGIN 
// This class handles user authentication

class UserAuthModule {
private:
    // A map to store usernames (key) and passwords (value).

    map<string, string> registeredUsers;

public:
    // Function to handle the creation of a new user account.
    bool signUp() {
        cout << "\n\n----- USER SIGN UP -----\n";
        string username, password;

        cout << "Enter new username: ";
        getline(cin, username);
        // Check if the username is already taken.
        if (registeredUsers.count(username)) {
            cout << "Error: Username already exists. Please log in or choose another.\n";
            return false;
        }

        cout << "Enter new password: ";
        getline(cin, password);
        // ensure both fields are not empty.
        if (username.empty() || password.empty()) {
            cout << "Sign up failed: Username or password cannot be empty.\n";
            return false;
        }

        registeredUsers[username] = password;// Store the new user's credentials
        cout << "Sign up successful!\n";
        return true;
    }
    // Function to handle the user login process.

    bool login() {
        cout << "\n\n----- USER LOGIN -----\n";
        string username, password;

        cout << "Enter username: ";
        getline(cin, username);

        cout << "Enter password: ";
        getline(cin, password);
        auto it = registeredUsers.find(username);

        if (it != registeredUsers.end()) {
            // Check if the password matches the stored password
            if (it->second == password) {
                cout << "Login successful! Welcome, " << username << ".\n";
                return true;
            }
        }
        // If the username is not found or the password doesn't match
        cout << "Login failed. Invalid username or password.\n";
        return false;
    }
};
// Function to display the main application menu after a successful login.

void showMainMenu() {
    cout << "\n\n**************************************************\n";
    cout << "      TOURIST MANAGEMENT SYSTEM MENU             \n";
    cout << "**************************************************\n";
    cout << "1. Calculate Distance\n";
    cout << "2. Hotel Booking\n";
    cout << "3. Transport Booking\n";
    cout << "0. Logout and Exit\n";
    cout << "Enter your choice: ";
}
// Function to display the initial menu for signing up or logging in.

void showAuthMenu() {
    cout << "\nWELCOME TO TOURIST MANAGEMENT SYSTEM\n";
    cout << "1. Sign Up\n";
    cout << "2. Login\n";
    cout << "0. Exit Program\n";
    cout << "Choice: ";
}

int main() {
    // Create an object for each management module.

    TourDistanceModule tourModule;
    HotelBookingModule hotelModule;
    TransportSystemModule transportModule;
    UserAuthModule authModule;

    bool loggedIn = false;
    // Keep asking the user to sign up or log in until they succeed or choose to exit.
    while (!loggedIn) {
        showAuthMenu();
        int authChoice;

        if (!(cin >> authChoice)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Please enter a number.\n";
            continue;
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        if (authChoice == 1) {
            // Sign Up then attempt to Login
            if (authModule.signUp()) {
                loggedIn = authModule.login();
            }
        }
        else if (authChoice == 2) {
            // Login directly
            loggedIn = authModule.login();
        }
        else if (authChoice == 0) {
            // Exit option from menu
            cout << "Exiting system. Goodbye!\n";
            return 0;
        }
        else {
            cout << "Invalid choice. Please try again.\n";
        }
    }

    //Main Application Loop runs only if loggedIn is true
    int choice;
    do {
        showMainMenu();
        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Please enter a number.\n";
            continue;
        }
        // Call the appropriate function/module based on the user's choice.

        switch (choice) {
        case 1:
            tourModule.runTourDistanceCalculator();
            break;
        case 2:
            hotelModule.runHotelBooking();
            break;
        case 3:
            transportModule.runTransportSystem();
            break;
        case 0:
            cout << "Logging out. Thank you!\n";
            break;
        default:
            cout << "Invalid option. Please try again.\n";
            break;
        }
    } while (choice != 0);// Loop until the user chooses option 0 (Logout and Exit).

    return 0;// Program finished successfully.
}
