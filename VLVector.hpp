//
// Created by ilay on 8/4/2020.
//

#ifndef EXAMCPP_VLVECTOR_HPP
#define EXAMCPP_VLVECTOR_HPP
#include <iostream>
#include <cmath>

typedef std::size_t size_t;
template<class T, int StaticCapacity=16>
class VLVector
{
public:
    class Iterator
    {
    public:
        typedef T value_type;
        typedef T& reference;
        typedef T* pointer;
        typedef typename std::iterator<std::random_access_iterator_tag, T>::difference_type
                difference_type;
        typedef std::random_access_iterator_tag iterator_category;
        Iterator(): cur(nullptr){}
        explicit Iterator(T* ptr): cur(ptr){}
        reference operator*() const {return *cur;}
        value_type operator->() const {return cur;}
        reference operator[](difference_type diff) const {return cur[diff];}
        Iterator& operator++(){cur++; return *this;}
        Iterator operator++(int)
        {
            Iterator tmp = *this;
            cur++;
            return tmp;
        }
        Iterator& operator--(){cur--; return *this;}
        Iterator operator--(int)
        {
            Iterator tmp = *this;
            cur--;
            return tmp;
        }
        Iterator operator+(difference_type diff) const {return Iterator(cur + diff);}
        Iterator operator-(difference_type diff) const {return Iterator(cur - diff);}
        difference_type operator-(const Iterator& rhs) const {return cur - rhs.cur;}
        Iterator& operator+=(difference_type diff)
        {
            cur += diff;
            return *this;
        }
        Iterator& operator-=(difference_type diff)
        {
            cur -= diff;
            return *this;
        }
        bool operator==(const Iterator& other) const {return cur == other.cur;}
        bool operator!=(const Iterator& other) const {return cur != other.cur;}
        bool operator<(const Iterator& other) const {return cur < other.cur;}
        bool operator<=(const Iterator& other) const {return cur <= other.cur;}
        bool operator>(const Iterator& other) const {return cur > other.cur;}
        bool operator>=(const Iterator& other) const {return cur >= other.cur;}
    protected:
        pointer cur;
    };

    class ConstIterator
    {
    public:
        typedef T value_type;
        typedef T& reference;
        typedef T* pointer;
        typedef typename std::iterator<std::random_access_iterator_tag, T>::difference_type
                difference_type;
        typedef std::random_access_iterator_tag iterator_category;
        ConstIterator(): cur(nullptr){}
        explicit ConstIterator(const T* ptr): cur(ptr){}
        value_type operator*() const {return *cur;}
        value_type operator->() const {return cur;}
        reference operator[](difference_type diff) const {return cur[diff];}
        ConstIterator& operator++(){cur++; return *this;}
        ConstIterator operator++(int)
        {
            ConstIterator tmp = *this;
            cur++;
            return tmp;
        }
        ConstIterator& operator--(){cur--; return *this;}
        ConstIterator operator--(int)
        {
            ConstIterator tmp = *this;
            cur--;
            return tmp;
        }
        ConstIterator operator+(difference_type diff) const {return Iterator(cur + diff);}
        ConstIterator operator-(difference_type diff) const {return ConstIterator(cur - diff);}
        difference_type operator-(const ConstIterator& rhs) const {return cur - rhs.cur;}
        ConstIterator& operator+=(difference_type diff)
        {
            cur += diff;
            return *this;
        }
        ConstIterator& operator-=(difference_type diff)
        {
            cur -= diff;
            return *this;
        }
        bool operator==(const ConstIterator& other) const {return cur == other.cur;}
        bool operator!=(const ConstIterator& other) const {return cur != other.cur;}
        bool operator<(const ConstIterator& other) const {return cur < other.cur;}
        bool operator<=(const ConstIterator& other) const {return cur <= other.cur;}
        bool operator>(const ConstIterator& other) const {return cur > other.cur;}
        bool operator>=(const ConstIterator& other) const {return cur >= other.cur;}
    protected:
        const T* cur;
    };

    typedef Iterator iterator;
    typedef ConstIterator const_iterator;

    VLVector() = default;

    VLVector(const VLVector& vec): VLVector(vec.begin(), vec.end()){}

    template <class InputIterator>
    VLVector(const InputIterator& first, const InputIterator& last)
    {
        int numElem = std::distance(first, last);
        _size = numElem;
        if (numElem > StaticCapacity)
        {
            _dynamicArr = new T[capacity()];
            std::copy(first, last, _dynamicArr);

        }
        else
        {
            std::copy(first, last, _staticArr);
        }
    }

    ~VLVector(){if(_size > StaticCapacity) delete[] _dynamicArr;}

    iterator begin(){return _size > StaticCapacity? iterator(_dynamicArr):iterator
                (_staticArr);}
    iterator end() {return _size > StaticCapacity? iterator(_dynamicArr + _size):iterator
                (_staticArr + _size);}

    const_iterator begin() const {return _size > StaticCapacity? const_iterator
                (_dynamicArr):const_iterator(_staticArr);}
    const_iterator end() const {return _size + 1 > StaticCapacity? const_iterator
                (_dynamicArr + _size):const_iterator(_staticArr + _size);}

    const_iterator cbegin() const {return _size > StaticCapacity?const_iterator(
    _dynamicArr):const_iterator(_staticArr);}
    const_iterator cend() const {return _size > StaticCapacity?const_iterator(
                _dynamicArr + _size):const_iterator(_staticArr + _size);}

    size_t size(){return _size;}

    size_t capacity(){
        int cap = _size + 1 > StaticCapacity? (floor(3 * (_size + 1)) / 2): StaticCapacity;
        std::cout << "capacity: " << cap << std::endl;
        return cap;}

    bool empty(){return _size == 0;}

    T& at(size_t pos)
    {
        if (pos >= _size)
        {
            //TODO throw exception
            std::cout << "exception!" << std::endl;
        }
        return (*this)[pos];
    }

    void push_back(const T& value)
    {
        if (_size == StaticCapacity)
        {
            changeToDynamic();
            _dynamicArr[_size++] = value;
        }
        else
        {
            _staticArr[_size++] = value;
        }
    }

    iterator insert(iterator pos, const T& value);

    template <class InputIterator>
    iterator insert(iterator pos, InputIterator first, InputIterator last);

    void pop_back();

    iterator erase(iterator pos);

    iterator erase(iterator first, iterator last);

    void clear();

    T* data() {return _size>StaticCapacity? _dynamicArr:&_staticArr;}

    VLVector& operator=(const VLVector& other);

    T& operator[](const size_t pos) {return _size > StaticCapacity?
    _dynamicArr[pos]:_staticArr[pos];}

    T& operator[](const size_t pos) const {return _size > StaticCapacity?
    _dynamicArr[pos]:_staticArr[pos];}

private:
    T* _dynamicArr{0};
    T _staticArr[StaticCapacity]{0};
    size_t _size = 0;
    void changeToDynamic()
    {
        _dynamicArr = new T[capacity()];
        auto b = begin();
        std::copy(begin(), end(), _dynamicArr);
    }
    void changeToStatic()
    {
        std::copy(begin(), end(), _staticArr);
        delete [] _dynamicArr;
    }
};
template <class T, int StaticCap>
bool operator==(const VLVector<T, StaticCap>& lhs, const VLVector<T, StaticCap>& rhs);

template <class T, int StaticCap>
bool operator!=(const VLVector<T, StaticCap>& lhs, const VLVector<T, StaticCap>& rhs);


#endif //EXAMCPP_VLVECTOR_HPP
