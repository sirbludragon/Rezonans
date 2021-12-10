#include <iostream>
#include <list>
#include <string>
#include <algorithm>
#include <math.h>
#include <list>
//wykresy oraz kąty z satelit
using namespace std;
class BodyBlue {
public:
    string name;
    double mass;
    int radius;
    double axis_period;
    int atmosphere;
    double semi_major_axis;
    double synchronus;
    float orbital_period;

};
class Orbit {
public:
    string name;
    double apogee;
    double perigee;
    double x;
    double y;
};
BodyBlue MakeNewBody(string name, double mass, int radius, double axis_period, int atmosphere, double semi_major_axis, double synchronus, float orbital_period) {
    BodyBlue test;
    test.name = name;
    test.mass = mass;
    test.radius = radius;
    test.axis_period = axis_period;
    test.atmosphere = atmosphere;
    test.semi_major_axis = semi_major_axis;
    test.synchronus = synchronus;
    test.orbital_period = orbital_period;
    return test;
}
Orbit MakeNewOrbit(string name, double apogee, double perigee, double x, double y) {
    Orbit test;
    test.name = name;
    test.apogee = apogee;
    test.perigee = perigee;
    test.x = x;
    test.y = y;
    return test;
}
string lowercase(string x) {
    transform(x.begin(), x.end(), x.begin(), ::tolower);
    return x;
}

