#include "Registry.h"
#include "create_testcase.h"
#include "FibHeap.cpp"
#include "random"
#include "appointment.h"

using namespace std;

int weekly_report(vector<Registry*> &station, CentralQueue<int> &Center,vector<FIFO*> &Hospitals,int day);
int monthly_report(vector<Registry*> &station, CentralQueue<int> &Center,vector<FIFO*> &Hospitals, int day);
int read_patient_info(vector<Registry*> &Station);

int main() {
    cout<<"-----------Welcome to the Hospital Registry System---------------"<<endl;
    cout<<"\n"<<endl;
    cout<<"-------------------------Initializing----------------------------"<<endl;
    cout<<"\n"<<endl;
    cout<<"..";
    int Day = 0;
    auto R_Station1 = new Registry(3,1);
    auto R_Station2 = new Registry(3,2);
    auto R_Station3 = new Registry(3,3);
    vector<Registry*> RegStation;
    RegStation.push_back(R_Station1);
    RegStation.push_back(R_Station2);
    RegStation.push_back(R_Station3);
    for (auto i:RegStation){
        i->updateDAY(Day);
    }

    auto Central = new CentralQueue<int>;
    Central->set_date(Day);

    auto Hospotal_1 = new FIFO;
    auto Hospital_2 = new FIFO;
    auto Hospital_3 = new FIFO;
    auto Hospital_4 = new FIFO;
    vector<FIFO*> Hospitals;
    Hospitals.push_back(Hospotal_1);
    Hospitals.push_back(Hospital_2);
    Hospitals.push_back(Hospital_3);
    Hospitals.push_back(Hospital_4);


    cout<<"..";
    uniform_int_distribution<unsigned> month_info(1,12);
    default_random_engine engine;
    int month = month_info(engine);
    create_testcase(month,Day); // Day 0 means that they are pre-registered.
    cout<<"reading...."<<endl;
    read_patient_info(RegStation);

    cout<<"..";
    Day++;

    int min = -1;
    for (auto i:RegStation){
        if(min<0){
            min = i->report_waiting()->size();
        }
        else{
            if (i->report_waiting()->size() < min){
                min = i->report_waiting()->size();
            }
        }
    }
    // push today's waiting people to the center queue.
    cout<<"..";
    if (min){
        for (int i=0;i<min;i++){
            Central->record_in(R_Station1->Daily_push());
            Central->record_in(R_Station2->Daily_push());
            Central->record_in(R_Station3->Daily_push());
        }
    }
    // push the center queue's result to the Target hospital.
    for (int i=0;i<100;i++){
        Tuple* t = Central->record_out();
        if (t) {
            Hospitals[t->get_registration()]->get_q()->push(*t);
        } else{
            break;
        }
    }

    cout<<"..";
    // Here we ve enter a normal work day.
    cout<<"\n "<<endl;

    while (Day){
        cout<<"----------------------Now Enter Day "<<Day<<"-------------------------"<<endl;
        // Deal with Daily appointment.
        for (auto i:RegStation){
            i->updateDAY(Day);
        }
        Central->set_date(Day);
        // 1. sent appointment to the patient.
        for (auto i:Hospitals){
            i->deal(Day);
            i->storage();
        }
        // 2. receive New applications.
        cout<<"-------------------Create new patients' information---------------"<<endl;
        create_testcase(month,Day%30);
        cout<<"reading...."<<endl;
        read_patient_info(RegStation);

        // 3. receive withdraw application and priority letter.
        cout<<"-----------------Patient application management-------------------"<<endl;
        int op,end,id;
        end = 1;
        op = 0;
        id = 0;
        while (end){
            cout<<"-------------------New Query--------------------"<<endl;
            cout<<"Hint: Operation code"<<endl;
            cout<<"1. withdraw patient with patient id."<<endl;
            cout<<"2. hand in priority letter with patient id."<<endl;
            cout<<"3. dump patient's information with patient id."<<endl;
            cout<<"4. Start new day. "<<endl;
            cout<<"5. Dump report immediately. "<<endl;
            cout<<"6. Cancel withdraw with patient ID. "<<endl;
            cout<<"default: terminate the program. "<<endl;
            cout<<"\n";
            cout<<"now enter op code. "<<endl;
            cin>>op;
            int priority;
            int status;
            Tuple* dump = nullptr;

            switch (op) {
                case 1:
                    cout<<"\nenter id. "<<endl;
                    cin>>id;
                    switch (id%3) {
                        case 0:
                            dump = R_Station3->withdraw(id);
                            Central->withdraw_heap(dump);
                            break;
                        case 1:
                            dump = R_Station1->withdraw(id);
                            Central->withdraw_heap(dump);
                            break;
                        case 2:
                            dump = R_Station2->withdraw(id);
                            Central->withdraw_heap(dump);
                            break;
                    }
                    // waiting for Hospital's withdraw.
                    for (auto i:Hospitals){
                        i->setwithdraw(*dump);
                    }
                    break;

                case 2:
                    cout<<"\nEnter id. "<<endl;
                    cin>>id;
                    cout<<"\nEnter priority deadline. "<<endl;
                    cin>>priority;
                    switch (id%3) {
                        case 0:
                            R_Station3->priority(id,priority);
                            break;
                        case 1:
                            R_Station1->priority(id,priority);
                            break;
                        case 2:
                            R_Station2->priority(id,priority);
                            break;
                    }
                    // waiting for next input.
                    break;
                case 3:
                    //query from the registration first.
                    cout<<"\nEnter id. "<<endl;
                    cin>>id;

                    switch (id%3) {
                        case 0:
                            dump = R_Station3->find_id(id);
                            break;
                        case 1:
                            dump = R_Station1->find_id(id);
                            break;
                        case 2:
                            dump = R_Station2->find_id(id);
                            break;
                    }
                    if (dump){
                        // find more info from Hospital database.
                        if (Hospitals[dump->get_registration()]->getDB()->find_ID(id)){
                            dump = Hospitals[dump->get_registration()]->getDB()->find_ID(id);
                            priority = dump->get_TreatDay() - dump->get_startDay();
                            status = 3;
                        }else {
                            // After that, Find more info from the Registry station.
                            priority = Day - dump->get_startDay();
                            if (dump->get_status() == applied){
                                status = 1;
                            } else{
                                status = 2;
                            }
                        }
                        cout<<"welcome patient "<<dump->get_name()<<"! Your";
                        cout<<" current status:"<<endl;
                        cout<<"Medico Risk | Treatment Type | Hospital | status | waiting Day "<<endl;
                        cout<<"      "<<dump->get_medic()<<"     |        "<<dump->get_Treatment()<<"       |     "<<dump->get_registration()<<"    |    "<<status<<"   |      "<<priority<<"     "<<endl;
                    } else{
                        cout<<"ID info not found. "<<endl;
                    }
                    break;
                case 4:
                    end = 0;
                    break;
                case 5:
                    weekly_report(RegStation,*Central,Hospitals,Day);
                    monthly_report(RegStation,*Central,Hospitals,Day);
                    break;
                case 6:
                    cout<<"\nEnter ID. "<<endl;
                    cin>>id;
                    switch (id%3) {
                        case 0:
                            R_Station3->resent_application(id);
                            break;
                        case 1:
                            R_Station1->resent_application(id);
                            break;
                        case 2:
                            R_Station2->resent_application(id);
                            break;
                    }
                    break;
                default:
                    return 1;
            }
        }
        // 4. push the local registry station's result to the center queue.
        min = -1;
        for (auto i:RegStation){
            if(min<0){
                min = (int)i->report_waiting()->size();
            }
            else{
                if (i->report_waiting()->size() < min){
                    min = (int)i->report_waiting()->size();
                }
            }
        }
        if (min) {
            for (int i = 0; i < min; i++) {
                Central->record_in(R_Station1->Daily_push());
                Central->record_in(R_Station2->Daily_push());
                Central->record_in(R_Station3->Daily_push());
            }
        }
        // 5. push the center queue's result to the Hospital.
        for (int i=0;i<150;i++){
            Tuple* t = Central->record_out();
            if (t) {
                cout<<t->get_registration()<<endl;
                Hospitals[t->get_registration()]->get_q()->push(*t);
                cout<<Hospitals[t->get_registration()]->get_q()->size()<<endl;
            } else{
                break;
            }
        }

        // 6. Check if the report is ready.
        if (!Day%7){
            weekly_report(RegStation,*Central,Hospitals,Day);
        }
        if (!Day%30){
            monthly_report(RegStation,*Central,Hospitals,Day);
        }
        // 7. update the date info.
        Day++;
        // check if a new month is coming.
        if (Day%30 == 1){
            month = (month+1)%12;
        }
    }

    return 0;
}

