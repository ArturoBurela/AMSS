#include <iostream>
#include <stdexcept>
#include <string>

using namespace std;

class Computadora{
protected:
  Computadora() = default;
  Computadora(string modelo): modelo(modelo){};
    public:
      string modelo;
      int serie;
      string marca;
      virtual Computadora* clone() = 0;
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

template<class Base, class SubClass>
class Clone : public Base{
public:
  Base* clone(){
    return new SubClass(dynamic_cast<SubClass&>(*this));
  }
  template<class Prod>
  Prod *factoryMethod(){
    return new Prod;
  }
};

class ComputadorasFactory : public Computadora{
public:
  template<class Prod>
  Prod *factoryMethod(){
    return new Prod;
  }
};


class Laptop: public Clone<Computadora, Laptop> {
private:
  Laptop(string n){
    modelo = n;
  }
    public:
      //Factory method
      static Laptop *getLaptop(string n){
        return new Laptop(n);
      }
      Laptop(const Laptop& p){
        modelo = p.modelo;
        serie = p.serie;
        marca = p.marca;
      }
};

class Desktop: public Clone<Computadora, Desktop> {
private:
  Desktop(string n){
    modelo = n;
  }
public:
  //Factory method
  static Desktop *getDesktop(string n){
    return new Desktop(n);
  }
  Desktop(const Desktop& p){
    modelo = p.modelo;
    serie = p.serie;
    marca = p.marca;
  }
};

class Netbook: public Clone<Computadora, Netbook> {
private:
  Netbook(string n){
    modelo = n;
  }
public:
  //Factory method
  static Netbook *getNetbook(string n){
    return new Netbook(n);
  }
  Netbook(const Netbook& p){
    modelo = p.modelo;
    serie = p.serie;
    marca = p.marca;
  }
};

class Tablet: public Clone<Computadora, Tablet> {
private:
  Tablet(string n){
    modelo = n;
  }
public:
  //Factory method
  static Tablet *getTablet(string n){
    return new Tablet(n);
  }
  Tablet(const Tablet& p){
    modelo = p.modelo;
    serie = p.serie;
    marca = p.marca;
  }
};

class Rack: public Clone<Computadora, Rack> {
private:
  Rack(string n){
    modelo = n;
  }
public:
  //Factory method
  static Rack *getRack(string n){
    return new Rack(n);
  }
  Rack(const Rack& p){
    modelo = p.modelo;
    serie = p.serie;
    marca = p.marca;
  }
};

class Tower: public Clone<Computadora, Tower> {
private:
  Tower(string n){
    modelo = n;
  }
public:
  //Factory method
  static Tower *getTower(string n){
    return new Tower(n);
  }
  Tower(const Tower& p){
    modelo = p.modelo;
    serie = p.serie;
    marca = p.marca;
  }
};

int main(int argc, char const *argv[]) {
  Clone<Computadora,Laptop> *x = new Clone<Computadora,Laptop>();
  /*Computadora *c = Computadora::getComputadora();
  //Uso de factoryMethod
  Laptop* pri = Laptop::getLaptop("XPS 15");
  pri->marca= "Dell";
  pri->serie = 14324213;
  //Uso de crtp
  Laptop* p = dynamic_cast<Laptop*>(pri->clone());
  pri->modelo = "Inspiron X";
  std::cout << p->modelo << '\n';
  std::cout << p->marca << '\n';
  std::cout << p->serie << '\n';
  Laptop* pp = dynamic_cast<Laptop*>(p->clone());*/
  //Laptop* x = new Laptop();
  //Uso de singleton

}
