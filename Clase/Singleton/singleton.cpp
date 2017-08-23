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
        std::cout << "/* message */" << '\n';
        return instance;
      }
      void operacion(){
        std::cout << "Dir de instancia"<< instance << '\n';
      };
};

Singleton* Singleton::instance = 0;

#endif

int main(int argc, char const *argv[]) {
  //Singleton s;
  //s.operacion();
  Singleton* lol = Singleton::getInstance();
  lol->operacion();
  Singleton* lol2 = Singleton::getInstance();
  lol->operacion();
  Singleton* lol3 = Singleton::getInstance();
  lol->operacion();
  return 0;
}
