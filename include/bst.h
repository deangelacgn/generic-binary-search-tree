#pragma once
#include <iostream>   // cout, cin, endl
#include <functional> // std::less<>()
#include <utility>    // std::pair<>
#include <random>     // radom_device, mt19937, std::shuffle.
#include <algorithm>  // std::copy
#include <iterator>   // std::begin, std::end
#include <exception>  // std::out_of_range
#include <stack>      // std::stack
#include <iomanip>    // std::setw()
#include <initializer_list> // std::initializer_list
#include <functional>


//!  This class implements a generic Binary Search Tree.
/*!
  BST is a sorted associative container that
  stores key-value pairs with unique keys.
  Keys are sorted by using the comparison function KeyTypeLess. 
  The elements of the container (nodes) are structured as a Binary Search Tree (BST).

  @tparam KeyType The type of the key associated with the data.
  @tparam ValueType The type of the data to be stored in the tree.
  @tparam KeyTypeLess A function object that compares two keys and returns true if
  the first argument of the call appears first than the second argument
  in the strict weak ordering relation induced by the KeyType, and false otherwise.

  By default we try to instantiate a STL's  std::less<KeyType> function object if one is
  available for the KeyType provided.
*/
template < typename KeyType, typename ValueType >
class BST
{
    public:
        //=== alias
        typedef std::function<bool(const KeyType& a, const KeyType& b) > KeyTypeLess; 

    private:
        //=== Definition of a BST node.
        //! Represents a single binary search tree node.
        struct BTNode {
            KeyType key;   //!< The unique key.
            ValueType data; //!< The data stored in a node.
            BTNode *left;  //!< Pointer to the left child (subtree).
            BTNode *right; //!< Pointer to the right child (subtree).

            //! Default constructor for a tree node.
            BTNode( const KeyType & k_=KeyType(), const ValueType & d_=ValueType(),
                    BTNode * lt_=nullptr, BTNode * rt_=nullptr )
                : key( k_ )
                , data( d_ )
                , left( lt_ )
                , right( rt_ )
                { /* empty */ }

            ~BTNode()
            {
                delete left;
                delete right;
            }
        };

        BTNode *m_root; //!< Pointer to the root of the entire tree.
        size_t m_n_nodes; //!< The count of nodes stored in the tree.
        std::function<bool(const KeyType &, const KeyType &)> m_key_less; //!< The key comparator function object.


        //=== INTERNAL MEMBERS

        //! Inserts a new pair <`key`,`value`> in the tree.
        /*! Recursively tried to look for the right place to createa and
         *  insert a new node with a <`key`,`value`> pair in the
         *  BST tree if the key is not already stored in the tree.
         *  @param root A pointer to the tree we want to operate on.
         *  @param key The key associated with the value we wish to operate on.
         *  @param value The value we wish to store in the tree.
         *  @see insert(const KeyType &, const ValueType & )
         */
        void insert( BTNode * & root, const KeyType & key, const ValueType & value );

        //! Removes from the BST a node containing the requested key.
        /*! Recursuvely tries to look for and remove from the BST
         *  a node containing the requested key, if one is found in the tree.
         *  The deletion might modifiy the tree structure to preserve the
         *  BST properties.
         *  If the key is not found, nothing happens to the tree.
         *  @param root A pointer to the tree we want to operate on.
         *  @param key The key associated with the value we wish to operate on.
         *  @param value The value we wish to store in the tree.
         */
        void remove( BTNode * & root, const KeyType & key );

        //! Checks whether the BST contains a given key.
        /*! Recursively search the `root` for the key provided.
         *  Returns true if the key is found, or false otherwise.
         *  @param root A pointer to the tree we want to operate on.
         *  @param key The key we are looking for.
         *  @return true if key is found in the tree, false otherwise.
         *  @see contains( const KeyType & ) const
         */
        bool contains( const BTNode * root , const KeyType & key ) const;

        //! Retrieves in `value` the value associated with the provided key.
        /*! Recursively tries to retrieve from the `root` BST the value associated
         *  with the provided key, if one is found.
         *  The retrieved value is stored in the output reference parameter `value`.
         *  @param root A pointer to the tree we want to operate on.
         *  @param key The key we are looking for.
         *  @param value The value associated with the target key.
         *  @return true if key is found in the tree and the data is retrieved in value, false otherwise.
         *  @see retrieve( const KeyType & , ValueType & ) const
         */
        bool retrieve( const BTNode * root , const KeyType & key, ValueType & value ) const ;

