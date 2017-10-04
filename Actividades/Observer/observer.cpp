#include <iostream>
#include <string>
#include <vector>

using namespace std;

//Observer base class
class Observer {
public:
  string name;
public:
  virtual void notify()=0;
  Observer () = default;
};

class Subject {
protected:
  string name;
  //List of observers
  std::vector<Observer*> observers;
  vector<Observer*>::iterator it;
public:
  //Add new observer
  void addObserver(Observer* ob){
    observers.push_back(ob);
  }
  void deleteObserver(Observer* ob){
    //Iterate the observers, if found delete, alert if not
    int i = 0;
    for(it = observers.begin(); it != observers.end(); it++,i++ ){
      if(observers.at(i)==ob){
        // erase the element
        observers.erase (observers.begin()+i);
        return;
      }
    }
    std::cout << "Este observador no estaba suscrito!" << '\n';
  }
  void notifyObservers(){
    //Call each observer notify
    int i = 0;
    for(it = observers.begin(); it != observers.end(); it++,i++ ){
      observers.at(i)->notify();
    }
  }
  Subject () = default;
};

class MVSNoticias : public Observer {
public:
  MVSNoticias(){
    name = "MVS Noticias";
  }
  void notify(){
    std::cout << name << " tiene noticias!" << '\n';
  }
};

class TelevisaNoticias : public Observer {
public:
  TelevisaNoticias(){
    name = "Televisa Noticias";
  }
  void notify(){
    std::cout << name << " tiene noticias!" << '\n';
  }
};

class RadioRedNoticias : public Observer {
public:
  RadioRedNoticias(){
    name = "Radio Red Noticias";
  }
  void notify(){
    std::cout << name << " tiene noticias!" << '\n';
  }
};

class NoticiasInternacionales : public Observer {
public:
  NoticiasInternacionales(){
    name = "Noticias Internacionales";
  }
  void notify(){
    std::cout << name << " tiene noticias!" << '\n';
  }
};

class Trump : public Subject {
public:
  Trump(){
    name = "Trump";
  }
};

class Pena : public Subject {
public:
  Pena(){
    name = "Peña";
  }
};

class Coreano : public Subject {
public:
  Coreano(){
    name = "Coreano";
  }
};

int main(int argc, char const *argv[]) {
  //Create all Observes and Subjects
  //Observers
  MVSNoticias* mvs = new MVSNoticias;
  TelevisaNoticias* televisa = new TelevisaNoticias;
  RadioRedNoticias* radiored = new RadioRedNoticias;
  NoticiasInternacionales* notiinternacional = new NoticiasInternacionales;
  //Subjects
  Trump trump;
  Pena pena;
  Coreano coreano;
  //Suscribe observers to subjects!
  trump.addObserver(mvs);
  trump.addObserver(televisa);
  trump.addObserver(radiored);
  trump.addObserver(notiinternacional);
  pena.addObserver(televisa);
  pena.addObserver(radiored);
  coreano.addObserver(notiinternacional);
  //Call to notify
  trump.notifyObservers();
  pena.notifyObservers();
  coreano.notifyObservers();
  //You may delete an observer from subject
  pena.deleteObserver(radiored);
  pena.deleteObserver(mvs);
  //Call again to notify
  pena.notifyObservers();
  //Free observers memory
  delete mvs;
  delete televisa;
  delete radiored;
  delete notiinternacional;
}
