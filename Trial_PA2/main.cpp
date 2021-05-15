#include "Registry.h"
#include "create_testcase.h"

#include "random"

using namespace std;

int weekly_report();
int monthly_report();
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

    cout<<"..";
    uniform_int_distribution<unsigned> month_info(1,12);
    default_random_engine engine;
    int month = month_info(engine);
    create_testcase(month,Day); // Day 0 means that they are pre-registered.
    read_patient_info(RegStation);

    cout<<"..";
    Day++;

    // push today's waiting people to the center queue.
    cout<<"..";
    // push the center queue's result to the Target hospital.
    cout<<"..";
    // Here we ve enter a normal work day.
    cout<<"\n "<<endl;
    while (Day){
        cout<<"----------------------Now Enter Day "<<Day<<"-------------------------"<<endl;
        // Deal with Daily appointment.
        // 1. sent appointment to the patient.

        // 2. receive New applications.
        cout<<"-------------------Create new patients' information---------------"<<endl;
        create_testcase(month,Day%30);
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
            cout<<"default: terminate the program. "<<endl;
            cout<<"\n";
            cout<<"now enter op code. "<<endl;
            cin>>op;
            int priority;
            Tuple* dump = nullptr;

            switch (op) {
                case 1:
                    cout<<"\nenter id. "<<endl;
                    cin>>id;
                    switch (id%3) {
                        case 0:
                            R_Station3->withdraw(id);
                            break;
                        case 1:
                            R_Station1->withdraw(id);
                            break;
                        case 2:
                            R_Station2->withdraw(id);
                            break;
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

                        cout<<"welcome patient "<<dump->get_name()<<"! Your";
                        cout<<" current status:"<<endl;
                        cout<<"Medico Risk | Treatment Type | Hospital | status | waiting Day "<<endl;
                        cout<<"      1     |        2       |     3    |    4   |      05     "<<endl;
                    } else{
                        cout<<"ID info not found. "<<endl;
                    }
                    break;
                case 4:
                    end = 0;
                    break;
                case 5:
                    weekly_report();
                    monthly_report();
                default:
                    return 1;
            }
        }
        // 4. push the local registry station's result to the center queue.

        // 5. push the center queue's result to the Hospital.

        // 6. Check if the report is ready.
        if (!Day%7){
            weekly_report();
        }
        if (!Day%30){
            monthly_report();
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

int weekly_report(vector<Registry*> &station, vector<Center*> Center, vector<Hospital*> HosGroup, int day){
    // generate weekly report to a csv file.

    return 0;
}