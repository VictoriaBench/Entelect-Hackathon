#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
using namespace std;

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
    int crates = vect[2];
    int bases = vect[1];
    int worms = vect[0];
    cout<<worms<<" "<<bases<<" "<<crates<<" "<<width<<" "<<height<<endl;
    vector<string> map;
    for(int i = 0;i<height;i++){
            string l;
        getline(file, l);
        map.push_back(l);
        cout<<map.back()<<endl;
    }


    return 0;
}
