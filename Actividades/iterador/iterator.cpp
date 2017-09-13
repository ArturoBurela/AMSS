#include <iostream>

template <class T>
class Iterator;

template <class T>
class Collection {
protected:
  T * array;
  int size;
  int cont;
public:
  friend class Iterator<T>;
  Collection (){
    size = 10;
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

int main(int argc, char const *argv[]) {
  Collection<int> i;
  i.addElement(1);
  i.addElement(2);
  i.addElement(3);
  i.addElement(4);
  i.addElement(5);
  i.addElement(6);
  i.addElement(7);
  i.addElement(8);
  i.addElement(9);
  Iterator<int>* it = i.getIterator();
  while (it->hasNext()) {
    std::cout << it->next() << '\n';
  }
  Iterator<int>* it2 = i.getIterator();
  find_if<int,bool (&)(int)>(*it2,isEven<int>);
  return 0;
}
