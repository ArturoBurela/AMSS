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

template<class T>
class Iterator;

template<class T>
class Collection;

//Singleton Factory Class
class ObjectFactory {
private:
    static ObjectFactory *instance;

    ObjectFactory() {};
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

    static ObjectFactory *getFactory() {
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
    int alive;
    string name;
protected:
    GameObject() {
        posX = 0;
        posY = 0;
        name = "Foo Fighter";
        alive = 1;
    };

    GameObject(int X, int Y, string n) : posX(X), posY(Y), name(n) {
        alive = 1;
    }
};

class SpaceCraft : public GameObject {
    friend class ObjectFactory;
protected:
    SpaceCraft() = default;
};

class Asteroid : public GameObject {
    friend class ObjectFactory;
protected:
    Asteroid() = default;
};

class Planet : public GameObject {
    friend class ObjectFactory;
protected:
    Planet() = default;
};

class ExplorationSpaceCraft : public SpaceCraft {
    friend class ObjectFactory;
protected:
    ExplorationSpaceCraft() = default;
};

class ColonizationSpaceCraft : public SpaceCraft {
    friend class ObjectFactory;
protected:
    ColonizationSpaceCraft() = default;
};

class ObservationSpaceCraft : public SpaceCraft {
    friend class ObjectFactory;
protected:
    ObservationSpaceCraft() = default;
};

class StonyAsteroid : public Asteroid {
    friend class ObjectFactory;
protected:
    StonyAsteroid() = default;
};

class IronAsteroid : public Asteroid {
    friend class ObjectFactory;
protected:
    IronAsteroid() = default;
};

class DesertPlanet : public Planet {
    friend class ObjectFactory;

protected:
    DesertPlanet() = default;
};

class EarthAnalog : public Planet {
    friend class ObjectFactory;
protected:
    EarthAnalog() = default;
};

template<class T>
class Collection {
protected:
    T *array;
    int size;
    int cont;
public:
    friend class Iterator<T>;

    Collection() {
        size = MAXELEMENTS;
        array = new T[size];
        cont = 0;
    }

    ~Collection(){
        delete[] array;
    }

    void addElement(T value) {
        if (cont <= size) {
            array[cont++] = value;
        } else {
            std::cout << "No hay más espacio" << '\n';
        }
    }

    Iterator<T> *getIterator();

    T at(int pos) {
        return array[pos];
    }
};

template<class T>
class Iterator {
protected:
    Collection<T> coll;
    int cont = 0;
public:
    Iterator(const Collection<T> &coll) : coll(coll) {}

    bool hasNext() {
        if (cont < coll.cont)
            return true;
        return false;
    }

    T next() {
        return coll.at(cont++);
    }
};

template<class T>
bool isEven(T n) {
    if (n % 2 == 0) {
        return true;
    }
    return false;
}

template<class T, typename F>
void find_if(Iterator<T> it, F f) {
    while (it.hasNext()) {
        T x = it.next();
        if (f(x))
            std::cout << x << '\n';
    }
}

template<class T>
Iterator<T> *Collection<T>::getIterator() {
    return new Iterator<T>(*this);
}


class GameSimulation {
private:
    //Escenario
    int space[BOARDX][BOARDY] = {{0}};
    //Contenedor de objetos (vivos y muertos)
    std::vector<GameObject *> objects;
    //Iterador objects
    vector<GameObject *>::iterator it;
    //Coleccion de Suscriptores (solo vivos)
    //Collection<GameObject *> suscribers;
public:
    //Creador de objectos
    ObjectFactory* factory;
    GameSimulation(){
        //Obtener la fabrica
        factory = ObjectFactory::getFactory();
        //Random en funcion del tiempo
        srand(time(NULL));
    };
    ~GameSimulation(){
        delete factory;
        //delete suscribers;
    };
    void randomScenario(){
        GameObject* x;
        for (int i = 0; i < INITIALELEMENTS; ++i) {

        }
        delete x;
    }
};

int main(int argc, char const *argv[]) {
    GameSimulation game;
    game.randomScenario();
    //Cant create objects without factory
    //EarthAnalog* l = new EarthAnalog();
    return 0;
}
