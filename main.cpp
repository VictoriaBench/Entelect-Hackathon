#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <cmath>
#include <algorithm>


using namespace std;

struct coord{
    int row=0, col=0;
};

int mDistance(coord A, coord B){
    return abs(A.row-B.row)+abs(A.col-B.col);
}




class Crate{
public:
    Crate(char id, coord crate_location, coord base_location): id(id), crate_location(crate_location), base_location(base_location){}
private:
    coord crate_location;
    coord base_location;
    char id;
    bool pickedUp=false;
public:
    int pathDistance(){
        return mDistance(crate_location, base_location);
    }
    void printCrate(){
        cout<<id<<" ("<<crate_location.row<<", "<<crate_location.col<<") --> ("<<base_location.row<<", "<<base_location.col<<")"<<"  "<<pathDistance()<<endl;
    }

    coord getBaseLocation(){
        return base_location;
    }

    coord getCrateLocation(){
        return crate_location;
    }

    char getId(){
        return id;
    }

    void pickUp(){
        pickedUp =true;
    }

    bool isPickedUp(){
        return pickedUp;
    }

};

class Worm{
private:
    coord location;
    std::vector<Crate> pickups;
public:
    void pickupCrate(Crate& crate){
        crate.pickUp();
        pickups.push_back(crate);
        location = crate.getBaseLocation();
    }

    int pathDistance(){
        int dist = 0;
        coord start;
        start.row = 0;
        start.col = 0;
        for(Crate& pickup : pickups){
            int worm2crate = mDistance(start, pickup.getCrateLocation());
            dist += worm2crate;
            int pathDist = pickup.pathDistance();
            dist += pathDist;
            start = pickup.getBaseLocation();
        }
        return dist;
    }

    string getPath(){
        stringstream ss;
        for(int i = 0;i<pickups.size();i++){
            auto crate = pickups[i];
            ss << crate.getId()<<","<<char(tolower(crate.getId()));
            if(i<pickups.size()-1){
                ss<<",";
            }else{
                ss<<" \n";
            }
        }
        return ss.str();
    }

    coord getLocation(){
        return location;
    }
};
bool cratesRemaining(const vector<Crate>& crates){
    bool allCratesPickedUp = true;
    for(auto crate:crates){
        allCratesPickedUp = allCratesPickedUp && crate.isPickedUp();
    }
    return !allCratesPickedUp;
}

int main()
{
    ifstream file("map_1.input");
    string line;
    getline(file, line);
    vector<int> vect;
    stringstream ss(line);

    for (int i; ss >> i;) {
        vect.push_back(i);
        if (ss.peek() == ',')
            ss.ignore();
    }

    int height = vect[4];
    int width = vect[3];
    int numcrates = vect[2];
    int bases = vect[1];
    int wormnum = vect[0];

    cout<<wormnum<<" "<<bases<<" "<<numcrates<<" "<<width<<" "<<height<<endl;
    vector<string> map;
    for(int i = 0;i<height;i++){
        string l;
        getline(file, l);
        map.push_back(l);
        cout<<map.back()<<endl;
    }
    string ids = "abcdefghijklmnopqrstuvwxyz";

    std::vector<Crate> crates;
    for(int i=0;i<numcrates;i++){
        coord crate_loc;
        coord base_loc;
        for(int row =0;row<height;row++){
            for(int col = 0;col<width;col++){
                char c= map[row][col];
                if(c == toupper(ids[i])){
                    crate_loc.row = height -1 - row;
                    crate_loc.col = col;
                }
                if(c==ids[i]){
                    base_loc.row = height -1-row;
                    base_loc.col = col;
                }
            }
        }
        crates.push_back(Crate(toupper(ids[i]),crate_loc, base_loc));
        crates.back().printCrate();
    }

    vector<Worm> worms;
    for(int i =0;i<wormnum;i++){
        Worm w;
        worms.push_back(w);
    }

    while(cratesRemaining(crates)){
        int min = 1000000;
        int chosenWorm;
        int chosenCrate;
        for(int i = 0;i<crates.size();i++){
            if(!crates[i].isPickedUp()){
                for(int j = 0;j<worms.size();j++){
                    int score = mDistance(worms[j].getLocation(), crates[i].getCrateLocation()) - crates[i].pathDistance();
                    if(score<min){
                        min = score;
                        chosenWorm = j;
                        chosenCrate = i;
                    }
                }
            }
        }
        worms[chosenWorm].pickupCrate(crates[chosenCrate]);
    }

    coord zero;

    for(auto& crate1 :crates){
        int dist = mDistance(crate1.getCrateLocation(), zero);
        cout<<crate1.getId()<<dist<<"\t|\t";
        for(auto& crate2: crates){
            dist = mDistance(crate1.getCrateLocation(),crate2.getBaseLocation());
            cout<<dist<<"\t|\t";
        }
        cout<<endl;
    }


    ofstream output;
    output.open("output.txt");

    int totalDistance = 0;
    for(int i = 0;i<wormnum;i++){
        int wormPath = worms[i].pathDistance();
        totalDistance += wormPath;
        output<<worms[i].getPath();
        cout<<worms[i].getPath();
    }
    cout<<"Total distance: "<<totalDistance<<endl;
    cout<<"All crates picked up: "<<(!cratesRemaining(crates)?"true":"false")<<endl;

    return 0;
}
