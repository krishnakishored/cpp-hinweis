// C++ Recipes - Classes

#ifndef IOSTREAM
#define IOSTREAM
#include<iostream>
#endif


#ifndef VECTOR
#define VECTOR
#include<vector>
#endif



#ifndef STRING
#define STRING
#include<string>
#endif

using std::cout;
using std::endl;
using std::string;

//Giving Each Instance of a Class a Unique Identifier
class UniqueID
{
  protected:
    static int nextID;

  public:
    int id;
    UniqueID();
    UniqueID(const UniqueID &orig);
    UniqueID &operator=(const UniqueID &orig);
};
int UniqueID::nextID = 0;
UniqueID::UniqueID()
{
    id = ++nextID;
}
UniqueID::UniqueID(const UniqueID &orig)
{
    id = orig.id;
}
UniqueID &UniqueID::operator=(const UniqueID &orig)
{
    id = orig.id;
    return (*this);
}

int main_uniqueIDForObject()
{
    UniqueID a;
    std::cout << a.id << std::endl;
    UniqueID b;
    std::cout << b.id << std::endl;
    UniqueID c;
    std::cout << c.id << std::endl;
    return 0;
}

class Singleton
{
  public:
    // This is how clients can access the single instance 
    static Singleton* getInstance();
    void setValue(int val) { value_ = val; }
    int getValue() { return (value_); }

  protected:
    int value_;

  private:
    static Singleton *inst_; // The one, single instance 
    Singleton() : value_(0) {} // private constructor 
    Singleton(const Singleton&);
    Singleton &operator=(const Singleton &);
};
// Define the static Singleton pointer
Singleton *Singleton::inst_ = NULL;
Singleton *Singleton::getInstance()
{
    if (inst_ == NULL)
    {
        inst_ = new Singleton();
    }
    return (inst_);
}
int main_SingletonClass()
{
    Singleton *p1 = Singleton::getInstance();
    p1->setValue(10);
    Singleton *p2 = Singleton::getInstance();
    cout << "Value = " << p2->getValue() << '\n';
    return 0;
}

//  a class whose members need to be different types in different situations
//  Writing a class template
template<typename T>
class TreeNode {
    public:
        TreeNode(const T& val): val_(val),left_(NULL),right_(NULL){}
        ~TreeNode()
        {
            delete left_;
            delete right_;
        }
        const T& getVal() const {return(val_);}
        void setVal(const T& val){val_ = val;}
        void addChild(TreeNode<T> *p){
            const T& other = p->getVal();
            if(other>val_){
                if(right_){
                    right_->addChild(p);
                }
                else{
                    right_=p;
                }
            }
            else{
                if(left_){
                    left_->addChild(p);
                }
                else{
                    left_=p;
                }
            }
        }
        const TreeNode<T> *getLeft() {return left_;}
        const TreeNode<T> *getRight() {return right_;}

      private:
        T  val_;
        TreeNode<T> *left_;
        TreeNode<T> *right_;

};

int main_ClassTemplate()
{
    TreeNode<string> node1("frank");
    TreeNode<string> node2("larry");
    TreeNode<string> node3("bill");
    node1.addChild(&node2);
    node1.addChild(&node3);
    return 0;
}

// Overloading the Increment and Decrement Operators
class Score
{
  public:
    Score() : score_(0) {}
    Score(int i) : score_(i) {}
    Score &operator++()
    { // prefix ++score_;
        return (*this);
    }
    const Score operator++(int)
    { // postfix
        Score tmp(*this);
        ++(*this); // Take advantage of the prefix operator
        return (tmp);
    }
    Score &operator--()
    {
        --score_;
        return (*this);
    }
    const Score operator--(int x)
    {
        Score tmp(*this);
        --(*this);
        return (tmp);
    }
    int getScore() const { return (score_); }

  private:
    int score_;
};

int main_overloadIncrementDecrement()
{
    Score player1(50);
    player1++;
    ++player1; // score_ = 52
    cout << "Score = " << player1.getScore() << '\n';
    (--player1)--; // score_ = 50
    cout << "Score = " << player1.getScore() << '\n';
    return 0;
}

class Balance
{
    // These have to see private data
    friend const Balance operator+(const Balance &lhs, const Balance &rhs);
    friend const Balance operator+(double lhs, const Balance &rhs);
    friend const Balance operator+(const Balance &lhs, double rhs);

  public:
    Balance() : val_(0.0) {}
    Balance(double val) : val_(val) {}
    ~Balance() {}
    // Unary operators
    Balance &operator+=(const Balance &other)
    {
        val_ += other.val_;
        return (*this);
    }
    Balance &operator+=(double other)
    {
        val_ += other;
        return (*this);
    }
    double getVal() const { return (val_); }

  private:
    double val_;
};

// Binary operators
const Balance operator+(const Balance &lhs, const Balance &rhs)
{
    Balance tmp(lhs.val_ + rhs.val_);
    return (tmp);
}
const Balance operator+(double lhs, const Balance &rhs)
{
    Balance tmp(lhs + rhs.val_);
    return (tmp);
}
const Balance operator+(const Balance &lhs, double rhs)
{
    Balance tmp(lhs.val_ + rhs);
    return (tmp);
}


int main_overloadingArithmaticOperators()
{
    Balance checking(500.00), savings(23.91);
    checking += 50;
    Balance total = checking + savings;
    cout << "Checking balance: " << checking.getVal() << '\n';
    cout << "Total balance: " << total.getVal() << '\n';
    return 0;
}

// Calling a specific version of a virtual function

class Base
{
  public:
    virtual void foo() { cout << "Base::foo()" << endl; }
};
class Derived : public Base
{
  public:
    virtual void foo() { cout << "Derived::foo()" << endl; }
};

int main_callingSpecificVirtualFunction()
{
    Derived *p = new Derived();
    p->foo();       // Calls the derived version
    p->Base::foo(); // Calls the base version }
    return 0;
}

int main()
{
    main_callingSpecificVirtualFunction();
    main_ClassTemplate();
    main_overloadIncrementDecrement();
    main_overloadingArithmaticOperators();
    main_SingletonClass();
    main_uniqueIDForObject();
    return 0;
}