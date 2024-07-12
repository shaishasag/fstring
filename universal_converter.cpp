#include <iostream>
#include <vector>
#include "universal_converter.h"

int main()
{
    std::vector<universal_converter> ucv;
    for (int i = 0; i < 11; ++i)
    {
        ucv.emplace_back();
    }
    
    ucv[0] = true;
    ucv[1] = false;
    ucv[2] = 12;
    ucv[3] = -13;
    ucv[4] = 12.12;
    ucv[5] = -90.12;
    ucv[6] = "la la la";
    ucv[7] = 'X';
    ucv[8] =  std::string_view("tsimuki");
    ucv[9] =  std::string("metuki");
    ucv[10] = fixed::fstring31("mamluki");

    universal_converter uc1; uc1 = "pam";
    
    for (auto& uc : ucv)
    {
        std::cout << std::string_view(uc) << std::endl;
    }
    
    return 0;
}