int main() {

    bool Found = false;
    string Body, variantType;
    int variant1,variant2;
    double period, periodSecond, gravitationalParameter, apogee, apogeeRadius, apogeeConstant, SOI, someConstant, apogeeSecond, perigee, perigeeRadius, apogeeFinal, velocityApogee,
    velocityPerigee, velocity, satellite, angleDegree, angleRadian ,degree, degreeSecond, radSecond, a ,x ,y, xFloor, yFloor;
    list<double> xlist;
    list<double> ylist;

    double constant_G = 6.67408 * pow(10, -11);
    double constantPI = 3.141592653589793;
    double sunMass = 1.98847e+30;

    input:cin >> Body;
    cin.ignore(100, '\n');
    string BodyLower = Body;
    BodyLower = lowercase(BodyLower);
    //BodyBlue kerbin = MakeNewBody("Kerbin", 5.2915158e+22, 600000, 5.98594444444, 70000, 13599840256, 2863330, 426.090046296);
    BodyBlue earth = MakeNewBody("Earth", 5.97219e+24, 6371000, 23.934472222222222, 300000, 149598023e+3, 35786000, 365.256363004);
    BodyBlue venus = MakeNewBody("Venus", 4.8675e+24, 6052000, 5832.5424, 200000, 108208e+6, 7132e+8, 224.701);
    BodyBlue mars = MakeNewBody("Mars", 6.4171e+23, 3389000, 24.622972222222224, 300000, 2279392e+5, 17032000, 686.98);
    Orbit initial;
    Orbit hohmann;
    Orbit final;

    list<BodyBlue> BodyList;

    BodyList.push_back(earth);
    BodyList.push_back(venus);
    BodyList.push_back(mars);
    //BodyList.push_back(kerbin);
    for (BodyBlue Element : BodyList) {
        if (lowercase(Element.name) == BodyLower) {
            Found = true;
            SOI = ((Element.semi_major_axis * (pow((Element.mass / sunMass), (2.0 / 5)))) - Element.radius);
            cout << "\nMass of " << Element.name << " is equal to: " << Element.mass << "kg\n";
            cout << "Radius of " << Element.name << " is equal to: " << Element.radius << "m\n";
            cout << "Axis period of " << Element.name << " is equal to: " << Element.axis_period << " h\n";
            cout << "Height of atmosphere (lowest height of stable orbit above surface)" << Element.name << " is equal to: " << Element.atmosphere << "m\n";
            cout << "Semi-Major axis of " << Element.name << " is equal to: " << Element.semi_major_axis << "m\n";
            cout << "Height of Synchronus orbit above surface" << Element.name << " is equal to: " << Element.synchronus << "m\n";
            cout << "Orbital period of " << Element.name << " is equal to: " << Element.orbital_period << " days\n";

            if (Element.name != "Earth") {
                float ratio = Element.semi_major_axis / earth.semi_major_axis;
                float avg = (1 + ratio) / 2;
                float p = pow(avg, (3.0 / 2)); //period
                float p1 = p * earth.orbital_period;
                float degs = 360 / Element.orbital_period;
                float deg = p1 * degs / 2;
                float angle = 180 - deg;
                cout << "Angle bettewen Earth and " << Element.name << " at launch time should be " << angle << " degrees\n";
            }
            inputVariantType:cout << "\nAre you approching planet? Yes/No\n\n";
            cin >> variantType;
            if (lowercase(variantType) == "no") {
                inputVariant1:cout << "\nIf you want the orbit to have a rotation period of your choice, enter: 1\n";
                cout << "If you want the orbit to have the selected height, enter: 2\n";
                cout << "If you want the orbit to have lowest height for network on the chosen number of satellites, enter: 3\n";
                cout << "If you want the orbit to be synchronous orbit, enter: 4\n\n" << "Please select a variant: ";
                cin >> variant1;
                cin.ignore(100, '\n');
                if (variant1 == 1) {
                    cout << "\nRotation time of " << Element.name << "around its axis: " << Element.axis_period << "hours\n";
                    cout << "Enter the target satellites rotation period: ";
                    cin >> period;
                    cin.ignore(100, '\n');
                    periodSecond = pow((period * 60 * 60), 2);
                    gravitationalParameter = (Element.mass * constant_G);
                    apogeeConstant = ((periodSecond * gravitationalParameter) / (4 * pow(constantPI, 2)));
                    apogee = (pow(apogeeConstant, (1.0 / 3)) - (Element.radius));
                    apogeeRadius = (pow(apogeeConstant, (1.0 / 3)));
                    if (apogee >= Element.atmosphere) {
                        cout << "Height of the circular orbit is: " << round(apogee) << " meters above sea level\n";
                    }
                    else {
                        cout << "Height of circular orbit is in atmosphere";
                        break;
                    }
                    if (apogee > SOI) {
                        cout << ("Height of circular orbit is out of SOI");
                        break;
                    }
                    cout << ("How many satellites do you want to orbit: ");
                    cin >> satellite;
                    cin.ignore(100, '\n');
                    someConstant = (pow((period * 60 * 60 * (satellite - 1)), 2) / pow(satellite, 2));
                    apogeeSecond = (someConstant * gravitationalParameter / (4 * pow(constantPI, 2)));
                    apogeeSecond = (pow(apogeeSecond, (1.0 / 3)));
                    perigee = (((2 * apogeeSecond) - apogeeRadius) - (Element.radius));
                    if (perigee >= Element.atmosphere) {
                        cout << "Initial orbit perigee: " << round(perigee) << " meters above sea level\n";
                        if (perigee > SOI) {
                            cout << ("Perigee of orbit is out of SOI");
                            break;
                        }
                        apogeeFinal = (((apogee + perigee) / 2) + Element.radius);
                        velocityApogee = pow(((constant_G * Element.mass) * ((2 / apogeeRadius) - (1 / apogeeFinal))), 0.5);
                        perigeeRadius = (perigee + Element.radius);
                        velocityPerigee = pow(((constant_G * Element.mass) * ((2 / perigeeRadius) - (1 / apogeeFinal))), 0.5);
                        velocity = pow(((constant_G * Element.mass) / apogeeRadius), 0.5);
                        cout << "delta-v required = " << abs(velocityApogee - velocity) << endl;
                    }
                    else {
                        someConstant = (pow((period * 60 * 60 * (satellite + 1)), 2) / pow(satellite, 2));
                        apogeeSecond = (someConstant * gravitationalParameter / (4 * pow(constantPI, 2)));
                        apogeeSecond = (pow(apogeeSecond, (1.0 / 3)));
                        perigee = (((2 * apogeeSecond) - apogeeRadius) - (Element.radius));
                        cout << "Initial orbit apogee: " << round(perigee) << " meters above sea level\n";
                        if (perigee > SOI) {
                            cout << ("Apogee of orbit is out of SOI");
                            break;
                        }
                        apogeeFinal = (((apogee + perigee) / 2) + Element.radius);
                        velocityApogee = pow(((constant_G * Element.mass) * ((2 / apogeeRadius) - (1 / apogeeFinal))), 0.5);
                        perigeeRadius = (perigee + Element.radius);
                        velocityPerigee = pow(((constant_G * Element.mass) * ((2 / perigeeRadius) - (1 / apogeeFinal))), 0.5);
                        velocity = pow(((constant_G * Element.mass) / apogeeRadius), 0.5);
                        cout << "delta-v required = " << abs(velocityApogee - velocity) << endl;
                    }
                }
                else if (variant1 == 2) {
                    cout << "\nRotation time of " << Element.name << "around its axis: " << Element.axis_period << "hours\n";
                    cout << "Enter altitude of target orbit for the satellites in meters: ";
                    cin >> apogee;
                    cin.ignore(100, '\n');
                    gravitationalParameter = (Element.mass * constant_G);
                    period = (((4 * pow(constantPI, 2)) * (pow((apogee + Element.radius), 3))) / (gravitationalParameter));
                    apogeeRadius = apogee + Element.radius;
                    if (apogee >= Element.atmosphere) {
                        cout << "Height of the circular orbit is: " << round(apogee) << " meters above sea level\n";
                    }
                    else {
                        cout << "Height of circular orbit is in atmosphere";
                        break;
                    }
                    if (apogee > SOI) {
                        cout << ("Height of circular orbit is out of SOI");
                        break;
                    }
                    cout << ("How many satellites do you want to orbit: ");
                    cin >> satellite;
                    cin.ignore(100, '\n');
                    someConstant = ((period * pow((satellite - 1), 2)) / pow(satellite, 2));
                    apogeeSecond = (someConstant * gravitationalParameter / (4 * pow(constantPI, 2)));
                    apogeeSecond = (pow(apogeeSecond, (1.0 / 3)));
                    perigee = (((2 * apogeeSecond) - apogeeRadius) - (Element.radius));
                    if (perigee >= Element.atmosphere) {
                        cout << "Initial orbit perigee: " << round(perigee) << " meters above sea level\n";
                        if (perigee > SOI) {
                            cout << ("Perigee of orbit is out of SOI");
                            break;
                        }
                        apogeeFinal = (((apogee + perigee) / 2) + Element.radius);
                        velocityApogee = pow(((constant_G * Element.mass) * ((2 / apogeeRadius) - (1 / apogeeFinal))), 0.5);
                        perigeeRadius = (perigee + Element.radius);
                        velocityPerigee = pow(((constant_G * Element.mass) * ((2 / perigeeRadius) - (1 / apogeeFinal))), 0.5);
                        velocity = pow(((constant_G * Element.mass) / apogeeRadius), 0.5);
                        cout << "delta-v required = " << abs(velocityApogee - velocity) << endl;
                    }
                    else {
                        someConstant = ((period * pow((satellite + 1), 2)) / pow(satellite, 2));
                        apogeeSecond = (someConstant * gravitationalParameter / (4 * pow(constantPI, 2)));
                        apogeeSecond = (pow(apogeeSecond, (1.0 / 3)));
                        perigee = (((2 * apogeeSecond) - apogeeRadius) - (Element.radius));
                        cout << "Initial orbit apogee: " << round(perigee) << " meters above sea level\n";
                        if (perigee > SOI) {
                            cout << ("Apogee of orbit is out of SOI");
                            break;
                        }
                        apogeeRadius = (apogee + Element.radius);
                        apogeeFinal = (((apogee + perigee) / 2) + Element.radius);
                        velocityApogee = pow(((constant_G * Element.mass) * ((2 / apogeeRadius) - (1 / apogeeFinal))), 0.5);
                        perigeeRadius = (perigee + Element.radius);
                        velocityPerigee = pow(((constant_G * Element.mass) * ((2 / perigeeRadius) - (1 / apogeeFinal))), 0.5);
                        velocity = pow(((constant_G * Element.mass) / apogeeRadius), 0.5);
                        cout << "delta-v required = " << abs(velocityApogee - velocity) << endl;
                    }
                }
                else if (variant1 == 3) {
                    cout << "\nRotation time of " << Element.name << "around its axis " << Element.axis_period << " hours\n";
                    gravitationalParameter = (Element.mass * constant_G);
                inputSatellite1:cout << ("How many satellites do you want to orbit: ");
                    cin >> satellite;
                    cin.ignore(100, '\n');
                    angleDegree = 90 - ((((satellite - 2) * 180)) / (2 * satellite));
                    angleRadian = (angleDegree * 2 * constantPI) / 360;
                    apogee = (Element.radius / cos(angleRadian)) - Element.radius;
                    period = (((4 * pow(constantPI, 2)) * (pow((apogee + Element.radius), 3))) / (gravitationalParameter));
                    if ((apogee >= Element.atmosphere) && (satellite > 2)) {
                        apogeeRadius = apogee + Element.radius;
                        someConstant = ((period * pow((satellite - 1), 2)) / pow(satellite, 2));
                        apogeeSecond = (someConstant * gravitationalParameter / (4 * pow(constantPI, 2)));
                        apogeeSecond = (pow(apogeeSecond, (1.0 / 3)));
                        perigee = (((2 * apogeeSecond) - apogeeRadius) - (Element.radius));
                        if (perigee > Element.atmosphere) {
                            cout << "The height of the circular orbit and the apogee of the initial orbit is: " << round(apogee) << " meters above sea level";
                            if (apogee > SOI) {
                                cout << "Height of circular orbit is out of SOI";
                                break;
                            }
                            cout << "Initial orbit perigee: " << round(perigee) << " meters above sea level\n";
                            if (perigee > SOI) {
                                cout << "Perigee of orbit is out of SOI\n";
                                break;
                            }
                            apogeeFinal = (((apogee + perigee) / 2) + Element.radius);
                            velocityApogee = pow(((constant_G * Element.mass) * ((2 / apogeeRadius) - (1 / apogeeFinal))), 0.5);
                            perigeeRadius = (perigee + Element.radius);
                            velocityPerigee = pow(((constant_G * Element.mass) * ((2 / perigeeRadius) - (1 / apogeeFinal))), 0.5);
                            velocity = pow(((constant_G * Element.mass) / apogeeRadius), 0.5);
                            cout << "delta-v required = " << abs(velocityApogee - velocity) << endl;
                        }
                        else {
                            apogeeRadius = apogee + Element.radius;
                            someConstant = ((period * pow((satellite + 1), 2)) / pow(satellite, 2));
                            apogeeSecond = (someConstant * gravitationalParameter / (4 * pow(constantPI, 2)));
                            apogeeSecond = (pow(apogeeSecond, (1.0 / 3)));
                            perigee = (((2 * apogeeSecond) - apogeeRadius) - (Element.radius));
                            cout << "The height of the circular orbit and the perigee of the initial orbit is: " << round(apogee) << " meters above sea level\n";
                            if (apogee > SOI) {
                                cout << "Height of circular orbit is out of SOI\n";
                                break;
                            }
                            cout << "Initial orbit Apogee: " << round(perigee) << " meters above sea level\n";
                            if (perigee > SOI) {
                                cout << "Apogee of orbit is out of SOI\n";
                                break;
                            }
                            apogeeFinal = (((apogee + perigee) / 2) + Element.radius);
                            velocityApogee = pow(((constant_G * Element.mass) * ((2 / apogeeRadius) - (1 / apogeeFinal))), 0.5);
                            perigeeRadius = (perigee + Element.radius);
                            velocityPerigee = pow(((constant_G * Element.mass) * ((2 / perigeeRadius) - (1 / apogeeFinal))), 0.5);
                            velocity = pow(((constant_G * Element.mass) / apogeeRadius), 0.5);
                            cout << "delta-v required = " << abs(velocityApogee - velocity) << endl;
                        }
                    }
                    else {
                        cout << "Wrong number of satellites to make perfect network select fewer/more satellites\n";
                        goto inputSatellite1;
                    }
                }
                else if (variant1 == 4) {
                    if (Element.synchronus < SOI) {
                        cout << "\nRotation time of " << Element.name << "around its axis " << Element.axis_period << " hours\n";
                        apogee = Element.synchronus;
                        gravitationalParameter = (Element.mass * constant_G);
                        period = (((4 * pow(constantPI, 2)) * (pow((apogee + Element.radius), 3))) / (gravitationalParameter));
                        apogeeRadius = apogee + Element.radius;
                        if (apogee >= Element.atmosphere) {
                            cout << "Height of the circular orbit is: " << round(apogee) << " meters above sea level\n";
                        }
                        else {
                            cout << "Height of circular orbit is in atmosphere";
                            break;
                        }
                        if (apogee > SOI) {
                            cout << "Height of circular orbit is out of SOI";
                            break;
                        }
                        cout << ("How many satellites do you want to orbit: ");
                        cin >> satellite;
                        cin.ignore(100, '\n');
                        someConstant = ((period * pow((satellite - 1), 2)) / pow(satellite, 2));
                        apogeeSecond = (someConstant * gravitationalParameter / (4 * pow(constantPI, 2)));
                        apogeeSecond = (pow(apogeeSecond, (1.0 / 3)));
                        perigee = (((2 * apogeeSecond) - apogeeRadius) - (Element.radius));
                        if (perigee >= Element.atmosphere) {
                            cout << "Initial orbit perigee: " << round(perigee) << " meters above sea level\n";
                            if (perigee > SOI) {
                                cout << ("Perigee of orbit is out of SOI");
                                break;
                            }
                            apogeeFinal = (((apogee + perigee) / 2) + Element.radius);
                            velocityApogee = pow(((constant_G * Element.mass) * ((2 / apogeeRadius) - (1 / apogeeFinal))), 0.5);
                            perigeeRadius = (perigee + Element.radius);
                            velocityPerigee = pow(((constant_G * Element.mass) * ((2 / perigeeRadius) - (1 / apogeeFinal))), 0.5);
                            velocity = pow(((constant_G * Element.mass) / apogeeRadius), 0.5);
                            cout << "delta-v required = " << abs(velocityApogee - velocity) << endl;
                        }
                        else {
                            someConstant = ((period * pow((satellite + 1), 2)) / pow(satellite, 2));
                            apogeeSecond = (someConstant * gravitationalParameter / (4 * pow(constantPI, 2)));
                            apogeeSecond = (pow(apogeeSecond, (1.0 / 3)));
                            perigee = (((2 * apogeeSecond) - apogeeRadius) - (Element.radius));
                            cout << "Initial orbit apogee: " << round(perigee) << " meters above sea level\n";
                            if (perigee > SOI) {
                                cout << ("Apogee of orbit is out of SOI");
                                break;
                            }
                            apogeeFinal = (((apogee + perigee) / 2) + Element.radius);
                            velocityApogee = pow(((constant_G * Element.mass) * ((2 / apogeeRadius) - (1 / apogeeFinal))), 0.5);
                            perigeeRadius = (perigee + Element.radius);
                            velocityPerigee = pow(((constant_G * Element.mass) * ((2 / perigeeRadius) - (1 / apogeeFinal))), 0.5);
                            velocity = pow(((constant_G * Element.mass) / apogeeRadius), 0.5);
                            cout << "delta-v required = " << abs(velocityApogee - velocity) << endl;
                        }
                    }
                    else {
                        cout << "\nHeight of synchronous orbit is out of SOI";
                        break;
                    }

                }
                else {
                    cout << "\nYou have selected a variant that does not exist\n";
                    goto inputVariant1;

                }
                if ((variant1 >= 1) && (variant1 <= 4)) {
                    degree = 360 / satellite;
                    for (int n = 0; n<(satellite + 1); n++) {
                        degreeSecond = 90 - n * degree;
                        radSecond = (degreeSecond * constantPI / 180);
                        a = (tan(radSecond));
                        if (degreeSecond >= -90 && degreeSecond <= 90) {
                            x = sqrt(pow(apogee, 2) / ((pow(a, 2) + 1)));
                        }
                        else {
                            x = -sqrt(pow(apogee, 2) / ((pow(a, 2) + 1)));
                        }
                        if (a >= 100000 || a <= -100000) {
                            a = 0;
                        }
                        xFloor = round(x * pow(10, 14)) / pow(10, 14);
                        y = sqrt(pow(apogee, 2) - pow(xFloor, 2));
                        if (degreeSecond >= -180 && degreeSecond <= 0) {
                            y = -(sqrt(pow(apogee, 2) - pow(xFloor, 2)));
                        }
                        yFloor = round(y * pow(10, 13)) / pow(10, 13);
                        ylist.push_back(yFloor);
                        xlist.push_back(yFloor);
                    }
                    Orbit initial = MakeNewOrbit("Initial", perigeeRadius, perigeeRadius, 0, 0);
                    Orbit final = MakeNewOrbit("Final", apogeeRadius, apogeeRadius, 0, 0);
                    Orbit hohmann = MakeNewOrbit("Hohmann", apogeeRadius, perigeeRadius, 0, 0);
                    //auto it = xlist.begin(); tak się wywołuje wartość z listy
                    //advance(it, 1);
                    //cout << *it;
                }
            }
            else if (lowercase(variantType) == "yes") {
                inputVariant2:cout << "\nIf you want the orbit to have a rotation period of your choice, enter: 1\n";
                cout << "If you want the orbit to have the selected height, enter: 2\n";
                cout << "If you want the orbit to have lowest height for network on the chosen number of satellites, enter: 3\n";
                cout << "If you want the orbit to be synchronous orbit, enter: 4\n\n" << "Please select a variant: ";
                cin >> variant2;
                cin.ignore(100, '\n');
                if (variant2 == 1) {
                    cout << "\nRotation time of " << Element.name << "around its axis: " << Element.axis_period << "hours\n";
                    cout << "Enter the target satellites rotation period: ";
                    cin >> period;
                    cin.ignore(100, '\n');
                    periodSecond = pow((period * 60 * 60), 2);
                    gravitationalParameter = (Element.mass * constant_G);
                    apogeeConstant = ((periodSecond * gravitationalParameter) / (4 * pow(constantPI, 2)));
                    apogee = (pow(apogeeConstant, (1.0 / 3)) - (Element.radius));
                    apogeeRadius = (pow(apogeeConstant, (1.0 / 3)));
                    if (apogee >= Element.atmosphere) {
                        cout << "Height of the circular orbit is: " << round(apogee) << "meters above sea level\n";
                    }
                    else {
                        cout << "Height of circular orbit is in atmosphere";
                        break;
                    }
                    if (apogee > SOI) {
                        cout << ("Height of circular orbit is out of SOI");
                        break;
                    }
                    cout << ("How many satellites do you want to orbit: ");
                    cin >> satellite;
                    cin.ignore(100, '\n');
                    someConstant = (pow((period * 60 * 60 * (satellite - 1)), 2) / pow(satellite, 2));
                    apogeeSecond = (someConstant * gravitationalParameter / (4 * pow(constantPI, 2)));
                    apogeeSecond = (pow(apogeeSecond, (1.0 / 3)));
                    perigee = (((2 * apogeeSecond) - apogeeRadius) - (Element.radius));
                    someConstant = (pow((period * 60 * 60 * (satellite + 1)), 2) / pow(satellite, 2));
                    apogeeSecond = (someConstant * gravitationalParameter / (4 * pow(constantPI, 2)));
                    apogeeSecond = (pow(apogeeSecond, (1.0 / 3)));
                    perigee = (((2 * apogeeSecond) - apogeeRadius) - (Element.radius));
                    cout << "Initial orbit apogee: " << round(perigee) << " meters above sea level\n";
                    if (perigee > SOI) {
                        cout << ("Apogee of orbit is out of SOI");
                        break;
                    }
                    apogeeFinal = (((apogee + perigee) / 2) + Element.radius);
                    velocityApogee = pow(((constant_G * Element.mass) * ((2 / apogeeRadius) - (1 / apogeeFinal))), 0.5);
                    perigeeRadius = (perigee + Element.radius);
                    velocityPerigee = pow(((constant_G * Element.mass) * ((2 / perigeeRadius) - (1 / apogeeFinal))), 0.5);
                    velocity = pow(((constant_G * Element.mass) / apogeeRadius), 0.5);
                    cout << "delta-v required = " << abs(velocityApogee - velocity) << endl;
                }
                else if (variant2 == 2) {
                    cout << "\nRotation time of " << Element.name << "around its axis: " << Element.axis_period << "hours\n";
                    cout << "Enter altitude of target orbit for the satellites in meters: ";
                    cin >> apogee;
                    cin.ignore(100, '\n');
                    gravitationalParameter = (Element.mass * constant_G);
                    period = (((4 * pow(constantPI, 2)) * (pow((apogee + Element.radius), 3))) / (gravitationalParameter));
                    apogeeRadius = apogee + Element.radius;
                    if (apogee >= Element.atmosphere) {
                        cout << "Height of the circular orbit is: " << round(apogee) << " meters above sea level\n";
                    }
                    else {
                        cout << "Height of circular orbit is in atmosphere";
                        break;
                    }
                    if (apogee > SOI) {
                        cout << ("Height of circular orbit is out of SOI");
                        break;
                    }
                    cout << ("How many satellites do you want to orbit: ");
                    cin >> satellite;
                    cin.ignore(100, '\n');
                    someConstant = ((period * pow((satellite + 1), 2)) / pow(satellite, 2));
                    apogeeSecond = (someConstant * gravitationalParameter / (4 * pow(constantPI, 2)));
                    apogeeSecond = (pow(apogeeSecond, (1.0 / 3)));
                    perigee = (((2 * apogeeSecond) - apogeeRadius) - (Element.radius));
                    cout << "Initial orbit apogee: " << round(perigee) << " meters above sea level\n";
                    if (perigee > SOI) {
                        cout << ("Apogee of orbit is out of SOI");
                        break;
                        }
                    apogeeRadius = (apogee + Element.radius);
                    apogeeFinal = (((apogee + perigee) / 2) + Element.radius);
                    velocityApogee = pow(((constant_G * Element.mass) * ((2 / apogeeRadius) - (1 / apogeeFinal))), 0.5);
                    perigeeRadius = (perigee + Element.radius);
                    velocityPerigee = pow(((constant_G * Element.mass) * ((2 / perigeeRadius) - (1 / apogeeFinal))), 0.5);
                    velocity = pow(((constant_G * Element.mass) / apogeeRadius), 0.5);
                    cout << "delta-v required = " << abs(velocityApogee - velocity) << endl;
                }
                else if (variant2 == 3) {
                    cout << "\nRotation time of " << Element.name << "around its axis " << Element.axis_period << " hours\n";
                    gravitationalParameter = (Element.mass * constant_G);
                    inputSatellite2:cout << ("How many satellites do you want to orbit: ");
                    cin >> satellite;
                    cin.ignore(100, '\n');
                    angleDegree = 90 - ((((satellite - 2) * 180)) / (2 * satellite));
                    angleRadian = (angleDegree * 2 * constantPI) / 360;
                    apogee = (Element.radius / cos(angleRadian)) - Element.radius;
                    period = (((4 * pow(constantPI, 2)) * (pow((apogee + Element.radius), 3))) / (gravitationalParameter));
                    if ((apogee >= Element.atmosphere) && (satellite > 2)) {
                        apogeeRadius = apogee + Element.radius;
                        someConstant = ((period * pow((satellite + 1), 2)) / pow(satellite, 2));
                        apogeeSecond = (someConstant * gravitationalParameter / (4 * pow(constantPI, 2)));
                        apogeeSecond = (pow(apogeeSecond, (1.0 / 3)));
                        perigee = (((2 * apogeeSecond) - apogeeRadius) - (Element.radius));
                        cout << "The height of the circular orbit and the perigee of the initial orbit is: " << round(apogee) << " meters above sea level\n";
                        if (apogee > SOI) {
                            cout << "Height of circular orbit is out of SOI\n";
                            break;
                        }
                        cout << "Initial orbit Apogee: " << round(perigee) << " meters above sea level\n";
                        if (perigee > SOI) {
                            cout << "Apogee of orbit is out of SOI\n";
                            break;
                        }
                        apogeeFinal = (((apogee + perigee) / 2) + Element.radius);
                        velocityApogee = pow(((constant_G * Element.mass) * ((2 / apogeeRadius) - (1 / apogeeFinal))), 0.5);
                        perigeeRadius = (perigee + Element.radius);
                        velocityPerigee = pow(((constant_G * Element.mass) * ((2 / perigeeRadius) - (1 / apogeeFinal))), 0.5);
                        velocity = pow(((constant_G * Element.mass) / apogeeRadius), 0.5);
                        cout << "delta-v required = " << abs(velocityApogee - velocity) << endl;
                    }
                    else {
                        cout << "Wrong number of satellites to make perfect network select fewer/more satellites\n";
                        goto inputSatellite2;
                    }
                }
                else if (variant2 == 4) {
                    if (Element.synchronus < SOI) {
                        cout << "\nRotation time of " << Element.name << "around its axis " << Element.axis_period << " hours\n";
                        apogee = Element.synchronus;
                        gravitationalParameter = (Element.mass * constant_G);
                        period = (((4 * pow(constantPI, 2)) * (pow((apogee + Element.radius), 3))) / (gravitationalParameter));
                        apogeeRadius = apogee + Element.radius;
                        if (apogee >= Element.atmosphere) {
                            someConstant = ((period * pow((satellite + 1), 2)) / pow(satellite, 2));
                            apogeeSecond = (someConstant * gravitationalParameter / (4 * pow(constantPI, 2)));
                            apogeeSecond = (pow(apogeeSecond, (1.0 / 3)));
                            perigee = (((2 * apogeeSecond) - apogeeRadius) - (Element.radius));
                            cout << "Initial orbit apogee: " << round(perigee) << " meters above sea level\n";
                            if (perigee > SOI) {
                                cout << ("Apogee of orbit is out of SOI");
                                break;
                            }
                            apogeeFinal = (((apogee + perigee) / 2) + Element.radius);
                            velocityApogee = pow(((constant_G * Element.mass) * ((2 / apogeeRadius) - (1 / apogeeFinal))), 0.5);
                            perigeeRadius = (perigee + Element.radius);
                            velocityPerigee = pow(((constant_G * Element.mass) * ((2 / perigeeRadius) - (1 / apogeeFinal))), 0.5);
                            velocity = pow(((constant_G * Element.mass) / apogeeRadius), 0.5);
                            cout << "delta-v required = " << abs(velocityApogee - velocity) << endl;
                        }
                    }
                else {
                    cout << "\nHeight of synchronous orbit is out of SOI";
                    break;
                }
                }
                else {
                    cout << "\nYou have selected a variant that does not exist\n";
                    goto inputVariant2;

                }
                if ((variant2 >= 1) && (variant2 <= 4)) {
                    degree = 360 / satellite;
                    for (int n = 0; n < (satellite + 1); n++) {
                        degreeSecond = 90 - n * degree;
                        radSecond = (degreeSecond * constantPI / 180);
                        a = (tan(radSecond));
                        if (degreeSecond >= -90 && degreeSecond <= 90) {
                            x = sqrt(pow(apogee, 2) / ((pow(a, 2) + 1)));
                        }
                        else {
                            x = -sqrt(pow(apogee, 2) / ((pow(a, 2) + 1)));
                        }
                        if (a >= 100000 || a <= -100000) {
                            a = 0;
                        }
                        xFloor = round(x * pow(10, 14)) / pow(10, 14);
                        y = sqrt(pow(apogee, 2) - pow(xFloor, 2));
                        if (degreeSecond >= -180 && degreeSecond <= 0) {
                            y = -(sqrt(pow(apogee, 2) - pow(xFloor, 2)));
                        }
                        yFloor = round(y * pow(10, 13)) / pow(10, 13);
                        ylist.push_back(yFloor);
                        xlist.push_back(yFloor);
                    }
                    Orbit initial = MakeNewOrbit("Initial", perigeeRadius, perigeeRadius, 0, 0);
                    Orbit final = MakeNewOrbit("Final", apogeeRadius, apogeeRadius, 0, 0);
                    Orbit hohmann = MakeNewOrbit("Hohmann", apogeeRadius, perigeeRadius, 0, 0);
                    //auto it = xlist.begin();
                    //advance(it, 1);
                    //cout << *it;
                }
            }
            else{
                cout << "\nPlease type Yes or No !\n";
                goto inputVariantType;
            }

        }
    }
    if (Found == false) {
        cout << "\nType correct planet name !\n\n";
        goto input;
    }
    return 0;
}
