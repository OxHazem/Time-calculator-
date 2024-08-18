#include <string>
#include <iostream>
#include <cmath>
#include <ctime>
#include <thread> 
#include <chrono> 
using namespace std;
tm examtime{};
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
void calc() {
    time_t elyoum = time(NULL);
    time_t event_time = mktime(&examtime);

    while (difftime(event_time, elyoum) > 0) {
        double seconds_left = difftime(event_time, elyoum);

        int days_left = seconds_left / (60 * 60 * 24);
        int hours_left = (seconds_left - (days_left * 60 * 60 * 24)) / (60 * 60);
        int minutes_left = (seconds_left - (days_left * 60 * 60 * 24) - (hours_left * 60 * 60)) / 60;
        int seconds_left_final = seconds_left - (days_left * 60 * 60 * 24) - (hours_left * 60 * 60) - (minutes_left * 60);

        
        cout << "\rTime left: " << days_left << " days, "
             << (hours_left < 10 ? "0" : "") << hours_left << " hours, "
             << (minutes_left < 10 ? "0" : "") << minutes_left << " minutes, "
             << (seconds_left_final < 10 ? "0" : "") << seconds_left_final << " seconds."
             << flush;

        this_thread::sleep_for(chrono::seconds(1)); // Wait for 1 second

        elyoum = time(NULL); // Update current time
    }

    cout << "\nEvent time has arrived!" << endl;
}

void specifictimecountdown() {
    int h, m,s;
    cout << "Enter the countdown time:" << endl;
    cout << "Hours: ";
    cin >> h;
    cout << "Minutes: ";
    cin >> m;
     while (h > 0 || m > 0) {
        cout << "Time left: " << h << " hours and " << m << " minutes." <<s<<" seconds"<< endl;
        this_thread::sleep_for(chrono::seconds(1)); // Wait for 1 minute
        if(s>0){
            s--;
        
        }else if (m > 0) {
            m--;
            s=59;
        } else if (h > 0) {
            h--; 
            m = 59;
            s=59;
        }
    }
    

    // Final update at the last minute
    cout << "Time left: 0 hours and 0 minutes." << endl;
    this_thread::sleep_for(chrono::seconds(60)); // Wait for the last minute to pass
    cout << "Time's up!" << endl;
}




int main(){
    string consent;
    cout<<"Welcome for T.d APP"<<endl;
    cout<<"********************************"<<endl;
    cout<<"Dear user the app will need to get your local time please approve [y/n]: ";
    cin>>consent;
    if ((consent =="y")||(consent =="Y")){
        MYlocaltime();
        cout<<"[1]set specific time countdown\n [2] set specific date or event count down\n"<<endl;
        cout<<"Choose an option: "<<endl;
        int choice;
        cin>>choice;
        if (choice ==1){
            specifictimecountdown();
        }else if(choice ==2){
            setdate();
            calc();
        }
    }else{
        cout<<"App will not run without getting your local time."<<endl;
        return 0;
    }
    
}