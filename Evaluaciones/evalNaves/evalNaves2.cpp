#include <iostream>
#include <string>
#include <vector>
//Board size
#ifndef BOARDX
#define BOARDX 10
#endif
#ifndef BOARDY
#define BOARDY 10
#endif
//Max number of graphic elements
#ifndef MAXELEMENTS
#define MAXELEMENTS 20
#endif
//Number of initial random elements
#ifndef INITIALELEMENTS
#define INITIALELEMENTS 7
#endif

using namespace std;
//Singleton Factory Class
class ObjectFactory {
private:
  static ObjectFactory* instance;
  ObjectFactory(){};
public:
  template<class Object>
  Object *create() {
      Object *x = new Object;
      return x;
  }
  template<class Object>
  Object *create(int X, int Y, string n) {
      Object *x = new Object;
      x->name = n;
      x->posX = X;
      x->posY = Y;
      return x;
  }
  static ObjectFactory* getFactory(){
    if (!instance) {
        instance = new ObjectFactory;
    }
    return instance;
  }
};

ObjectFactory *ObjectFactory::instance = 0;

class GameObject {
friend class ObjectFactory;
public:
  int posX;
  int posY;
  int alive = 1;
  string name;
protected:
    GameObject(){
      posX = 0;
      posY = 0;
      name = "fooFighter";
    };
    GameObject(int X, int Y, string n) : posX(X), posY(Y), name(n) {}
};

class SpaceCraft : public GameObject {
protected:
    SpaceCraft() = default;
};

class Asteroid : public GameObject {
protected:
    Asteroid() = default;
};

class Planet : public GameObject {
friend class ObjectFactory;
protected:
    Planet() = default;
};

class ExplorationSpaceCraft : public SpaceCraft {
protected:
    ExplorationSpaceCraft() = default;
};

class ColonizationSpaceCraft : public SpaceCraft {
protected:
    ColonizationSpaceCraft() = default;
};

class ObservationSpaceCraft : public SpaceCraft {
protected:
    ObservationSpaceCraft() = default;
};

class StonyAsteroid : public Asteroid {
protected:
    StonyAsteroid() = default;
};

class IronAsteroid : public Asteroid {
protected:
    IronAsteroid() = default;
};

class DesertPlanet : public Planet {
friend class ObjectFactory;
protected:
    DesertPlanet() = default;
};

class EarthAnalog : public Planet {
protected:
    EarthAnalog() = default;
};

int main(int argc, char const *argv[]) {
  ObjectFactory* factory = ObjectFactory::getFactory();
  DesertPlanet* planet = factory->create<DesertPlanet>(1,2,"lol");
  //Cant create objects without factory
  //EarthAnalog* l = new EarthAnalog();
  delete factory;
  delete planet;
  /* code */
  return 0;
}
