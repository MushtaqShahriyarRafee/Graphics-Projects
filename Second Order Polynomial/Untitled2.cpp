#include<iostream>
#include<cstring>
#include<cstdlib>
using namespace std;

int main(){
    //array declaration
    int size = 100;
    string registerno[size]; //for storing register numbers
    float registance[100]; //for storing registance value

    for(int i = 0; i<=100;i++){
    string input = "";
    cout<<"Enter Register Number: ";
    cin>>input;
    if(input == "exit"){
        break;
    }
    else{
    registerno[i] = input;
    }
    input = "";
    cout<<"Enter Registance: ";
    cin>>input;
    float inputtofloat = atoi(input.c_str());
    if(input == "exit"){
        registerno[i] = "";
        break;
    }
    else{
    registance[i] = input;
    }
    cout<<endl;
    }

    //printing

   for(int i = 0; i<=size;i++){
        if(!registerno[i].empty()){
        cout<<"Register: "<<registerno[i]<<endl;
        cout<<"Registance: "<<registance[i]<<endl;
        cout<<endl;
        }
    }

    return 0;
}
