//
// Created by ilay on 8/4/2020.
//

#ifndef EXAMCPP_VLVECTOR_HPP
#define EXAMCPP_VLVECTOR_HPP
#define OUT_OF_BOUND_ERR "Index out of bound"
#define DEFAULT_CAPACITY 16
#include <iostream>

typedef unsigned int size;
template<class T, size StaticCapacity = DEFAULT_CAPACITY>
/**
 * @brief VLVector is a container that utilize static and dynamic memory
 * @tparam T
 * @tparam StaticCapacity
 */
class VLVector
{
public:
    /**
     * @brief iterator class
     */
    class Iterator
    {
    public:
        typedef T value_type;
        typedef T &reference;
        typedef T *pointer;
        typedef typename std::iterator<std::random_access_iterator_tag, T>::difference_type
                difference_type;
        typedef std::random_access_iterator_tag iterator_category;

        // constructors
        Iterator() : cur(nullptr){}
        explicit Iterator(T *ptr) : cur(ptr){}

        // basic operators
        reference operator*() const {return *cur; }

        reference operator*() {return *cur; }

        reference operator[](difference_type diff) const {return this->cur[diff]; }

        reference operator[](difference_type diff) {return this->cur[diff]; }

        //increment decrement
        Iterator &operator++()
        {
            ++cur;
            return *this;
        }

        Iterator operator++(int)
        {
            pointer tmp = this->cur;
            ++*this;
            return Iterator(tmp);
        }

        Iterator &operator--()
        {
            --cur;
            return *this;
        }

        Iterator operator--(int)
        {
            pointer tmp = this->cur;
            --*this;
            return Iterator(tmp);
        }

        //arithmetic
        Iterator operator+(difference_type diff) const {return Iterator(this->cur + diff); }

        friend Iterator operator+(difference_type diff, const Iterator &rhs)
        {
            return Iterator(diff + rhs.cur);
        }

        Iterator operator-(difference_type diff) const {return Iterator(cur - diff); }

        difference_type operator-(const Iterator &rhs) const {return cur - rhs.cur; }

        Iterator &operator+=(difference_type diff)
        {
            cur += diff;
            return *this;
        }

        Iterator &operator-=(difference_type diff)
        {
            cur -= diff;
            return *this;
        }

        // comparisons
        bool operator==(const Iterator &other) const {return cur == other.cur; }

        bool operator!=(const Iterator &other) const {return cur != other.cur; }

        bool operator<(const Iterator &other) const {return cur < other.cur; }

        bool operator<=(const Iterator &other) const {return cur <= other.cur; }

        bool operator>(const Iterator &other) const {return cur > other.cur; }

        bool operator>=(const Iterator &other) const {return cur >= other.cur; }

    protected:
        pointer cur;
    };

    /**
     * @brief const iterator class
     */
    class ConstIterator
    {
    public:
        typedef T value_type;
        typedef const T &reference;
        typedef const T *pointer;
        typedef typename std::iterator<std::random_access_iterator_tag, T>::difference_type
                difference_type;
        typedef std::random_access_iterator_tag iterator_category;

        // constructors
        ConstIterator() : cur(nullptr){}
        explicit ConstIterator(const T *ptr) : cur(ptr){}
        // basic operators
        value_type operator*() const {return *cur; }

        reference operator[](difference_type diff) const {return this->cur[diff]; }
        // increment decrement
        ConstIterator &operator++()
        {
            ++cur;
            return *this;
        }

        ConstIterator operator++(int)
        {
            pointer tmp = cur;
            ++*this;
            return ConstIterator(tmp);
        }

        ConstIterator &operator--()
        {
            cur--;
            return *this;
        }

        ConstIterator operator--(int)
        {
            pointer tmp = this->cur;
            --cur;
            return ConstIterator(tmp);
        }

        // arithmetic
        ConstIterator operator+(difference_type diff) const
        {
            return ConstIterator(this->cur + diff);
        }

        friend ConstIterator operator+(difference_type diff, const ConstIterator &rhs)
        {
            return ConstIterator(diff + rhs.cur);
        }

        ConstIterator operator-(difference_type diff) const
        {
            return ConstIterator(this->cur - diff);
        }

        difference_type operator-(const ConstIterator &rhs) const {return cur - rhs.cur; }

        ConstIterator &operator+=(difference_type diff)
        {
            cur += diff;
            return *this;
        }

