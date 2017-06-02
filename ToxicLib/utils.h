#pragma once
#include "toxic_lib.h"

BEGIN_NAMESPACE(toxic_lib)
BEGIN_NAMESPACE(utils)

template<typename T>
inline void swap( T* v1, T* v2 )
{
    T temp;
    temp = std::move( *v1 );
    *v1 = std::move( *v2 );
    *v2 = std::move( temp );
}

template<typename T>
inline void swap( T& v1, T& v2 )
{
    T temp;
    temp = std::move( v1 );
    v1 = std::move( v2 );
    v2 = std::move( temp );
}

inline int int_from_bytes( const unsigned char* bytes, size_t byte_count, const bool little_endian )
{
    const unsigned char* start = bytes;
    const unsigned char* end = bytes + byte_count - 1;

    int incrementor = 1;

    if( !little_endian ) {
        swap( &start, &end );
        incrementor = -1;
    }

    unsigned int pos;

    // Get the first significant byte
    for( pos = 0; pos < byte_count; ++pos ) {
        if( *( end + ( ( -incrementor ) * pos ) ) != 0x00 )
            break;
    }

    size_t significant_bytes = byte_count - pos;

    unsigned int result = 0;
    for( pos = 0; pos < significant_bytes; ++pos ) {
        result |= *( start + ( incrementor * pos ) ) << ( pos * 8 );
    }

    return result;
}

template<typename _GENERATOR>
inline int get_random_int( const int& min, const int& max )
{
    std::random_device random_device;
    _GENERATOR gen( random_device() );
    std::uniform_int_distribution<int> dist( min, max );

    return dist( gen );
}

inline void swap_chars( std::string& str, const std::initializer_list<std::pair<int, int>>& to_swap )
{
    for( std::initializer_list<std::pair<int, int>>::iterator iter = to_swap.begin(); iter != to_swap.end(); ++iter ) {
        swap( str[ iter->first ], str[ iter->second ] );
    }
}

END_NAMESPACE(utils)
END_NAMESPACE(toxic_lib)