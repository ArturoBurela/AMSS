#include <iostream>
#include <stdexcept>
#include <string>

using namespace std;

class Computadora{
protected:
  Computadora();
public:
  string modelo;
  int serie;
  string marca;
  virtual Computadora* clonar() = 0;
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
};

class Desktop: public Clone<Desktop> {
  friend class ComputadorasFactory;
private:
  Desktop(){}
};

class Netbook: public Clone<Netbook> {
  friend class ComputadorasFactory;
private:
  Netbook(){}
};

class Tablet: public Clone<Tablet> {
  friend class ComputadorasFactory;
private:
  Tablet(){}
};

class Rack: public Clone<Rack> {
  friend class ComputadorasFactory;
private:
  Rack(){}
};

class Tower: public Clone<Tower> {
  friend class ComputadorasFactory;
private:
  Tower(){}
};
