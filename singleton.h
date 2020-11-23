#ifndef _SINGLETON_HPP
#define _SINGLETON_HPP

// Singleton.hpp

// declaration of class

template <typename T>
class Singleton {
   private:
    static T* _ptrInstance;

   public:
    static void setInstance(T* p) {
        _ptrInstance = p;
    }

    static bool doesInstanceExist() {
        bool output = not(NULL == _ptrInstance);
        return output;
    }

    static T* getInstance() {
        return _ptrInstance;
    }
};

// declaration of static class
template <typename T>
T* Singleton<T>::_ptrInstance(NULL);

#endif