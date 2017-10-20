#include <iostream>   // cout, cin, endl
#include <utility>    // std::pair<>
#include <random>     // radom_device, mt19937, std::shuffle.
#include <iomanip>    // std::setw()
#include <string>     // std::string
#include <cassert>
#include <vector>
#include <algorithm>

#include "../include/bst.h"

template<class T>
void print(const T &arg)
{
    std::cout << arg << std::endl;
}

int main()
{
    //auto n_unit{0}; // unit test count.

    // Our BST will store strings with integer keys.
    typedef std::pair< size_t,std::string > test_type;

    // Input data
    test_type data[] = {
        { 0, "zero" },
        { 1, "one" },
        { 2, "two" },
        { 3, "three" },
        { 4, "four" },
        { 5, "five" },
        { 6, "six" },
        { 7, "seven" },
        { 8, "eight" },
        { 9, "nine" },
        { 10, "ten" }
    };

    std::vector<test_type> data2 = {{ 5, "five" }, { 1, "one" }, { 7, "seven" }, { 0, "zero" }, { 6, "six" }, { 2, "two" }};
    std::initializer_list<test_type> data3 = {{ 5, "five" }, { 1, "one" }, { 7, "seven" }, { 0, "zero" }, { 6, "six" }, { 2, "two" }};


    // Print the input
    {
        size_t insertion_order[] = { 5, 1, 7, 0, 3, 2 };
        // The tree declaration.
//#define USE_FUNCTOR
#ifdef USE_FUNCTOR
        struct CompareKey {
            bool operator()( const size_t & a, const size_t & b )
            {
                return a > b ;
            }
        };
        BST< size_t, std::string, CompareKey > tree;
#else // Use lambda
        auto compare_keys = []( const size_t &a, const size_t &b )->bool
        {
            return a > b ;
        };
        //BST< size_t, std::string, decltype( compare_keys ) > tree( compare_keys );
#endif
        // Test standard constructor
        BST< size_t, std::string > tree( compare_keys );
        // Test iterator constructor
        BST< size_t, std::string > tree2( data2.begin(), data2.end() ,compare_keys );
        
        // Test insertion method
        std::cout << ">>> Inserting data:\n";
        for( const auto & e : insertion_order )
        {
            std::cout << "< " << std::setw(3) << data[e].first << " , \"" << data[e].second << "\" >\n";
            tree.insert( data[e].first, data[e].second );
        }

        // Test copy constructor
        BST< size_t, std::string > tree3(tree);

        //Test list constructor
        BST< size_t, std::string > tree4(data3, compare_keys);

        std::cout << "\n>>> The tree:\n" << tree << std::endl;

        //Test the constains() method
        std::cout << "Does this tree contain the key 3? "<< tree.contains(3)<< std::endl;

        std::cout << "Does this tree contain the key 11? "<< tree.contains(11)<< std::endl;

        std::cout << "Does this tree contain the key 9? "<< tree.contains(9)<< std::endl;

        //Test the find_max() method
        std::cout << "Maximum value in the tree: "<< tree.find_max() << std::endl;

        //Test the find_mind() method
        std::cout << "Minimum value in the tree: "<< tree.find_min() << std::endl;

        // Test retrieve() method
        std::string placeholder;
        tree.retrieve(3, placeholder);
        std::cout << "Value of placeholder: "<< placeholder << std::endl;

        std::cout << "\n>>> The tree 2:\n" << tree2 << std::endl;

        std::cout << "\n>>> The tree 3:\n" << tree3 << std::endl;

        std::cout << "\n>>> The tree 4:\n" << tree4 << std::endl;

        // Test all traversals
        std::cout << "Inorder traversal:"<<std::endl;
        tree.inorder(print<std::string>);

        std::cout << "Preorder traversal:"<<std::endl;
        tree.preorder(print<std::string>);

        std::cout << "postorder traversal:"<<std::endl;
        tree.postorder(print<std::string>);

        //Test clear method
        tree.clear();

        std::cout << "Number of nodes: "<< tree.size() <<std::endl;

        tree.remove(1);
        tree.remove(7);
        tree.remove(3); 
        
        std::cout << "\n>>> The tree:\n" << tree << std::endl;



    }

    return EXIT_SUCCESS;
}
