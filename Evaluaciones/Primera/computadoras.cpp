#include "computadoras.h"

Computadora::Computadora(){
  Computadora::seleccionarComponentes();
  Computadora::EnsamblarComponentes();
  Computadora::InstalarConfigurarSoftware();
  Computadora::Empaquetar();
}

void Computadora::seleccionarComponentes(){
  std::cout << "Seleccionar componentes" << '\n';
}

void Computadora::EnsamblarComponentes(){
  std::cout << "Ensamblar componentes" << '\n';
}

void Computadora::InstalarConfigurarSoftware(){
  std::cout << "Instalar y configurar software" << '\n';
}

void Computadora::Empaquetar(){
  std::cout << "Empaquetar Computadora" << '\n';
}

ComputadorasFactory::ComputadorasFactory(){

}

ComputadorasFactory* ComputadorasFactory::getFactory(){
  if (factory) {
    return factory;
  } else {
    return new ComputadorasFactory;
  }
}

ComputadorasFactory * ComputadorasFactory::factory = 0;

int main(int argc, char const *argv[]) {
  //Cant do any of these
  /*Computadora *c = new Computadora;
  Clone<Laptop> *clone = new Clone<Laptop>;
  Laptop *l = new Laptop;
  Desktop *d = new Desktop;
  Netbook *n = new Netbook;
  Tablet *t = new Tablet;
  Rack *r = new Rack;
  Tower *to = new Tower;*/

  //Create ComputadorasFactory singleton
  ComputadorasFactory *fabrica = ComputadorasFactory::getFactory();

  //Use factoryMethod to create computadoras
  Laptop *l = fabrica->factoryMethod<Laptop>();
  Netbook *n = fabrica->factoryMethod<Netbook>();
  Tower *t = fabrica->factoryMethod<Tower>();

  //You can use CRTP
  Laptop *l2 = dynamic_cast<Laptop*>(l->clonar());
  Desktop *d = dynamic_cast<Desktop*>(l->clonar());


  //Dont forget to clear memory
  /*delete fabrica;
  delete t;
  delete l;
  delete ...
  ...*/
}
