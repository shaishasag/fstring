#include "gtest/gtest.h"
#include "fstring.h"
#include <type_traits>

TEST(TypeTraits, traits_to_fix)
{
    // these should be EXPECT_TRUE, but they are EXPECT_FALSE
    EXPECT_FALSE((std::is_swappable_with_v<fstr::fstr31, fstr::fstr31>));
    EXPECT_FALSE((std::is_nothrow_swappable_with_v<fstr::fstr31, fstr::fstr31>));

    EXPECT_FALSE((std::is_trivially_assignable_v<fstr::fstr31, char>));
    EXPECT_FALSE((std::is_trivially_assignable_v<fstr::fstr31, char*>));
    EXPECT_FALSE((std::is_trivially_assignable_v<fstr::fstr31, std::string_view>));
    EXPECT_FALSE((std::is_trivially_assignable_v<fstr::fstr31, std::string>));
    EXPECT_FALSE((std::is_trivially_assignable_v<fstr::fstr31, fstr::fstr_ref>));

    EXPECT_FALSE((std::is_convertible_v<fstr::fstr31, std::string>));
}


TEST(TypeTraits, some_traits)
{
    // irrelevant is_....
    {
        EXPECT_FALSE(std::is_void_v<fstr::fstr31>);
        EXPECT_FALSE(std::is_void_v<fstr::fstr_ref>);
        EXPECT_FALSE(std::is_void_v<fstr::fstr31>);
        EXPECT_FALSE(std::is_void_v<fstr::fstr_ref>);
        EXPECT_FALSE(std::is_integral_v<fstr::fstr31>);
        EXPECT_FALSE(std::is_integral_v<fstr::fstr_ref>);
        EXPECT_FALSE(std::is_floating_point_v<fstr::fstr31>);
        EXPECT_FALSE(std::is_floating_point_v<fstr::fstr_ref>);
        EXPECT_FALSE(std::is_enum_v<fstr::fstr31>);
        EXPECT_FALSE(std::is_enum_v<fstr::fstr_ref>);
        EXPECT_FALSE(std::is_union_v<fstr::fstr31>);
        EXPECT_FALSE(std::is_pointer_v<fstr::fstr_ref>);
        EXPECT_FALSE(std::is_pointer_v<fstr::fstr31>);
        EXPECT_FALSE(std::is_lvalue_reference_v<fstr::fstr_ref>);
        EXPECT_FALSE(std::is_lvalue_reference_v<fstr::fstr31>);
        EXPECT_FALSE(std::is_rvalue_reference_v<fstr::fstr_ref>);
        EXPECT_FALSE(std::is_member_object_pointer_v<fstr::fstr31>);
        EXPECT_FALSE(std::is_member_object_pointer_v<fstr::fstr_ref>);
        EXPECT_FALSE(std::is_member_function_pointer_v<fstr::fstr31>);
        EXPECT_FALSE(std::is_member_function_pointer_v<fstr::fstr_ref>);

        EXPECT_FALSE(std::is_fundamental_v<fstr::fstr31>);
        EXPECT_FALSE(std::is_fundamental_v<fstr::fstr_ref>);
        EXPECT_FALSE(std::is_arithmetic_v<fstr::fstr31>);
        EXPECT_FALSE(std::is_arithmetic_v<fstr::fstr_ref>);
        EXPECT_FALSE(std::is_scalar_v<fstr::fstr31>);
        EXPECT_FALSE(std::is_scalar_v<fstr::fstr_ref>);
        EXPECT_FALSE(std::is_reference_v<fstr::fstr31>);
        EXPECT_FALSE(std::is_reference_v<fstr::fstr_ref>);
        EXPECT_FALSE(std::is_member_pointer_v<fstr::fstr31>);
        EXPECT_FALSE(std::is_member_pointer_v<fstr::fstr_ref>);
        EXPECT_FALSE(std::is_const_v<fstr::fstr31>);
        EXPECT_FALSE(std::is_const_v<fstr::fstr_ref>);
        EXPECT_FALSE(std::is_volatile_v<fstr::fstr31>);
        EXPECT_FALSE(std::is_volatile_v<fstr::fstr_ref>);
        EXPECT_FALSE(std::is_trivial_v<fstr::fstr31>);
        EXPECT_FALSE(std::is_trivial_v<fstr::fstr_ref>);
#ifndef _MSC_VER 
        EXPECT_FALSE(std::is_pod_v<fstr::fstr31>);
        EXPECT_FALSE(std::is_pod_v<fstr::fstr_ref>);
#endif
        EXPECT_FALSE(std::is_empty_v<fstr::fstr31>);
        EXPECT_FALSE(std::is_empty_v<fstr::fstr_ref>);
        EXPECT_FALSE(std::is_polymorphic_v<fstr::fstr31>);
        EXPECT_FALSE(std::is_polymorphic_v<fstr::fstr_ref>);
        EXPECT_FALSE(std::is_abstract_v<fstr::fstr31>);
        EXPECT_FALSE(std::is_abstract_v<fstr::fstr_ref>);
        EXPECT_FALSE(std::is_final_v<fstr::fstr31>);
        EXPECT_FALSE(std::is_final_v<fstr::fstr_ref>);
        EXPECT_FALSE(std::is_aggregate_v<fstr::fstr31>);
        EXPECT_FALSE(std::is_aggregate_v<fstr::fstr_ref>);
        EXPECT_FALSE(std::is_signed_v<fstr::fstr31>);
        EXPECT_FALSE(std::is_signed_v<fstr::fstr_ref>);
        EXPECT_FALSE(std::is_unsigned_v<fstr::fstr31>);
        EXPECT_FALSE(std::is_unsigned_v<fstr::fstr_ref>);

        EXPECT_FALSE((std::has_virtual_destructor_v<fstr::fstr31>));
        EXPECT_FALSE((std::has_virtual_destructor_v<fstr::fstr_ref>));
    }

    // future is_...
    {
        #if (__cplusplus >= 202002L)  // c++20
            EXPECT_FALSE(std::is_bounded_array_v<fstr::fstr31>);
            EXPECT_FALSE(std::is_bounded_array_v<fstr::fstr_ref>);
            EXPECT_FALSE(std::is_unbounded_array_v<fstr::fstr31>);
            EXPECT_FALSE(std::is_unbounded_array_v<fstr::fstr_ref>);
            EXPECT_TRUE((std::is_nothrow_convertible_v<fstr::fstr31, std::string_view>));
            EXPECT_TRUE((std::is_nothrow_convertible_v<fstr::fstr_ref, std::string_view>));
        #endif
        #if (__cplusplus == 202100L)  // c++23
            EXPECT_FALSE(std::is_scoped_enum_v<fstr::fstr31>);
            EXPECT_FALSE(std::is_scoped_enum_v<fstr::fstr_ref>);
        #endif
    }



    // is_class_v / is_compound_v / is_object_v / is_standard_layout_v / is_trivially_copyable_v
    {
        EXPECT_TRUE(std::is_class_v<fstr::fstr31>);
        EXPECT_TRUE(std::is_class_v<fstr::fstr_ref>);

        EXPECT_TRUE(std::is_compound_v<fstr::fstr31>);
        EXPECT_TRUE(std::is_compound_v<fstr::fstr_ref>);

        EXPECT_TRUE(std::is_object_v<fstr::fstr31>);
        EXPECT_TRUE(std::is_object_v<fstr::fstr_ref>);

        EXPECT_TRUE(std::is_standard_layout_v<fstr::fstr31>);
        EXPECT_FALSE(std::is_standard_layout_v<fstr::fstr_ref>);

        EXPECT_TRUE(std::is_trivially_copyable_v<fstr::fstr31>);
        EXPECT_FALSE(std::is_trivially_copyable_v<fstr::fstr_ref>);

        EXPECT_TRUE(std::has_unique_object_representations_v<fstr::fstr31>);
        EXPECT_FALSE(std::has_unique_object_representations_v<fstr::fstr_ref>);
    }


    // is_copy_constructible_v / is_trivially_copy_constructible_v / is_nothrow_copy_constructible_v
    {
        EXPECT_TRUE(std::is_copy_constructible_v<fstr::fstr31>);
        EXPECT_TRUE(std::is_copy_constructible_v<fstr::fstr_ref>);

        EXPECT_TRUE(std::is_trivially_copy_constructible_v<fstr::fstr31>);
        EXPECT_TRUE(std::is_trivially_copy_constructible_v<fstr::fstr_ref>);

        EXPECT_TRUE(std::is_nothrow_copy_constructible_v<fstr::fstr31>);
        EXPECT_TRUE(std::is_nothrow_copy_constructible_v<fstr::fstr_ref>);
    }

    // is_move_constructible_v / is_trivially_move_constructible_v / is_nothrow_move_constructible_v
    {
        EXPECT_TRUE(std::is_move_constructible_v<fstr::fstr31>);
        EXPECT_TRUE(std::is_move_constructible_v<fstr::fstr_ref>);

        EXPECT_TRUE(std::is_trivially_move_constructible_v<fstr::fstr31>);
        EXPECT_TRUE(std::is_trivially_move_constructible_v<fstr::fstr_ref>);

        EXPECT_TRUE(std::is_nothrow_move_constructible_v<fstr::fstr31>);
        EXPECT_TRUE(std::is_nothrow_move_constructible_v<fstr::fstr_ref>);
    }

    // is_copy_assignable_v / is_trivially_copy_assignable_v / is_nothrow_copy_assignable_v
    {
        EXPECT_TRUE(std::is_copy_assignable_v<fstr::fstr31>);
        EXPECT_TRUE(std::is_copy_assignable_v<fstr::fstr_ref>);

        EXPECT_TRUE(std::is_trivially_copy_assignable_v<fstr::fstr31>);
        EXPECT_FALSE(std::is_trivially_copy_assignable_v<fstr::fstr_ref>);

        EXPECT_TRUE(std::is_nothrow_copy_assignable_v<fstr::fstr31>);
        EXPECT_TRUE(std::is_nothrow_copy_assignable_v<fstr::fstr_ref>);
    }

    // is_move_assignable_v / is_trivially_move_assignable_v / is_nothrow_move_assignable_v
    {
        EXPECT_TRUE(std::is_move_assignable_v<fstr::fstr31>);
        EXPECT_TRUE(std::is_move_assignable_v<fstr::fstr_ref>);

        EXPECT_TRUE(std::is_trivially_move_assignable_v<fstr::fstr31>);
        EXPECT_FALSE(std::is_trivially_move_assignable_v<fstr::fstr_ref>);

        EXPECT_TRUE(std::is_nothrow_move_assignable_v<fstr::fstr31>);
        EXPECT_TRUE(std::is_nothrow_move_assignable_v<fstr::fstr_ref>);
    }

    // is_destructible_v / is_trivially_destructible_v / is_nothrow_destructible_v
    {
        EXPECT_TRUE(std::is_destructible_v<fstr::fstr31>);
        EXPECT_TRUE(std::is_destructible_v<fstr::fstr_ref>);

        EXPECT_TRUE(std::is_trivially_destructible_v<fstr::fstr31>);
        EXPECT_TRUE(std::is_trivially_destructible_v<fstr::fstr_ref>);

        EXPECT_TRUE(std::is_nothrow_destructible_v<fstr::fstr31>);
        EXPECT_TRUE(std::is_nothrow_destructible_v<fstr::fstr_ref>);
    }

    // is_assignable_v
    {
        EXPECT_TRUE((std::is_assignable_v<fstr::fstr31, char>));
        EXPECT_TRUE((std::is_assignable_v<fstr::fstr_ref, char>));

        EXPECT_TRUE((std::is_assignable_v<fstr::fstr31, char*>));
        EXPECT_TRUE((std::is_assignable_v<fstr::fstr_ref, char*>));

        EXPECT_TRUE((std::is_assignable_v<fstr::fstr31, fstr::fstr15>));
        EXPECT_TRUE((std::is_assignable_v<fstr::fstr_ref, fstr::fstr15>));

        EXPECT_TRUE((std::is_assignable_v<fstr::fstr31, fstr::fstr_ref>));
        EXPECT_TRUE((std::is_assignable_v<fstr::fstr_ref, fstr::fstr_ref>));

        EXPECT_TRUE((std::is_assignable_v<fstr::fstr31, std::string_view>));
        EXPECT_TRUE((std::is_assignable_v<fstr::fstr_ref, std::string_view>));

        EXPECT_TRUE((std::is_assignable_v<fstr::fstr31, std::string>));
        EXPECT_TRUE((std::is_assignable_v<fstr::fstr_ref, std::string>));
    }

    // is_swappable_v / is_nothrow_swappable_v
    {
        EXPECT_TRUE((std::is_swappable_v<fstr::fstr31>));
        EXPECT_TRUE((std::is_swappable_v<fstr::fstr_ref>));

        EXPECT_TRUE((std::is_nothrow_swappable_v<fstr::fstr31>));
        EXPECT_TRUE((std::is_nothrow_swappable_v<fstr::fstr_ref>));
    }

    // is_convertible_v
    {
        EXPECT_TRUE((std::is_convertible_v<fstr::fstr31, std::string_view>));
        EXPECT_TRUE((std::is_convertible_v<fstr::fstr_ref, std::string_view>));

        EXPECT_TRUE((std::is_convertible_v<fstr::fstr31, fstr::fstr_ref>));
        EXPECT_TRUE((std::is_convertible_v<fstr::fstr31, fstr::fstr_ref>));

        EXPECT_TRUE((std::is_convertible_v<fstr::fstr31, fstr::fstr31>));
        EXPECT_TRUE((std::is_convertible_v<fstr::fstr_ref, fstr::fstr31>));

        EXPECT_TRUE((std::is_convertible_v<fstr::fstr31, fstr::fstr15>));
    }


    // is_nothrow_assignable_v
    {
        EXPECT_TRUE((std::is_nothrow_assignable_v<fstr::fstr31, char>));
        EXPECT_TRUE((std::is_nothrow_assignable_v<fstr::fstr_ref, char>));

        EXPECT_TRUE((std::is_nothrow_assignable_v<fstr::fstr31, char*>));
        EXPECT_TRUE((std::is_nothrow_assignable_v<fstr::fstr_ref, char*>));

        EXPECT_TRUE((std::is_nothrow_assignable_v<fstr::fstr31, std::string_view>));
        EXPECT_TRUE((std::is_nothrow_assignable_v<fstr::fstr_ref, std::string_view>));

        EXPECT_TRUE((std::is_nothrow_assignable_v<fstr::fstr31, std::string>));
        EXPECT_TRUE((std::is_nothrow_assignable_v<fstr::fstr_ref, std::string>));

        EXPECT_TRUE((std::is_nothrow_assignable_v<fstr::fstr31, fstr::fstr31>));
        EXPECT_TRUE((std::is_nothrow_assignable_v<fstr::fstr31, fstr::fstr_ref>));

        EXPECT_TRUE((std::is_nothrow_assignable_v<fstr::fstr_ref, fstr::fstr_ref>));
        EXPECT_TRUE((std::is_nothrow_assignable_v<fstr::fstr_ref, fstr::fstr31>));
    }

    // is_constructible_v / is_default_constructible_v / is_nothrow_constructible_v / is_nothrow_default_constructible_v
    {
        EXPECT_TRUE(std::is_constructible_v<fstr::fstr31>);
        EXPECT_FALSE(std::is_constructible_v<fstr::fstr_ref>); //??

        EXPECT_TRUE(std::is_default_constructible_v<fstr::fstr31>);
        EXPECT_FALSE(std::is_default_constructible_v<fstr::fstr_ref>);

        EXPECT_TRUE(std::is_nothrow_constructible_v<fstr::fstr31>);
        EXPECT_FALSE(std::is_nothrow_constructible_v<fstr::fstr_ref>); //??

        EXPECT_TRUE(std::is_nothrow_default_constructible_v<fstr::fstr31>);
        EXPECT_FALSE(std::is_nothrow_default_constructible_v<fstr::fstr_ref>);
    }

    // is_trivially_constructible_v / is_trivially_default_constructible_v
    {
        EXPECT_FALSE(std::is_trivially_constructible_v<fstr::fstr31>);
        EXPECT_FALSE(std::is_trivially_constructible_v<fstr::fstr_ref>);

        EXPECT_FALSE(std::is_trivially_default_constructible_v<fstr::fstr31>);
        EXPECT_FALSE(std::is_trivially_default_constructible_v<fstr::fstr_ref>);
    }

}