        //! Removes all the elements from the BST.
        /*! Recursively deletes all the nodes of the BST pointed by `root`.
         *  All the allocated memory is freed to the system.
         *  The count of nodes is set to zero.
         *  @param root A pointer to the tree we want to operate on.
         *  @see clear(void)
         */
        void clear( BTNode * & root );

        //! Creates a copy of a BST tree.
        /*! Creates and returns an entire new tree that is a *deep copy*
         *  of the original BST passed in as argument.
         *  By deep copy we mean that new nodes are allocated, and all the
         *  key-value pairs are replicated on the new tree, preserving the
         *  same tree structure.
         *  @param root A pointer to the root of the tree we want to clone from.
         *  @return A pointer to the cloned tree.
         */
        BTNode * clone( const BTNode * root );

        //=== Tree traversal members
        //! Traverses and visits each BST node in **preorder** fashion.
        /*! Recursively traverses the BST in **preorder** while applying an unary function to
         *  the value field of each node.
         *  This strategy is knows as [**the visitor design pattern**](https://en.wikipedia.org/wiki/Visitor_pattern), which
         *  enables the client code freedom to specify what to do to each
         *  data node, according to application needs.
         *  @tparam UnaryFunction A function object of the form `std::function<void( const ValueType  & )>`.
         *  @param root A pointer to the root of the tree we want to traverse.
         *  @param visit The function object to be applied to each value stored in the BST.
         *  @see preorder( const UnaryFunction & ) const
         */
        template < typename UnaryFunction >
        void preorder( const BTNode * root, const UnaryFunction & visit ) const ;

        //! Traverses and visits each BST node in **postorder** fashion.
        /*! Recursively traverses the BST in **postorder** while applying an unary function to
         *  the value field of each node.
         *  This strategy is knows as [**the visitor design pattern**](https://en.wikipedia.org/wiki/Visitor_pattern), which
         *  enables the client code freedom to specify what to do to each
         *  data node, according to application needs.
         *  @tparam UnaryFunction A function object of the form `std::function<void( const ValueType  & )>`.
         *  @param root A pointer to the root of the tree we want to traverse.
         *  @param visit The function object to be applied to each value stored in the BST.
         *  @see postorder( const UnaryFunction & ) const
         */
        template < typename UnaryFunction >
        void postorder( const BTNode * root, const UnaryFunction & visit ) const ;

        //! Traverses and visits each BST node in **inorder** fashion.
        /*! Recursively traverses the BST in **inorder** while applying an unary function to
         *  the value field of each node.
         *  This strategy is knows as [**the visitor design pattern**](https://en.wikipedia.org/wiki/Visitor_pattern), which
         *  enables the client code freedom to specify what to do to each
         *  data node, according to application needs.
         *  @tparam UnaryFunction A function object of the form `std::function<void( const ValueType  & )>`.
         *  @param root A pointer to the root of the tree we want to traverse.
         *  @param visit The function object to be applied to each value stored in the BST.
         *  @see inorder( const UnaryFunction & ) const
         */
        template < typename UnaryFunction >
        void inorder( const BTNode * root, const UnaryFunction & visit ) const ;

        //! Returns a pointer to the BST node with the smallest key value.
        /*!
         * Helper method needed by remove() when the target node has 2 children.
         * @param root Pointer to the root node of a tree.
         * @return A pointer to a leaf with the smallest key (left most leaf).
         */
        const BTNode * get_smallest_leaf( const BTNode * root ) const ;

    public:
        //=== alias
        typedef std::pair<KeyType, ValueType> node_content_type; //!< Represents a pair of key-value elements.
        //=== special member
        //! Default constructor.
        /*!
         *  Creates an empty BST.
         *  @param comp The function object necessary to compare keys.
         */
        explicit BST( const KeyTypeLess & comp = KeyTypeLess() )
            : m_root( nullptr )
            , m_n_nodes(0)
            , m_key_less ( comp )
            {/* empty */}

        //! Copy constructor.
        /*!
         *  The BST copy constructor.
         *  This constructor creates a *deep copy* of the
         *  of the original BST passed in as argument.
         *  By deep copy we mean that new nodes are allocated, and all the
         *  key-value pairs are replicated on the new tree, preserving the
         *  same tree structure.
         *  @param other The BST we are copying-constructing from.
         *  @see clone( const BTNode *)
         */
        BST( const BST & other ) ;

        //! Regular destructor.
        /*! The destructor frees all the memory allocated while creating the BST.
         */
        ~BST();

