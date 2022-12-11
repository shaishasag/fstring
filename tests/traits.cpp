#include "gtest/gtest.h"
#include "fstring.h"
#include <type_traits>

TEST(TypeTraits, traits_to_fix)
{
    // these should be EXPECT_TRUE, but they are EXPECT_FALSE
    EXPECT_FALSE((std::is_swappable_with_v<fixed::fstring31, fixed::fstring31>));
    EXPECT_FALSE((std::is_nothrow_swappable_with_v<fixed::fstring31, fixed::fstring31>));

    EXPECT_FALSE((std::is_trivially_assignable_v<fixed::fstring31, char>));
    EXPECT_FALSE((std::is_trivially_assignable_v<fixed::fstring31, char*>));
    EXPECT_FALSE((std::is_trivially_assignable_v<fixed::fstring31, std::string_view>));
    EXPECT_FALSE((std::is_trivially_assignable_v<fixed::fstring31, std::string>));
    EXPECT_FALSE((std::is_trivially_assignable_v<fixed::fstring31, fixed::fstring_ref>));

    EXPECT_FALSE((std::is_nothrow_assignable_v<fixed::fstring31, char>));
    EXPECT_FALSE((std::is_nothrow_assignable_v<fixed::fstring31, char*>));
    EXPECT_FALSE((std::is_nothrow_assignable_v<fixed::fstring31, std::string_view>));
    EXPECT_FALSE((std::is_nothrow_assignable_v<fixed::fstring31, std::string>));
    EXPECT_FALSE((std::is_nothrow_assignable_v<fixed::fstring31, fixed::fstring_ref>));
}


