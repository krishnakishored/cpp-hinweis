// ---------- SMART POINTER EXAMPLE ----------s

#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
#include <ctime>
#include <numeric>
#include <cmath>
#include <sstream>
#include <iterator>
#include <memory>
#include <stdio.h>

// A Smart pointer is a class that provides the power of pointers, 
// but also handles the reallocation of memory when it is no longer required (The pointer is automatically destroyed)

// typedef creates an alias for a more complex type name
typedef std::vector<int32_t> intVec;

int main_malloc()
{
    // MALLOC EXAMPLE
    // When you define a primitive type like int or float 
    // you define exactly the amount of space to set aside
    
    // If you need to define how much space to set aside
    // you could call malloc() and tell it how much
    // space to set aside and it returns the address to
    // that memory address
    
    int amtToStore;
    std::cout << "How many numbers do you want to store : ";
    std::cin >> amtToStore;
    
    // Create an int pointer and set aside enough space
    int * pNums;
    
    // Cast the pointer and define how much space to set aside
    pNums = (int *) malloc(amtToStore * sizeof(int));
    
    // Check if memory was allocated
    if(pNums != NULL){
        int i = 0;
        
        // Store values
        while(i < amtToStore){
            std::cout << "Enter a Number : ";
            std::cin >> pNums[i];
            i++;
        }
    }
    
    std::cout << "You entered these numbers\n";
    for(int i = 0; i < amtToStore; i++){
        std::cout << pNums[i] << "\n";
    }
    
    // Delete the pointer
    delete pNums;

    return 0;
}

int main_smartpointer(){
     
    // Smart Pointer Solution
    int amtToStore;
    std::cout << "How many numbers do you want to store : ";
    std::cin >> amtToStore;
    
    // This memory will be automatically reallocated
    std::unique_ptr<int[]> pNums(new int[amtToStore]);
    
    // unique_ptr can only have one owner
    // so this throws an error
    // std::unique_ptr<int[]> pNums2 = pNums;
    // I'll cover how to do this with shared_ptr
    // in a later tutorial
    
    if(pNums != NULL){
        int i = 0;
        
        // Store values
        while(i < amtToStore){
            std::cout << "Enter a Number : ";
            std::cin >> pNums[i];
            i++;
        }
    }
    
    std::cout << "You entered these numbers\n";
    for(int i = 0; i < amtToStore; i++){
        std::cout << pNums[i] << "\n";
    }

    return 0;
}

// ---------- END SMART POINTER EXAMPLE ----------

// ---------- POLYMORPHIC TEMPLATES ----------

// Here I demonstrate how to use templates polymorphically 
// Base class all pizzas inherit along with MakePizza which will be overridden
class Pizza{
public:
    virtual void MakePizza() = 0;
};
 
// The last templates that will be called
class NYStyleCrust {
public:
  std::string AddIngredient() {
    return "Crust so Thin You can See through it\n\n";
  }
};
 
class DeepDishCrust {
public:
  std::string AddIngredient() {
    return "Super Awesome Chicago Deep Dish Crust\n\n";
  }
};

// End of last templates called
 
// The middle templates called
template <typename T>
class LotsOfMeat: public T {
public:
  std::string AddIngredient() {
    return "Lots of Random Meat, " + T::AddIngredient();
  }
};
 
template <typename T>
class Vegan: public T {
public:
  std::string AddIngredient() {
    return "Vegan Cheese, Veggies, " + T::AddIngredient();
  }
};

// End of middle templates called
 
// We inherit from Pizza as well as the initial next template
template <typename T>
class MeatNYStyle: public T, public Pizza {
public:
  void MakePizza() { std::cout << "Meat NY Style Pizza : " << 
          T::AddIngredient(); }
};
 
template <typename T>
class VeganDeepDish: public T, public Pizza {
public:
  void MakePizza() { std::cout << "Vegan Deep Dish : " << 
          T::AddIngredient(); }
};

int main_polymorphictemplates()
{
    // unique_ptr is a smart pointer that disposes of
    // a pointer when it is no longer in use
    std::vector<std::unique_ptr<Pizza>> pizzaOrders;
    
    // Generate Pizza types and place them at the end of the vector
    pizzaOrders.emplace_back(new MeatNYStyle<LotsOfMeat<NYStyleCrust>>());
    pizzaOrders.emplace_back(new VeganDeepDish<Vegan<DeepDishCrust>>());
    
    // Call the pizzas and execute the directions for making them
    for(auto &pizza: pizzaOrders){
        pizza->MakePizza();
    }
    
    return 0;
}

int main()
{
    // main_malloc();
    // main_smartpointer();
    main_polymorphictemplates();
}

// ---------- END POLYMORPHIC TEMPLATES ----------