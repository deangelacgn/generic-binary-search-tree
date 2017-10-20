#include "bst.h"

template < typename KeyType, typename ValueType >
void BST< KeyType, ValueType >::insert( BTNode * & root, const KeyType & key, const ValueType & value )
{
	if(contains(root, key))
    {
        return;
    }
    else
    {
        if(root == nullptr)
        {
            root = new BTNode(key, value, nullptr, nullptr);
            m_n_nodes++;
        }
        else if(m_key_less(root->key, key))
        {
            insert(root->left, key, value);
        }
        else
        {
            insert(root->right, key, value);
        }
    }
}

template < typename KeyType, typename ValueType >
void BST< KeyType, ValueType >::remove( BTNode * & root, const KeyType & key )
{
    if(root == nullptr)
    {
        return;
    }
    if(m_key_less(root->key, key))
    {
        remove(root->left, key);
    }
    else if(!m_key_less(root->key, key) && !m_key_less(key, root->key))
    {
        if(root->left == nullptr && root->right == nullptr)
        {
            delete root;
            root = nullptr;
            m_n_nodes--;
        }
        else if(root->right == nullptr)
        {
            BTNode * temp = root;
            root = root->left;
            temp->left = nullptr;
            temp->right = nullptr;
            delete temp;
            temp = nullptr;
            m_n_nodes--;
        }
        else if (root->left == nullptr)
        {
            BTNode * temp = root;
            root = root->right;
            temp->left = nullptr;
            temp->right = nullptr;
            delete temp;
            temp = nullptr;
            m_n_nodes--;
        }
        else
        {
            const BTNode * temp = get_smallest_leaf(root->right);
            root->key = temp->key;
            root->data = temp->data;
            remove(root->right, temp->key);
        }

    }
    else
    {
        remove(root->right, key);
    }

    return;
}

template < typename KeyType, typename ValueType >
bool BST< KeyType, ValueType >::contains( const BTNode * root , const KeyType & key ) const
{
    while(root != nullptr)
    {
        if(m_key_less(root->key, key))
        {
            root = root->left;
        }
        else if(!m_key_less(root->key, key) && !m_key_less(key, root->key))
        {
            return true;
        }
        else
        {
            root = root->right;
        }
    }

    return false;
}

template < typename KeyType, typename ValueType >
bool BST< KeyType, ValueType >::retrieve( const BTNode * root , const KeyType & key, ValueType & value ) const 
{
    while(root != nullptr)
    {
        if(m_key_less(root->key, key))
        {
            root = root->left;
        }
        else if(!m_key_less(root->key, key) && !m_key_less(key, root->key))
        {
            value = root->data;
            return true;
        }
        else
        {
            root = root->right;
        }
    }
    return false;
}

template < typename KeyType, typename ValueType >
void BST< KeyType, ValueType >::clear( BTNode * & root )
{
     if(root != nullptr)
    {
        delete root;
        root = nullptr;
        m_n_nodes = 0;
    }
    else
    {
        return;
    }
}

template < typename KeyType, typename ValueType >
typename BST< KeyType, ValueType >::BTNode * BST< KeyType, ValueType >::clone( const BTNode * root )
{
    if(root == nullptr)
    {
        return nullptr;
    }

    BTNode * new_node = new BTNode(root->key, root->data);

    new_node->left = clone(root->left);
    new_node->right = clone(root->right);

    return new_node;
}

template < typename KeyType, typename ValueType >
template < typename UnaryFunction >
void BST< KeyType, ValueType >::preorder( const BTNode * root, const UnaryFunction & visit ) const 
{
    if(root == nullptr)
    {
        return;
    }
    
    visit(root->data);

    preorder(root->left, visit);
    preorder(root->right, visit);
}

template < typename KeyType, typename ValueType >
template < typename UnaryFunction >
void BST< KeyType, ValueType >::postorder( const BTNode * root, const UnaryFunction & visit ) const 
{
    if(root == nullptr)
    {
        return;
    }

    postorder(root->left, visit);
    postorder(root->right, visit);

    visit(root->data);
}

