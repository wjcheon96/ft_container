#ifndef RBTREE_ITERATOR_TRAITS
#define RBTREE_ITERATOR_TRAITS

#include "RBtree_node.hpp"

namespace ft {
    template <typename T>
	class RBtree_iterator : public ft::iterator<ft::bidirectional_iterator_tag, T> {
        private:
			typedef ft::RBtree_node<T>		Node;
			typedef ft::RBtree_node<T>*		NodePtr;
			typedef NodePtr					_node;
		public:
			typedef	bidirectional_iterator_tag		iterator_category;
			typedef	T								value_type;
			typedef	T*								pointer;
			typedef	T&								reference;
			typedef	std::ptrdiff_t					difference_type;

			RBtree_iterator() : _node(NULL) {}
			RBtree_iterator(const RBtree_iterator &other) : _node(other._node) {}
			RBtree_iterator(NodePtr node) : _node(node) {}
			~RBtree_iterator() {}
			RBtree_iterator &operator=(const RBtree_iterator &obj) {
				_node = obj._node;
				return *this;
			}
			NodePtr	 base() const { return (_node); }

			RBtree_iterator& operator++() {
				if (_node->right != NULL) {
					_node = min_value_node(_node->right);
					return (*this);
				}
				while (_node->parent != NULL && _node != _node->parent->left)
					_node = _node->parent;
				if (_node->parent != NULL)
					_node = _node->parent;
				return (*this);
			}
			RBtree_iterator operator++(int) {
				RBtree_iterator tmp(*this);
				++(*this);
				return (tmp);
			}

			RBtree_iterator& operator--() {
				if (_node->left != NULL) {
					_node = max_value_node(_node->left);
					return (*this);
				}
				while (_node->parent != NULL && _node != _node->parent->right)
					_node = _node->parent;
				if (_node->parent != NULL)
					_node = _node->parent;
				else 
					_node = NULL;
				return (*this);
			}

			RBtree_iterator operator--(int) {
				RBtree_iterator tmp(*this);
				--(*this);
				return (tmp);
			}

			reference operator*() const {return (_node->value);}
			pointer operator->() const { return (&(_node->value)); }
			bool operator==(const RBtree_iterator& obj) const { return (_node == obj.base()); }
			bool operator!=(const RBtree_iterator& obj) const { return (_node != obj.base()); }
			bool operator==(const RBtree_const_iterator<T>& obj) const { return (_node == obj.base()); }
			bool operator!=(const RBtree_const_iterator<T>& obj) const { return (_node != obj.base()); }
			
			private:
				NodePtr min_value_node(NodePtr node) {
					if (node->left == NULL)
						return (node);
					return (min_value_node(node->left));
				}

				NodePtr max_value_node(NodePtr node) {
					if (node->right == NULL)
						return (node);
					return (max_value_node(node->right));
				}
	};
	template <typename T>
	class RBtree_const_iterator : public ft::iterator<ft::bidirectional_iterator_tag, T> {
        private:
			typedef ft::RBtree_node<T>		Node;
			typedef ft::RBtree_node<T>*		NodePtr;
			typedef NodePtr					_node;
		public:
			typedef	bidirectional_iterator_tag		iterator_category;
			typedef	T								value_type;
			typedef	const T*						pointer;
			typedef	const T&						reference;
			typedef	std::ptrdiff_t					difference_type;

			RBtree_const_iterator() : _node(NULL) {}
			RBtree_const_iterator(const RBtree_const_iterator &other) : _node(other._node) {}
			RBtree_const_iterator(const RBtree_iterator<T> &other) : _node(other.base()) {}
			RBtree_const_iterator(NodePtr node) : _node(node) {}
			virtual ~RBtree_iterator() {}
			RBtree_const_iterator &operator=(const RBtree_const_iterator &obj) {
				_node = obj._node;
				return *this;
			}
			NodePtr	 base() const { return (_node); }

			RBtree_const_iterator& operator++() {
				if (_node->right != NULL) {
					_node = min_value_node(_node->right);
					return (*this);
				}
				while (_node->parent != NULL && _node != _node->parent->left)
					_node = _node->parent;
				if (_node->parent != NULL)
					_node = _node->parent;
				return (*this);
			}
			RBtree_const_iterator operator++(int) {
				RBtree_const_iterator tmp(*this);
				++(*this);
				return (tmp);
			}

			RBtree_const_iterator& operator--() {
				if (_node->left != NULL) {
					_node = max_value_node(_node->left);
					return (*this);
				}
				while (_node->parent != NULL && _node != _node->parent->right)
					_node = _node->parent;
				if (_node->parent != NULL)
					_node = _node->parent;
				else 
					_node = NULL;
				return (*this);
			}

			RBtree_const_iterator operator--(int) {
				RBtree_const_iterator tmp(*this);
				--(*this);
				return (tmp);
			}

			reference operator*() const {return (_node->value);}
			pointer operator->() const { return (&(_node->value)); }
			bool operator==(const RBtree_const_iterator& obj) const { return (_node == obj.base()); }
			bool operator!=(const RBtree_const_iterator& obj) const { return (_node != obj.base()); }
			bool operator==(const RBtree_iterator<T>& obj) const { return (_node == obj.base()); }
			bool operator!=(const RBtree_iterator<T>& obj) const { return (_node != obj.base()); }
			
			private:
				NodePtr min_value_node(NodePtr node) {
					if (node->left == NULL)
						return (node);
					return (min_value_node(node->left));
				}

				NodePtr max_value_node(NodePtr node) {
					if (node->right == NULL)
						return (node);
					return (max_value_node(node->right));
				}
	};
}

#endif