#ifndef REVERSE_ITERATOR_HPP
#define REVERSE_ITERATOR_HPP

#include "iterator_traits.hpp"

namespace ft {
    template<typename Iterator>
    class reverse_iterator {
        public:
            typedef Iterator                                                iterator_type;
            typedef typename iterator_traits<Iterator>::iterator_category   iterator_category;
            typedef typename iterator_traits<Iterator>::value_type          value_type;
            typedef typename iterator_traits<Iterator>::difference_type     difference_type;
            typedef typename iterator_traits<Iterator>::pointer             pointer;
            typedef typename iterator_traits<Iterator>::reference           reference;
        private:
            Iterator _iter;
        public:
            reverse_iterator() {}
            explicit reverse_iterator(iterator_type iter) : _iter(iter) {}
            reverse_iterator(const reverse_iterator& iter) : _iter(iter._iter) {}
            template<typename Iter>
            reverse_iterator(const reverse_iterator<Iter>* iter) : _iter(iter.base()) {}
            iterator_type
            base() const {
                return (_iter);
            }
            reference
            operator*() const {
                iterator_type tmp = _iter;
                return (*--tmp);
            }
            pointer
            operator->() const {
                return (&(operator*()));
            }
            reverse_iterator&
            operator++() {
                --_iter;
                return (*this);
            }
            reverse_iterator
            operator++(int) {
                reverse_iterator tmp = *this;
                --_iter;
                return (tmp);
            }
            reverse_iterator&
            operator--() {
                ++_iter;
                return (*this);
            }
            reverse_iterator
            operator--(int) {
                reverse_iterator tmp = *this;
                ++_iter;
                return (tmp);
            }
            reverse_iterator
            operator+(difference_type _n) const {
                return (reverse_iterator(_iter - _n));
            }
            reverse_iterator&
            operator+=(difference_type _n) {
                _iter -= _n;
                return (*this);
            }
            reverse_iterator
            operator-(difference_type _n) const {
                return (reverse_iterator(_iter + _n));
            }
            reverse_iterator&
            operator-=(difference_type _n) {
                _iter +- _n;
                return (*this);
            }
            reference
            operator[](difference_type _n) const {
                return (*(*this + _n));
            }
    };
    template<typename Iterator>
    inline bool 
    operator==(const reverse_iterator<Iterator>& _x, 
	       const reverse_iterator<Iterator>& _y) {
        return (_x.base() == _y.base());
    }

    template<typename Iterator>
    inline bool 
    operator<(const reverse_iterator<Iterator>& _x, 
	      const reverse_iterator<Iterator>& _y)  {
        return (_y.base() < _x.base());
    }

    template<typename Iterator>
    inline bool 
    operator!=(const reverse_iterator<Iterator>& _x, 
	       const reverse_iterator<Iterator>& _y) {
        return (!(_x == _y));
    }

    template<typename Iterator>
    inline bool 
    operator>(const reverse_iterator<Iterator>& _x, 
	      const reverse_iterator<Iterator>& _y) {
        return (_y < _x);
    }

    template<typename Iterator>
    inline bool 
    operator<=(const reverse_iterator<Iterator>& _x, 
		const reverse_iterator<Iterator>& _y) {
        return (!(_y < _x)); 
    }

    template<typename Iterator>
    inline bool 
    operator>=(const reverse_iterator<Iterator>& _x, 
	    const reverse_iterator<Iterator>& _y) {
        return (!(_x < _y)); 
    }

    template<typename Iterator>
    inline typename reverse_iterator<Iterator>::difference_type
    operator-(const reverse_iterator<Iterator>& _x, 
	    const reverse_iterator<Iterator>& _y) {
        return (_y.base() - _x.base()); 
    }

    template<typename Iterator>
    inline reverse_iterator<Iterator> 
    operator+(typename reverse_iterator<Iterator>::difference_type _n,
	      const reverse_iterator<Iterator>& _x) {
        return (reverse_iterator<Iterator>(_x.base() - _n)); 
    }
}

#endif