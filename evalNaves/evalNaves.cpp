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

//Game Graphics Classes

class GameObject {
    friend class ObjectFactory;

public:
    int posX;
    int posY;
    int alive;
    string name;

    //Observer model notify
    void notify() {
        if (alive) {
            std::cout << "Yo " << name << " recibí alerta de colisión" << '\n';
        }
    }

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

//Clases collection e iterator

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

    ~Collection() {
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
    //Contenedor de objetos
    std::vector<GameObject *> objects;
    //Coleccion de Suscriptores
    Collection<GameObject *> suscribers;
public:
    //Creador de objectos
    ObjectFactory *factory;

    GameSimulation() {
        //Obtener la fabrica
        factory = ObjectFactory::getFactory();
        //Random en funcion del tiempo
        srand(time(NULL));
    };

    ~GameSimulation() {
        //Eliminar fabrica
        delete factory;
        //liberar objectos
        vector<GameObject *>::iterator it;
        for (it = objects.begin(); it != objects.end(); it++) {
            delete *it;
        }
        objects.clear();
    };

    void randomScenario() {
        //Crear objectos de clase aleatoria
        GameObject *x;
        for (int i = 0; i < INITIALELEMENTS; ++i) {
            int j = rand() % (6) + 1;
            switch (j) {
                case 1:
                    x = factory->create<DesertPlanet>();
                    break;
                case 2:
                    x = factory->create<EarthAnalog>();
                    break;
                case 3:
                    x = factory->create<StonyAsteroid>();
                    break;
                case 4:
                    x = factory->create<IronAsteroid>();
                    break;
                case 5:
                    x = factory->create<ObservationSpaceCraft>();
                    break;
                case 6:
                    x = factory->create<ColonizationSpaceCraft>();
                    break;
                case 7:
                    x = factory->create<ExplorationSpaceCraft>();
                    break;
            }
            //Asignar pos random
            x->posX = rand() % (9);
            x->posY = rand() % (9);
            //Agregar a suscriptores y lista de objetos
            objects.push_back(x);
            suscribers.addElement(x);
            //Actualizar mapa
            space[x->posX][x->posY]++;
            //Verificar colision
            checkCol(x->posX, x->posY);
        }
        int i = 0;
        //Iterador objects
        vector<GameObject *>::iterator it;
        for (it = objects.begin(); it != objects.end(); it++, i++) {
            std::cout << "Graphic: " << i << " name " << objects.at(i)->name << '\n';
        }
        printMap();
    }

    void starGame() {
        int total = 0;
        vector<GameObject *>::iterator it;
        int i = 0;
        //Loop infinito
        while (1) {
            nextMove();
            //Verificar después de cada movimiento todos los muertos
            for (it = objects.begin(); it != objects.end(); it++, i++) {
                if (objects.at(i)->alive == 0) {
                    total++;
                }
            }
            i = 0;
            //Salir del juego si ya no hay vivos
            if (total >= objects.size() - 1) {
                break;
            }
            total = 0;
        }
    }

    void nextMove() {
        //Iterador objects
        vector<GameObject *>::iterator it;
        int i = 0;
        for (it = objects.begin(); it != objects.end(); it++, i++) {
            if (objects.at(i)->alive) {
                //Mover random
                int y = rand() % (4) + 1;
                switch (y) {
                    case 1:
                        //Derecha
                        if (objects.at(i)->posX != BOARDX - 1 &&
                            space[objects.at(i)->posX + 1][objects.at(i)->posY] != 2) {
                            space[objects.at(i)->posX][objects.at(i)->posY]--;
                            objects.at(i)->posX++;
                            space[objects.at(i)->posX][objects.at(i)->posY]++;
                        }
                    case 2:
                        //Izquierda
                        if (objects.at(i)->posX != 0 && space[objects.at(i)->posX - 1][objects.at(i)->posY] != 2) {
                            space[objects.at(i)->posX][objects.at(i)->posY]--;
                            objects.at(i)->posX--;
                            space[objects.at(i)->posX][objects.at(i)->posY]++;
                        }
                    case 3:
                        //Arriba
                        if (objects.at(i)->posY != BOARDY - 1 &&
                            space[objects.at(i)->posX][objects.at(i)->posY + 1] != 2) {
                            space[objects.at(i)->posX][objects.at(i)->posY]--;
                            objects.at(i)->posY++;
                            space[objects.at(i)->posX][objects.at(i)->posY]++;
                        }
                    case 4:
                        //Abajo
                        if (objects.at(i)->posY != 0 && space[objects.at(i)->posX][objects.at(i)->posY - 1] != 2) {
                            space[objects.at(i)->posX][objects.at(i)->posY]--;
                            objects.at(i)->posY--;
                            space[objects.at(i)->posX][objects.at(i)->posY]++;
                        }
                }
                //Después de mover revisar colisiones
                checkCol(objects.at(i)->posX, objects.at(i)->posY);
            }
        }
        //Imprimir el mapa
        printMap();
    }

    void checkCol(int X, int Y) {
        //Iterador objects
        vector<GameObject *>::iterator it;
        int i = 0;
        if (space[X][Y] >= 2) {
            for (it = objects.begin(); it != objects.end(); it++, i++) {
                if (objects.at(i)->posX == X && objects.at(i)->posY == Y) {
                    //Kill ship
                    objects.at(i)->alive = 0;
                    //Notify all ships
                    notifyObservers();
                }
            }
        }
    }

    void printMap() {
        for (size_t i = 0; i < BOARDX; i++) {
            for (size_t j = 0; j < BOARDY; j++) {
                std::cout << space[j][i] << " ";
            }
            std::cout << '\n';
        }
        std::cout << '\n';
    }

    void notifyObservers() {
        Iterator<GameObject *> *it = suscribers.getIterator();
        while (it->hasNext()) {
            it->next()->notify();
        }
    }
};

int main(int argc, char const *argv[]) {
    GameSimulation game;
    game.randomScenario();
    game.starGame();
    //Cant create objects without factory
    //EarthAnalog* l = new EarthAnalog();
    return 0;
}
