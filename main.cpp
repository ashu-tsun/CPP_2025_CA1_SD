#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <map>
using namespace std;

//Makes a struct for Characters with their details
struct Character
{
    int id;
    string name;
    int hp;
    int attack;
    int defense;
    int xp;
    int gold;
    double height;
    string location;
    string aggressive;
};

//Method to display the Character given
void displayCharacter(const Character &c) {
    cout << left //Print on the left side
    << setw(4) << c.id
    << setw(25) << c.name //set the field width to be 5 characters
    << setw(10) << c.hp
    << setw(10) << c.attack
    << setw(10) << c.defense
    << setw(10) << c.xp
    << setw(10) << c.gold
    << setw(10) << c.height
    << setw(15) << c.location
    << setw(5) << c.aggressive
    <<endl;
}

void displayAllCharacters(const vector<Character> &c) {
    cout << left //Print out for data headings
    << setw(4) << "ID"
    << setw(25) << "Name"
    << setw(10) << "HP"
    << setw(10) << "Attack"
    << setw(10) << "Defense"
    << setw(10) << "XP"
    << setw(10) << "Gold"
    << setw(10) << "Height"
    << setw(15) << "Location"
    << setw(5) << "Aggressive"
    <<endl;

    //Display the characters
    for (const Character &chara : c) {
        displayCharacter(chara);
    }
}

int searchByName(const vector <Character> &c, const string &name) {
    for (int i = 0; i<c.size();i++) { //Loop through character vector
        if ( c[i].name == name) { //if the name matches the input
            return i; //return the index
        }
    }
    return -1; //If name not found then return -1
}

//I had a look at : https://www.geeksforgeeks.org/map-associative-containers-the-c-standard-template-library-stl/
// and https://www.w3schools.com/cpp/cpp_maps.asp
//To help understand the logic for adding a printing results
map<string, int> countByLocation(const vector<Character> &c, const string &location) {
    map<string, int> locationMap;
    for (const Character &chara : c) {
        if (chara.location == location) {
            locationMap[chara.location]++;
        }

    }
    return locationMap;
}

void displayLocationMap(map<string, int> locationMap) {
    bool notEmpty = false;
    for (auto count : locationMap) {
        cout << count.first << " " << count.second << endl;
        notEmpty = true;
    }
    if (!notEmpty) {
        cout << "Sorry, there was no data with that location" << endl;
    }
}

void displayAggressiveSubset(const vector<Character> &c, const string &aggresive) {
    cout << "Characters are aggressive: " << aggresive << endl;
    //Print the headers if the subset will work
    if (aggresive == "Yes" || aggresive == "No") {
        cout << left //Print out for data headings
        << setw(4) << "ID"
        << setw(25) << "Name"
        << setw(10) << "HP"
        << setw(10) << "Attack"
        << setw(10) << "Defense"
        << setw(10) << "XP"
        << setw(10) << "Gold"
        << setw(10) << "Height"
        << setw(15) << "Location"
        << setw(5) << "Aggressive"
        <<endl;
    }

    bool notEmpty = false;
    for (const Character &chara : c) {
        if (chara.aggressive == aggresive) {
            displayCharacter(chara);
            notEmpty = true;
        }
    }
    if (!notEmpty) {
        cout << "Sorry, there was no data with that aggression type" << endl;
    }
}

//Method to read the lines
void parseLine(string line, Character &chr)
{
    string temp; //Temp for values that are not strings
    stringstream ss(line);//String stream to hold the line

    //Get the line up until the comma
    getline(ss, temp, ','); //asign it to the temp
    chr.id = stoi(temp);//convert it to an integer and assign it to the Character id

    getline(ss, chr.name, ',');

    getline(ss, temp, ',');
    chr.hp = stoi(temp);

    getline(ss, temp, ',');
    chr.attack = stoi(temp);

    getline(ss, temp, ',');
    chr.defense = stoi(temp);

    getline(ss, temp, ',');
    chr.xp = stoi(temp);

    getline(ss, temp, ',');
    chr.gold = stoi(temp);

    getline(ss, temp, ',');
    chr.height = stod(temp);//Convert it to a decimal and assign it to height

    getline(ss, chr.location, ',');

    getline(ss, chr.aggressive, ',');

}

//Read csv file and populate vector of characters
void load(string fname, vector<Character> &data)
{
    //Open the filename assigned to fname
    ifstream fin(fname);

    //Check if fin is true (it opened)
    if(fin)
    {
        string line; //Variable to store the line
        while(getline(fin, line)) //Get lines until there are no more
        {
            Character ch;
            parseLine(line, ch); //Call parseLine to store the data in a Character struct
            data.push_back(ch); //Add the Character to the data vector
        }
        fin.close();
    }
    //If the file couldn't be opened/ found
    else
    {
        cout << "Error opening file." <<endl;
    }
}

int main() {
    vector<Character> c;
    string fname = "undertale.csv";



    //Stage 2
    //Load the data from csv into a vector of structs (Character)
    load(fname, c);

    //Stage 3 part 1
    //Display all characters using method
    displayAllCharacters(c);

    //Stage 3 part 2
    string name;
    cout << "Enter Character Name to search: (e.g Gaster, Papyrus, Temmie)\n";
    //Read in input and assign it to name
    cin >> name;
    //Use the name to search
    int index =searchByName(c,name);
    //If the character is not found
    if(index == -1)
        cout << "Character not found" << endl;
    else
        cout << "\nIndex of " << name <<" is " << index << endl;

    //Stage 3 part 3
    string location;
    cout << "\nEnter Character Location to search: (e.g Hotland, Ruins, Snowdin)\n";
    cin >> location;
    displayLocationMap(countByLocation(c, location));

    //Stage 3 part 4
    string aggressive;
    cout << "\nEnter the Aggressive subset you are looking for (e.g Yes, No\n";
    cin >> aggressive;
    displayAggressiveSubset(c, aggressive);


    return 0;
}