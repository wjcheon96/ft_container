#ifndef RBTREE_HPP
#define RBTREE_HPP

#include <memory>
#include "pair.hpp"
#include "utils.hpp"
#include "RBtree_iterator_traits.hpp"
#include "RBtree_node.hpp"
#include "iterator_traits.hpp"
#include "reverse_iterator.hpp"
#include "utils.hpp"

namespace ft {
    template<typename T, typename Compare, typename Alloc = std::allocator<T> > 
    class RBTree {
        private:
			typedef ft::RBtree_node<T>									node_type;
			typedef ft::RBtree_node<T>* 								NodePtr;
			typedef typename Alloc::template rebind<node_type>::other	node_alloc_type;
		public:
			typedef T													value_type;
			typedef Compare												value_compare;
			typedef Alloc												allocator_type;
			typedef size_t												size_type;
			typedef ptrdiff_t											difference_type;
			typedef typename allocator_type::pointer					pointer;
			typedef typename allocator_type::const_pointer				const_pointer;
			typedef typename allocator_type::reference					reference;
			typedef typename allocator_type::const_reference			const_reference;
			typedef ft::RBtree_iterator<value_type>						iterator;
			typedef ft::RBtree_const_iterator<value_type>				const_iterator;
			typedef ft::reverse_iterator<iterator>						reverse_iterator;
			typedef ft::reverse_iterator<const_iterator>				const_reverse_iterator;
        private:
			value_compare	_comp;
			allocator_type	_alloc;
			node_alloc_type	_node_alloc;
			NodePtr			_root;
            NodePtr        	_nil;
			size_type		_size;
        public:
            red_black_tree(value_compare const& comp, allocator_type const& alloc, node_alloc_type const& node_alloc = node_alloc_type())
            : _comp(comp), _alloc(alloc), _node_alloc(node_alloc), _head_node(NULL), _nil(NULL), _size(0) {
                _root = _node_alloc.allocate(1);
                _node_alloc.construct(_root, node_type());
            }
            red_black_tree(const red_black_tree& x) : _comp(x._comp), _alloc(x._alloc), _node_alloc(x._node_alloc), _root(NULL), _size(0) {
				_root = _node_alloc.allocate(1);
				_node_alloc.construct(_root, node_type());
				if(x.get_root() != NULL){
					copy_tree(x.get_root());
				}
			}
        private:
            void    create_rbtree(void) {
				_root
				_root->color = _color->RBTREE_BLACK;
				_nil->color = _color->RBTREE_BLACK;
            }

    };
}

#endif