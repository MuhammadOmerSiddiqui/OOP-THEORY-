#include <iostream>
#include <string>
#include <cstdlib> 

using namespace std;

class Vehicle {
protected:
    string vehicleid;
    int speed; 
    int capacity;  
    double efficiency; 

public:
    Vehicle(string id, int spd, int cap, double eff)
        : vehicleid(id), speed(spd), capacity(cap), efficiency(eff) {}

    virtual void deliver() = 0; 
    virtual void move() = 0; 

    bool operator==(const Vehicle &v) {
        return (this->efficiency == v.efficiency);
    }
    friend void resolveconflict(Vehicle &v1, Vehicle &v2);
    
    string getid() { return vehicleid; }
    int getspeed() { return speed; }
    int getcapacity() { return capacity; }
    double getefficiency() { return efficiency; }

    virtual ~Vehicle() {}
};


class ramazandrone : public Vehicle {
public:
    ramazandrone(string id) : Vehicle(id, 150, 10, 15.0) {} 

    void deliver() override {
        cout << "Drone " << vehicleid << " is delivering small iftar meals.\n";
    }

    void move() override {
        cout << "Drone " << vehicleid << " is flying in the air.\n";
    }
};

class ramazantimeship : public Vehicle {
public:
    ramazantimeship(string id) : Vehicle(id, 50, 200, 5.0) {}

    void deliver() override {
        cout << "TimeShip " << vehicleid << " is delivering food through time.\n";
    }

    void move() override {
        cout << "TimeShip " << vehicleid << " is traveling through time.\n";
    }
};

class ramazanhyperpod : public Vehicle {
public:
    ramazanhyperpod(string id) : Vehicle(id, 300, 1000, 12.0) {}

    void deliver() override {
        cout << "HyperPod " << vehicleid << " is delivering large iftar packages.\n";
    }

    void move() override {
        cout << "HyperPod " << vehicleid << " is speeding through underground tunnels.\n";
    }
};

void resolveconflict(Vehicle &v1, Vehicle &v2) {
    if (v1 == v2) {
        cout << "Both vehicles " << v1.getid() << " and " << v2.getid() << " have equal efficiency.\n";
    } else {
        cout << "Choosing the more efficient vehicle based on efficiency:\n";
        if (v1.getefficiency() > v2.getefficiency()) {
            cout << "Vehicle " << v1.getid() << " is more efficient.\n";
        } else {
            cout << "Vehicle " << v2.getid() << " is more efficient.\n";
        }
    }
}

int main() {
    cout<<"Muhammad Omer Siddiqui/n24k-0022"<<endl;
    ramazandrone drone1("Drone 01");
    ramazantimeship timeShip1("TimeShip 01");
    ramazanhyperpod hyperPod1("HyperPod 01");

    drone1.deliver();
    timeShip1.deliver();
    hyperPod1.deliver();

    drone1.move();
    timeShip1.move();
    hyperPod1.move();

    resolveconflict(drone1, timeShip1);
    resolveconflict(timeShip1, hyperPod1);
    resolveconflict(drone1, hyperPod1);

    return 0;
}
