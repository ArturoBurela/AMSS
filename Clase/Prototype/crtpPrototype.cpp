#ifndef FAMETHOD
#define FAMETHOD

#include <iostream>
#include <stdexcept>
#include <string>

using namespace std;

/*
El patron de prototipo está basado en copiar objetos ya existentes
*/

class Mundo {
private:
  /* data */

public:
  Mundo(string nombre) : nombre(nombre){}
  string nombre;
};

class Personaje{
    public:
      Personaje() = default;
      Personaje(string nombre): nombre(nombre){}
      string nombre;
      int telefono;
      Mundo* mundo;
      string correo;
      virtual Personaje* clone() = 0;
};

template<class SubClase>
class ClonePersonaje : public Personaje{
public:
  Personaje* clone(){
    return new SubClase(dynamic_cast<SubClase&>(*this));
  }

};

class Princesa: public ClonePersonaje<Princesa> {
    public:
      Princesa(string n){
        nombre = n;
      }
      Princesa(const Princesa& p){
        nombre = p.nombre;
        telefono = p.telefono;
        mundo = new Mundo(p.mundo->nombre);
        correo = p.correo;
      }
      void gritar(/* arguments */) {
        std::cout << "Ah!!" << '\n';
      }
};

class Villano: public ClonePersonaje<Villano> {
public:
  Villano(string n){
    nombre = n;
  }
  Villano(const Villano& p){
    nombre = p.nombre;
    telefono = p.telefono;
    mundo = new Mundo(p.mundo->nombre);
    correo = p.correo;
  }
  void secuestrar(/* arguments */) {
    std::cout << "#!$" << '\n';
  }
};

class Heroe: public ClonePersonaje<Heroe> {
public:
  Heroe(string n){
    nombre = n;
  }
  Heroe(const Heroe& p){
    nombre = p.nombre;
    telefono = p.telefono;
    mundo = new Mundo(p.mundo->nombre);
    correo = p.correo;
  }
  void salvar(/* arguments */) {
    std::cout << "Salvando" << '\n';
  }
};

#endif

int main(int argc, char const *argv[]) {
  Princesa* pri = new Princesa("Rapunzel");
  pri->correo= "princesita12@tec.mx";
  pri->telefono = 14324213;
  pri-> mundo = new Mundo("Paleta");
  Princesa* p = dynamic_cast<Princesa*>(pri->clone());
  pri->nombre = "RAPUNZEL";
  pri->mundo->nombre = "LOL";
  std::cout << p->nombre << '\n';
  std::cout << p->correo << '\n';
  std::cout << p->telefono << '\n';
  Princesa* pp = dynamic_cast<Princesa*>(p->clone());
  pp->mundo->nombre = "Paletita";
}