int read_patient_info(vector<Registry*> &station){
    int linecounter = 0;
    vector<string> oneline;
    string number;
    ifstream Patient("patient.csv",ios::in);
    string Linestr;
    while (getline(Patient,Linestr)) {
        oneline.clear();
        stringstream PSS(Linestr);
        while (getline(PSS, number, ',')) {
            oneline.push_back(number);
        }
        if (!linecounter) {
            linecounter = 1;
            continue;
        }

        string name = oneline[0];

        stringstream utility; // use for change string to int.
        utility.clear();
        utility.str("");
        utility<<oneline[1];
        int Medi;
        utility>>Medi;
        // Treatment
        utility.clear();
        utility.str("");
        utility<<oneline[2];
        int Treat;
        utility>>Treat;
        // Hospital
        utility.clear();
        utility.str("");
        utility<<oneline[3];
        int Hospital;
        utility>>Hospital;
        // Registry Station No.
        utility.clear();
        utility.str("");
        utility<<oneline[4];
        int RegNo;
        utility>>RegNo;

        switch (RegNo) {
            case 1:
                station[0]->insert(name,Medi,Hospital,Treat);
                break;
            case 2:
                station[1]->insert(name,Medi,Hospital,Treat);
                break;
            case 3:
                station[2]->insert(name,Medi,Hospital,Treat);
                break;
            default:
                break;
        }
    }
    return 1;
}

