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
