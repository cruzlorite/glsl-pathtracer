//    Copyright(C) 2019, 2020 José María Cruz Lorite
//
//    This file is part of voxfracturer.
//
//    voxfracturer is free software: you can redistribute it and/or modify
//    it under the terms of the GNU General Public License as published by
//    the Free Software Foundation, either version 3 of the License, or
//    (at your option) any later version.
//
//    voxfracturer is distributed in the hope that it will be useful,
//    but WITHOUT ANY WARRANTY; without even the implied warranty of
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//    GNU General Public License for more details.
//
//    You should have received a copy of the GNU General Public License
//    along with voxfracturer.  If not, see <https://www.gnu.org/licenses/>.

#ifndef VOXFRACTURER_UTIL_SINGLETON_H_
#define VOXFRACTURER_UTIL_SINGLETON_H_

namespace util {

    /**
     * This class provides a base for singleton class
     *
     * @code Usage example
     * class Foo : public Singleton<Foo> {
     * private:
     *    // Singleton<Foo> needs access to the constructor and destructor
     *    friend class Singleton<Foo>;
     *    // constructor and destructor must be private
     *    Foo() {}
     *    ~Foo() {}
     * }
     *
     * @see https://en.wikipedia.org/wiki/Singleton_pattern
     */
    template<typename T>
    class Singleton {
    public:

        /**
         * Get singleton instance
         * @return The singleton instance
         */
        static T &instance();

        // Prevents wrong use of singleton classes
        Singleton(Singleton const &)            = delete;
        Singleton(Singleton &&)                 = delete;
        Singleton &operator=(Singleton const &) = delete;
        Singleton &operator=(Singleton &&)      = delete;

    protected:

        // Derived classes need access to Singleton() and ~Singleton()
        Singleton() = default;
        virtual ~Singleton() = default;

    };

    template<typename T>
    T &Singleton<T>::instance() {
        static T instance;  //!< Singleton static instance
        return instance;
    }
}

#endif //VOXFRACTURER_UTIL_SINGLETON_H_