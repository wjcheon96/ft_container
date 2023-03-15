#ifndef RBTREE_ITERATOR_TRAITS
#define RBTREE_ITERATOR_TRAITS

#include "RBtree_node.hpp"
#include <iostream>

namespace ft {
	template <typename T>
	class RBtree_const_iterator; 

    template <typename T>
	class RBtree_iterator : public ft::iterator<ft::bidirectional_iterator_tag, T> {
        private:
			typedef ft::RBtree_node<T>		Node;
			typedef ft::RBtree_node<T>*		NodePtr;
			NodePtr							_node;
			NodePtr							_nil;
		public:
			typedef	bidirectional_iterator_tag		iterator_category;
			typedef	T								value_type;
			typedef	T*								pointer;
			typedef	T&								reference;
			typedef	std::ptrdiff_t					difference_type;

			RBtree_iterator() : _node(NULL) {}
			RBtree_iterator(const RBtree_iterator &other) : _node(other._node), _nil(other._nil) {}
			RBtree_iterator(NodePtr node, NodePtr nil) : _node(node), _nil(nil) {}
			~RBtree_iterator() {}
			RBtree_iterator &operator=(const RBtree_iterator &obj) {
				_node = obj._node;
				_nil = obj._nil;
				return *this;
			}
			NodePtr	 base() const { return (_node); }

			NodePtr  get_nil() const { return (_nil); }

			RBtree_iterator& operator++() {
				if (_node->_right != _nil) {
					_node = _node->_right;
					while (_node->_left != _nil)
						_node = _node->_left;
				}
				else {
					NodePtr tmp = _node->_parent;
					while (_node == tmp->_right) {
						_node = tmp;
						tmp = tmp->_parent;
					}
					if (_node->_right != tmp)
						_node = tmp;
				}
				// if (_node->_right != _nil) {
				// 	_node = min_value_node(_node->_right);
				// 	return (*this);
				// }
				// while (_node->_parent != NULL && _node != _node->_parent->_left)
				// 	_node = _node->_parent;
				// if (_node->_parent != NULL)
				// 	_node = _node->_parent;
				return (*this);
			}
			RBtree_iterator operator++(int) {
				RBtree_iterator tmp(*this);
				++(*this);
				return (tmp);
			}

			RBtree_iterator& operator--() {
				if (_node->_color == RED && _node->_parent->_parent == _node)
					_node = _node->_right;
				else if (_node->_left != _nil) {
					NodePtr tmp = _node->_left;
					while (tmp->_right != _nil)
						tmp = tmp->_right;
					_node = tmp;
				}
				else {
					NodePtr tmp = _node->_parent;
					while (_node == tmp->_left) {
						_node = tmp;
						tmp = tmp->_parent;
					}
					_node = tmp;
				}
				// if (_node->_left != _nil) {
				// 	_node = max_value_node(_node->_left);
				// 	return (*this);
				// }
				// while (_node->_parent != NULL && _node != _node->_parent->_right)
				// 	_node = _node->_parent;
				// if (_node->_parent != NULL)
				// 	_node = _node->_parent;
				// else 
				// 	_node = _nil;
				return (*this);
			}

			RBtree_iterator operator--(int) {
				RBtree_iterator tmp(*this);
				--(*this);
				return (tmp);
			}

			reference operator*() const {return (_node->_value);}
			pointer operator->() const { return (&(_node->_value)); }
			bool operator==(const RBtree_iterator& obj) const { return (_node == obj.base()); }
			bool operator!=(const RBtree_iterator& obj) const { return (_node != obj.base()); }
			bool operator==(const RBtree_const_iterator<T>& obj) const { return (_node == obj.base()); }
			bool operator!=(const RBtree_const_iterator<T>& obj) const { return (_node != obj.base()); }
			
			private:
				NodePtr min_value_node(NodePtr node) {
					if (node->_left == _nil)
						return (node);
					return (min_value_node(node->_left));
				}

				NodePtr max_value_node(NodePtr node) {
					if (node->_right == _nil)
						return (node);
					return (max_value_node(node->_right));
				}
	};
	
