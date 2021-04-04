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
    while (Duration >= 0){
        // remember to mod 7 and 30 to call the report program.
        if (! Duration%7){
            report_weekly();
        }
        if (! Duration%30){
            report_monthly();
        }
    }
};
