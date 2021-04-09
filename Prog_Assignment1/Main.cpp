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

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <cstdlib>

#include "appointment.h"
#include "FibHeap.cpp"
#include "Registry.h"


using namespace std;

int report_weekly(int Day,Registry* Reg,CentralQueue<int>* Cent,vector<FIFO*> fun)
{
    // wite the report program part here.
    int op,end;
    end = 1;
    cout << "Choose the output mode "<<endl;
    cout<< "0. Do not sort" <<endl;
    cout<<"1. Sort by name (from a to z )"<<endl;
    cout <<"2. Sort by age group(1-8)"<<endl;
    cout<<"3. Sort by profession(1-7)"<<endl;
    cin>>op;
    vector<Reg_Node*> result_waiting;
    vector<Reg_Node*> result_done;
    vector<Reg_Node*> queueing;
    int h_num = fun.size();

    //test here
    int test = fun[1]->get_p()->size();
    cout<<"-----------------------------------Testing ---------------------------------"<<endl;
    cout<<test<<endl;
    cout<<Cent->waiting_number();

    switch (op) {
        default:
            end = 0;
        case 0:
            break;
        case 1:
            for (int i = 0;i<h_num;i++){
                fun[i]->namesort();
            }
            break;
        case 2:
            for (int i = 0;i<h_num;i++){
                fun[i]->agesort();
            }
            break;
        case 3:
            for (int i = 0;i<h_num;i++){
                fun[i]->profsort();
            }
            break;
    }
    ofstream out;
    stringstream filename;
    filename<<"Weekly_";
    filename<<Day<<".csv";
    string name = filename.str();
    out.open(name.c_str());
    out<<"The Treated People :: "<<endl;
    out<<"name"<<","<<"ID"<<","<<"Profession"<<","<<"Age Cata."<<","<<"Risk"<<","<<"waiting Time"<<endl;
    int length;
    Reg_Node* con;
    for (int i=0;i<h_num;i++){

        result_done = fun[i]->displaytreated();
        length = result_done.size();
        for (int j = 0; j <length;j++) {
            con = result_done[j];
            cout<<con->get_name()<<endl;
            out << con->get_name() << "," << con->get_id() << "," << con->get_profession() << "," << con->get_age() << ","<< con->get_risk() << "," << (con->get_treatDay() - con->get_RegDay()) << endl;
        }
    }
    out<<endl;
    out<<endl;

    for (int j=0;j<h_num;j++) {
        result_waiting  = fun[j]->displaywaiting();
        out << "The Not Appointed people :: " << endl;
        out << "name" << "," << "ID" << "," << "Profession" << "," << "Age Cata." << "," << "Risk" << ","
            << "waiting Time" << endl;
        length = result_waiting.size();
        for (int i = 0; i < length; i++) {
            con = result_waiting[i];
            out << con->get_name() << "," << con->get_id() << "," << con->get_profession() << "," << con->get_age()
                << "," << con->get_risk() << "," << (Day - con->get_RegDay()) << endl;
        }
    }
    out<<"\n"<<endl;
    out<<"The Queueing People :: "<<endl;
    out<<"name"<<","<<"ID"<<","<<"Profession"<<","<<"Age Cata."<<","<<"Risk"<<","<<"waiting Time"<<endl;


    length = queueing.size();
    for (int i=0;i<length;i++){
        con = queueing[i];
        out<<con->get_name()<<","<<con->get_id()<<","<<con->get_profession()<<","<<con->get_age()<<","<<con->get_risk()<<","<<(Day-con->get_RegDay())<<endl;
    }
    out.close();
    cout<<"-----------------------------Weekly Report is Done----------------------------------"<< endl;
    return end;
}
int report_monthly(Registry* Reg,CentralQueue<int>* Cent,vector<FIFO*> Fun)
{
    // write the monthly report here.
    // you maybe need to add it to the friend function list.
    int end = 1;
    cout<<"The current static number is: "<<endl;
    cout<<"1. The Total Register number is "<<Reg->getlength()<<" people."<<endl;
    int numitem;
    vector<int> output = Reg->get_waiting(0);
    numitem = output.size();
    cout<<"2. The waiting people is "<<numitem<<" People. "<<endl;
    int queuepeople,app_num;
    app_num = 0;
    queuepeople = Cent->waiting_number();

    int h_num = Fun.size();
    for (int j=0;j<h_num;j++){
        app_num += Fun[j]->numwaiting();
    }

    queuepeople += numitem;
    queuepeople += app_num;
    cout<<"3. The total waiting people(also included in the queue) is "<<queuepeople<<" People. "<<endl;
    int treat=0;

    for (int j=0;j<h_num;j++){
        treat += Fun[j]->numcomplete();
    }

    cout<<"4. The total Treatment Done are "<<treat<<" Cases. "<<endl;
    int time = 0;

    for (int j=0;j<h_num;j++){
        time += Fun[j]->Avtime();
    }
    time = time/h_num;

    cout<<"5. The average waiting time is "<<time<<" Days. "<<endl;
    int num_with;
    output = Reg->get_withdraw(0);
    num_with = output.size();
    cout<<"6. The total withdraw people is "<<num_with<<" People."<<endl;
    return end;
}

