#include <iostream>
#include <vector>
#include <algorithm>
#include <stdbool.h>
using namespace std;

bool checkPlatform(vector<double> &platform, double arrival, double departure)
{
    for (int i = 0; i < platform.size(); i++)
    {
        if (platform[i] <= arrival)
        {
            platform[i] = departure;
            return true;
        }
    }
    return false;
}

int minPlatforms(vector<pair<double, double>> &trains)
{
    vector<double> platform;
    platform.push_back(trains[0].second); // First train will always need a platform
    for (int i = 1; i < trains.size(); i++)
    {
        if (!checkPlatform(platform, trains[i].first, trains[i].second))
        {
            platform.push_back(trains[i].second);
        }
    }
    return platform.size();
}

int main()
{
    vector<double> arrival = {9.00, 9.40, 9.50, 11.00, 15.00, 18.00};
    vector<double> departure = {9.10, 12.00, 11.20, 11.30, 19.00, 20.00};
    vector<pair<double, double>> trains;
    for (int i = 0; i < arrival.size(); i++)
    {
        trains.push_back({arrival[i], departure[i]});
    }
    sort(trains.begin(), trains.end());
    cout << "Minimum platforms required: " << minPlatforms(trains) << endl;
    return 0;
}