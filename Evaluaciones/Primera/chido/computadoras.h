#include <iostream>
#include <stdexcept>
#include <string>

using namespace std;

class Computadora{
  friend class ComputadorasFactory;
protected:
  Computadora();
public:
  virtual ~Computadora ();
  Computadora *newComputadora();
  string modelo;
  int serie;
  string marca;
  virtual Computadora* clone();
  void seleccionarComponentes();
  void EnsamblarComponentes();
  void InstalarConfigurarSoftware();
  void Empaquetar();
};

class ComputadorasFactory {
protected:
  static ComputadorasFactory *factory;
  ComputadorasFactory ();
public:
  static ComputadorasFactory* getFactory();
  template<class Tipo>
  Tipo* factoryMethod(){
    return new Tipo;
  }
  template<class Tipo>
  static Tipo* create(string modelo){
    Tipo x = new Tipo;
    x.modelo = modelo;
    return x;
  }
};

template <class Tipo>
class Clone:public Computadora
{
protected:
  Clone(){}
public:
  Computadora* clonar(){
    return new Tipo(dynamic_cast<Tipo&>(*this));
  }
};

class Laptop: public Clone<Laptop> {
  friend class ComputadorasFactory;
private:
  Laptop(){}
public:
  static Laptop *getLaptop();
};

class Desktop: public Clone<Desktop> {
  friend class ComputadorasFactory;
private:
  Desktop(){}
public:
  static Desktop *getDesktop();
};

class Netbook: public Clone<Netbook> {
  friend class ComputadorasFactory;
private:
  Netbook(){}
public:
  static Netbook *getNetbook();
};

class Tablet: public Clone<Tablet> {
  friend class ComputadorasFactory;
private:
  Tablet(){}
public:
  static Tablet *getTablet();
};

class Rack: public Clone<Rack> {
  friend class ComputadorasFactory;
private:
  Rack(){}
public:
  static Rack *getRack();
};

class Tower: public Clone<Tower> {
  friend class ComputadorasFactory;
private:
  Tower(){}
public:
  static Tower *getTower();
};
