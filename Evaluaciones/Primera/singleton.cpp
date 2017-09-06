#ifndef SINGLETON
#define SINGLETON

#include <iostream>
#include <stdexcept>

//template <class T>
class Singleton {
    private:
        static Singleton *instance;
        Singleton(){};
    public:
      // Access methods
      //template <class T>
      static Singleton *getInstance()
      {
        //instance =! NULL ? return instance : instance = new Singleton;
        if(!instance){
          instance = new Singleton;
        }
        return instance;
      }
      void operation(){
        std::cout << "Dir instance"<< instance << '\n';
      };
};

Singleton* Singleton::instance = 0;

#endif

int main(int argc, char const *argv[]) {
  //Singleton s;
  //s.operation();
  Singleton* lol = Singleton::getInstance();
  lol->operation();
  Singleton* lol2 = Singleton::getInstance();
  lol->operation();
  Singleton* lol3 = Singleton::getInstance();
  lol->operation();
  return 0;
}