void insert_patient(Registry* LocalReg, CentralQueue<int>* Central){

    vector<string> singleP;
    string number;
    ifstream Patient("patient.csv",ios::in);
    string LineStr; // all the information is inside.
    while (getline(Patient,LineStr)){
        singleP.clear();
        stringstream PaSS(LineStr);
        while (getline(PaSS,number,',')){
            singleP.push_back(number);
        }
        // now all the patient info are in this single array.
        string name = singleP[0];
        if (name.c_str() == "name"){
            continue;
        }
        string Birth = singleP[1];
        stringstream utility;
        utility.str("");
        utility<<singleP[2];
        int ageint;
        utility>>ageint;
        //prof
        utility.str("");
        utility<<singleP[3];
        int prof;
        utility>>prof;
        // risk;
        utility.str("");
        utility<<singleP[4];
        int risk;
        utility>>risk;
        //location
        utility.str("");
        utility<<singleP[5];
        int loc;
        utility>>loc;
        // RegDAY
        string RegDay = singleP[6];
        string weChat = singleP[7];
        string QQ = singleP[8];
        string email = singleP[9];
        string phone = singleP[10];
        //now push it into the linked list of different location.
        // Since it is before a day.....no one can withdraw.
        int result = LocalReg->search_name(name);
        if (result > 0) {
            Reg_Node* same = LocalReg->search_id(result);
            if (same->get_status() == withdraw) {
                Central->record_in(same);
                same->set_status(applied);
            }
            else {
                same->set_status(applied);
            }
        }
        else {
            LocalReg->insert(name, Birth, RegDay, ageint, risk, prof, loc, weChat, QQ,
                               email, phone);
            cout << "New Patient Added." << endl;
        }

    }

    Patient.close();
}

