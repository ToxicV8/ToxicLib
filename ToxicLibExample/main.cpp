#include "../ToxicLib/toxic_lib.h"
#include "../ToxicLib/utils.h"
#include "../ToxicLib/vector_wrapper.h"
#include <assert.h>

void test_vector_wrapper()
{
    toxic_lib::wrapper::vector_wrapper<char> wrapper;

    wrapper.push_as_byte( 0x100000000 );
    wrapper().push_back( 0x23 );
    wrapper.print( std::cout );
}

void test_ínt_from_bytes()
{
    unsigned char bytes[] = { 0x00, 0x00, 0xFF };
    int integer = toxic_lib::utils::int_from_bytes( bytes, 3, false );
    
    assert( integer == 255 );

    std::cout << "int_from_bytes: " << integer << '\n';
}

void test_swap_chars()
{
    std::string string = "ow tirked";

    toxic_lib::utils::swap_chars( string, {
        { 0, 4 },
        { 1, 3 }
    } );

    assert( string == "it worked" );
    std::cout << "Swapped String: " << string << '\n';
}

void test_random_gen()
{
    std::cout << "random int with default engine: " << toxic_lib::utils::get_random_int<std::default_random_engine>( 10, 10000 ) << '\n';
}

int main()
{
    test_random_gen();
    test_ínt_from_bytes();
    test_swap_chars();
    test_vector_wrapper();

    getchar();
    return 0;
}