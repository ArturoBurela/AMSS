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
//Max number of initial random elements
#ifndef INITIALELEMENTS
#define INITIALELEMENTS 7
#endif

using namespace std;

template <class T>
class Iterator;

template <class T>
class Collection;

class Board {
private:
  int space[BOARDX][BOARDY] = {{0}};
public:
  Board () = default;
};

class GameObject {
public:
  int posX;
  int posY;
  string name;
  GameObject() = default;
  GameObject (int X, int Y, string n): posX(X), posY(Y), name(n){}
  void moveRandom(){
    srand(time(NULL));
    switch (rand()%(4 + 1)) {
      case 1:
        if (posX != BOARDX - 1) {
          posX++;
        }
      case 2:
        if (posX != 0) {
          posX--;
        }
      case 3:
        if (posY != BOARDY - 1) {
          posY++;
        }
      case 4:
        if (posY != 0) {
          posY--;
        }
    }
  }
  void notify(){
    std::cout << name << "recibió alerta de colisión!" << '\n';
  }
};

class SpaceCraft : public GameObject {
public:
  SpaceCraft() = default;
};

class Asteroid : public GameObject {
public:
  Asteroid() = default;
};

class Planet : public GameObject {
public:
  Planet() = default;
};

class ExplorationSpaceCraft : public SpaceCraft {
public:
  ExplorationSpaceCraft() = default;
};

class ColonizationSpaceCraft : public SpaceCraft {
public:
  ColonizationSpaceCraft() = default;
};

class ObservationSpaceCraft : public SpaceCraft {
public:
  ObservationSpaceCraft() = default;
};

class StonyAsteroid : public Asteroid {
public:
  StonyAsteroid() = default;
};

class IronAsteroid : public Asteroid {
public:
  IronAsteroid() = default;
};

class DesertPlanet : public Planet {
public:
  DesertPlanet() = default;
};

class EarthAnalog : public Planet {
public:
  EarthAnalog() = default;
};

template <class T>
class Collection {
protected:
  T * array;
  int size;
  int cont;
public:
  friend class Iterator<T>;
  Collection (){
    size = MAXELEMENTS;
    array = new T[size];
    cont = 0;
  }
  void addElement(T value) {
    if (cont<=size) {
      array[cont++] = value;
    }else{
      std::cout << "No hay más espacio" << '\n';
    }
  }
  Iterator<T>* getIterator();
  T at(int pos){
    return array[pos];
  }
};

template <class T>
class Iterator {
protected:
  Collection<T> coll;
  int cont = 0;
public:
  Iterator (const Collection<T>& coll): coll(coll){}
  bool hasNext(){
    if(cont < coll.cont)
      return true;
    return false;
  }
  T next(){
    return coll.at(cont++);
  }
};

template <class T>
bool isEven(T n){
  if(n%2==0){
    return true;
  }
  return false;
}

template <class T, typename F>
void find_if(Iterator<T> it, F f){
  while (it.hasNext()) {
    T x = it.next();
    if(f(x))
      std::cout << x << '\n';
  }
}

template <class T>
Iterator<T>* Collection<T>::getIterator(){
  return new Iterator<T>(*this);
}

class SpaceControl {
public:
  Collection<GameObject*> i;
  SpaceControl () = default;
  void notifyObservers(){
    Iterator<GameObject*>* it = i.getIterator();
    while (it->hasNext()) {
      it->next()->notify();
    }
  }
};

