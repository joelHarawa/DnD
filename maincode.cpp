#include <iostream>
#include <vector>
#include <string>
#include <fstream>
using namespace std;
class Noble;

class Warrior {
private:
    const string warrior_name;
    double warrior_strength;
    bool hired = false;
    Noble* my_noble;
public:
    Warrior(const string& name, double strength);
    const string& get_name();
    bool set_hire(bool h);
    bool get_hire();
    double get_strength();
    void set_strength(double s);
    void runaway();
    bool isHired();
    void set_noble(Noble* n);
};

class Noble {
private:
    vector<Warrior*> my_warriors;
    const string noble_name;
    bool alive;
public:
    Noble(const string& name);
    void hire(Warrior& new_warrior);
    void fire(Warrior& fire_warrior);
    void battle(Noble& the_opps);
    const string& get_name();
    void kick(Warrior& W);
    friend ostream& operator<<(ostream& n_out, const Noble& N);

};
//Noble methods
Noble::Noble(const string& name): noble_name(name), my_warriors(), alive(true) {}
void Noble::hire(Warrior& new_warrior){
    if (!new_warrior.get_hire() && alive) {
        new_warrior.set_hire(true);
        my_warriors.push_back(&new_warrior);
        new_warrior.set_noble(this);
    }
}

void Noble::kick(Warrior& fire_warrior) {
    bool found = false;
    Warrior* temp_warrior;
    for (size_t i=0; i < my_warriors.size()-1; i++) {
        if (&fire_warrior == my_warriors[i]) {
            found = true;
            temp_warrior = my_warriors[i];
            my_warriors[i] = my_warriors[i + 1];
            my_warriors[i + 1] = temp_warrior;
        }
    }
    if (found) {
        my_warriors.pop_back();
        fire_warrior.set_hire(false);
    }
}

void Noble::fire(Warrior& fire_warrior) {
    cout << "You don't work for me anymore " << fire_warrior.get_name()
         << "! -- " << noble_name << "\n";
    kick(fire_warrior);
}

void Noble::battle(Noble& the_opps) {
    cout << noble_name << " battles " << the_opps.noble_name << "\n";
    double my_strength = 0;
    double opp_strength = 0;
    for (size_t my_army = 0; my_army < my_warriors.size(); my_army++) {
        my_strength += my_warriors[my_army]->get_strength();
    }
    for (size_t opp_army = 0; opp_army < the_opps.my_warriors.size(); opp_army++) {
        opp_strength += the_opps.my_warriors[opp_army]->get_strength();
    }
    if (my_strength == 0 && opp_strength == 0) {
        cout << "Oh NO! They're both dead! Yuck!\n";
    }
    else if (my_strength > opp_strength) {
        if (opp_strength == 0) {
            cout << "He's dead, " << noble_name << "\n";
        }
        cout << noble_name << " defeats " << the_opps.noble_name << "\n";
        double damage = 1-(opp_strength/my_strength);
        for (size_t x=0; x < my_warriors.size(); x++) {
            my_warriors[x]->set_strength(damage*my_warriors[x]->get_strength());
        }
        for (size_t y=0; y < the_opps.my_warriors.size(); y++) {
            the_opps.my_warriors[y]->set_strength(0);
        }
        the_opps.alive = false;

    } else if (my_strength < opp_strength) {
        if (my_strength == 0) {
            cout << "He's dead, " << the_opps.noble_name << "\n";
        }
        cout << the_opps.noble_name << " battles " << noble_name << "\n";
        double damage = 1-(my_strength/opp_strength);
        for (size_t x = 0; x < my_warriors.size(); x++) {
            the_opps.my_warriors[x]->set_strength(damage*the_opps.my_warriors[x]->get_strength());
        }
        for (size_t y = 0; y < the_opps.my_warriors.size(); y++) {
            my_warriors[y]->set_strength(0);
        }
        alive = false;

    }  else if (my_strength == opp_strength) {
        cout << "Mutual Annihilation: " << the_opps.noble_name << " and " << noble_name
             << " die at each other's hands\n";
        for (size_t x = 0; x < the_opps.my_warriors.size(); x++) {
            the_opps.my_warriors[x]->set_strength(0);
        }
        for (size_t y = 0; y < my_warriors.size(); y++) {
            my_warriors[y]->set_strength(0);
        }
        alive = false;
        the_opps.alive = false;
    }
}
const string& Noble::get_name() {return noble_name;}
ostream& operator<<(ostream& n_out, const Noble& N) {
    n_out << N.noble_name << " has an army of " << N.my_warriors.size() << endl;
    for (Warrior* W: N.my_warriors) {
        n_out << "\t" << W->get_name() << ": " << W->get_strength() << endl;
    }
    return n_out;
}


// Warrior methods
Warrior::Warrior(const string &name, double strength): warrior_name(name),
                                                       warrior_strength(strength) {}
const string&  Warrior::get_name() {return warrior_name;}
bool Warrior::set_hire(bool h) {hired = h;}
bool Warrior::get_hire() {return hired;}
double Warrior::get_strength() {return warrior_strength;}
void  Warrior::set_strength(double s) {warrior_strength = s;}
void Warrior::runaway() {
    cout << warrior_name << " flees in terror, abandoning his lord"
    << my_noble->get_name();
    my_noble->kick(*this);
}
bool Warrior::isHired() {return hired;}
void Warrior::set_noble(Noble *nob) {my_noble = nob;}

int main() {
    Noble art("King Arthur");
    Noble lance("Lancelot du Lac");
    Noble jim("Jim");
    Noble linus("Linus Torvalds");
    Noble billie("Bill Gates");

    Warrior cheetah("Tarzan", 4);
    Warrior sky("Leia", 6);
    Warrior wizard("Merlin", 9);
    Warrior jaffa("Teal'c", 9);
    Warrior theGovernator("Conan", 12);
    Warrior nimoy("Spock", 15);
    Warrior lawless("Xena", 20);
    Warrior mrGreen("Hulk", 8);
    Warrior dylan("Hercules", 3);

    jim.hire(nimoy);
    lance.hire(theGovernator);
    art.hire(jaffa);
    art.hire(cheetah);
    art.hire(wizard);
    art.hire(sky);
    lance.hire(dylan);
    linus.hire(lawless);
    billie.hire(mrGreen);
    art.hire(nimoy);

    cout << "================ Initial Status ===============" << endl;
    cout << art << endl
         << lance << endl
         << jim << endl
         << linus << endl
         << billie << endl;
    cout << "===============================================\n\n";

    art.fire(cheetah);
    wizard.runaway();
    cout << endl << art << endl;

    art.battle(lance);
    jim.battle(lance);
    linus.battle(billie);
    billie.battle(lance);

    cout << "\n================ Final Status ===============" << endl;
    cout << art << endl
         << lance << endl
         << jim << endl
         << linus << endl
         << billie << endl;

    // Tarzan and Merlin should be unemployed
    cout << "Tarzan's Hire Status: " << boolalpha
         << cheetah.isHired() << endl;
    cout << "Merlin's Hire Status: " << boolalpha
         << wizard.isHired() << endl;
    cout << "===============================================\n\n";

    return 0;
}