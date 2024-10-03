#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <algorithm>

using namespace std;

// ---------------------- Location Class ----------------------
class Location
{
public:
    string name;
    double latitude;
    double longitude;

    Location(string name, double lat, double lon) : name(name), latitude(lat), longitude(lon) {}

    void displayLocation() const
    {
        cout << "Location: " << name << " (Lat: " << latitude << ", Lon: " << longitude << ")\n";
    }
};

// ---------------------- Location Manager Class ----------------------
class LocationManager
{
private:
    vector<Location> locations;

public:
    void addLocation(const string &name, double lat, double lon)
    {
        locations.emplace_back(name, lat, lon);
        cout << "Location " << name << " added.\n";
    }

    void removeLocation(const string &name)
    {
        locations.erase(remove_if(locations.begin(), locations.end(),
                                  [&](Location &loc)
                                  { return loc.name == name; }),
                        locations.end());
        cout << "Location " << name << " removed.\n";
    }

    void listLocations() const
    {
        cout << "Listing all locations:\n";
        for (const auto &loc : locations)
        {
            loc.displayLocation();
        }
    }
};

// ---------------------- WeatherVariable Class ----------------------
class WeatherVariable
{
private:
    double temperature;
    double windSpeed;

public:
    void setTemperature(double temp)
    {
        temperature = temp;
    }

    void setWindSpeed(double speed)
    {
        windSpeed = speed;
    }

    double getTemperature() const
    {
        return temperature;
    }

    double getWindSpeed() const
    {
        return windSpeed;
    }

    void displayWeatherVariables() const
    {
        cout << "Temperature: " << temperature << "°C\n";
        cout << "Wind Speed: " << windSpeed << " m/s\n";
    }
};

// ---------------------- WeatherForecastingSystem Class ----------------------
class WeatherForecastingSystem
{
public:
    void fetchWeatherData()
    {
        cout << "Fetching weather data...\n";
        WeatherVariable weather;
        weather.setTemperature(25.5);
        weather.setWindSpeed(5.2);
        weather.displayWeatherVariables();
    }

    void displayWeatherData()
    {
        cout << "Displaying weather data...\n";
        fetchWeatherData();
    }
};

// ---------------------- HistoricalWeatherSystem Class ----------------------
class HistoricalWeatherSystem
{
public:
    void fetchHistoricalData()
    {
        cout << "Fetching historical weather data...\n";
        WeatherVariable weather;
        weather.setTemperature(20.0); // Simulated past temperature
        weather.setWindSpeed(4.0);    // Simulated past wind speed
        weather.displayWeatherVariables();
    }

    void displayHistoricalData()
    {
        cout << "Displaying historical weather data...\n";
        fetchHistoricalData();
    }
};

// ---------------------- DataExporter Class ----------------------
class DataExporter
{
public:
    void exportToCSV(const string &fileName, const WeatherVariable &weather)
    {
        ofstream file(fileName);
        if (file.is_open())
        {
            file << "Temperature,Wind Speed\n";
            file << weather.getTemperature() << "," << weather.getWindSpeed() << "\n";
            file.close();
            cout << "Data exported to " << fileName << " in CSV format.\n";
        }
        else
        {
            cerr << "Error opening file.\n";
        }
    }

    void exportToJSON(const string &fileName, const WeatherVariable &weather)
    {
        ofstream file(fileName);
        if (file.is_open())
        {
            file << "{\n";
            file << "  \"Temperature\": " << weather.getTemperature() << ",\n";
            file << "  \"Wind Speed\": " << weather.getWindSpeed() << "\n";
            file << "}\n";
            file.close();
            cout << "Data exported to " << fileName << " in JSON format.\n";
        }
        else
        {
            cerr << "Error opening file.\n";
        }
    }
};

// ---------------------- Main Program ----------------------
int main()
{
    // Manage locations
    LocationManager locationManager;
    locationManager.addLocation("New York", 40.7128, -74.0060);
    locationManager.addLocation("Los Angeles", 34.0522, -118.2437);
    locationManager.listLocations();

    // Remove a location
    locationManager.removeLocation("Los Angeles");
    locationManager.listLocations();

    // Fetch and display weather forecast
    WeatherForecastingSystem weatherSystem;
    weatherSystem.displayWeatherData();

    // Fetch and display historical weather data
    HistoricalWeatherSystem historicalWeatherSystem;
    historicalWeatherSystem.displayHistoricalData();

    // Export weather data to CSV and JSON
    WeatherVariable weather;
    weather.setTemperature(25.5);
    weather.setWindSpeed(5.2);

    DataExporter exporter;
    exporter.exportToCSV("weather.csv", weather);
    exporter.exportToJSON("weather.json", weather);

    return 0;
}