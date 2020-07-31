#include <fstream>
#include <iostream>
#include <string>
#include <sstream>

using namespace std;
int main(){
    string fileline;
    string word;
    ifstream data;
    data.open("map_1.input");
    while(data){
        getline(data,fileline);
        istringstream ss(fileline);
        while(getline(ss, word,',')){
            cout << word << '\n';

        }

    }
    return(0);
}
