/*
 * @ Author     : 
 * 
 * @ File       : 
 * 
 * @ Purpose    : 
 * 
 * @ Usage      : 
 * 
 * @ Description: 
 * 
 * @ Input      : 
 * 
 * @ Output     : 
 * 
 */

#include <vector>
#include <iostream>
using namespace std;

class booking{
    public:
        booking(int a, int d){
            arrival = a;
            departure = d;
        };
        int arrival; 
        int departure; 
};


class Bookings{
    public:
        Bookings(vector<booking> bookings, int K){
            bks = bookings;
            k = K;
        };
        vector <booking> bks;
        int k;
        void bookings_print();
        void test();
        
        // Modify the following to solve the exercise
        // You may also add your own help function
        bool checkdemands();


    private:

};

// quicksort for int array
void quicksort(int array[], int L, int R) {
    if (L >= R)
        return;
    int left = L, right = R;
    int pivot = array[left];
    while(left < right) {
        while(left < right && array[right] >= pivot) {
            right--;
        }
        
        if (left < right) {
            array[left] = array[right];
        }
        
        while(left < right && array[left] <= pivot) {
            left++;
        }
        
        if (left < right) {
            array[right] = array[left];
        }
        
        if (left >= right) {
            array[left] = pivot;
        }
    }
    
    quicksort(array, L, right-1);
    quicksort(array, right+1, R);
}

// You should right the following to finish the exercise
// You may also add your own help function
bool Bookings::checkdemands(){
    
    // General thoughts:
    // use two auxiliary arrays to load the arrival date and the departure date, respectively.
    // sort these two arrays.
    // check whether the room is enough each day.
    
    // part 1,create the auxiliary array
    int n;
    n = static_cast<int>(this->bks.size());
    
    int arrival[n];
    int departure[n];
    
    int i;
    for (i = 0; i < n; i++) {
        arrival[i] = this->bks[i].arrival;
        departure[i] = this->bks[i].departure;
    }
    
    
    // part 2, sort arr[] and dep[]
    quicksort(arrival, 0, n-1);
    quicksort(departure, 0, n-1);
    
    // part 3, check whether the room is enough
    // compare the room required and the room available each day
    int room_require = 0;
    int arr_pos = 0;
    int dep_pos = 0;
    
    for (i = arrival[0]; i <= departure[n-1]; i++) {
        
        // if one booking for arrival at day i, room_require++;
        while(arrival[arr_pos] == i) {
            arr_pos++;
            room_require++;
        }
        
        // if one booking for departure at day i, room_require--;
        while(departure[dep_pos] == i) {
            dep_pos++;
            room_require--;
        }
        
        if (room_require > this->k) {return 0;} // the room is not enough at that time
        
    }
    
    
    
    return 1; // the room is enough all the time
    
};






// DO NOT modify the following 
void Bookings::bookings_print(){
    cout << "Bookings as follow:" << endl;
    for(booking i: this->bks){
        cout << "A: " << i.arrival << "  | D: " << i.departure << endl;
    }
    cout << "Max available room:" << this->k << endl;
    return ;
}

void Bookings::test(){
    bookings_print();
    cout << "Check whether satisfy the demands: " << (checkdemands()? "Success":"Fail") << endl;
}
