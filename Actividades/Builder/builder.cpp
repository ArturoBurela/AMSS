#include <iostream>
#include <string>

using namespace std;

class Motor {
private:
  int potencia;
  int numSerie;
public:
  Motor() = default;
  Motor (int pot, int nS): potencia(pot), numSerie(nS){}
  int getPotencia() {return potencia;}
  int getNumSerie() {return numSerie;}
};

class Alas {
private:
  string marca;
  int numSerie;
  int hiper;
  int spoilers;
public:
  Alas () = default;
  Alas(string m, int n, int h, int s): marca(m), numSerie(n), hiper(h), spoilers(s){}
  string getMarca(){return marca;}
  int getNumSerie(){return numSerie;}
  int getHiper(){return hiper;}
  int getSpoilers(){return spoilers;}
};

class Builder;
class BoeingBuilder;
class Avion {
  friend class Builder;
  friend class BoeingBuilder;
private:
  Motor* motor;
  Alas* alas;
  string marca;
  string modelo;
  int numSerie;
  void setAlas(Alas* a){alas = a;}
  void setMotor(Motor* a){motor = a;}
  void setMarca(string m){marca = m;}
  void setModelo(string m){modelo = m;}
  void setNumSerie(int ns){numSerie = ns;}
public:
  Avion () = default;
  string getMarca(){return marca;}
  string getModelo(){return modelo;}
  int getNumSerie(){return numSerie;}
  Motor* getMotor(){return motor;}
  Alas* getAlas(){return alas;}
};

class Builder {
protected:
  Avion* avion;
public:
  Avion* getAvion(){return avion;}
  void createAvion() {
    avion = new Avion;
  }
  virtual Motor* buildMotor() = 0;
  virtual Alas* buildAlas() = 0;
  virtual string buildMarca() = 0;
  virtual string buildModelo() = 0;
  virtual int buildNumSerie() = 0;
  Builder () = default;
};

class BoeingBuilder : public Builder {
public:
  Motor* buildMotor(){
    Motor* motor = new Motor(10000,11111);
    avion->setMotor(motor);
    return motor;
  }
  Alas* buildAlas(){
    Alas* alas = new Alas("Boeing",22123,14,14);
    avion->setAlas(alas);
    return alas;
  }
  string buildMarca(){
    avion->setMarca("Boeing");
    return "Boeing";
  }
  string buildModelo(){
    avion->setModelo("747");
    return "747";
  }
  int buildNumSerie(){
    avion->setNumSerie(1234);
    return 1234;
  }
  BoeingBuilder () = default;
};

class Director {
private:
  Builder * builder;
public:
  void setBuilder(string tipo){
    if(tipo=="Boeing"){
      builder = new BoeingBuilder;
    }
  }
  Avion* getAvion(){
    return builder->getAvion();
  }
  void construct(){
    builder->createAvion();
    builder->buildAlas();
    builder->buildMotor();
    builder->buildMarca();
    builder->buildModelo();
    builder->buildNumSerie();
  }
  Director () = default;
};

int main(int argc, char const *argv[]) {
  Director d;
  d.setBuilder("Boeing");
  d.construct();
  Avion* a = d.getAvion();
  std::cout << a->getMarca() << '\n';
  return 0;
}
