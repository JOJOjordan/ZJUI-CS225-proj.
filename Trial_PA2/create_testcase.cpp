//
// Created by jordan on 2021/4/7.
//
#include "create_testcase.h"

using namespace std;

int create_testcase(int month,int date)
{
    ofstream testcase;
    testcase.open("patient.csv");
    testcase<<"name"<<","<<"Medico_Risk"<<","<<"Treatment_Method"<<","<<"Hospital_ID"<<","
    <<"Registry_station"<<","<<"Registry_Date"<<endl;

    int check = 0;

    const char* word[26] = {"a","b","c","d","e","f","g","h","i","j","k","l","m","n","o","p","q","r","s","t","u","v","w","x","y","z"};
    string words[26];
    for (int i=0;i<26;i++){
        words[i] = word[i];
    }

    do {
        cout << "choose approx. daily patient ( from 0 to 100 )" << endl;
        cin >> check;
        if (0 > check || check > 100) {
            cout << "bad input! " << endl;
        }
    }while (0 > check || check > 100);

    stringstream date_ss;
    string month_str;
    if (month < 10){
        month_str = "0";
    }
    else{
        month_str = "";
    }
    month_str.append(to_string(month));

    string year = "2077";
    // the year info wont be update! we are all lived in the Cyber world.
    date_ss.clear();
    date_ss.str("");
    date_ss<<year;
    date_ss<<month_str;

    if (date < 10 ){
        date_ss<<0<<(date);
    }else {
        date_ss<<(date);
    }

    // then generate the patient.

    int today = check + (rand()%11 -5);
    for (int j=0;j<today;j++){
        string name = words[rand()%26];

        int n_lengh = rand()%4 + 3;
        for (int k = 0; k< n_lengh;k++){
            name.append(words[rand()%26]);
        }


        int risk = rand()%4;
        int Treatment = rand()%3;
        int location = rand()%4;
        int RegStation = rand()%3 + 1;
        string date_info = date_ss.str();
        testcase<<name<<",";
        testcase<<risk<<",";
        testcase<<Treatment<<",";
        testcase<<location<<",";
        testcase<<RegStation<<",";
        testcase<<date_info<<endl;
    }
    testcase.close();
    return 0;
}