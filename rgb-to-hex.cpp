// RGB-to-HEX BETA

// Author: Tristan Seto
// Date: 2023-10-03
// Description: Program takes in three colour inputs (red, green, blue) from user in RGB (value between 0-255) and converts it to a 6-digit HEX CODE printed at the end of the program.


#include <iostream>
#include <string>
using namespace std;

int main(){
    int rgb[3];
    
    cout << "Enter red value: ";
    cin >> rgb[0];

    while(cin.fail() || rgb[0] < 0 || rgb[0] > 255){
        cin.clear();
        cin.ignore(1000,'\n');
        cout << "Please retry! Enter red value: ";
        cin >> rgb[0];
    }

    cout << "Enter green value: ";
    cin >> rgb[1];

    while(cin.fail() || rgb[1] < 0 || rgb[1] > 255){
        cin.clear();
        cin.ignore(1000,'\n');
        cout << "Please retry! Enter green value: ";
        cin >> rgb[1];
    }

    cout << "Enter blue value: ";
    cin >> rgb[2];

    while(cin.fail() || rgb[2] < 0 || rgb[2] > 255){
        cin.clear();
        cin.ignore(1000,'\n');
        cout << "Please retry! Enter blue value: ";
        cin >> rgb[2];
    }

    int hexNum[6];
    string hex[6];

    hexNum[0] = rgb[0] / 16;
    hexNum[1] = rgb[0] % 16;
    hexNum[2] = rgb[1] / 16;
    hexNum[3] = rgb[1] % 16;
    hexNum[4] = rgb[2] / 16;
    hexNum[5] = rgb[2] % 16;

    for(int i = 0; i < 6; i++){
        if(hexNum[i] > 0 && hexNum[i] < 10){
            hex[i] = to_string(hexNum[i]);
        } else if(hexNum[i] >= 10 && hexNum[i] < 16){
            hex[i] = 'A' - 10 + hexNum[i];
        } else {
            cerr << "Error";
            return -1;
        }
    }

    string hexCode = "#";

    for(int i = 0; i < 6; i++){
        hexCode = hexCode + hex[i];
    }

    cout << endl << "Your HEX Code: " << hexCode << endl;

    return 0;
}
