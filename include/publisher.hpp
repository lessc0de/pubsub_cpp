#pragma once

#include "subscriber.hpp"

#include <memory>
#include <vector>
#include <thread>

template< typename T, typename S=yielding_sequence >
class publisher
{
friend class subscriber< T, S >;
public:
    publisher( size_t );

    subscriber< T, S >& subscribe();

    template< typename F >
    void publish( size_t, F func );

private:
    subscriber< T, S >& subscribe( S& );

    T& at( typename S::value_type );

    typename S::value_type tail();

    size_t size_;

    std::unique_ptr< T[] > data_;

    S head_;

    typedef std::vector< std::unique_ptr< subscriber< T, S > > > subscriber_list;
    subscriber_list tail_;
};

#include "publisher.inl"
