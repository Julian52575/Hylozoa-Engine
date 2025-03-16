#ifndef LIB_SINGLETON_HPP
    #define LIB_SINGLETON_HPP

namespace Lib {

// https://stackoverflow.com/questions/41328038/singleton-template-as-base-class-in-c
// need default constructor
    template <typename T>
    class Singleton {
        public:
            static T& getInstance()
            {
                static T instance;
                return instance;
            }

        protected:
            Singleton() {}
            ~Singleton() {}

        public:
            Singleton(Singleton const &) = delete;
            Singleton& operator=(Singleton const &) = delete;

    };  // class Singletone
}  // lib
#endif  // LIB_SINGLETONE_HPP
