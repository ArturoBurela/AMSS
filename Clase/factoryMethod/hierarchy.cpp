#ifndef FAMETHOD
#define FAMETHOD

#include <iostream>
#include <stdexcept>

//template <class T>
class Product {
    public:
      void operation(){
        std::cout << "Operacion" << '\n';
      }
      void operation2(){
        std::cout << "Otro mensaje" << '\n';
      }
};

class Creator {
    private:
      virtual Product * createProduct(int type) = 0;
    public:
      Product* factoryMethod(int type){
        Product *p = createProduct(type);
        p->operation();
        return p;
      }
};

class CreatorA : public Creator {
public:
  Product * createProduct(int type){
    if (type==1) {
      /* code */
      return new Product;
    }
  }
};

#endif

int main(int argc, char const *argv[]) {
  //Creator deber{ia} de ser contructor privado
  Creator * c = new CreatorA;
  Product *p = c->factoryMethod(1);
  p->operation2();
  delete(c);
  delete(p);
}
