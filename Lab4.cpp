/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Lab4.cpp
 * Author: Molham Alsaati
 *
 * Created on October 11, 2021, 4:33 PM
 */

#include <iostream>
#include <fstream>
#include <sstream>
#include <cstring>
#include <cstdlib>
#include <iomanip>
#include <climits>
#include <valarray>
#include "Lab4.h"
using namespace std;

enum BloodType {A, AB, O, B};
enum Organ {heart, kidney, lung, liver};

struct PatientRecord{
    string firstName;
    string lastName;
    BloodType bloodType;
    Organ organ;
    int age;
    int yearAdded;
};

PatientRecord tokenizeAndFillup(stringstream& aStrStream, PatientRecord& tempRecord);

void processToken(int tokNum, string& tok, PatientRecord& tempRecord);

void displayRecord(PatientRecord* patientRecord, int i);

void writeFile (PatientRecord pRecord[], int num);

void writeIntoFileStream(PatientRecord pRecord[], ofstream& outputFileStream, int num);

int readFile(PatientRecord pRecord[]);

int readFromFileStream(ifstream& inputFileStream, PatientRecord pRecord[]);

int main(int argc, char* argv[]) {
    PatientRecord patientRecord[100];
    PatientRecord tempRecord;
    int i = 0; //keeps track of number of patients entered
    int option; //which option user chooses
    string aString; //user's input in the form of patient info
    
    while(argc == 1){
        cout << "=======================" << endl;
        cout << "[Organ Transplant List]" << endl;
        cout << "There are currently " << i << " patient(s) in the list";
        cout << "\n" << endl;
        
        cout << "Please choose an option: " << endl;
        cout << "1. Add Patient \n2. Show List of Patients " << endl;
        cout << "3. Save List of Patients \n4. Quit " << "\n>> ";
        cin >> option;
        
        if (option == 1){
            cout << "=============\n[Add Patient]\n";
            cout << "Please enter the Patient Record: \n" << endl;
            //ask for input, then receive input
            cin.clear(); cin.ignore(INT_MAX, '\n');
            getline(cin, aString, '\n');
            
            cout << ".. [Adding]" << endl;
            stringstream ss;
            ss.str(aString);
            
            patientRecord[i] = tokenizeAndFillup(ss, tempRecord);
            i++; //number of patients in record increased
        }
        else if (option == 2){
            displayRecord(patientRecord, i);
        }
        else if (option == 3){
            cout << "[Save List of Patients] (File: transplantPatients.txt)" << endl;
            writeFile(patientRecord, i);
        }
        else if (option == 4){
            cout << "Quitting..." << endl;
            break;
        }
    }
    
    while(argc == 2){
        i = readFile(patientRecord);
        
        cout << "=======================" << endl;
        cout << "[Organ Transplant List]" << endl;
        cout << "There are currently " << i << " patient(s) in the list";
        cout << "\n" << endl;
        
        cout << "Please choose an option: " << endl;
        cout << "1. Add Patient \n2. Show List of Patients " << endl;
        cout << "3. Save List of Patients \n4. Quit " << "\n>> ";
        cin >> option;
        
        if (option == 1){
            cout << "=============\n[Add Patient]\n";
            cout << "Please enter the Patient Record: \n" << endl;
            //ask for input, then receive input
            cin.clear(); cin.ignore(INT_MAX, '\n');
            getline(cin, aString, '\n');
            
            cout << ".. [Adding]" << endl;
            stringstream ss;
            ss.str(aString);
            
            patientRecord[i] = tokenizeAndFillup(ss, tempRecord);
            i++; //number of patients in record increased
        }
        else if (option == 2){
            displayRecord(patientRecord, i);
        }
        else if (option == 3){
            cout << "[Save List of Patients] (File: transplantPatients.txt)" << endl;
            writeFile(patientRecord, i);
        }
        else if (option == 4){
            cout << "Quitting..." << endl;
            break;
        }
    }
    
}//end of main

PatientRecord tokenizeAndFillup(stringstream& aStrStream, PatientRecord& tempRecord){
    string token;
    int tokenNumber = 1;
    
    while (aStrStream >> token){
        processToken(tokenNumber, token, tempRecord);
        tokenNumber++;
    }
    
    return tempRecord;
}

