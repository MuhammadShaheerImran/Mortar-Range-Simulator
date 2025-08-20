#include <iostream>
#include <cmath>
using namespace std;

const double M_PI = 3.141592653589793;
const double EarthRadius = 6371000;     // in meters
const double Gravity = 9.81;            // gravity in m/s^2
const double RadToDeg = 180.0 / M_PI;   // radians to degrees
const double DegToRad = M_PI / 180.0;   // degrees to radians

// Haversine distance formula (returns distance in meters)
double HaversineDistance(double LatMortar, double LongMortar, double LatTarget, double LongTarget) {
    double dLat = LatTarget - LatMortar;
    double dLon = LongTarget - LongMortar;
    double a = sin(dLat/2)*sin(dLat/2) + cos(LatMortar)*cos(LatTarget)*sin(dLon/2)*sin(dLon/2);
    return EarthRadius * 2 * atan2(sqrt(a), sqrt(1-a));
}

// Elevation angles (returns both low and high arc solutions)
void ElevationAngles(double Range, double EffectiveVelocity, double &angleLow, double &angleHigh) {
    double ratio = (Gravity * Range) / (EffectiveVelocity * EffectiveVelocity);

    if (ratio > 1.0) { // target unreachable
        angleLow = angleHigh = -1;
        return ;
    }

    double theta = 0.5 * asin(ratio);     // in radians
    angleLow  = theta * RadToDeg;         // low arc
    angleHigh = (M_PI/2 - theta) * RadToDeg; // high arc
}

// Bearing (left/right angle) with wind & drift correction
double LeftRightAngle(double LatMortar, double LongMortar, double LatTarget, double LongTarget, double windSpeed, double windDirection) {
    double dLon = LongTarget - LongMortar;
    double y = sin(dLon) * cos(LatTarget);
    double x = cos(LatMortar) * sin(LatTarget) - sin(LatMortar) * cos(LatTarget) * cos(dLon);
    double angle = atan2(y, x) * RadToDeg;

    // Drift factor 
    double driftFactor = 1.5;  
    angle += driftFactor;

    // Wind correction
    angle += windSpeed * cos(windDirection) * 0.1;

    return angle;
}

int main() {
    double LatMortar, LongMortar, LatTarget, LongTarget;
    double EffectiveVelocity, WindSpeed, WindDirection;

    cout << "--- Mortar Ballistics Simulator ---\n\n";

    // input mortar and target coordinates
    cout << "Enter mortar latitude (degrees): ";
    cin >> LatMortar;
    cout << "Enter mortar longitude (degrees): ";
    cin >> LongMortar;
    cout << "Enter target latitude (degrees): ";
    cin >> LatTarget;
    cout << "Enter target longitude (degrees): ";
    cin >> LongTarget;

    // convert to radians
    LatMortar *= DegToRad;
    LongMortar *= DegToRad;
    LatTarget *= DegToRad;
    LongTarget *= DegToRad;

    // input velocity and wind
    cout << "Enter muzzle velocity of mortar (m/s): ";
    cin >> EffectiveVelocity;
    cout << "Enter wind speed (m/s): ";
    cin >> WindSpeed;
    cout << "Enter wind direction (degrees): ";
    cin >> WindDirection;
    WindDirection *= DegToRad; // convert to radians 

    cout.setf(ios::fixed);
    cout.precision(4); // precision fixed to 4 decimal places

    while (true) {
        double Range = HaversineDistance(LatMortar, LongMortar, LatTarget, LongTarget);

        if ((Gravity * Range) / (EffectiveVelocity * EffectiveVelocity) > 1) {
            cout << "\nTarget is not in range with current velocity.\n";
            break;
        }

        // calculate angles
        double angleLow, angleHigh;
        ElevationAngles(Range, EffectiveVelocity, angleLow, angleHigh);
        double bearing = LeftRightAngle(LatMortar, LongMortar, LatTarget, LongTarget, WindSpeed, WindDirection);

        cout << "\n--- Firing Solution ---\n";
        cout << "Range to target      : " << Range << " meters\n";
        cout << "Elevation (low arc)  : " << angleLow << " degrees\n";
        cout << "Elevation (high arc) : " << angleHigh << " degrees\n";
        cout << "Left/Right bearing   : " << bearing << " degrees\n";

        // soldier confirmation
        char confirm;
        cout << "\nDid the mortar hit the target? (y/n): ";
        cin >> confirm;

        if (confirm == 'y' || confirm == 'Y') {
            cout << "\nTarget destroyed successfully.\n";
            break;
        } else {
            cout << "\nEnter new impact location (latitude & longitude in degrees): ";
            cin >> LatTarget >> LongTarget;
            LatTarget *= DegToRad;
            LongTarget *= DegToRad;
        }
    }

    return 0;
}














