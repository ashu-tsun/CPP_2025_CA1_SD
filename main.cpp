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

void displayHeaders() {
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

void displayAllCharacters(const vector<Character> &c) {
    displayHeaders();

    //Display the characters
    for (const Character &chara : c) {
        displayCharacter(chara);
    }
}

int indexByName(const vector <Character> &c, const string &name) {
    for (int i = 0; i<c.size();i++) { //Loop through character vector
        if ( c[i].name == name) { //if the name matches the input
            cout << "\nIndex of " << name <<" is " << i << endl;
            return i; //return the index
        }
    }
    cout << "\nName not found in data"<< endl;
    return -1; //If name not found then return -1
}

//I had a look at : https://www.geeksforgeeks.org/map-associative-containers-the-c-standard-template-library-stl/
// and https://www.w3schools.com/cpp/cpp_maps.asp
//To help understand the logic for adding a printing results
map<string, int> countByLocation(const vector<Character> &c, const string &location) {
    map<string, int> locationMap;
    for (const Character &chara : c) {
        //If the location matches what we're looking for
        if (chara.location == location) {
            //add and increase the count for that location
            locationMap[chara.location]++;
        }
    }
    return locationMap;
}

void displayLocationMap(map<string, int> locationMap) {
    bool notEmpty = false;

    for (auto count : locationMap) {
        cout << "The count for this location is: " << endl;
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
        displayHeaders();
        for (const Character &chara : c) {
            if (chara.aggressive == aggresive) {
                displayCharacter(chara);
            }
        }
    }
    else{
        cout << "Sorry, there was no data with that aggression type" << endl;
    }
}

int highestLowestAverageGold(const vector<Character> &c) {
    Character max = c[0]; //Setting max and min to be able to check values
    Character min = c[0];
    int sum = 0;
    for (const Character& chara : c) { //loop through characters and get total of gold
        sum += chara.gold;

        if (chara.gold>max.gold) { //if the gold is higher than the last max saved assign it as the new max
            max = chara;
        }
        else if (chara.gold<min.gold) {
            min = chara;
        }
    }
    //Get the average
    const int avg = sum/c.size();
    //Display the Max and Min values
    cout << "Highest Gold given by: " << endl;
    displayHeaders();
    displayCharacter(max);
    cout << "Lowest Gold given by: " << endl;
    displayHeaders();
    displayCharacter(min);
    return avg;
}

int highestLowestAverageXP(const vector<Character> &c) {
    Character max = c[0]; //Setting max and min to be able to check values
    Character min = c[0];
    int sum = 0;
    for (const Character& chara : c) { //loop through characters and get total of xp
        sum += chara.xp;

        if (chara.xp>max.xp) { //if the xp is higher than the last max saved assign it as the new max
            max = chara;
        }
        else if (chara.xp<min.xp) {
            min = chara;
        }
    }
    //Get the average
    const int avg = sum/c.size();
    //Display the Max and Min values
    cout << "Highest XP given by: " << endl;
    displayHeaders();
    displayCharacter(max);
    cout << "\nLowest XP given by: " << endl;
    displayHeaders();
    displayCharacter(min);
    return avg;
}

vector<Character> searchByNameSubstring(const vector<Character> &c, const string &name) {
    vector<Character> result;
    cout << "Characters names with : " << name << endl;
    //Had a look for substring searching: https://www.geeksforgeeks.org/string-find-in-cpp/
    //Using iterators to loop through the vector
    for (auto it = c.begin(); it != c.end(); it++) {
        //If the inputted name is found in the  reference of the name
        if ((*it).name.find(name) != string::npos) //The find function will return string::npos if it is not found in the name
        {
            //Add the character to the result
            result.push_back(*it);
        }
    }
    return result;
}

void displaySubstringSubset(const vector<Character> &c) {
    //Print the headers if the subset will work
    if (!c.empty()) {
        displayHeaders();
        for (const Character &chara : c) {
            displayCharacter(chara);
        }
    }
    else{
        cout << "Sorry, there was no data with that text" << endl;
    }
}

void sortByHeight(const vector<Character> &c) {
    vector <Character> sorted = c;//Store a copy of the characters as we are using a reference that cannot be changed
    auto func =[](Character c1, Character c2){return c1.height > c2.height;};//Lamda sorting function
    sort(sorted.begin(), sorted.end(), func); //Sorting using the lamda function

    displayAllCharacters(sorted);//Display the sorted characters
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
    cout << "\nEnter Character Name to search: (e.g Gaster, Papyrus, Temmie)\n";
    //Read in input and assign it to name
    getline(cin,name);
    //Use the name to search
    indexByName(c,name);


    //Stage 3 part 3
    string location;
    cout << "\nEnter Character Location to search: (e.g Hotland, Ruins, Snowdin)\n";
    getline(cin,location);
    displayLocationMap(countByLocation(c, location));

    //Stage 3 part 4
    string aggressive;
    cout << "\nEnter the Aggressive subset you are looking for (e.g Yes, No)\n";
    cin >> aggressive;
    //Since I was mixing cin and newline, the input stream was not taking in new values, so I looked up something similar to clearing the scanner in java
    //https://www.geeksforgeeks.org/cin-ignore-function-in-cpp/?ref=ml_lbp
    cin.ignore(); //Ignores certain amounts of characters to allow for the next input to work
    displayAggressiveSubset(c, aggressive);

    //Stage 3 part 5
    cout << "\nThe Maximum, Minimum and Average of gold dropped by characters:\n";
    int avgGold = highestLowestAverageGold(c);
    cout << "\nThe average gold drop is: " << avgGold << endl;

    cout << "\nThe Maximum, Minimum and Average of XP dropped by characters:\n";
    int avgXP = highestLowestAverageXP(c);
    cout << "The average XP drop is: " << avgXP << endl;

    //Stage 3 part 6
    string search;
    cout << "\nEnter a name or part of a name of a character" << endl;
    getline(cin, search);
    displaySubstringSubset(searchByNameSubstring(c,search));

    //Stage 3 part 7
    cout <<"\nDisplaying all characters descending by height:\n";
    sortByHeight(c);
    return 0;
}