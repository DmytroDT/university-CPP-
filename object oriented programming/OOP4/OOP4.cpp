#include <iostream>
#include <list>
#define ls 6

using namespace std;

class Forecast {
protected: 
    int day, time;

public:
    Forecast(int Day=0, int Time=0) : day(Day),time(Time){}
     
    friend ostream& operator <<(ostream& os, Forecast& F) {
        os << endl;
        os << "Day=" << F.day << "\tTime=" << F.time;
        return os;
    }
};

class WindForecast:private Forecast {
private:
            int temp, hum, pre, windsp;


public:
    static      list<WindForecast> WindList;

    WindForecast(int Day=0, int Time=0, int Temp=0, int Hum=0,int Pre=0, int Windsp=0): Forecast(Day, Time),temp(Temp),hum(Hum),pre(Pre),windsp(Windsp){}
     
    friend ostream& operator <<(ostream& os, WindForecast& F) {
        os << endl;
        os << "Day=" << F.day << "\tTime=" << F.time <<"\nWind: Temperature="<<F.temp<<"\tHumidity="<<F.hum<<"\tPressure="<<F.pre<<"\tSpeed="<<F.windsp;
        return os;
    }

  void  Reinitialize(){

        cout << "Day=";
        cin >>  day;
        cout << "\nTime=";
        cin >> time;
        cout << "\nWind temperature=";
        cin >> temp;
        cout << "\nHumidity=";
        cin >> hum;
        cout << "\nPressure=";
        cin >> pre;
        cout << "\nSpeed=";
        cin >> windsp;

     }

 static float avgT(WindForecast* arr, int amount) {
        double result = 0;
        for (int i = 0; i < amount; i++) {
            result += arr[i].temp;
        }
        result /= amount;

        return result;
    }

 static  void MaxWind(WindForecast* arr, int amount) {
        int max=0;
        WindList.clear();
        for (int i = 0; i < amount; i++) {
            if (arr[max].windsp < arr[i].windsp) {
                max = i;
            }
        }
        for (int i = 0; i < amount; i++) {
            if (arr[max].windsp == arr[i].windsp) {
                    WindList.push_back(arr[i]);
            }
        }

    }

 static  void MaxHum(WindForecast* arr, int amount) {
     int max = 0;
     WindList.clear();
     for (int i = 0; i < amount; i++) {
         if (arr[max].hum < arr[i].hum) {
             max = i;
         }
     }
     for (int i = 0; i < amount; i++) {
         if (arr[max].hum == arr[i].hum) {
                 WindList.push_back(arr[i]);
         }
     }
    }

 static  void MinHum(WindForecast* arr, int amount) {
     int min = 0;
     WindList.clear();
     for (int i = 0; i < amount; i++) {
         if (arr[min].hum > arr[i].hum) {
             min = i;
         }
     }
     for (int i = 0; i < amount; i++) {
         if (arr[min].hum == arr[i].hum) {
                 WindList.push_back(arr[i]);
         }
     }
    }

 static void DisplayMM() {
     int listSize = WindForecast::WindList.size()-1;

     if (WindForecast::WindList.empty()) {
         cout << "Collection is empty." << endl;
     }
     else {
         for (int i = 0; i <= listSize; i++) {
             cout << WindForecast::WindList.front();
             WindForecast::WindList.pop_front();
         }
     }
 }

};

list<WindForecast> WindForecast::WindList;

int main()
{

    WindForecast FArray[ls] = { WindForecast(0,13,+19,50,2,12), WindForecast(1,14,+18,70,4,5) , WindForecast(2,15,+20,80,1,12) , WindForecast(3,14,+16,65,3,4),WindForecast(4,14,+17,80,4,5) };

    FArray[ls-1].Reinitialize();
    
    cout << "\nAverage temp=" << WindForecast::avgT(FArray, ls) << "\n\n";

    cout << "Days with max wind:" << endl;
    WindForecast::MaxWind(FArray, ls);
    WindForecast::DisplayMM();
   

    cout << "\n\nDays with max humidity:" << endl;
    WindForecast::WindForecast::MaxHum(FArray, ls);
    WindForecast::DisplayMM();

    cout << "\n\nDays with min humidity:" << endl;
    WindForecast::WindForecast::MinHum(FArray, ls);
    WindForecast::DisplayMM();

    cout << endl;
  }