TEST(TypeTraits, some_traits)
{
    EXPECT_FALSE(std::is_void_v<fixed::fstring31>);
    EXPECT_FALSE(std::is_null_pointer_v<fixed::fstring31>);
    EXPECT_FALSE(std::is_integral_v<fixed::fstring31>);
    EXPECT_FALSE(std::is_floating_point_v<fixed::fstring31>);
    EXPECT_FALSE(std::is_enum_v<fixed::fstring31>);
    EXPECT_FALSE(std::is_union_v<fixed::fstring31>);
    EXPECT_FALSE(std::is_pointer_v<fixed::fstring31>);
    EXPECT_FALSE(std::is_lvalue_reference_v<fixed::fstring31>);
    EXPECT_FALSE(std::is_rvalue_reference_v<fixed::fstring31>);
    EXPECT_FALSE(std::is_member_object_pointer_v<fixed::fstring31>);
    EXPECT_FALSE(std::is_member_function_pointer_v<fixed::fstring31>);

    EXPECT_FALSE(std::is_fundamental_v<fixed::fstring31>);
    EXPECT_FALSE(std::is_arithmetic_v<fixed::fstring31>);
    EXPECT_FALSE(std::is_scalar_v<fixed::fstring31>);
    EXPECT_FALSE(std::is_reference_v<fixed::fstring31>);
    EXPECT_FALSE(std::is_member_pointer_v<fixed::fstring31>);
    EXPECT_FALSE(std::is_const_v<fixed::fstring31>);
    EXPECT_FALSE(std::is_volatile_v<fixed::fstring31>);
    EXPECT_FALSE(std::is_trivial_v<fixed::fstring31>);
    EXPECT_FALSE(std::is_pod_v<fixed::fstring31>);
    EXPECT_FALSE(std::is_empty_v<fixed::fstring31>);
    EXPECT_FALSE(std::is_polymorphic_v<fixed::fstring31>);
    EXPECT_FALSE(std::is_abstract_v<fixed::fstring31>);
    EXPECT_FALSE(std::is_final_v<fixed::fstring31>);
    EXPECT_FALSE(std::is_aggregate_v<fixed::fstring31>);
    EXPECT_FALSE(std::is_signed_v<fixed::fstring31>);
    EXPECT_FALSE(std::is_unsigned_v<fixed::fstring31>);
    EXPECT_FALSE(std::is_trivially_constructible_v<fixed::fstring31>);
    EXPECT_FALSE(std::is_nothrow_constructible_v<fixed::fstring31>);
    EXPECT_FALSE(std::is_trivially_default_constructible_v<fixed::fstring31>);
    EXPECT_FALSE(std::is_nothrow_default_constructible_v<fixed::fstring31>);

    EXPECT_FALSE((std::has_virtual_destructor_v<fixed::fstring31>));

#if (__cplusplus == 202002L)  // c++20
    EXPECT_FALSE(std::is_bounded_array_v<fixed::fstring31>);
    EXPECT_FALSE(std::is_unbounded_array_v<fixed::fstring31>);
    EXPECT_TRUE((std::is_nothrow_convertible_v<fixed::fstring31, std::string_view>));
#endif
#if (__cplusplus == 202100L)  // c++23
    EXPECT_FALSE(std::is_scoped_enum_v<fixed::fstring31>);
#endif




    EXPECT_TRUE(std::is_class_v<fixed::fstring31>);
    EXPECT_TRUE(std::is_compound_v<fixed::fstring31>);
    EXPECT_TRUE(std::is_object_v<fixed::fstring31>);
    EXPECT_TRUE(std::is_standard_layout_v<fixed::fstring31>);
    EXPECT_TRUE(std::is_trivially_copyable_v<fixed::fstring31>);
    EXPECT_TRUE(std::has_unique_object_representations_v<fixed::fstring31>);
    EXPECT_TRUE(std::is_constructible_v<fixed::fstring31>);
    EXPECT_TRUE(std::is_default_constructible_v<fixed::fstring31>);
    EXPECT_TRUE(std::is_copy_constructible_v<fixed::fstring31>);
    EXPECT_TRUE(std::is_trivially_copy_constructible_v<fixed::fstring31>);
    EXPECT_TRUE(std::is_nothrow_copy_constructible_v<fixed::fstring31>);
    EXPECT_TRUE(std::is_move_constructible_v<fixed::fstring31>);
    EXPECT_TRUE(std::is_trivially_move_constructible_v<fixed::fstring31>);
    EXPECT_TRUE(std::is_nothrow_move_constructible_v<fixed::fstring31>);
    EXPECT_TRUE(std::is_copy_assignable_v<fixed::fstring31>);
    EXPECT_TRUE(std::is_trivially_copy_assignable_v<fixed::fstring31>);
    EXPECT_TRUE(std::is_nothrow_copy_assignable_v<fixed::fstring31>);
    EXPECT_TRUE(std::is_move_assignable_v<fixed::fstring31>);
    EXPECT_TRUE(std::is_trivially_move_assignable_v<fixed::fstring31>);
    EXPECT_TRUE(std::is_nothrow_move_assignable_v<fixed::fstring31>);
    EXPECT_TRUE(std::is_destructible_v<fixed::fstring31>);
    EXPECT_TRUE(std::is_trivially_destructible_v<fixed::fstring31>);
    EXPECT_TRUE(std::is_nothrow_destructible_v<fixed::fstring31>);

    EXPECT_TRUE((std::is_assignable_v<fixed::fstring31, char>));
    EXPECT_TRUE((std::is_assignable_v<fixed::fstring31, char*>));
    EXPECT_TRUE((std::is_assignable_v<fixed::fstring31, std::string_view>));
    EXPECT_TRUE((std::is_assignable_v<fixed::fstring31, std::string>));
    EXPECT_TRUE((std::is_assignable_v<fixed::fstring31, fixed::fstring_ref>));

    EXPECT_TRUE((std::is_swappable_v<fixed::fstring31>));
    EXPECT_TRUE((std::is_nothrow_swappable_v<fixed::fstring31>));

    EXPECT_TRUE((std::is_convertible_v<fixed::fstring31, std::string_view>));
    EXPECT_TRUE((std::is_convertible_v<fixed::fstring31, std::string>));
    EXPECT_TRUE((std::is_convertible_v<fixed::fstring31, fixed::fstring_ref>));
    EXPECT_TRUE((std::is_convertible_v<fixed::fstring31, fixed::fstring31>));
    EXPECT_TRUE((std::is_convertible_v<fixed::fstring31, fixed::fstring15>));


}
