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

class Princesa: public Personaje {
    public:
      Princesa(string n): Personaje(n){}
      Princesa(const Princesa& p){
        nombre = p.nombre;
        telefono = p.telefono;
        mundo = new Mundo(p.mundo->nombre);
        correo = p.correo;
      }
      void gritar(/* arguments */) {
        std::cout << "Ah!!" << '\n';
      }
      Personaje* clone(){
        return new Princesa(*this);
      }
};

class Villano: public Personaje {
public:
  Villano(string n): Personaje(n){}
  Villano(const Villano& p){
    nombre = p.nombre;
    telefono = p.telefono;
    mundo = new Mundo(p.mundo->nombre);
    correo = p.correo;
  }
  void secuestrar(/* arguments */) {
    std::cout << "#!$" << '\n';
  }
  Personaje* clone(){
    return new Villano(*this);
  }
};

class Heroe: public Personaje {
public:
  Heroe(string n): Personaje(n){}
  Heroe(const Heroe& p){
    nombre = p.nombre;
    telefono = p.telefono;
    mundo = new Mundo(p.mundo->nombre);
    correo = p.correo;
  }
  void salvar(/* arguments */) {
    std::cout << "Salvando" << '\n';
  }
  Personaje* clone(){
    return new Heroe(*this);
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
}
