#pragma once
#include "toxic_lib.h"

BEGIN_NAMESPACE(toxic_lib)
BEGIN_NAMESPACE(wrapper)

template<class T>
class vector_wrapper
{
public:

    std::vector<T>& operator() ()
    {
        return object;
    }

    void print( std::ostream& stream, const bool use_newlines = true )
    {
        constexpr bool is_char = std::is_same<T, char>::value;

        if( is_char ) {
            std::cout << std::hex;
        }

        for( size_t i = 0; i < object.size(); ++i ) {
            if( is_char ) {
                stream << i << ':' << ( int( object.at( i ) ) & 0xFF );
            }
            else {
                stream << i << ':' << object.at( i );
            }

            if( use_newlines )
                stream << '\n';
        }

        if( is_char ) {
            std::cout << std::dec;
        }
    }

    // Will only work for types with right shift operator
    template<typename ValType, typename = std::enable_if_t<std::is_same<T, char>::value>>
    void push_as_byte( const ValType& value )
    {
        for( int i = 0; i < sizeof( ValType ); ++i ) {
            object.push_back( unsigned char( value >> ( ( ( sizeof( value ) - 1 ) * 8 ) - ( i * 8 ) ) & 0xFF ) );
        }
    }

private:
    std::vector<T> object;
};

END_NAMESPACE(wrapper)
END_NAMESPACE(toxic_lib)