        ConstIterator &operator-=(difference_type diff)
        {
            cur -= diff;
            return *this;
        }

        // comparisons
        bool operator==(const ConstIterator &other) const {return cur == other.cur; }
        bool operator!=(const ConstIterator &other) const {return cur != other.cur; }
        bool operator<(const ConstIterator &other) const { return cur < other.cur; }
        bool operator<=(const ConstIterator &other) const {return cur <= other.cur; }
        bool operator>(const ConstIterator &other) const {return cur > other.cur; }
        bool operator>=(const ConstIterator &other) const {return cur >= other.cur; }

    protected:
        const T *cur;
    };

    typedef Iterator iterator;
    typedef ConstIterator const_iterator;

    /**
     * default constructor
     */
    VLVector()
    {
//        _updateCapacity(Iterator());
    }

    /**
     * @brief copy constructor
     * @param vec VLVector object
     */
    VLVector(const VLVector &vec) : VLVector(vec.begin(), vec.end()){}

    /**
     * @brief constructor in range [first last)
     * @tparam InputIterator iterator satisfied input-iterator API
     * @param first iterator to first element to copy
     * @param last iterator to last element to copy
     */
    template<class InputIterator>
    VLVector(InputIterator first, InputIterator last) {insert(this->begin(), first, last); }

    /**
     * @brief destructor
     */
    ~VLVector()
    {
        if (_size > StaticCapacity)
        {
            delete[] _dynamicArr;
        }
    }

    // begin and end for non-const iterator
    iterator begin()
    {
        return _size > StaticCapacity ? iterator(_dynamicArr) : iterator
                (_staticArr);
    }

    iterator end()
    {
        return _size > StaticCapacity ? iterator(_dynamicArr + _size) : iterator
                (_staticArr + _size);
    }
    // begin and end for const iterator
    const_iterator begin() const
    {
        return _size > StaticCapacity ? const_iterator(_dynamicArr) : const_iterator(_staticArr);
    }

    const_iterator end() const
    {
        return _size > StaticCapacity ? const_iterator(_dynamicArr + _size) :
               const_iterator(_staticArr + _size);
    }
    // cbegin and cend for const iterator
    const_iterator cbegin() const
    {
        return _size > StaticCapacity ? const_iterator(_dynamicArr) : const_iterator(_staticArr);
    }

    const_iterator cend() const
    {
        return _size > StaticCapacity ? const_iterator(_dynamicArr + _size) :
               const_iterator(_staticArr + _size);
    }

    /**
     * @brief return size of container
     * @return _size (number of elements)
     */
    size_t size() const {return _size; }

    /**
     * @brief return capacity as follow: cap(s) = C if s + 1 <= C , floor(1.5*(s+1)) else
     * where C is StaticCapacity ans s _size
     * @return capacity
     */
    size_t capacity() const {return _dynamicCap > StaticCapacity ? _dynamicCap : StaticCapacity; }

    /**
     * @brief check if container is empty
     * @return bool of emptiness
     */
    bool empty() const {return _size == 0; }

    /**
     * @brief return a reference to the element at specified location pos, with bounds checking
     * @param pos position of element
     * @return Reference to the requested element.
     */
    T &at(size_t pos)
    {
        _checkBounds(pos);
        return (*this)[pos];
    }

    /**
     * @brief const version of at function
     */
    const T &at(size_t pos) const
    {
        _checkBounds(pos);
        return (*this)[pos];
    }

    /**
     * @brief insert value at end
     * @param value value to insert
     */
    void push_back(const T &value);

    /**
     * @brief insert value at position pos
     * @param pos iterator to insert position
     * @param value insertion value
     * @return iterator to the new element
     */
    iterator insert(iterator pos, const T &value)
    {
        auto first = const_iterator(&value);
        return insert(pos, first, first + 1);
    }

    /**
    * @brief insert elements in range [first last)
    * @tparam InputIterator iterator satisfied input-iterator API
    * @param pos iterator to position of insertion
    * @param first first element in range
    * @param last last element in range
    * @return iterator to the first element in the new range
    */
    template<class InputIterator>
    iterator insert(Iterator pos, InputIterator first, InputIterator last);
    /**
     * @brief remove last element
     */
    void pop_back();

