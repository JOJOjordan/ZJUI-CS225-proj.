//
// Created by jordan on 2021/4/3.
//

//In my design, our program will first read the local reg file(in csv will be better)
// then we will push them into the queue.
// assume that The local appointment could accept 50 people a day.
// So we will pop 90% of the maximum size (i.e.45 people in this case) a day
// to each different local appointment.
// then the local appointment could simply use a FIFO queue to assign the appointment.
// Finally, we can output such queues to generate the report.
// To output such report, the most important structure is a multiple linked list.

#include <iostream>;
#include <string>;
#include <vector>;
#include <fstream>;
#include <sstream>;
#include <cstdlib>;
#include "Appointment.h"
#include "Queue.h";
#include "Registry.h";
#include "Treated_Reg.h";

using namespace std;

int report_weekly()
{
    // write the report program part here.
}
int report_monthly()
{
    // write the monthly report here.
    // you maybe need to add it to the friend function list.
}


int main()
{
    // main program here.a
    int Duration = 0;
    // day0: basic information are created.
    // 1. registry will record first wave of patient.
    // 2. the queue and the appointment queue is also created, but the reg will not push anythings in it.
    // 3. the risk 3 may receive treatment in Day 1.
    // 4. then we will push the day to day1. 
    while (Duration >= 0){
        // part A : deal with daily things.
        // 1. push new waiting people int the queue.
        // 2. then, the queue push several numbers. or check the risk rank 2 and 3.
        // 3. send treatment appointment to the patient.
        // Part B : patient management.
        // 1. this part will raise a menu, where can choose several service : insert new
        // patient, withdraw patient, check status of a patient, or check the risk 2 or 3
        // patient.
        // PartC : End of a Day
        // 1. In this part, all need to do is to update the day info and some other else. 7
        // sick suck fuck!2
        // remember to mod 7 and 30 to call the report program.
        if (! Duration%7){
            cout<<"Generating weekly report......";
            cout<<"......"<<endl;
            report_weekly();
        }
        if (! Duration%30){
            cout<<"Generating monthly report ......"<<endl;
            report_monthly();
        }
    }
};
