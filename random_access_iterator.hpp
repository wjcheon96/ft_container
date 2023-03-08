#ifndef RANDOM_ACCESS_ITERATOR_HPP
#define RANDOM_ACCESS_ITERATOR_HPP

#include "iterator_traits.hpp"

namespace ft {
    template<typename Iterator, typename Container>
    class random_access_iterator {
        public:
            typedef typename iterator_traits<Iterator>::iterator_category   iterator_category;
            typedef typename iterator_traits<Iterator>::value_type          value_type;
            typedef typename iterator_traits<Iterator>::difference_type     difference_type;
            typedef typename iterator_traits<Iterator>::pointer             pointer;
            typedef typename iterator_traits<Iterator>::reference           reference;
        private:
            Iterator    _iter;
        public:
            random_access_iterator() : _iter(NULL) {}
            explicit random_access_iterator() {}
			random_access_iterator(Iterator iter) : _iter(iter) {}
			random_access_iterator(const random_access_iterator &other) : _iter(other._iter) {}
			template<typename Iter>
			random_access_iterator(const random_access_iterator<Iter, Container> &other) : _iter(other.base()) {}
			virtual ~random_access_iterator() {}
            random_access_iterator &operator=(const random_access_iterator &other) {
				if (this != &other)
					_iter = other._iter;
				return *this;
			}
            Iterator
            base() const {
                return (_iter);
            }
            reference
            operator*() const {
                return (*_iter);
            }
            pointer
            operator->() {
                return (_iter);
            }            
            random_access_iterator&
            operator++() {
                ++_iter;
                return (*this);
            }
            random_access_iterator
            operator++(int) {
                return (random_access_iterator(_iter++));
            }
            random_access_iterator&
            operator--() {
                --_iter;
                return (*this);
            }
            random_access_iterator
            operator--(int) {
                return (random_access_iterator(_iter--));
            }
            reference
            operator[](const difference_type& _n) const {
                return (_iter[_n]);
            }
            random_access_iterator&
            operator+=(const difference_type& _n) {
                _iter += _n;
                return (*this);
            }
            random_access_iterator
            operator+(const difference_type& _n) const {
                return (random_access_iterator(_iter + _n));
            }
            random_access_iterator&
            operator-=(const difference_type& _n) {
                _iter -= _n;
                return (*this);
            }
            random_access_iterator
            operator-(const difference_type& _n) const {
                return (random_access_iterator(_iter - _n));
            }
            difference_type
            operator-(const random_access_iterator& _i) const {
                return (_iter - _i._iter);
            }
    };
    template<typename IteratorL, typename IteratorR, typename Container>
    inline bool
    operator==(const random_access_iterator<IteratorL, Container>& _lhs,
            const random_access_iterator<IteratorR, Container>& _rhs) {
        return (_lhs.base() == _rhs.base());
    }
    template<typename IteratorL, typename IteratorR, typename Container>
    inline bool
    operator!=(const random_access_iterator<IteratorL, Container>& _lhs,
            const random_access_iterator<IteratorR, Container>& _rhs) {
        return (!(_lhs == _rhs));
    }
    template<typename IteratorL, typename IteratorR, typename Container>
    inline bool 
    operator<(const random_access_iterator<IteratorL, Container>& _lhs,
        const random_access_iterator<IteratorR, Container>& _rhs) {
        return (_lhs.base() < _rhs.base());
    }
    template<typename IteratorL, typename IteratorR, typename Container>
    inline bool
    operator>(const random_access_iterator<IteratorL, Container>& _lhs,
        const random_access_iterator<IteratorR, Container>& _rhs) {
        return (_rhs < _lhs);
    }
    template<typename IteratorL, typename IteratorR, typename Container>
    inline bool
    operator<=(const random_access_iterator<IteratorL, Container>& _lhs,
            const random_access_iterator<IteratorR, Container>& _rhs) {
        return (!(_rhs < _lhs));
    }
    template<typename IteratorL, typename IteratorR, typename Container>
    inline bool
    operator>=(const random_access_iterator<IteratorL, Container>& _lhs,
            const random_access_iterator<IteratorR, Container>& _rhs) {
        return (!(_lhs < _rhs));
    }
    template<typename Iterator, typename Container>
    inline random_access_iterator<Iterator, Container>
    operator+(typename random_access_iterator<Iterator, Container>::difference_type _n,
        const random_access_iterator<Iterator, Container>& _i) {
        return (random_access_iterator<Iterator, Container>(_i.base() + _n)); 
    }
}

#endif