    /**
     * @brief remove element at position pos
     * @param pos iterator to position
     * @return iterator to the element to the right of the removed one
     */
    iterator erase(iterator pos) {return erase(pos, pos + 1); }

    /**
     * @brief remove elements in range [first last)
     * @param first first element to remove
     * @param last last element to remove
     * @return iterator to the element to the right of the removed range
     */
    iterator erase(iterator first, iterator last);

    /**
     * @brief remove all elements in container
     */
    void clear();

    /**
     * @brief return the data structure that store the container elemnets
     * @return pointer to data structure
     */
    T* data() {return _size > StaticCapacity ? _dynamicArr : _staticArr; }

    /**
     * @brief assignment operator
     * @param other VLVector to copy from
     */
    VLVector& operator=(const VLVector &other);

    /**
     * @brief Returns a reference to the element at specified location pos. No bounds checking
     * @param pos position of the element to return
     * @return reference to the element at pos
     */
    T& operator[](size_t pos)
    {
        return _size > StaticCapacity ?
               _dynamicArr[pos] : _staticArr[pos];
    }

    /**
     * @brief const version of operator []
     */
    const T& operator[](size_t pos) const
    {
        return _size > StaticCapacity ?
               _dynamicArr[pos] : _staticArr[pos];
    }

private:
    T *_dynamicArr{0}; //dynamic array
    T _staticArr[StaticCapacity]; // static array
    size_t _size = 0; // container size
    size_t _dynamicCap = 0; // dynamic capacity

    /**
     * @brief change data from static to dynamic memory
     * @param pos iterator to element in static array
     * @param newCapacity dynamic capacity
     * @return iterator to element in dynamic array that points to the data pos was pointed
     * in static array
     */
    Iterator _changeToDynamic(Iterator pos);

    /**
     * @brief change data from dynamic to static memory
     * @param pos iterator to element in dynamic array
     * @return iterator to element in static array that points to the data pos was pointed
     * in dynamic array
     */
    Iterator _changeToStatic(Iterator pos);

    /**
     * @brief check bounds of index
     * @param pos index
     */
    void _checkBounds(int pos) const
    {
        if (pos < 0 || pos >= int(_size))
        {
            throw std::out_of_range(OUT_OF_BOUND_ERR);
        }
    }

    /**
     * @brief update capacity and increase dynamic memory
     */
    Iterator _updateCapacity(Iterator pos);

};
/**
 * @brief operator ==
 * @tparam T class type
 * @tparam StaticCapacity class capacity
 * @param lhs VLVector object
 * @param rhs VlVector object
 * @return comparison between lhs ans rhs (element wise)
 */
template <class T, size StaticCapacity>
bool operator==(const VLVector<T, StaticCapacity>& lhs, const VLVector<T, StaticCapacity>& rhs);

/**
 * @brief operator !=
 * @tparam T class type
 * @tparam StaticCapacity class capacity
 * @param lhs VLVector object
 * @param rhs VlVector object
 * @return negation comparison between lhs ans rhs (element wise)
 */
template <class T, size StaticCapacity>
bool operator!=(const VLVector<T, StaticCapacity>& lhs, const VLVector<T, StaticCapacity>& rhs)
{return !(lhs == rhs); }

template <class T, size StaticCapacity>
void VLVector<T, StaticCapacity>::push_back(const T& value)
{
    if (_size == StaticCapacity)
    {
        _dynamicCap = _size == 0 ? 1 : _dynamicCap;
        _changeToDynamic(this->end());
    }
    _size++;
    size_t diff = _size - 1;
    *(this->begin() + diff) = value;
    _updateCapacity(this->begin());
}

template <class T, size StaticCapacity>
void VLVector<T, StaticCapacity>::pop_back()
{
    if(_size - 1 == StaticCapacity)
    {
        _changeToStatic(this->begin());
    }
    _dynamicCap = _size == StaticCapacity? 0 : _dynamicCap;
    _size--;
}