class SpaceGod {
private:
  int total = 0;
  static SpaceGod *instance;
  Board board;
  std::vector<GameObject*> objects;
  vector<GameObject*>::iterator it;
  SpaceControl control;
  SpaceGod () = default;
public:
  static SpaceGod *getInstance()
  {
    if(!instance){
      instance = new SpaceGod;
    }
    return instance;
  }
  template<class Object>
  Object *factoryMethod(int X, int Y, string n){
    Object *x = new Object;
    x->name = n;
    x->posX = X;
    x->posY = Y;
    objects.push_back(x);
    GameObject *y = x;
    control.i.addElement(y);
    return x;
  }
  void createUniverse() {
    for (size_t i = 0; i < INITIALELEMENTS; i++) {
      int j = rand()%(7 + 1);
      if (j == 1) {
        DesertPlanet* x = new DesertPlanet;
        //Assing random positions
        x->posX = rand()%(4 + 1);
        x->posY = rand()%(4 + 1);
        //Static name foo
        x->name = "FOO";
        //Push to universe
        objects.push_back(x);
        GameObject *y = x;
        control.i.addElement(y);
      }
      if (j == 2) {
        EarthAnalog* x = new EarthAnalog;
        //Assing random positions
        x->posX = rand()%(4 + 1);
        x->posY = rand()%(4 + 1);
        //Static name foo
        x->name = "FOO";
        //Push to universe
        objects.push_back(x);
        GameObject *y = x;
        control.i.addElement(y);
      }
      if (j == 3) {
        ExplorationSpaceCraft* x = new ExplorationSpaceCraft;
        //Assing random positions
        x->posX = rand()%(4 + 1);
        x->posY = rand()%(4 + 1);
        //Static name foo
        x->name = "FOO";
        //Push to universe
        objects.push_back(x);
        GameObject *y = x;
        control.i.addElement(y);
      }
      if (j == 4) {
        ColonizationSpaceCraft* x = new ColonizationSpaceCraft;
        //Assing random positions
        x->posX = rand()%(4 + 1);
        x->posY = rand()%(4 + 1);
        //Static name foo
        x->name = "FOO";
        //Push to universe
        objects.push_back(x);
        GameObject *y = x;
        control.i.addElement(y);
      }
      if (j == 5) {
        ObservationSpaceCraft* x = new ObservationSpaceCraft;
        //Assing random positions
        x->posX = rand()%(4 + 1);
        x->posY = rand()%(4 + 1);
        //Static name foo
        x->name = "FOO";
        //Push to universe
        objects.push_back(x);
        GameObject *y = x;
        control.i.addElement(y);
      }
      if (j == 6) {
        StonyAsteroid* x = new StonyAsteroid;
        //Assing random positions
        x->posX = rand()%(4 + 1);
        x->posY = rand()%(4 + 1);
        //Static name foo
        x->name = "FOO";
        //Push to universe
        objects.push_back(x);
        GameObject *y = x;
        control.i.addElement(y);
      }
      if (j == 7) {
        DesertPlanet* x = new DesertPlanet;
        //Assing random positions
        x->posX = rand()%(4 + 1);
        x->posY = rand()%(4 + 1);
        //Static name foo
        x->name = "FOO";
        //Push to universe
        objects.push_back(x);
        GameObject *y = x;
        control.i.addElement(y);
      }
    }
  }
  void nextMove(/* arguments */) {
    //Move each objects
    int i = 0;
    for(it = objects.begin(); it != objects.end(); it++, i++){
      std::cout << "LOL" << '\n';
      objects.at(i)->moveRandom();
      /*if(objects.at(i)==ob){
        // erase the element
        objects.erase (objects.begin()+i);
        return;
      }*/
    }
  }
  void checkColitions(/* arguments */) {
    /* code */
  }
};

SpaceGod* SpaceGod::instance = 0;

int main(int argc, char const *argv[]) {
  /* Every constructor is private */
  //GameObject *x = new GameObject(1,2,"lol");
  //x->moveRandom();
  //Create god, god does everything
  SpaceGod *god = SpaceGod::getInstance();
  //God may create a random escenario, or you may tell it to create specific items
  god->createUniverse();
  //Tell god to create a few new Planets
  //God automatically handle universe objects
  god->factoryMethod<DesertPlanet>(1,2,"lol");
  //But god also shares power returning the object
  GameObject *y = god->factoryMethod<EarthAnalog>(1,2,"lol");
  //Tell god to create some ships
  god->factoryMethod<ExplorationSpaceCraft>(1,2,"lol");
  god->factoryMethod<ColonizationSpaceCraft>(1,2,"lol");
  god->factoryMethod<ObservationSpaceCraft>(1,2,"lol");
  //Tell god to create asteroids
  god->factoryMethod<IronAsteroid>(1,2,"lol");
  god->factoryMethod<StonyAsteroid>(1,2,"lol");
  //Now tell god to move everything
  god->nextMove();
  return 0;
}
