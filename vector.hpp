#include <memory>

//push_back -> pop_back -> assign -> constructor -> front -> back -> at ->operator[] -> empty -> capacity -> max_size -> resize
namespace ft
{
    template<class T, class Alloc = std::allocator<T>> class vector {
        public:
            typedef T                                           value_type;
            typedef Alloc                                       allocator_type;
            typedef typename allocator_type::reference          reference;
            typedef typename allocator_type::const_reference    const_reference;
            typedef typename allocator_type::pointer            pointer;
            typedef typename allocator_type::const_pointer      pointer;
/*            typedef typename random_access_iterator::value_type   iterator;
            typedef typename random_access_iterator::value_type const_iterator;
            typedef typename random_access_iterator::value_type iterator;
            typedef typename random_access_iterator::value_type iterator; */
            typedef typename allocator_type::difference_type    difference_type;
            typedef typename allocator_type::size_type          size_type;
            explicit vector (const allocator_type& alloc = allocator_type()) {
                _alloc = alloc;
                _begin = alloc.allocate(0);
                _end = _begin;
                _capacity = _begin;
            };
            void reserve (size_type n) {
                if (_capacity - _begin < n) {
                    pointer tmp;
                    tmp = alloc.allocate(n);
                    size_type _size = size();
                    for (int i = 0; i < _size; i++) {    
                        tmp[i] = alloc.construct(_begin[i]);
                    }
                    clear();
                    alloc.deallocate(_begin, _size);
                    _begin = tmp;
                    _end = _begin + _size;
                    _capacity = _begin + n;
                }
            };
            size_type size() const {
                return (_end - _begin);
            };
            void push_back(const value_type& val) {
                
            }
            void clear() {
                while (_end != _begin) {
                    alloc.destroy(_end);
                    --end;
                }
                alloc.destroy(_end);
            };
        private:
            pointer     _begin;
            pointer     _end;
            pointer     _val;
            pointer     _capacity;
            allocator _alloc;
    };
}