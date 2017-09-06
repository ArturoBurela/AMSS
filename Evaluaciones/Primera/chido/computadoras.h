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
  template<class Tipo>
  static Tipo* factoryMethod(){
    return new Tipo;
  }
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
public:
  ComputadorasFactory ();
  Computadora* getComputadora();
};

template <class Tipo>
class Clone:public Computadora
{
	public:
		Computadora* clonar(){
      return new Tipo(dynamic_cast<Tipo&>(*this));
    }
};

class Laptop: public Clone<Laptop> {
  friend class Computadora;
private:
  Laptop(){}
public:
  static Laptop *getLaptop();
};

class Desktop: public Clone<Desktop> {
  friend class Computadora;
private:
  Desktop(){}
public:
  static Desktop *getDesktop();
};

class Netbook: public Clone<Netbook> {
  friend class Computadora;
private:
  Netbook(){}
public:
  static Netbook *getNetbook();
};

class Tablet: public Clone<Tablet> {
  friend class Computadora;
private:
  Tablet(){}
public:
  static Tablet *getTablet();
};

class Rack: public Clone<Rack> {
  friend class Computadora;
private:
  Rack(){}
public:
  static Rack *getRack();
};

class Tower: public Clone<Tower> {
  friend class Computadora;
private:
  Tower(){}
public:
  static Tower *getTower();
};
