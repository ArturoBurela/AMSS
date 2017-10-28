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

template<class T>
class Iterator;

template<class T>
class Collection;

class Board {
public:
    int space[BOARDX][BOARDY] = {{0}};

    Board() = default;
};

static Board board;

class GameObject {
public:
    int *x = new int[2];
    int posX;
    int posY;
    int alive = 1;
    string name;

    GameObject() = default;

    GameObject(int X, int Y, string n) : posX(X), posY(Y), name(n) {}

    int *moveRandom() {
        x[0] = 0;
        x[1] = 0;
        if (alive) {
            int y = rand() % (4) + 1;
            switch (y) {
                case 1:
                    //Derecha
                    if (posX != BOARDX - 1 && board.space[posX + 1][posY] != 2) {
                        board.space[posX][posY]--;
                        posX++;
                        board.space[posX][posY]++;
                    }
                case 2:
                    //Izquierda
                    if (posX != 0 && board.space[posX - 1][posY] != 2) {
                        board.space[posX][posY]--;
                        posX--;
                        board.space[posX][posY]++;
                    }
                case 3:
                    //Arriba
                    if (posY != BOARDY - 1 && board.space[posX][posY + 1] != 2) {
                        board.space[posX][posY]--;
                        posY++;
                        board.space[posX][posY]++;
                    }
                case 4:
                    //Abajo
                    if (posY != 0 && board.space[posX][posY - 1] != 2) {
                        board.space[posX][posY]--;
                        posY--;
                        board.space[posX][posY]++;
                    }
            }
            x[0] = posX;
            x[1] = posY;
        }
        return x;
    }

    int *lol() {
        return x;
    }

