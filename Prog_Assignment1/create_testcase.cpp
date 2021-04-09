//
// Created by jordan on 2021/4/7.
//

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>

using namespace std;

int main()
{
    ofstream testcase;
    testcase.open("patient.csv");
    testcase<<"name"<<","<<"Birthday"<<","<<"Age"<<","<<"Professional"<<","<<"risk"<<","<<"location"<<","<<"Register Day"<<",";
    testcase<<"wechat_ID"<<","<<"QQ"<<","<<"E-mail"<<","<<"phone"<<endl;

    int check = 0;
    int end = 1;
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
    int month = rand()%12 +1;
    string month_str;
    if (month < 10){
        month_str = "0";
    }
    else{
        month_str = "";
    }
    month_str.append(to_string(month));
    string year = "2077";
    while (end){

        for (int i=0;i<30;i++){
            date_ss.str("");
            date_ss<<year;
            date_ss<<month_str;
            int today = check + (rand()%11 -5);

            if (i < 10 ){
                date_ss<<0<<(i+1);
            }else {
                date_ss<<(i+1);
            }

            for (int j=0;j<today;j++){
                string name = words[rand()%26];
                string wechat = words[rand()%26];
                string QQ = "1";
                string phone = "1";

                int n_lengh = rand()%3 + 3;
                for (int k = 0; k< n_lengh;k++){
                    name.append(words[rand()%26]);
                    wechat.append(words[rand()%26]);
                }

                int professional = rand()%8 +1;
                int age = rand()%101;
                int risk = rand()%4;
                // we define 4 hospital now.
                int location = rand()%4 +1;
                for (int k = 0; k < 10;k++){
                    QQ.append(to_string(rand()%10));
                    phone.append(to_string(rand()%10));
                }
                string email = "Faden_is_Fat@163.com";
                string Birthday = "20000101";

                string Reg_date = date_ss.str();

                testcase<<name<<","<<Birthday<<",";
                testcase<<age<<",";
                testcase<<professional<<",";
                testcase<<risk<<",";
                testcase<<location<<",";
                testcase<<Reg_date<<",";
                testcase<<wechat<<",";
                testcase<<QQ<<",";
                testcase<<email<<",";
                testcase<<phone<<","<<endl;
            }
        }
        cout<<"end now or add another 30 days? 0 for stop"<<endl;
        cin >> end;
        month = (month+1)%12;
        if (month < 10){
            month_str = "0";
        }
        else{
            month_str = "";
        }
        month_str.append(to_string(month));

    }
    testcase.close();

}