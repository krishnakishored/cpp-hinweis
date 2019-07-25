//CookBook - Creating an Exception Class for throwing and catching


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

class SimpleException //a simple exception class
{
  public:
    SimpleException(const string &msg) : msg_(msg) {}
    ~SimpleException() {}
    string getMessage() const { return (msg_); }
  private:
    string msg_;
};

void f(){
    throw(SimpleException("Mr.Exceptional"));
}

int main_simpleException()
{
    try
    {
        f();
    }
    catch (SimpleException& e){
        cout << "You threw an SimpleException: " << e.getMessage() << endl;
    }
    return 0;
}

//Making a Constructor Exception-Safe

class Device
{
  public:
    Device(int devno)
    {
        if (devno == 2)
            throw std::runtime_error("Big problem");
    }
    ~Device() {}
};

class Broker
{
  public:
    Broker(int devno1, int devno2) : dev1_(NULL), dev2_(NULL)
    {
        try
        {
            dev1_ = new Device(devno1); // Enclose the creation of heap
            dev2_ = new Device(devno2); // objects in a try block... 
        }
        catch (...)
        {
            delete dev1_; // ...clean up and rethrow if
            throw;        // something goes wrong.
        }
    }
    ~Broker()
    {
        delete dev1_;
        delete dev2_;
    }

  private:
    Broker();
    Device *dev1_;
    Device *dev2_;
};

int main_CtorExceptionSafe()
{
    try
    {
        Broker b(1, 2);
    }
    catch (std::exception &e)
    {
        std::cerr << "Exception: " << e.what() << endl;
    }
    return 0;
}

//Making an Initializer List Exception-Safe

class Broker2
{
public:
    // Broker(int devno1, int devno2):try:dev1_(Device(devno1)),dev2_(Device(devno2)){}
    Broker2 (int devno1, int devno2)
        try : 
            dev1_(Device(devno1)),
             dev2_(Device(devno2)) {} // list.
    catch(...)
    {
        throw;//Log the message or translate the error here
    }
    ~Broker2(){}
private:
    Broker2( );
    Device dev1_;
    Device dev2_;
};

int main_SafeInitializerList()
{
    try
    {
        Broker2 b(1, 2);
    }
    catch (std::exception &e)
    {
        std::cerr << "Exception: " << e.what() << endl;
    }
    return 0;
}

const static int DEFAULT_BUF_SIZE = 3;
const static int MAX_SIZE = 4096;

//ToDo: Making Member Functions Exception-Safe
template <typename T>
class MessageGeneric
{
  public:
    MessageGeneric(int bufSize = DEFAULT_BUF_SIZE) : bufSize_(bufSize),
                                                     initBufSize_(bufSize),
                                                     msgSize_(0),
                                                     buf_(new T[bufSize]) {}
    ~MessageGeneric()
    {
        delete[] buf_;
    }
    void appendData(int len, const T *data)
    {
        if (msgSize_ + len > MAX_SIZE)
        {
            throw std::out_of_range("Data size exceeds maximum size.");
        }
        if (msgSize_ + len > bufSize_)
        {
            int newBufSize = bufSize_;
            while ((newBufSize *= 2) < msgSize_ + len)
                ;
            T *p = new T[newBufSize];
            copy(buf_, buf_ + msgSize_, p); // Can these throw?
            copy(data, data + len, p + msgSize_);
            msgSize_ += len;
            bufSize_ = newBufSize;
            delete[] buf_; // Get rid of old buffer and point to new
            buf_ = p;
        }
        else
        {
            copy(data, data + len, buf_ + msgSize_);
            msgSize_ += len;
        }
    }

    // Copy the data out to the caller's buffer
    int getData(int maxLen, T *data)
    {
        if (maxLen < msgSize_)
        {
            throw std::out_of_range("This data is too big for your buffer.");
        }
        copy(buf_, buf_ + msgSize_, data);
        return (msgSize_);
    }

  private:
    MessageGeneric(const MessageGeneric &orig) {}
    MessageGeneric &operator=(const MessageGeneric &rhs) {}

    int bufSize_;
    int initBufSize_;
    int msgSize_;
    T *buf_;
};

//ToDo: Exception-safe assignment and copy construction
class Message
{
  public:
    Message(int bufSize = DEFAULT_BUF_SIZE) : bufSize_(bufSize),
                                              initBufSize_(bufSize),
                                              msgSize_(0),
                                              key_("")
    {
        buf_ = new char[bufSize]; // Note: now this is in the body
    }
    ~Message()
    {
        delete[] buf_;
    }

    // Exception-safe copy ctor
    Message(const Message &orig) : bufSize_(orig.bufSize_),
                                   initBufSize_(orig.initBufSize_),
                                   msgSize_(orig.msgSize_),
                                   key_(orig.key_)
    {                                                     // This can throw...
        buf_ = new char[orig.bufSize_];                   // ...so can this
        std::copy(orig.buf_, orig.buf_ + msgSize_, buf_); // This can't
    }
    // Exception-safe assignment, using the copy ctor
    Message &operator=(const Message &rhs)
    {
        Message tmp(rhs);   // Copy construct a temporary
        swapInternals(tmp); // Swap members with it
        return (*this);     // When we leave, tmp is destroyed, taking the original data with it
    }
    const char *data()
    {
        return (buf_);
    }

  private:
    void swapInternals(Message &msg)
    {
        // Since key_ is not a built-in data type it can throw,
        // so do it first.
        std::swap(key_, msg.key_);
        // If it hasn't thrown, then do all the primitives
        std::swap(bufSize_, msg.bufSize_);
        std::swap(initBufSize_, msg.initBufSize_);
        std::swap(msgSize_, msg.msgSize_);
        std::swap(buf_, msg.buf_);
    }
    int bufSize_;
    int initBufSize_;
    int msgSize_;
    char *buf_;
    string key_;
};

int main(){
     main_simpleException();
     main_CtorExceptionSafe();
      main_SafeInitializerList();
    return 0;
}