        //! The range constructor.
        /*!
         *  The BST range constructor.
         *  This constructor creates a new tree inserting key-value elements
         *  from the range `[first, last)` provided.
         *  We assume the range is valid and that each element of the
         *  range is of the type BST::node_content_type.
         *  If multiple elements in the range have keys that compare equivalent,
         *  only the first instance of the pair key-value is inserted.
         *
         *  @tparam InputItr The input iterator to the range we insert from.
         *  @param first the begining of the range to copy from.
         *  @param last the end (exclusive) of the range to copy from.
         *  @param comp The function object necessary to compare keys.
         */
        template < typename InputItr >
        BST( InputItr first, InputItr last, const KeyTypeLess & comp = KeyTypeLess() );

        //! The intializer list constructor.
        /*!
         *  The BST initializer list constructor.
         *  This constructor creates a new tree inserting key-value elements
         *  from the range initializer list `init` provided.
         *  We assume the input list is valid and that each element of the
         *  list is of the type BST::node_content_type.
         *  If multiple elements in the initialize list have keys that compare equivalent,
         *  only the first instance of the pair key-value is inserted.
         *
         *  @param init The initializer list to initialize the elements of the BST with.
         *  @param comp The function object necessary to compare keys.
         */
        BST( std::initializer_list< node_content_type > init , const KeyTypeLess & comp = KeyTypeLess());


        //! The copy assignment operator.
        /*!
         *  The BST copy assignment operator.
         *  This operator replaces the current BST content with a *deep copy* of
         *  the elements from the `rhs` BST. 
         *  By deep copy we mean that new nodes are allocated, and all the
         *  key-value pairs are replicated on the new tree, preserving the
         *  same tree structure.
         *
         *  @param rhs The BST container to use as data source.
         *  @return `*this` to enable chained assignments.
         */
        BST & operator=( const BST & rhs );

        //! The initializer list assignment operator.
        /*!
         *  The BST initializer list assignment operator.
         *  This operator replaces the current BST content with the contents from
         *  the intializer list `ilist`.
         *  We assume the input list is valid and that each element of the
         *  list is of the type BST::node_content_type.
         *  If multiple elements in the initialize list have keys that compare equivalent,
         *  only the first instance of the pair key-value is inserted.
         *
         *  @param ilist The initialize list to use as data source.
         *  @return `*this` to enable chained assignments.
         */
        BST & operator=( std::initializer_list< node_content_type > ilist );

        //=== access members
        //! Returns the value associated with the smallest key.
        const ValueType & find_min( void ) const;
        //! Returns the value associated with the largest key.
        const ValueType & find_max( void ) const;

        //! Checks whether the BST contains a given key.
        /*! Returns true if the BST contains a given key, or false otherwise.
         *  @param key The key we are looking for.
         *  @return true if key is found in the tree, false otherwise.
         *  @see contains( const BTNode * , const KeyType & ) const
         */
        bool contains( const KeyType & key ) const;

        //! Returns true if the BST is empty, or false otherwise.
        inline bool empty( void ) const { return m_n_nodes == 0; };
        //! Returns the number of key-value elements stored in the BST.
        inline size_t size( void ) const { return m_n_nodes; };

        //! Retrieves in `value` the value associated with the provided key.
        /*! Retrieves from the BST the value associated with the provided key, if one is found.
         *  The retrieved value is stored in the output reference parameter `value`.
         *  @param key The key we are looking for.
         *  @param value The value associated with the target key we copied into.
         *  @return true if key is found in the tree and the data is retrieved in value, false otherwise.
         *  @see retrieve( const BTNode * , const KeyType & , ValueType & ) const
         */
        bool retrieve( const KeyType & key, ValueType & value ) const;

        //=== tree traversal members
        //! Traverses and visits each BST node in **preorder** fashion.
        /*! During the **preorder** BST traversal the method applies an unary function to
         *  the value field of each visited node.
         *  This strategy is knows as [**the visitor design pattern**](https://en.wikipedia.org/wiki/Visitor_pattern),
         *  which enables the client code to decouple the algorithm to be applied to each
         *  node from the BST structure.
         *  @tparam UnaryFunction A function object of the form `std::function<void( const ValueType  & )>`.
         *  @param visit The function object to be applied to each value stored in the BST.
         *  @see preorder( const BTNode * , const UnaryFunction & ) const
         */
        template < typename UnaryFunction >
        void preorder( const UnaryFunction & visit ) const ;