template <class T, size StaticCapacity>
typename VLVector<T, StaticCapacity>::iterator VLVector<T, StaticCapacity>::erase(iterator first,
                                                                                  iterator last)
{
    int numElem = std::distance(first, last);
    int end1 = std::distance(this->begin(), first);
    int end2 = std::distance(last, this->end());
    T* tmp = new T[end1 + end2];
    std::copy(this->begin(), first, iterator(&tmp[0]));
    std::copy(last, this->end(), iterator(&tmp[0]) + end1);
    std::copy(iterator(&tmp[0]), iterator(&tmp[0]) + end1 + end2, this->begin());
    delete[] tmp;
    size_t newSize =  _size - numElem;
    if (newSize <= StaticCapacity)
    {
        first = _changeToStatic(first);
        _dynamicCap = newSize == StaticCapacity? (int) (3 * (newSize + 1) / 2) : 0;
    }
    _size = newSize;
    return first;
}

template <class T, size StaticCapacity>
template<class InputIterator>
typename VLVector<T, StaticCapacity>::iterator VLVector<T, StaticCapacity>::insert(Iterator pos, InputIterator first, InputIterator last)
{
    int numElem = std::distance(first, last);
    int off = std::distance(pos, this->end());
    if (_size + numElem > StaticCapacity && _size <= StaticCapacity)
    {
        _dynamicCap = (int) (3 * (_size + numElem) / 2);
        pos = _changeToDynamic(pos);
    }
    T* tmp = new T[off];
    std::copy(pos, pos + off, iterator(&tmp[0]));
    std::copy(iterator(&tmp[0]), iterator(&tmp[off]), pos + numElem);
    std::copy(first, last, pos);
    _size += numElem;
    delete[] tmp;
    pos = _updateCapacity(pos);
    return pos;
}

template <class T, size StaticCapacity>
void VLVector<T, StaticCapacity>::clear()
{
    delete[] _dynamicArr;
    _dynamicArr = nullptr;
    _dynamicCap = _size = 0;
}

template <class T, size StaticCapacity>
VLVector<T, StaticCapacity>& VLVector<T, StaticCapacity>::operator=(const VLVector& other)
{
    if (this == &other)
    {
        return *this;
    }
    delete[] _dynamicArr;
    _dynamicArr = nullptr;
    _dynamicCap = other._dynamicCap;
    _size = other._size;
    if (_dynamicCap)
    {
        _dynamicArr = new T[_dynamicCap]();
    }
    std::copy(other.begin(), other.end(), this->begin());
    return *this;
}

template <class T, size StaticCapacity>
typename VLVector<T, StaticCapacity>::Iterator VLVector<T, StaticCapacity>::_changeToDynamic(Iterator pos)
{
    delete[] _dynamicArr;
    _dynamicArr = new T[_dynamicCap]();
    auto newPos = std::move(this->begin(), pos, _dynamicArr);
    std::move(pos, this->end(), Iterator(newPos));
    return Iterator(newPos);
}

template <class T, size StaticCapacity>
typename VLVector<T, StaticCapacity>::Iterator VLVector<T, StaticCapacity>::_changeToStatic
(Iterator pos)
{
    auto newPos = std::move(this->begin(), pos, _staticArr);
    std::move(pos, this->end(), Iterator(newPos));
    delete [] _dynamicArr;
    _dynamicArr = nullptr;
    _dynamicCap = (int) (3 * _size / 2);
    return Iterator(newPos);
}

template <class T, size StaticCapacity>
typename VLVector<T, StaticCapacity>::Iterator VLVector<T, StaticCapacity>::_updateCapacity
(Iterator pos)
{
    if (_size == StaticCapacity)
    {
        _dynamicCap = (int) (3 * (_size + 1) / 2);
    }
    else if (_size == _dynamicCap && _size > StaticCapacity)
    {
        _dynamicCap = (int) (3 * (_size + 1) / 2);
        T *newDynamicArr = new T[_dynamicCap];
        auto newPos = std::move(this->begin(), pos, Iterator(&newDynamicArr[0]));
        std::move(pos, this->end(), Iterator(newPos));
        delete[] _dynamicArr;
        _dynamicArr = newDynamicArr;
        return Iterator(newPos);
    }
    return pos;
}

template <class T, size StaticCapacity>
bool operator==(const VLVector<T, StaticCapacity>& lhs, const VLVector<T, StaticCapacity>& rhs)
{
    if(lhs.size() != rhs.size())
    {
        return false;
    }
    auto it1 = lhs.begin();
    auto it2 = rhs.begin();
    while(it1 != lhs.end())
    {
        if (*it1 != *it2)
        {
            return false;
        }
        it1++;
        it2++;
    }
    return true;
}

#endif //EXAMCPP_VLVECTOR_HPP