int main()
{
    // main program here.a
    int Duration = 0;
    // day0: basic information are created.
    // 1. registry will record first wave of patient.
    Registry* LocalReg_1 = new Registry;
    //Registry* LocalReg_2 = new Registry;
   // Registry* LocalReg_3 = new Registry;
    //Registry* LocalReg_4 = new Registry;
    CentralQueue<int>* Central = new CentralQueue<int>;

    insert_patient(LocalReg_1,Central);
    // 2. the queue and the appointment queue is also created, but the reg will not push anythings in it.

    // 3. the risk 3 may receive treatment in Day 1.

    FIFO* Hospital_1 = new FIFO;
    FIFO* Hospital_2 = new FIFO;
    FIFO* Hospital_3 = new FIFO;
    FIFO* Hospital_4 = new FIFO;

    vector<FIFO*> Hospital;
    Hospital.push_back(Hospital_1);
    Hospital.push_back(Hospital_2);
    Hospital.push_back(Hospital_3);
    Hospital.push_back(Hospital_4);
    // 4. then we will push the day to day1.
    Duration ++;

    while (Duration) {
        // part A : deal with daily things.
        cout<<"The System Have RUN "<<Duration<<" DAY."<<endl;
        cout<<"Daily patient appointment handle. "<<endl;

        LocalReg_1->set_Day(Duration);
        Central->set_date(Duration);
        // 1. push new waiting people int the queue.
        vector < Reg_Node * > waiting = LocalReg_1->push2Queue();


        cout<<"-----------------------------------Testing ---------------------------------"<<endl;
        cout<<waiting.size()<<endl;


        int size = waiting.size();
        for (int i = 0; i < size; i++) {
            Central->record_in(waiting[i]);
        }
        // 2. then, the queue push several numbers. or check the risk rank 2 and 3.
        Reg_Node *record;
        vector < Reg_Node * > Queue;

        int length = Queue.size();
        int c1,c2,c3,c4;
        c1=c2=0;
        c3=c4=0;
        record = Central->record_out();

        cout<<"-----------------------------------Testing ---------------------------------"<<endl;

        cout<<c1<<" "<<c2<<" "<<c3<<" "<<c4<<endl;
        // Since we decide that everyday the hospital can only deal with 40 people,
        // so when people reach 1.5 timea of the hospital, the appointment would stop.

        while (record != nullptr && c1 <=60 &&c2<=60 && c3<=60 && c4 <=60) {
            Queue.push_back(record);
            switch (record->get_location()) {
                case 1:
                    c1++;
                    break;
                case 2:
                    c2++;
                    break;
                case 3:
                    c3++;
                    break;
                case 4:
                    c4++;
                    break;
                default:
                    break;
            }
            record = Central->record_out();
        }
        // 3. send treatment appointment to the patient.

        for (int i = 0; (i < length); i++) {
            record = Queue[i];
            switch (record->get_location()) {
                case 1:
                    (Hospital_1->get_q())->push(*record);
                    break;
                case 2:
                    (Hospital_2->get_q())->push(*record);
                    break;
                case 3:
                    (Hospital_3->get_q())->push(*record);
                    break;
                case 4:
                    (Hospital_4->get_q())->push(*record);
                    break;
            }
        }
        Hospital_1->deal(Duration);
        Hospital_2->deal(Duration);
        Hospital_3->deal(Duration);
        Hospital_4->deal(Duration);
        // Part B : patient management.
        // 1. this part will raise a menu, where can choose several service : insert new
        int op,end,id;
        end = 1;
        while (end) {
            cout << "Patient management system.\n" << endl;
            cout << "Choose operations 1~5,7 to close the sys. " << endl;
            cout << "1. record new patient" << endl;
            cout << "2. withdraw application" << endl;
            cout << "3. Hand-in priority letter" << endl;
            cout << "4. Profession modification" << endl;
            cout << "5.. start new day" << endl;
            cin >> op;
            int deadline;
            Reg_Node* search;
            int ageint,prof;
            string name;

            switch (op) {
                case 1:
                    insert_patient(LocalReg_1,Central);
                    break;

                case 2:
                    cout << "Now enter the ID. " << endl;
                    cin >> id;
                    search = LocalReg_1->search_id(id);
                    LocalReg_1->withdrawn(id);
                    Central->withdraw_heap(search);
                    switch (search->get_location()) {
                        case 1:
                            Hospital_1->setwithdraw(search);
                            break;
                        case 2:
                            Hospital_2->setwithdraw(search);
                            break;
                        case 3:
                            Hospital_3->setwithdraw(search);
                            break;
                        case 4:
                            Hospital_4->setwithdraw(search);
                            break;
                    }

                    break;

                case 3:
                    cout<<"Now Enter the VIP's ID"<<endl;
                    cin>>id;
                    cout<<"Now Enter the VIP's DeadLine"<<endl;
                    cin>>deadline;
                    search = LocalReg_1->search_id(id);
                    LocalReg_1->priority_letter(search,deadline);
                    Central->record_in(search);
                    break;

                case 4:
                    cout<<"Now enter Op ID"<<endl;
                    cin >> id;
                    cout<<"Now enter new Profession"<<endl;
                    cin>> deadline;
                    search = LocalReg_1->search_id(id);
                    LocalReg_1->change_profssion(search,deadline);
                    Central->change_profession(search);
                    cout<<"Your info was Updated"<<endl;
                    break;

                case 5:
                    cout<<" Now Moving to Next day. "<<endl;
                    end = 0;
                    break;
                case 6:
                    cout<<" Now Enter the ID"<<endl;
                    cin>>id;
                    search = LocalReg_1->search_id(id);
                    cout<<"now search is done. "<<endl;
                    if (search!= nullptr) {
                        name = search->get_name();
                        prof = search->get_profession();
                        ageint = search->get_age();
                        cout<<name<<" "<<prof<<" "<<" "<<ageint<< endl;
                    }
                    else{
                        cout<<"Not such ID!!!"<<endl;
                        cout<<"\n"<<"\n"<<"\n"<<endl;
                    }
                    break;
                case 7:
                    return 1;
                default:
                    return 2;

            }
        }

        // patient, withdraw patient, check status of a patient, or check the risk 2 or 3
        // patient.
        // PartC : End of a Day
        // 1. In this part, all need to do is to update the day info and some other else.
        // remember to mod 7 and 30 to call the report program.
        if (Duration%7 == 0){
            cout<<"\n"<<"\n"<<endl;
            cout<<"------------------------Generating weekly report--------------------------------";
            cout<<endl;
            report_weekly(Duration,LocalReg_1,Central,Hospital);
        }
        if (Duration%30 == 0){
            cout<<"\n"<<"\n"<<endl;
            cout<<"------------------------Generating monthly report----------------------------------"<<endl;
            report_monthly(LocalReg_1,Central,Hospital);
            cout<<"--------------------------------END------------------------------------------"<<endl;
        }
        Duration ++;
    }
    return 0;
}