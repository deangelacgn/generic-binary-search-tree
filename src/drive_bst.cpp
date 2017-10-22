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
    auto n_unit{0}; // unit test count.

    // Our BST will store integers with integer keys.
    typedef std::pair< size_t,size_t > test_type;

    // Input data
    test_type data[] = {
        { 0, 0},
        { 1, 1},
        { 2, 2},
        { 3, 3 },
        { 4, 4},
        { 5, 5 },
        { 6, 6 },
        { 7, 7 },
        { 8, 8 },
        { 9, 9 },
        { 10, 10 }
    };

    // Print the input
    {
        //size_t insertion_order[] = { 5, 1, 7, 0, 3, 2 };
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

    {
    	{
	        std::cout << ">>> Unit teste #" << ++n_unit << ": insertion.\n";
	        //The tree
	        BST< size_t, size_t > tree( compare_keys );

	        for( const auto & e : data)
	        {
	            //std::cout << "< " << std::setw(3) << data[e].first << " , \"" << data[e].second << "\" >\n";
	            tree.insert( e.first, e.second );
	        }
	        
	        for( const auto & e : data )
	        {
	            assert( tree.contains( e.first ) );   
	        }
	        
	        std::cout << ">>> Passed!\n\n";
    	}

    	{
	        std::cout << ">>> Unit teste #" << ++n_unit << ": find_min.\n";

	        BST< size_t, size_t > tree( compare_keys );

	        auto min{ data[0].first };
	        for( const auto & e : data )
	        {
	            // Get the smallest so far.
	            min = std::min( min, e.first );
	            tree.insert( e.first, e.second );
	            assert( tree.find_min() == min );
	        }

	        std::cout << ">>> Passed!\n\n";
    	}
     
	    {   
	        std::cout << ">>> Unit teste #" << ++n_unit << ": find_max.\n";

	        BST< size_t, size_t > tree( compare_keys );

	        auto max{ data[0].first };
	        for( const auto & e : data )
	        {
	            // Get the smalles so far.
	            max = std::max( max, e.first );
	            tree.insert( e.first, e.second );
	            assert( tree.find_max() == max );
	        }

	        std::cout << ">>> Passed!\n\n";
	    }

	    {
	        std::cout << ">>> Unit teste #" << ++n_unit << ": size.\n";
	        // The tree
	        BST< size_t, size_t > tree( compare_keys );

	        size_t expected_size{1};
	        for( const auto & e : data )
	        {
	            tree.insert( e.first, e.second );
	            assert( expected_size == tree.size() );
	            ++expected_size;
	        }

        	std::cout << ">>> Passed!\n\n";
    	}

	    {
	        std::cout << ">>> Unit teste #" << ++n_unit << ": clear.\n";
	        // The tree
	        BST< size_t, size_t > tree( compare_keys );
	        assert( true == tree.empty() );

	        for( const auto & e : data )
	            tree.insert( e.first, e.second );

	        tree.clear();
	        assert( true == tree.empty() );

	        std::cout << ">>> Passed!\n\n";
	    }

	    {
	        std::cout << ">>> Unit teste #" << ++n_unit << ": retrieve.\n";
	        // The tree
	        BST< size_t, size_t > tree( compare_keys );
	        assert( true == tree.empty() );

	        for( const auto & e : data )
	            tree.insert( e.first, e.second );

	        for( const auto & e : data )
	        {
	            size_t value;
	            assert( tree.retrieve( e.first, value ) );
	            assert( value == e.second );
	        }

	        std::cout << ">>> Passed!\n\n";
    	}

	    {
	        std::cout << ">>> Unit teste #" << ++n_unit << ": contains.\n";
	        // The tree
	        BST< size_t, size_t > tree( compare_keys );
	        assert( true == tree.empty() );

	        for( const auto & e : data )
	            tree.insert( e.first, e.second );

	        for( const auto & e : data )
	        {
	            assert( tree.contains( e.first ) );
	        }

	        std::cout << ">>> Passed!\n\n";
	    }

	    {
	        std::cout << ">>> Unit teste #" << ++n_unit << ": assignment operator.\n";
	        // The tree
	        BST< size_t, size_t > tree( compare_keys );
	        assert( true == tree.empty() );

	        for( const auto & e : data )
	            tree.insert( e.first, e.second );

	        // Assignment operator.
	        auto tree2 = tree;

	        // Let us test if everything is ok with the clone tree.
	        for( const auto & e : data )
	            assert( tree2.contains( e.first ) );

	        std::cout << ">>> Passed!\n\n";
    	}

    	{
	        std::cout << ">>> Unit teste #" << ++n_unit << ": copy constructor.\n";
	        // Creating a tree with > instead of <.
	        BST< size_t, size_t > tree( compare_keys );
	        assert( true == tree.empty() );

	        for( const auto & e : data )
	            tree.insert( e.first, e.second );

	        // Assignment operator.
	        auto tree_copy( tree );

	        tree.clear();

	        // Let us test if everything is ok with the clone tree.
	        for( const auto & e : data )
	            assert( tree_copy.contains( e.first ) );

	        std::cout << ">>> Passed!\n\n";
    	}

    	{
	        std::cout << ">>> Unit teste #" << ++n_unit << ": empty.\n";
	        // The tree
	        BST< size_t, size_t > tree( compare_keys );

	        assert( true == tree.empty() );

	        for( const auto & e : data )
	        {
	            tree.insert( e.first, e.second );
	            assert( false == tree.empty() );
	        }
	        
	        for( const auto & e : data )
	        {
	            //std::cout << "Removing: < " << std::setw(3) << e.first << " , \"" << e.second << "\" >\n";
	            tree.remove( e.first );
	            //std::cout << "\n>>> [main()] The tree:\n" << tree << std::endl;
	        }
	        assert( true == tree.empty() );

	        std::cout << ">>> Passed!\n\n";
    	}

    	{
	        std::cout << ">>> Unit teste #" << ++n_unit << ": deletion.\n";

	        BST< size_t, size_t > tree( compare_keys );

	        
	        auto tree_copy( tree );
	        for( const auto & e : data)
	        {
	            tree = tree_copy; // restore back the original tree.
	            tree.remove( e.first ); // Remove a single node.
	        }
	        
	         for( const auto & e : data)
	        {
	            tree.remove( e.first ); // Remove a single node.
	        }
	        std::cout << ">>> Passed!\n\n";

    	}

    	{
	        std::cout << ">>> Unit teste #" << ++n_unit << ": tree traversal.\n";
	        // The tree
	        BST< size_t, size_t > tree( compare_keys );

	        // Insert elements.
	        for( const auto & e : data )
	            tree.insert( e.first, e.second );

	        // Expected answers
	        std::vector< decltype(data[0].second) > pre_vec =
	        { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
	        std::vector< decltype(data[0].second) > in_vec =
	        { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
	        std::vector< decltype(data[0].second) > pos_vec =
	        { 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0 };

	        // function object.
	        std::vector< decltype(data[0].second) > vec;
	        auto print = [&]( const decltype(data[0].second) & data_ )-> void
	        {
	            vec.push_back ( data_ ); // Capture data.
	            //std::cout << data_ << ", ";
	        };

	        vec.clear();
	        //std::cout << ">>> preorder tree traversal:\n";
	        tree.preorder( print );
	        assert( vec == pre_vec );

	        vec.clear();
	        //std::cout << "\n>>> inorder tree traversal:\n";
	        tree.inorder( print );
	        assert( vec == in_vec );

	        vec.clear();
	        //std::cout << "\n>>> postorder tree traversal:\n";
	        tree.postorder( print );
	        assert( vec == pos_vec );

	        std::cout << ">>> Passed!\n\n";
    	}

    }
		std::cout << "\n>>> Normal exiting...\n";	
    }

    return EXIT_SUCCESS;
}