void processToken(int tokNum, string& tok, PatientRecord& tempRecord){
    if (tokNum == 1){
        tempRecord.firstName = tok;
    }
    if (tokNum == 2){
        tempRecord.lastName = tok;
    }
    if (tokNum == 3){
        if (tok.compare("A") == 0 || tok.compare("a") == 0 ){
            tempRecord.bloodType = A;
        }
        if (tok.compare("AB") == 0 || tok.compare("ab") == 0 ){
            tempRecord.bloodType = AB;
        }
        if (tok.compare("O") == 0 || tok.compare("o") == 0 ){
            tempRecord.bloodType = O;
        }
        if (tok.compare("B") == 0 || tok.compare("b") == 0 ){
            tempRecord.bloodType = B;
        }
    }
    if (tokNum == 4){
        if (tok.compare("heart") == 0 || tok.compare("Heart") == 0){
            tempRecord.organ = heart;
        }
        if (tok.compare("kidney") == 0 || tok.compare("Kidney") == 0){
            tempRecord.organ = kidney;
        }
        if (tok.compare("lung") == 0 || tok.compare("Lung") == 0){
            tempRecord.organ = lung;
        }
        if (tok.compare("liver") == 0 || tok.compare("Liver") == 0){
            tempRecord.organ = liver;
        }
    }
    if (tokNum == 5){
        tempRecord.age = atoi(tok.c_str());
    }
    if (tokNum == 6){
        tempRecord.yearAdded = atoi(tok.c_str());
    }
}

void displayRecord(PatientRecord* patientRecord, int i){
    int y;
    
    cout << "[Show List of Patients]" << endl;
    cout << "ID" << setw(19) << "Name" << setw(15) << "Blood" << setw(12);
    cout << "Organ" << setw(11) << "Age" << setw(15) << "Year added" << endl;
    cout << "-----------------------------------------------------------------";
    cout << "----------\n";
    for (y = 0; y < i; y++){

        cout << (y+1) << setw(20) << patientRecord[y].lastName << ", ";
        cout << patientRecord[y].firstName[0] << setw(10);
        if (patientRecord[y].bloodType == 0) {
            cout << "A";
        } else if (patientRecord[y].bloodType == 1) {
            cout << "AB";
        } else if (patientRecord[y].bloodType == 2) {
            cout << "O";
        } else if (patientRecord[y].bloodType == 3) {
            cout << "B";
        }
        cout << setw(15);
        
        if (patientRecord[y].organ == 0) {
            cout << "Heart";
        } else if (patientRecord[y].organ == 1) {
            cout << "Kidney";
        } else if (patientRecord[y].organ == 2) {
            cout << "Lung";
        } else if (patientRecord[y].organ == 3) {
            cout << "Liver";
        }
        cout << setw(10);
        
        cout << patientRecord[y].age << setw(10);
        cout << patientRecord[y].yearAdded << endl;
    }
}

void writeIntoFileStream(PatientRecord pRecord[], ofstream& outputFileStream, int num){
    outputFileStream << "Patients " << num << endl;
    for(int i = 0; i < num; i++){
        outputFileStream << pRecord[i].firstName << " " << pRecord[i].lastName << " ";
        if (pRecord[i].bloodType == 0){
            outputFileStream << "A";
        }
        else if (pRecord[i].bloodType == 1){
            outputFileStream << "AB";
        }
        else if (pRecord[i].bloodType == 2){
            outputFileStream << "O";
        }
        else if (pRecord[i].bloodType == 3){
            outputFileStream << "B";
        }
        outputFileStream << " ";
        
        if (pRecord[i].organ == 0){
            outputFileStream << "Heart";
        }
        else if (pRecord[i].organ == 1){
            outputFileStream << "Kidney";
        }
        else if (pRecord[i].organ == 2){
            outputFileStream << "Lung";
        }
        else if (pRecord[i].organ == 3){
            outputFileStream << "Liver";
        }
        outputFileStream << " " << pRecord[i].age << " " << pRecord[i].yearAdded << endl;
    }
}

void writeFile(PatientRecord pRecord[], int num){
    ofstream outputFileStream;
    outputFileStream.open("transplantPatients.txt");
    
    if (outputFileStream.is_open()){
        writeIntoFileStream(pRecord, outputFileStream, num);
        outputFileStream.close();
    }
    else{
        cout << "Unable to open file" << endl;
    }
}

int readFromFileStream(ifstream& inputFileStream, PatientRecord pRecord[]){
    stringstream ss;
    string txtLine;
    int i = 0;
    
    getline(inputFileStream, txtLine);
    ss.str(txtLine);
    ss.str("");
    ss.clear();
    
    while(getline(inputFileStream, txtLine)){
        ss.str(txtLine);
        tokenizeAndFillup(ss, pRecord[i]);
        i++;
        ss.str("");
        ss.clear();
    }
    
    return i;
}

int readFile(PatientRecord pRecord[]){
    int num;
    ifstream inputFileStream;
    inputFileStream.open("transplantPatients.txt");
    
    if (inputFileStream.is_open()){
        num = readFromFileStream(inputFileStream, pRecord);
        inputFileStream.close();
    }
    else{
        cout << "Unable to open file" << endl;
    }
    
    return num;
}