        //! Traverses and visits each BST node in **postorder** fashion.
        /*! During the **postorder** BST traversal the method applies an unary function to
         *  the value field of each visited node.
         *  This strategy is knows as [**the visitor design pattern**](https://en.wikipedia.org/wiki/Visitor_pattern), which
         *  enables the client code freedom to specify what to do to each
         *  data node, according to application needs.
         *  @tparam UnaryFunction A function object of the form `std::function<void( const ValueType  & )>`.
         *  @param visit The function object to be applied to each value stored in the BST.
         *  @see postorder( const BTNode * , const UnaryFunction & ) const
         */
        template < typename UnaryFunction >
        void postorder( const UnaryFunction & visit ) const ;

        //! Traverses and visits each BST node in **inorder** fashion.
        /*! During the **inorder** BST traversal the method applies an unary function to
         *  the value field of each visited node.
         *  This strategy is knows as [**the visitor design pattern**](https://en.wikipedia.org/wiki/Visitor_pattern), which
         *  enables the client code freedom to specify what to do to each
         *  data node, according to application needs.
         *  @tparam UnaryFunction A function object of the form `std::function<void( const ValueType  & )>`.
         *  @param visit The function object to be applied to each value stored in the BST.
         *  @see inorder( const BTNode * , const UnaryFunction & ) const
         */
        template < typename UnaryFunction >
        void inorder( const UnaryFunction & visit ) const ;


        //=== MODIFIER MEMBERS

        //! Removes all the elements from the BST.
        /*! Removes all the nodes of the BST, freeing the memory associated with the BST.
         *  The count of nodes is set to zero.
         *  @see clear( BTNode * & )
         */
        void clear( void );

        //! Inserts a new pair <`key`,`value`> in the tree.
        /*! Creates and inserts a new node with a <`key`,`value`> pair in the
         *  BST tree if the key is not already stored in the tree.
         *  @param key The key associated with the value we wish to operate on.
         *  @param value The value we wish to store in the tree.
         *  @see insert( BTNode * & , const KeyType & , const ValueType & )
         */
        void insert( const KeyType & key , const ValueType & value );

        //! Removes from the BST a node containing the requested key.
        /*! Removes from the BST a node containing the requested key if one
         *  is found in the tree.
         *  The deletion might modifiy the tree structure to preserve the
         *  BST properties.
         *  If the key is not found, nothing happens to the tree.
         *  @param key The key associated with the value we wish to operate on.
         *  @param value The value we wish to store in the tree.
         *  @see remove( BTNode * & , const KeyType & , const ValueType & )
         */
        void remove( const KeyType & key );


        //=== FRIEND FUNCTION
        //! Prints out an ascii tree-bar representation of the BST.
        /*!
         *  Sends to the output stream an ascii tree-bar representation of the BST.
         *  Left subtrees appear before right subtrees.
         *  Null nodes are represented with `X`.
         *  @param os_ The output stream to write to.
         *  @param root_ The pointer to the root of the BST we wish to visualize.
         *  @return A reference to the ostream object to enable further chained operation on the ostream object.
         */
        friend std::ostream& operator<< ( std::ostream& os_, const BST & root_ )
        {
            if ( root_.empty() )
            {
                os_ << "<empty tree>";
                return os_;
            }

            typedef std::pair< size_t, BTNode * > stack_type;
            std::stack< stack_type > s;
            // We have at least one element in the tree.
            s.push( std::make_pair( 0, root_.m_root ) ); // push root at level 0.

            // We follow pre-order traversal strategy.
            while( not s.empty() )
            {
                // (1) Visite the root first.
                auto visited = s.top(); s.pop();
                for( auto i(0u) ; i < visited.first ; ++i )
                    os_ << "--";
                if ( visited.second == nullptr )
                {
                    os_ << "X\n";
                    continue;
                }
                else
                {
                    os_ << visited.second->data  << "\n";
                }

                // (2) Now we traverse the left and right subtrees.
                // Store the children for future processing (next loop iteration).
                /*
                if ( visited.second->right == nullptr 
                        and visited.second->left == nullptr ) // avoid tail recursion.
                    continue;
                */
                // At least one child left
                //if ( visited.second->right != nullptr ) // avoid tail recursion.
                    s.push( std::make_pair( visited.first+1, visited.second->right ) );
                //if ( visited.second->left != nullptr ) // avoid tail recursion.
                    s.push( std::make_pair( visited.first+1, visited.second->left ) );
            }
            return os_;
        }
};

#include "bst.inl"
