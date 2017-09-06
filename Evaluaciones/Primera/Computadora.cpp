#ifndef FAMETHOD
#define FAMETHOD

#include <iostream>
#include <stdexcept>
using namespace std;

class Computadora {
protected:
  Computadora();
  float ram;
  int cpuCores;
  string modelo;
  string fabricante;

public:
  //crtp
  virtual Computadora* clone() = 0;
  //
  template<class Tipo>
  Tipo *getComputadora(){
    return new Tipo;
  }
  template<class Prod>
  Prod *factoryMethod(){
    return new Prod;
  }
  void seleccionarComponentes(/* arguments */) {
    /* code */
  }
  void EnsamblarComponentes(/* arguments */) {
    /* code */
  }
  void InstalarConfigurarSoftware(/* arguments */) {
    /* code */
  }
  void Empaquetar(/* arguments */) {
    /* code */
  }
};

template<class Tipo>
class Clone : public Computadora{
protected:
  Clone();
public:
  Computadora* clone(){
    return new Tipo(dynamic_cast<Tipo&>(*this));
  }

};

class Laptop: public Clone<Laptop> {
private:
  Laptop(){};
public:
  void operation(/* arguments */) {
    std::cout << "Este es el producto A" << '\n';
  }
  static Laptop *getLaptop(){
    return new Laptop;
  }
};

//Singleton FactoryComputadora, solo puede haber una fábrica
class FactoryComputadora {
private:
  static FactoryComputadora *instance;
  FactoryComputadora(){};
public:
  template<class Tipo>
  Tipo *factoryMethod(int op){
    std::cout << op << '\n';
    return Laptop::getLaptop();
  }
  static FactoryComputadora *getFactory(){
    if(!instance){
      instance = new FactoryComputadora;
    }
    return instance;
  }
};

#endif

FactoryComputadora* FactoryComputadora::instance = 0;

int main(int argc, char const *argv[]) {
  //Singleton de Factory
  FactoryComputadora *lol = FactoryComputadora::getFactory();
  //
  Laptop *l = lol->factoryMethod<Laptop>(1);
  return 0;
}
