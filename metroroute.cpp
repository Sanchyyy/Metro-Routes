#include <algorithm>
#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <limits.h>
#include <string>
#include <cctype> // For tolower

using namespace std;

// Helper function to convert a string to lowercase
string toLowerCase(const string& str) {
    string lowerStr = str;
    transform(lowerStr.begin(), lowerStr.end(), lowerStr.begin(), ::tolower);
    return lowerStr;
}

// Structure to represent a metro station and its connections
struct Station {
    string name;
    unordered_map<string, int> neighbors; // Adjacent stations and distance
};

// Graph class for metro network
class MetroNetwork {
    unordered_map<string, Station> stations;
    vector<string> pinkLine = {"Majlis Park", "Azadpur", "Shalimar Bagh", "Netaji Subhash Place", "Welcome", 
                               "East Azad Nagar", "Krishna Nagar", "Karkarduma Court", "Karkarduma", 
                               "Anand Vihar ISBT", "IP Extension", "Vinod Nagar", "Trilokpuri", "Mayur Vihar"};
    vector<string> blueLine = {"Dwarka Sector 21", "Dwarka", "Rajouri Garden", "Karol Bagh", "Rajiv Chowk", 
                               "Mandi House", "Yamuna Bank", "Karkarduma", "Anand Vihar ISBT", "Vaishali", "Kaushambi"};

public:
    // Adding a station to the network
    void addStation(string name) {
        stations[name] = Station{name};
    }

    // Connecting two stations with a distance
    void addConnection(string from, string to, int distance) {
        stations[from].neighbors[to] = distance;
        stations[to].neighbors[from] = distance; // Undirected graph
    }

    // Checking if a station exists (case-insensitive comparison)
    bool stationExists(const string& station) {
        string lowerStation = toLowerCase(station);
        for (const auto& s : stations) {
            if (toLowerCase(s.first) == lowerStation) {
                return true;
            }
        }
        return false;
    }

    // Getting the actual station name (case-insensitive)
    string getActualStation(const string& station) {
        string lowerStation = toLowerCase(station);
        for (const auto& s : stations) {
            if (toLowerCase(s.first) == lowerStation) {
                return s.first;
            }
        }
        return "";
    }

    // Finding shortest path based on Dijkstra's algorithm
    vector<string> shortestRoute(string src, string dest) {
        unordered_map<string, int> dist;
        unordered_map<string, string> prev;
        priority_queue<pair<int, string>, vector<pair<int, string>>, greater<>> pq;

        // Initialize distances
        for (auto& station : stations) {
            dist[station.first] = INT_MAX;
        }

        // Starting point
        dist[src] = 0;
        pq.push({0, src});

        // Dijkstra's algorithm
        while (!pq.empty()) {
            string u = pq.top().second;
            pq.pop();

            if (u == dest) break; // Reached destination

            // Check neighbors
            for (auto& neighbor : stations[u].neighbors) {
                string v = neighbor.first;
                int weight = neighbor.second;
                if (dist[u] + weight < dist[v]) {
                    dist[v] = dist[u] + weight;
                    prev[v] = u;
                    pq.push({dist[v], v});
                }
            }
        }

        // Reconstruct the path
        vector<string> path;
        for (string at = dest; !at.empty(); at = prev[at]) {
            path.push_back(at);
        }
        reverse(path.begin(), path.end());
        return path;
    }

    // Checking if two stations are on the same line
    bool areStationsOnSameLine(const string& src, const string& dest) {
        bool srcOnPink = find(pinkLine.begin(), pinkLine.end(), src) != pinkLine.end();
        bool destOnPink = find(pinkLine.begin(), pinkLine.end(), dest) != pinkLine.end();
        bool srcOnBlue = find(blueLine.begin(), blueLine.end(), src) != blueLine.end();
        bool destOnBlue = find(blueLine.begin(), blueLine.end(), dest) != blueLine.end();
        
        // If both are on Pink or both are on Blue, they are on the same line
        return (srcOnPink && destOnPink) || (srcOnBlue && destOnBlue);
    }

    // Calculating fare based on number of stations
    int calculateFare(int numStations) {
        return numStations * 5; // Example: 5 units per station
    }

    // Display stations on Pink and Blue lines
    void displayStations() {
        cout << "Available Stations on Pink Line:" << endl;
        for (const auto& station : pinkLine) {
            cout << station << endl;
        }

        cout << "\nAvailable Stations on Blue Line:" << endl;
        for (const auto& station : blueLine) {
            cout << station << endl;
        }
    }

