#include <iostream>
#include <list>
#define ls 7

using namespace std;

class Forecast {
protected:
    int day, time;

public:
    Forecast(int Day = 0, int Time = 0) : day(Day), time(Time) {}

    friend ostream& operator <<(ostream& os, Forecast& F) {
        os << endl;
        os << "Day=" << F.day << "\tTime=" << F.time;
        return os;
    }

   virtual void  Reinitialize() {
        cout << "Day=";
        cin >> day;
        cout << "\nTime=";
        cin >> time;
   }

};

class FallForecast : public Forecast {
private:

    bool rain=0, snow = 0, hail = 0, lightnings = 0;
    static list<FallForecast> FallList;

    void setBool(bool& var,char ch) {

        if ((ch == 'T') || (ch == 't')) {
            var = true;
        }
        else {
            var = false;
        }
    }

    static   string displayBool(bool var) {
        if (var) {
            return "true";
        }     
        return "false";
    }

public:
         FallForecast(int Day = 0, int Time = 0,bool Rain=0, bool Snow = 0, bool Hail = 0, bool Lightnings = 0): Forecast(Day,Time),rain(Rain),snow(Snow),hail(Hail),lightnings(Lightnings) {}

        void  Reinitialize() override {
            char tempchar='a';

            cout << "\nReinitializing fall forecast:\nDay=";
            cin >> day;
            cout << "\nTime=";
            cin >> time;

            cout << "\nRain=";
            cin >> tempchar;
            setBool(rain, tempchar);

            cout << "\nSnow=";
            cin >> tempchar;
            setBool(snow, tempchar);

            cout << "\nhail=";
            cin >> tempchar;
            setBool(hail, tempchar);

            cout << "\nlightnings=";
            cin >> tempchar;
            setBool(lightnings, tempchar);

        }

        friend ostream& operator <<(ostream& os, FallForecast& F) {
            os << endl;
            os << "Day=" << F.day << "\tTime=" << F.time;
            os << "\nRain=" << displayBool(F.rain) << "\tSnow=" << displayBool(F.snow) << "\tHail=" << displayBool(F.hail) << "\tlightnings=" << displayBool(F.lightnings);
            os << endl;
            return os;
        }


        static bool checkFall(FallForecast F, int st) {
            switch (st) {
            case(0):if (F.rain) { return true; } break;
            case(1):if (F.snow) { return true; }  break;
            case(2):if (F.hail) { return true; }  break;
            case(3):if (F.lightnings) { return true; }  break;
            }
            return false;
        }

        static void FallStat(Forecast** arr, int size,int par1,int par2) {
            FallList.clear();
            for (int i = 0; i < size; i++) {
                if (dynamic_cast<FallForecast*>(arr[i])) {
                   if (checkFall(*dynamic_cast<FallForecast*>(arr[i]), par1) && checkFall(*dynamic_cast<FallForecast*>(arr[i]), par2)) {
                       FallList.push_back(*dynamic_cast<FallForecast*>(arr[i])); 
                   }
                }

            }
        }

        static void DisplayFL() {
            int listSize = FallForecast::FallList.size() - 1;

            if (FallForecast::FallList.empty()) {
                cout << "Collection is empty." << endl;
            }
            else {
                for (int i = 0; i <= listSize; i++) {
                    cout << FallForecast::FallList.front();
                    FallForecast::FallList.pop_front();
                }
            }
        }

};

class WindForecast :public Forecast {
private:
    int temp, hum, pre, windsp;
    static      list<WindForecast> WindList;

public:

    WindForecast(int Day = 0, int Time = 0, int Temp = 0, int Hum = 0, int Pre = 0, int Windsp = 0) : Forecast(Day, Time), temp(Temp), hum(Hum), pre(Pre), windsp(Windsp) {}

    friend ostream& operator <<(ostream& os, WindForecast& F) {
        os << endl;
        os << "Day=" << F.day << "\tTime=" << F.time << "\nWind: Temperature=" << F.temp << "\tHumidity=" << F.hum << "\tPressure=" << F.pre << "\tSpeed=" << F.windsp;
        return os;
    }

