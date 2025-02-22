#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <vector>
#include <algorithm>
using namespace std;

//Makes a struct for Pokémon with their details
struct Pokemon
{
    int pokedex;
    int generation;
    string name;
    string type;
    int hp;
    int attack;
    int defense;
    double height;
    double weight;
    string region;
    string ability;
};

//Method to display the Pokémon given
void displayPokemon(const Pokemon &p) {
    cout << left //Print on the left side
    << setw(5) << p.pokedex //set the field width to be 5 characters
    << setw(2) << p.generation
    << setw(20) << p.name
    << setw(10) << p.type
    << setw(5) << p.hp
    << setw(5) << p.attack
    << setw(5) << p.defense
    << setw(5) << p.height
    << setw(5) << p.weight
    << setw(20) << p.region
    << setw(20) << p.ability
    <<endl;
}

//Method to read the lines
void parseLine(string line, Pokemon &poke)
{
    string temp; //Temp for values that are not strings
    stringstream ss(line);//String stream to hold the line

    //Get the line up until the comma
    getline(ss, temp, ','); //asign it to the temp
    poke.pokedex = stoi(temp);//convert it to an integer and assign it to the Pokédex value of a Pokémon

    getline(ss, temp, ',');
    poke.generation = stoi(temp);

    getline(ss, poke.name, ',');

    getline(ss, poke.type, ',');

    getline(ss, temp, ',');
    poke.hp = stoi(temp);

    getline(ss, temp, ',');
    poke.attack = stoi(temp);

    getline(ss, temp, ',');
    poke.defense = stoi(temp);

    getline(ss, temp, ',');
    poke.height = stod(temp);//Convert it to a decimal and assign it to height

    getline(ss, temp, ',');
    poke.weight = stod(temp);

    getline(ss, poke.region, ',');

    getline(ss, poke.ability, ',');

}

void load(string fname, vector<Pokemon> &data)
{
    //Open the filename assigned to fname
    ifstream fin(fname);

    //Check if fin is true (it opened)
    if(fin)
    {
        string line; //Variable to store the line
        while(getline(fin, line)) //Get lines until there are no more
        {
            Pokemon poke; //Pokémon struct to hold the data
            parseLine(line, poke); //Call parseLine to store the data in a Pokémon struct
            data.push_back(poke); //Add the Pokémon to the data vector
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
    vector<Pokemon> p;
    string fname = "C:/Users/sophi/CLionProjects/CPP_2025_CA1_SD/pokemon.csv";

    load(fname, p);
    for (const Pokemon &pokemon : p) {
        displayPokemon(pokemon);
    }


    return 0;
}