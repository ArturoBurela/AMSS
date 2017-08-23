#ifndef CLOCK
#define CLOCK

#include <iostream>
#include <time.h>

//template <class T>
class Clock {
    private:
        static Clock *instance;
        Clock(){};
    public:
      static Clock *getInstance()
      {
        if(!instance){
          instance = new Clock;
        }
        return instance;
      }
      void printHour(){
        time_t theTime = time(NULL);
        struct tm *aTime = localtime(&theTime);
        int hour=aTime->tm_hour;
        int min=aTime->tm_min;
        std::cout << "Hour:"<< hour << " Minute:" << min << '\n';
      };
};

Clock* Clock::instance = 0;

#endif

int main(int argc, char const *argv[]) {
  Clock* lol = Clock::getInstance();
  lol->printHour();
  return 0;
}