     void  Reinitialize() override {
         
        cout << "\nReinitializing wind forecast:\nDay=";
        cin >> day;
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

    static double avgT(Forecast** arr,int size) {
        int amount = 0;
        double result = 0;
        for (int i = 0; i < size; i++) {
            if (dynamic_cast<WindForecast*>(arr[i])) {
                result += dynamic_cast<WindForecast*>(arr[i])->temp;
                amount++;
            }
        }

        result /= amount;

        return result;
    }

    static  void MaxWind(Forecast** Barr, int amount) {
        int max = 0;
        WindList.clear();
        for (int i = 0; i < amount; i++) {
            if (dynamic_cast<WindForecast*>(Barr[i])) {

              if (dynamic_cast<WindForecast*>(Barr[max])->windsp < dynamic_cast<WindForecast*>(Barr[i])->windsp) {
              max = i;
              }
            }
        }
         for (int i = 0; i < amount; i++) {
             if (dynamic_cast<WindForecast*>(Barr[i])) {
                 if (dynamic_cast<WindForecast*>(Barr[max])->windsp == dynamic_cast<WindForecast*>(Barr[i])->windsp) {
                     WindList.push_back(*dynamic_cast<WindForecast*>(Barr[i]));
                 }
             }
         }

    }

    static  void MaxHum(Forecast** Barr, int amount) {
        int max = 0;
        WindList.clear();
        for (int i = 0; i < amount; i++) {
            if (dynamic_cast<WindForecast*>(Barr[i])) {
                if (dynamic_cast<WindForecast*>(Barr[max])->hum < dynamic_cast<WindForecast*>(Barr[i])->hum) {
                    max = i;
                }
            }
        }
        for (int i = 0; i < amount; i++) {
            if (dynamic_cast<WindForecast*>(Barr[i])) {
                if (dynamic_cast<WindForecast*>(Barr[max])->hum == dynamic_cast<WindForecast*>(Barr[i])->hum) {
                    WindList.push_back(*dynamic_cast<WindForecast*>(Barr[i]));
                }
            }
        }
    }
   
    static  void MinHum(Forecast** Barr, int amount) {
        int min = 0;
        WindList.clear();
        for (int i = 0; i < amount; i++) {
            if (dynamic_cast<WindForecast*>(Barr[i])) {
                if (dynamic_cast<WindForecast*>(Barr[min])->hum > dynamic_cast<WindForecast*>(Barr[i])->hum) {
                    min = i;
                }
            }
        }
        for (int i = 0; i < amount; i++) {
            if (dynamic_cast<WindForecast*>(Barr[i])) {
                if (dynamic_cast<WindForecast*>(Barr[min])->hum == dynamic_cast<WindForecast*>(Barr[i])->hum) {
                    WindList.push_back(*dynamic_cast<WindForecast*>(Barr[i]));
                }
            }
        }
    }

    static void DisplayMM() {
        int listSize = WindForecast::WindList.size() - 1;

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
list<FallForecast> FallForecast::FallList;


class ForecastType {
public:

    virtual ~ForecastType() {}
    virtual void tellForecast(Forecast** Barr, int amount) = 0;

};

class ReportFor {
private:
    Forecast** Barr;
    int amount;
    ForecastType* forecastType;
public:
    ReportFor(Forecast** Barr, int amount) {
        this->Barr = Barr;
        this->amount = amount;

    }

    void setForecastType(ForecastType* forecastType) {
        this->forecastType = forecastType;
    }

    void reportForecast() {
        forecastType->tellForecast(Barr, amount);
    }

    void setAmount(int newAMount) {
        amount = newAMount;
    }

    void setArrRef(Forecast** Barr) {
        this->Barr = Barr;
    }


};

class MaxWind : public ForecastType {
public:
    void tellForecast(Forecast** Barr, int amount) {

        cout << "Days with max wind:" << endl;
        WindForecast::MaxWind(Barr, amount);
        WindForecast::DisplayMM();

    }

};

class MaxHum : public ForecastType {
public:
    void tellForecast(Forecast** Barr, int amount) {
        cout << "\n\nDays with max humidity:" << endl;
        WindForecast::MaxHum(Barr, amount);
        WindForecast::DisplayMM();
    }
};

class MinHum : public ForecastType {
public:
    void tellForecast(Forecast** Barr, int amount) {

        cout << "\n\nDays with min humidity:" << endl;
        WindForecast::MinHum(Barr, amount);
        WindForecast::DisplayMM();
    }
};

class RainSnow : public ForecastType {
public:
    void tellForecast(Forecast** Barr, int amount) {

        cout << "\n\nDays rain and snow:" << endl;
        FallForecast::FallStat(Barr, amount, 0, 1);
        FallForecast::DisplayFL();
    }
};

class HailLigtnings : public ForecastType {
public:
    void tellForecast(Forecast** Barr, int amount) {

        cout << "\n\nDays hail and lightnings:" << endl;
        FallForecast::FallStat(Barr, amount, 2, 3);
        FallForecast::DisplayFL();
    }
};



int main()
{

   Forecast* FArray[ls] = { new WindForecast(0,13,+19,50,2,12),new FallForecast(1,14,1,0,1,0),new WindForecast(2,15,+20,80,1,12),new FallForecast(3,17,0,0,1,1),
       new WindForecast(4,14,+17,80,4,5),new FallForecast(5,13,1,1,0,0),new WindForecast() };

   ReportFor rep(FArray, ls);

   rep.setForecastType(new MaxWind);

   rep.reportForecast();

   rep.setForecastType(new RainSnow);

   rep.reportForecast();

   rep.setForecastType(new HailLigtnings);

   rep.reportForecast();

}