int weekly_report(vector<Registry*> &station, CentralQueue<int> &Center,vector<FIFO*> &Hospitals,int day){
    // generate weekly report to a csv file.
    cout<<"----------------------------Weekly Report Generated---------------------------"<<endl;
    ofstream out;
    stringstream filename;
    filename<<"weekly_Day"<<day<<".csv";
    string name = filename.str();
    out.open(name.c_str());
    out<<"----Weekly Report----"<<endl;

    out<<"Treated People :"<<endl;
    out<<""<<","<<"ID"<<","<<"name"<<","<<"Medico Risk"<<","<<"Hospital"<<","<<"Treat_type"<<","<<"Waiting_time"<<endl;
    for (auto i:Hospitals){
        for(int o=0;o<i->get_q()->size();o++){
            auto tempT = i->get_q()->front();
            out<<""<<","<<tempT.get_name()<<","<<tempT.get_medic()<<","<<tempT.get_registration()<<","<<tempT.get_Treatment()<<","<<tempT.get_TreatDay()-tempT.get_startDay()<<endl;
            i->get_q()->pop();
        }

    }

    out<<"Waiting People(Not Appointed)"<<endl;
    out<<""<<","<<"ID"<<","<<"name"<<","<<"Medico Risk"<<","<<"Hospital"<<","<<"Treat_type"<<","<<"Waiting_time"<<endl;
    for (auto i:Hospitals){
        for(int o=0;o<i->get_q()->size();o++){
            auto tempT = i->get_p()->front();
            out<<""<<","<<tempT.get_name()<<","<<tempT.get_medic()<<","<<tempT.get_registration()<<","<<tempT.get_Treatment()<<","<<tempT.get_TreatDay()-tempT.get_startDay()<<endl;
            i->get_p()->push(i->get_p()->front());
            i->get_p()->pop();
        }

    }

    out<<"The Queueing people"<<endl;
    out<<""<<","<<"ID"<<","<<"name"<<","<<"Medico Risk"<<","<<"Hospital"<<","<<"Treat_type"<<","<<"Waiting_time"<<endl;
    for (auto i : station){
        for (auto p:*i->report_waiting()){
            out<<""<<","<<p->get_id()<<","<<p->get_name()<<","<<p->get_medic()<<","<<p->get_registration()<<","<<p->get_Treatment()<<","<<day-p->get_startDay()<<endl;
        }
    }
    // from Central queue.

    out.close();
    return 0;
}

int monthly_report(vector<Registry*> &station, CentralQueue<int> &Center,vector<FIFO*> &Hospitals, int day){
    cout<<"-------------------------Monthly Report Generated----------------------------"<<endl;
    ofstream out;
    stringstream filename;
    filename<<"Monthly_Day"<<day<<".txt";
    string name = filename.str();
    out.open(name.c_str());
    out<<"--------Monthly Report--------"<<endl;

    int static_num = 0;
    for (auto i:station){
        static_num+=i->getitem();
    }
    out<<"1. The Total Registered number: "<<static_num<<" People. "<<endl;

    static_num = 0;
    for (auto i:station){
        static_num += i->report_waiting()->size();
    }
    out<<"2. The Total Waiting Number:    "<<static_num<<" People. "<<endl;

    static_num = Center.waiting_number();
    out<<"3. The Total Queueing People:   "<<static_num<<" People. "<<endl;

    static_num = 0;
    for (auto i:Hospitals){
        static_num += i->getDB()->getlength();
    }
    out<<"4. The Total Treated Number:    "<<static_num<<" People. "<<endl;

    static_num = 0;
    for (auto i:Hospitals){
        static_num += i->Avtime();
    }
    static_num = static_num/Hospitals.size();
    out<<"5. The Average Waiting time:    "<<static_num<<" Days."<<endl;

    static_num = 0;
    for (auto  i:station){
        static_num += i->report_withdraw()->size();
    }
    out<<"6. The Total Withdraw Number:   "<<static_num<<" People. "<<endl;
    out.close();
    return 0;
}