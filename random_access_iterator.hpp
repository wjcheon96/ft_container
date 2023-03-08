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
            operator*() {
                return (*_iter);
            } 
    };
}

#endif