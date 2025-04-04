#include <iostream>
#include <string>

using namespace std;

class User {
protected:
    string id, name;
    bool haspaid;
    string stopAssigned;

public:
    User(string uid, string uname) : id(uid), name(uname), haspaid(false), stopAssigned("None") {}

    virtual void payfees() = 0; 

    void assignstop(string stop) { stopAssigned = stop; }

    virtual void showdetails() {
        cout << "ID: " << id << "\nName: " << name
             << "\nTransport Paid: " << (haspaid ? "Yes" : "No")
             << "\nAssigned Stop: " << stopAssigned << endl;
    }

    bool isactive() { return haspaid; }
};

class Student : public User {
public:
    Student(string id, string name) : User(id, name) {}

    void payfees() override {
        haspaid = true;
        cout << name << " has paid semester fees. Transportation card activated.\n";
    }
};

class Teacher : public User {
public:
    Teacher(string id, string name) : User(id, name) {}

    void payfees() override {
        haspaid = true;
        cout << name << " has paid monthly transport fees.\n";
    }
};

class staffmember : public User {
public:
    staffmember(string id, string name) : User(id, name) {}

    void payfees() override {
        haspaid = true;
        cout << name << " has paid a discounted monthly transport fee.\n";
    }
};

class busroute {
private:
    string routename;
    string stops[3];

public:
    busroute(string name, string s1, string s2, string s3) : routename(name) {
        stops[0] = s1;
        stops[1] = s2;
        stops[2] = s3;
    }

    void showstops() {
        cout << "Route: " << routename << "\nStops: " << stops[0] << ", " << stops[1] << ", " << stops[2] << endl;
    }

    string getstop(int index) { return stops[index]; }

    bool operator==(const busroute &other) {
        return routename == other.routename &&
               stops[0] == other.stops[0] &&
               stops[1] == other.stops[1] &&
               stops[2] == other.stops[2];
    }
};

class transportsystem {
private:
    User *registereduser;
    busroute *routes[2];

public:
    transportsystem() {
        registereduser = nullptr;
        routes[0] = new busroute("Route A", "Stop 1", "Stop 2", "Stop 3");
        routes[1] = new busroute("Route B", "Stop A", "Stop B", "Stop C");
    }

    void registerUser(string id, string name, int type) {
        if (registereduser) {
            delete registereduser; 
        }

        switch (type) {
            case 1:
                registereduser = new Student(id, name);
                break;
            case 2:
                registereduser = new Teacher(id, name);
                break;
            case 3:
                registereduser = new staffmember(id, name);
                break;
            default:
                cout << "Invalid type!\n";
                return;
        }
        cout << name << " registered successfully!\n";
    }

    void payfees() {
        if (registereduser) {
            registereduser->payfees();
        } else {
            cout << "No user registered!\n";
        }
    }

    void showavailableroutes() {
        for (int i = 0; i < 2; i++) {
            routes[i]->showstops();
        }
    }

    void assignroutes(int routeindex, int stopindex) {
        if (!registereduser) {
            cout << "No user registered!\n";
            return;
        }

        if (routeindex < 1 || routeindex > 2 || stopindex < 1 || stopindex > 3) {
            cout << "Invalid choice!\n";
            return;
        }

        registereduser->assignstop(routes[routeindex - 1]->getstop(stopindex - 1));
        cout << "Stop assigned successfully!\n";
    }

    void chackattendence() {
        if (registereduser && registereduser->isactive()) {
            registereduser->showdetails();
            cout << "Attendance Recorded!\n";
        } else {
            cout << "User has not paid fees! No access to transportation.\n";
        }
    }

    ~transportsystem() {
        delete registereduser;
        for (int i = 0; i < 2; i++) {
            delete routes[i];
        }
    }
};

int main() {
    transportsystem system;
    cout<<"Muhammad Omer Siddiqui/n24k-0022"<<endl;

    int usertype;
    cout << "Enter user type (1-Student, 2-Teacher, 3-Staff): ";
    cin >> usertype;

    system.registerUser("0022", "Omer", usertype);
    system.payfees();
    system.showavailableroutes();

    int routechoice, stopchoice;
    cout << "Enter route number (1-2): ";
    cin >> routechoice;
    cout << "Enter stop number (1-3): ";
    cin >> stopchoice;

    system.assignroutes(routechoice, stopchoice);
    system.chackattendence();

    busroute route1("Route C", "Stop X", "Stop Y", "Stop Z");
    busroute route2("Route C", "Stop X", "Stop Y", "Stop Z");
    if (route1 == route2) {
        cout << "The two routes are identical!\n";
    } else {
        cout << "The routes are different!\n";
    }

    return 0;
}