    // Display change options at intersection stations
    void displayChangeOptions() {
        cout << "You can change at the following intersections:\n";
        cout << "1. Karkarduma (Change Line)\n";
        cout << "2. Anand Vihar ISBT (Change Line)\n";
    }
};

int main() {
    MetroNetwork metro;

    // Adding stations for Pink Line and Blue Line
    vector<string> pinkStations = {"Majlis Park", "Azadpur", "Shalimar Bagh", "Netaji Subhash Place", "Welcome", 
                                   "East Azad Nagar", "Krishna Nagar", "Karkarduma Court", "Karkarduma", 
                                   "Anand Vihar ISBT", "IP Extension", "Vinod Nagar", "Trilokpuri", "Mayur Vihar"};
    vector<string> blueStations = {"Dwarka Sector 21","tilak nagar", "Dwarka", "Rajouri Garden", "Karol Bagh", "Rajiv Chowk", 
                                   "Mandi House", "Yamuna Bank", "Karkarduma", "Anand Vihar ISBT", "Vaishali", "Kaushambi"};

    // Adding stations to the metro network
    for (const auto& station : pinkStations) {
        metro.addStation(station);
    }
    for (const auto& station : blueStations) {
        metro.addStation(station);
    }

    // Connecting stations
    metro.addConnection("Majlis Park", "Azadpur", 5);
    metro.addConnection("Azadpur", "Shalimar Bagh", 3);
    metro.addConnection("Shalimar Bagh", "Netaji Subhash Place", 4);
    metro.addConnection("Netaji Subhash Place", "Welcome", 6);
    metro.addConnection("Welcome", "East Azad Nagar", 2);
    metro.addConnection("East Azad Nagar", "Krishna Nagar", 2);
    metro.addConnection("Krishna Nagar", "Karkarduma Court", 5);
    metro.addConnection("Karkarduma Court", "Karkarduma", 3);
    metro.addConnection("Karkarduma", "Anand Vihar ISBT", 2);
    metro.addConnection("Anand Vihar ISBT", "IP Extension", 4);
    metro.addConnection("IP Extension", "Vinod Nagar", 3);
    metro.addConnection("Vinod Nagar", "Trilokpuri", 4);
    metro.addConnection("Trilokpuri", "Mayur Vihar", 5);
    
    metro.addConnection("Dwarka Sector 21", "Dwarka", 3);
    metro.addConnection("Dwarka", "Rajouri Garden", 6);
    metro.addConnection("Rajouri Garden", "Karol Bagh", 4);
    metro.addConnection("Karol Bagh", "Rajiv Chowk", 2);
    metro.addConnection("Rajiv Chowk", "Mandi House", 3);
    metro.addConnection("Mandi House", "Yamuna Bank", 5);
    metro.addConnection("Yamuna Bank", "Karkarduma", 4);
    metro.addConnection("Karkarduma", "Anand Vihar ISBT", 3);
    metro.addConnection("Anand Vihar ISBT", "Vaishali", 5);
    metro.addConnection("Vaishali", "Kaushambi", 2);

    string source, destination;
    char choice;

    do {
        // Displaying all stations
        metro.displayStations();

        // Taking user input for source and destination
        cout << "\nEnter the source station: ";
        getline(cin, source);
        cout << "Enter the destination station: ";
        getline(cin, destination);

        // Case-insensitive check for station existence
        if (!metro.stationExists(source)) {
            cout << "Source station doesn't exist!" << endl;
        } else if (!metro.stationExists(destination)) {
            cout << "Destination station doesn't exist!" << endl;
        } else if (source == destination) {
            cout << "Source and destination are the same. No need to travel!" << endl;
        } else {
            // Get the actual station names (in case of different casing)
            source = metro.getActualStation(source);
            destination = metro.getActualStation(destination);

            // Finding and displaying the shortest route
            vector<string> route = metro.shortestRoute(source, destination);
            cout << "Stations along the route: ";
            for (const auto& station : route) {
                cout << station << " -> ";
            }
            cout << "End\n";

            // Displaying the fare and estimated time
            int numStations = route.size();
            int fare = metro.calculateFare(numStations);
            cout << "Total number of stations: " << numStations << endl;
            cout << "Fare for the route: ₹" << fare << endl;
            cout << "Estimated time: " << numStations * 2 << " minutes" << endl;

            // Check if a line change is needed
            if (!metro.areStationsOnSameLine(source, destination)) {
                cout << "You will need to change lines during your journey." << endl;
                metro.displayChangeOptions();
            }
        }

        cout << "\nDo you want to plan another route? (Y/N): ";
        cin >> choice;
        cin.ignore(); // To consume the newline character left in the input buffer

    } while (choice == 'Y' || choice == 'y');

    return 0;
}
