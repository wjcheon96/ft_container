#ifndef SET_HPP
#define SET_HPP

#include "RBtree.hpp"
#include "utils.hpp"
#include <memory>

namespace ft {
    template < typename T, typename Compare = ft::less<T>, typename Alloc = std::allocator<T> > 
    class set {
        public:
            typedef T                           key_type;
            typedef T                           value_type;
            typedef Compare                     key_compare;
            typedef Compare                     value_compare;
            typedef Alloc                       allocator_type;
            typedef size_t                      size_type;
            typedef ptrdiff_t                   difference_type;

            typedef typename allocator_type::pointer            pointer;
            typedef typename allocator_type::const_pointer      const_pointer;
            typedef typename allocator_type::reference          reference;
            typedef typename allocator_type::const_reference    const_reference;

            typedef typename ft::RBtree_iterator<value_type>            iterator;
            typedef typename ft::RBtree_const_iterator<value_type>      const_iterator;
            typedef ft::reverse_iterator<iterator>                      reverse_iterator;
            typedef ft::reverse_iterator<const_iterator>                const_reverse_iterator;
        
            class value_compare : public std::binary_function<value_type, value_type, bool> {
                friend class map;
                protected:
                    Compare comp;
                    value_compare(Compare const& c) : comp(c) {}
                public:
                    typedef bool result_type;
                    typedef value_type first_argument_type;
                    typedef value_type second_argument_type;
                    bool operator()(const value_type& x, const value_type& y) const {
                        return comp(x.first, y.first);
                    }
            };
    };

}

#endif