template < typename KeyType, typename ValueType >
template < typename UnaryFunction >
void BST< KeyType, ValueType >::inorder( const BTNode * root, const UnaryFunction & visit ) const 
{
    if(root == nullptr)
    {
        return;
    }

    inorder(root->left, visit);

    visit(root->data);

    inorder(root->right, visit);
}

template < typename KeyType, typename ValueType >
const typename BST< KeyType, ValueType >::BTNode * BST< KeyType, ValueType >::get_smallest_leaf( const BTNode * root ) const 
{
    if(root == nullptr)
    {   
        return nullptr;
    }

    if(root->left == nullptr)
    {
        return root;
    }
    else
    {
        return get_smallest_leaf(root->left);
    }
}
template < typename KeyType, typename ValueType >
BST< KeyType, ValueType >::BST( const BST & other ):m_key_less(other.m_key_less) 
{
    *this = other;
}

template < typename KeyType, typename ValueType >
BST< KeyType, ValueType >::~BST()
{ 
    delete m_root;
}

template < typename KeyType, typename ValueType >
template < typename InputItr >
BST< KeyType, ValueType >::BST( InputItr first, InputItr last, const KeyTypeLess & comp ): m_key_less(comp) 
{
    for(auto it=first; it!= last; it++)
    {  
        (*this).insert(m_root, (*it).first, (*it).second);
    }
}

template < typename KeyType, typename ValueType >
BST< KeyType, ValueType >::BST( std::initializer_list< BST< KeyType, ValueType >::node_content_type > init , const KeyTypeLess & comp ):m_key_less(comp)
{
    *this = init;
}

template < typename KeyType, typename ValueType >
BST< KeyType, ValueType > & BST< KeyType, ValueType >::operator=( const BST< KeyType, ValueType > & rhs )
{

    delete m_root;
    m_root = clone(rhs.m_root);
    m_n_nodes = rhs.m_n_nodes;
    m_key_less = rhs.m_key_less;

    return *this;

}

template < typename KeyType, typename ValueType >
BST< KeyType, ValueType > & BST< KeyType, ValueType >::operator=( std::initializer_list< BST< KeyType, ValueType >::node_content_type > ilist )
{
    for(const auto & element: ilist)
    {
        (*this).insert(element.first, element.second);
    }

    return *this;
}

template < typename KeyType, typename ValueType >
const ValueType & BST< KeyType, ValueType >::find_min( void ) const
{
    return get_smallest_leaf(m_root)->data;
}

template < typename KeyType, typename ValueType >
const ValueType & BST< KeyType, ValueType >::find_max( void ) const
{
    if(m_root != nullptr)
    {
        BTNode * temp = m_root;
        while(temp->right != nullptr)
        {
            temp = temp->right;
        }

        return temp->data;
    }
    else
    {
        throw std::runtime_error("find_max: called upon an empty tree");
    }
}

template < typename KeyType, typename ValueType >
bool BST< KeyType, ValueType >::contains( const KeyType & key ) const
{
    return contains(m_root, key);
}

template < typename KeyType, typename ValueType >
bool BST< KeyType, ValueType >::retrieve( const KeyType & key, ValueType & value ) const
{
    return retrieve(m_root, key, value);
}

template < typename KeyType, typename ValueType >
template < typename UnaryFunction >
void BST< KeyType, ValueType >::preorder( const UnaryFunction & visit ) const 
{
    return preorder(m_root, visit);
}

template < typename KeyType, typename ValueType >
template < typename UnaryFunction >
void BST< KeyType, ValueType >::postorder( const UnaryFunction & visit ) const 
{
    return postorder(m_root, visit);
}

template < typename KeyType, typename ValueType >
template < typename UnaryFunction >
void BST< KeyType, ValueType >::inorder( const UnaryFunction & visit ) const 
{
    return inorder(m_root, visit);
}

template < typename KeyType, typename ValueType >
void BST< KeyType, ValueType >::clear( void )
{
    return clear(m_root);
}

template < typename KeyType, typename ValueType >
void BST< KeyType, ValueType >::insert( const KeyType & key , const ValueType & value )
{
    return insert(m_root, key, value);
}

template < typename KeyType, typename ValueType >
void BST< KeyType, ValueType >::remove( const KeyType & key )
{
    remove(m_root, key);
}
