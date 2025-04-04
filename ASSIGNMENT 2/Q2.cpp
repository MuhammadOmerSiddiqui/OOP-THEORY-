#include<iostream>
#include<string>
using namespace std;

class ghost {
protected:
    string name;
    int scareLevel;
public:
    ghost(string n, int scare) {
        name = n;
        scareLevel = scare;
    }
    virtual void haunt() const = 0;

    int getScareLevel() const {
        return scareLevel;
    }

    friend ostream& operator<<(ostream& os, const ghost& g) {
        os << g.name << " (Scare Level: " << g.scareLevel << ")";
        return os;
    }

    virtual ~ghost() {}
};

class ultepaonwalichurail : public ghost {
public:
    ultepaonwalichurail() : ghost("", 0) {
        name = "Specter";
        scareLevel = 6;
    }

    void haunt() const override {
        cout << name << " hovers eerily!\n";
    }
};

class pichalperi : public ghost {
public:
    pichalperi() : ghost("", 0) {
        name = "Wraith";
        scareLevel = 8;
    }

    void haunt() const override {
        cout << name << " glides silently through walls!\n";
    }
};

class banshee : public ghost {
public:
    banshee() : ghost("", 0) {
        name = "Banshee";
        scareLevel = 7;
    }

    void haunt() const override {
        cout << name << " screams with an ear-piercing wail!\n";
    }
};

class karsazkidulhan : public ghost {
public:
    karsazkidulhan() : ghost("", 0) {
        name = "Revenant";
        scareLevel = 9;
    }

    void haunt() const override {
        cout << name << " rises from the ground in fury!\n";
    }
};

class poltergeist : public ghost {
public:
    poltergeist() : ghost("", 0) {
        name = "Poltergeist";
        scareLevel = 5;
    }

    void haunt() const override {
        cout << name << " throws objects around wildly!\n";
    }
};

class visitor {
    string name;
    int bravery;
public:
    visitor(string n, int b) {
        name = n;
        bravery = b;
    }

    void react(const ghost& g) const {
        int scare = g.getScareLevel();
        if (scare < bravery - 2) cout << name << " chuckles at the ghost!\n";
        else if (scare > bravery + 2) cout << name << " screams and runs away!\n";
        else cout << name << " trembles in fear!\n";
    }

    string getName() const {
        return name;
    }
};

class hauntedhouse {
    string houseName;
    ghost* ghosts[5];
    int ghostCount;

public:
    hauntedhouse(string name) {
        houseName = name;
        ghostCount = 0;
    }

    void addghost(ghost* g) {
        if (ghostCount < 5) {
            ghosts[ghostCount] = g;
            ghostCount++;
        }
    }

    void runsimulation(visitor visitors[], int visitorCount) {
        cout << "\nWelcome to " << houseName << "!\n";

        for (int i = 0; i < visitorCount; i++) {
            cout << "\nVisitor " << visitors[i].getName() << " enters...\n";
            for (int j = 0; j < ghostCount; j++) {
                ghosts[j]->haunt();
                visitors[i].react(*ghosts[j]);
            }
        }
        cout << "\nEnd of " << houseName << " Visit\n";
    }

    ~hauntedhouse() {
        for (int i = 0; i < ghostCount; i++) delete ghosts[i];
    }
};

void visit(visitor visitors[], int count, hauntedhouse& house) {
    house.runsimulation(visitors, count);
}

int main() {
    cout<<"Muhammad Omer Siddiqui/n24k-0022"<<endl;
    hauntedhouse house1("bangali baba ki kothi");
    hauntedhouse house2("purani haweli");

    house1.addghost(new ultepaonwalichurail());
    house1.addghost(new pichalperi());
    house1.addghost(new banshee());

    house2.addghost(new karsazkidulhan());
    house2.addghost(new poltergeist());
    house2.addghost(new ultepaonwalichurail());

    visitor visitors[3] = {
        visitor("Omer", 3),
        visitor("ammar", 6),
        visitor("arham", 9)
    };
    visit(visitors, 3, house1);
    visit(visitors, 3, house2);
    return 0;
}
