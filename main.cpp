#include <string>
#include <iostream>
#include <cmath>
#include <ctime>
#include <thread> 
#include <chrono> 
using namespace std;
tm examtime{};
bool stopCountdown = false;
void setdate(){
    
    int day,month,year,day1,month1,year1,hour,hour1;
    cout<<"Enter date:"<<endl;
    cout<<"day:\t";
    cin>>day;
    cout<<"month:\t";
    cin>>month;
    cout<<"year:\t";
    cin>>year;
    day1=examtime.tm_mday=day;
    year1=examtime.tm_year=year-1900;
    month1=examtime.tm_mon=month-1;
    
}
void MYlocaltime(){
    int year,month,day,hours,minutes,seconds;
    time_t elyoum=time(NULL);
    tm* time=localtime(&elyoum);
    year=time->tm_year+1900;
    month=time->tm_mon+1;
    day=time->tm_mday;
    hours=time->tm_hour;
    minutes=time->tm_min;
    seconds=time->tm_sec;
    cout<<"your localtime is ";
    cout<<day<<"/"<<month<<"/"<<year<<endl;
    if (hours>=12){
        cout<<hours-12<<":"<<minutes<<":"<<seconds<<"  PM"<<endl;
    }else{
        cout<<hours<<":"<<minutes<<":"<<seconds<<" AM"<<endl;
    }
    

} 


void listenForExit() {
    char c;
    while (true) {
        cin >> c;
        if (c == 'q' || c == 'Q') {
            stopCountdown = true;
            break;
        }
    }
}


void calc() {
    stopCountdown = false;

    time_t now = time(NULL);
    time_t event_time = mktime(&examtime);

    if (difftime(event_time, now) <= 0) {
        cout << "Error: The date is in the past!" << endl;
        return;
    }

   
    thread inputThread(listenForExit);

    while (difftime(event_time, now) > 0 && !stopCountdown) {
        double seconds_left = difftime(event_time, now);
        long long total_seconds = static_cast<long long>(seconds_left);

        int days = total_seconds / 86400;
        int hours = (total_seconds % 86400) / 3600;
        int minutes = (total_seconds % 3600) / 60;
        int seconds = total_seconds % 60;

        cout << "\rTime left: "
             << days << "d "
             << hours << "h "
             << minutes << "m "
             << seconds << "s   "
             << flush;

        this_thread::sleep_for(chrono::seconds(1));
        now = time(NULL);
    }

    inputThread.detach(); // stop listening

    if (stopCountdown) {
        cout << "\nCountdown stopped by user.\n";
    } else {
        cout << "\nEvent time has arrived!\n";
    }
}

void specifictimecountdown() {
    stopCountdown = false; 

    int h, m, s = 0;

    cout << "Enter the countdown time:" << endl;
    cout << "Hours: ";
    cin >> h;
    cout << "Minutes: ";
    cin >> m;

    cout << "Press 'q' then Enter to stop...\n";

    thread inputThread(listenForExit);
    inputThread.detach();

    while ((h > 0 || m > 0 || s > 0) && !stopCountdown) { 

        cout << "\rTime left: "
             << h << " hours, "
             << m << " minutes, "
             << s << " seconds   "
             << flush;

        this_thread::sleep_for(chrono::seconds(1));

        if (s > 0) {
            s--;
        } else if (m > 0) {
            m--;
            s = 59;
        } else if (h > 0) {
            h--;
            m = 59;
            s = 59;
        }
    }

    if (stopCountdown) {
        cout << "\nCountdown stopped.\n";
    } else {
        cout << "\rTime left: 0 hours, 0 minutes, 0 seconds   \n";
        cout << "Time's up!\n";
    }
}




int main(){
    string consent;
    cout<<"Welcome for T.d APP"<<endl;
    cout<<"********************************"<<endl;
    MYlocaltime();
    cout<<"[1]set specific time countdown\n[2]set specific date or event count down\n"<<endl;
    cout<<"Choose an option: "<<endl;
    int choice;
        cin>>choice;
        if (choice ==1){
            specifictimecountdown();
        }else if(choice ==2){
            setdate();
            calc();
        }
    return 0;}
    