	template <typename T>
	class RBtree_const_iterator : public ft::iterator<ft::bidirectional_iterator_tag, T> {
        private:
			typedef ft::RBtree_node<T>		Node;
			typedef ft::RBtree_node<T>*		NodePtr;
			NodePtr							_node;
			NodePtr							_nil;
		public:
			typedef	bidirectional_iterator_tag		iterator_category;
			typedef	T								value_type;
			typedef	const T*						pointer;
			typedef	const T&						reference;
			typedef	std::ptrdiff_t					difference_type;

			RBtree_const_iterator() : _node(NULL) {}
			RBtree_const_iterator(const RBtree_const_iterator &other) : _node(other._node), _nil(other._nil) {}
			RBtree_const_iterator(const RBtree_iterator<T> &other) : _node(other.base()), _nil(other.get_nil()) {}
			RBtree_const_iterator(NodePtr node) : _node(node) {}
			RBtree_const_iterator(NodePtr node, NodePtr nil) : _node(node), _nil(nil) {}
			virtual ~RBtree_const_iterator() {}
			RBtree_const_iterator &operator=(const RBtree_const_iterator &obj) {
				_node = obj._node;
				_nil = obj._nil;
				return *this;
			}
			NodePtr	 base() const { return (_node); }

			RBtree_const_iterator& operator++() {
				if (_node->_right != _nil) {
					_node = _node->_right;
					while (_node->_left != _nil)
						_node = _node->_left;
				}
				else {
					NodePtr tmp = _node->_parent;
					while (_node == tmp->_right) {
						_node = tmp;
						tmp = tmp->_parent;
					}
					if (_node->_right != tmp)
						_node = tmp;
				}
				// if (_node->_right != _nil) {
				// 	_node = min_value_node(_node->_right);
				// 	return (*this);
				// }
				// while (_node->_parent != NULL && _node != _node->_parent->_left)
				// 	_node = _node->_parent;
				// if (_node->_parent != NULL)
				// 	_node = _node->_parent;
				return (*this);
			}
			RBtree_const_iterator operator++(int) {
				RBtree_const_iterator tmp(*this);
				++(*this);
				return (tmp);
			}

			RBtree_const_iterator& operator--() {
				if (_node->_color == RED && _node->_parent->_parent == _node)
					_node = _node->_right;
				else if (_node->_left != _nil) {
					NodePtr tmp = _node->_left;
					while (tmp->_right != _nil)
						tmp = tmp->_right;
					_node = tmp;
				}
				else {
					NodePtr tmp = _node->_parent;
					while (_node == tmp->_left) {
						_node = tmp;
						tmp = tmp->_parent;
					}
					_node = tmp;
				}

				// if (_node->_left != _nil) {
				// 	_node = max_value_node(_node->_left);
				// 	return (*this);
				// }
				// while (_node->_parent != NULL && _node != _node->_parent->_right)
				// 	_node = _node->_parent;
				// if (_node->_parent != NULL)
				// 	_node = _node->_parent;
				// else 
				// 	_node = _nil;
				return (*this);
			}

			RBtree_const_iterator operator--(int) {
				RBtree_const_iterator tmp(*this);
				--(*this);
				return (tmp);
			}

			reference operator*() const {return (_node->_value);}
			pointer operator->() const { return (&(_node->_value)); }
			bool operator==(const RBtree_const_iterator& obj) const { return (_node == obj.base()); }
			bool operator!=(const RBtree_const_iterator& obj) const { return (_node != obj.base()); }
			bool operator==(const RBtree_iterator<T>& obj) const { return (_node == obj.base()); }
			bool operator!=(const RBtree_iterator<T>& obj) const { return (_node != obj.base()); }
			
			private:
				NodePtr min_value_node(NodePtr node) {
					if (node->_left == _nil)
						return (node);
					return (min_value_node(node->_left));
				}

				NodePtr max_value_node(NodePtr node) {
					if (node->_right == _nil)
						return (node);
					return (max_value_node(node->_right));
				}
	};
	
}

#endif