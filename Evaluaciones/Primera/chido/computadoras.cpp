#include "computadoras.h"

Computadora::Computadora(){
  Computadora::seleccionarComponentes();
  Computadora::EnsamblarComponentes();
  Computadora::InstalarConfigurarSoftware();
  Computadora::Empaquetar();
}

Computadora::~Computadora (){

}

Computadora* Computadora::newComputadora(){
  return new Computadora;
}

Computadora* Computadora::clone(){
  return new Computadora;
}
void Computadora::seleccionarComponentes(){
  std::cout << "Seleccionando componentes" << '\n';
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

Computadora* ComputadorasFactory::getComputadora(){
  return new Computadora;
}

int main(int argc, char const *argv[]) {
  ComputadorasFactory *fabrica = new ComputadorasFactory;
  delete fabrica;
  return 0;
}