    void notify() {
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

class SpaceControl {
public:
    Collection<GameObject *> i;

    SpaceControl() = default;

    void notifyObservers() {
        Iterator<GameObject *> *it = i.getIterator();
        while (it->hasNext()) {
            it->next()->notify();
        }
    }
};

class SpaceGod {
private:
    int total = 0;
    int game = 1;
    static SpaceGod *instance;
    std::vector<GameObject *> objects;
    vector<GameObject *>::iterator it;
    SpaceControl control;

    SpaceGod() = default;

public:
    static SpaceGod *getInstance() {
        if (!instance) {
            instance = new SpaceGod;
            srand(time(NULL));
        }
        return instance;
    }

    template<class Object>
    Object *factoryMethod(int X, int Y, string n) {
        Object *x = new Object;
        x->name = n;
        x->posX = X;
        x->posY = Y;
        board.space[x->posX][x->posY]++;
        objects.push_back(x);
        GameObject *y = x;
        control.i.addElement(y);
        return x;
    }

    void createUniverse() {
        for (size_t i = 0; i < INITIALELEMENTS; i++) {
            int j = rand() % (6) + 1;
            //Create random graphics
            if (j == 1) {
                DesertPlanet *x = new DesertPlanet;
                //Assing random positions
                x->posX = rand() % (9);
                x->posY = rand() % (9);
                board.space[x->posX][x->posY]++;
                //Static name foo
                x->name = "FOO";
                //Push to universe
                objects.push_back(x);
                GameObject *y = x;
                control.i.addElement(y);
            }
            if (j == 2) {
                EarthAnalog *x = new EarthAnalog;
                //Assing random positions
                x->posX = rand() % (9);
                x->posY = rand() % (9);
                board.space[x->posX][x->posY]++;
                //Static name foo
                x->name = "FOO";
                //Push to universe
                objects.push_back(x);
                GameObject *y = x;
                control.i.addElement(y);
            }
            if (j == 3) {
                ExplorationSpaceCraft *x = new ExplorationSpaceCraft;
                //Assing random positions
                x->posX = rand() % (9);
                x->posY = rand() % (9);
                board.space[x->posX][x->posY]++;
                //Static name foo
                x->name = "FOO";
                //Push to universe
                objects.push_back(x);
                GameObject *y = x;
                control.i.addElement(y);
            }
            if (j == 4) {
                ColonizationSpaceCraft *x = new ColonizationSpaceCraft;
                //Assing random positions
                x->posX = rand() % (9);
                x->posY = rand() % (9);
                board.space[x->posX][x->posY]++;
                //Static name foo
                x->name = "FOO";
                //Push to universe
                objects.push_back(x);
                GameObject *y = x;
                control.i.addElement(y);
            }
            if (j == 5) {
                ObservationSpaceCraft *x = new ObservationSpaceCraft;
                //Assing random positions
                x->posX = rand() % (9);
                x->posY = rand() % (9);
                board.space[x->posX][x->posY]++;
                //Static name foo
                x->name = "FOO";
                //Push to universe
                objects.push_back(x);
                GameObject *y = x;
                control.i.addElement(y);
            }
            if (j == 6) {
                StonyAsteroid *x = new StonyAsteroid;
                //Assing random positions
                x->posX = rand() % (9);
                x->posY = rand() % (9);
                board.space[x->posX][x->posY]++;
                //Static name foo
                x->name = "FOO";
                //Push to universe
                objects.push_back(x);
                GameObject *y = x;
                control.i.addElement(y);
            }
            if (j == 7) {
                DesertPlanet *x = new DesertPlanet;
                //Assing random positions
                x->posX = rand() % (9);
                x->posY = rand() % (9);
                board.space[x->posX][x->posY]++;
                //Static name foo
                x->name = "FOO";
                //Push to universe
                objects.push_back(x);
                GameObject *y = x;
                control.i.addElement(y);
            }
        }
        std::cout << "Universe created" << '\n';
        printMap();
    }

    void startSimulation(/* arguments */) {
        while (game) {
            nextMove();
        }
        std::cout << "Terminado" << '\n';
    }

    void nextMove(/* arguments */) {
        //Move each objects
        int y, i = 0;
        int *x = new int[2];
        int l[4] = {0};
        for (it = objects.begin(); it != objects.end(); it++, i++) {
            x = objects.at(i)->moveRandom();
            checkColitions(x);
        }
        printMap();
    }

    void checkColitions(int x[]) {
        if (board.space[x[0]][x[1]] >= 2) {
            int i = 0;
            vector<GameObject *>::iterator it2;
            for (it2 = objects.begin(); it2 != objects.end(); it2++, i++) {
                if (objects.at(i)->posX == x[0] && objects.at(i)->posY == x[1]) {
                    std::cout << "Killing in position: " << x[0] << "" << x[1] << '\n';
                    objects.at(i)->alive = 0;
                    control.notifyObservers();
                    checkFinish();
                }
            }
        }
    }

    void checkFinish() {
        total = 0;
        int i = 0;
        vector<GameObject *>::iterator it2;
        for (it2 = objects.begin(); it2 != objects.end(); it2++, i++) {
            if (!objects.at(i)->alive) {
                total++;
            }
            if (total >= objects.size() - 1) {
                game = 0;
            }
        }
        std::cout << "Total:" << total << '\n';
    }

    void printMap() {
        for (size_t i = 0; i < BOARDX; i++) {
            for (size_t j = 0; j < BOARDY; j++) {
                std::cout << board.space[j][i] << " ";
            }
            std::cout << '\n';
        }
        std::cout << '\n';
    }
};

SpaceGod *SpaceGod::instance = 0;

int main(int argc, char const *argv[]) {
    /* Every constructor is private */
    //GameObject *x = new GameObject(1,2,"lol");
    //x->moveRandom();
    //Only one god can exist, god does everything
    SpaceGod *god = SpaceGod::getInstance();
    //God may create a random escenario, or you may tell it to create specific items
    god->createUniverse();
    //Tell god to create a few new Planets
    //God creates universe objects
    /*god->factoryMethod<DesertPlanet>(1,2,"lol");
    //God also shares power returning the object
    GameObject *y = god->factoryMethod<EarthAnalog>(5,2,"lol");
    //Tell god to create some ships
    god->factoryMethod<ExplorationSpaceCraft>(7,2,"lol");
    god->factoryMethod<ColonizationSpaceCraft>(1,8,"lol");
    god->factoryMethod<ObservationSpaceCraft>(4,2,"lol");
    //Tell god to create asteroids
    god->factoryMethod<IronAsteroid>(5,7,"lol");
    god->factoryMethod<StonyAsteroid>(3,5,"lol");
    //Now tell god to start game*/
    god->startSimulation();
    return 0;
}
