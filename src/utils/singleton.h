#ifndef SINGLETON_H
#define SINGLETON_H

template <class T>
class Singleton
{
public:
    Singleton (const Singleton&) = delete;
    
    
    static T& getInstance ()
    {
        static T instance;
        return instance;
    }


    void operator = (const Singleton&) = delete;

protected:
    Singleton () {}
    ~Singleton () {}

private:

};

#endif