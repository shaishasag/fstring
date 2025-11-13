#include <iostream>
#include <chrono>
#include <random>
#include <cstdint>
#include <string_view>

#include "fstringstream.h"

using namespace std::chrono_literals;

class Measure
{
public:
    Measure(std::string_view in_title) : title(in_title) {}
    ~Measure()
    {
        after = std::chrono::steady_clock::now();
        std::chrono::duration<double, std::milli> duration_milli{after - before};
        std::cout << title << ": " << duration_milli.count() << "ms" <<std::endl;
    }
    std::string_view title;
    std::chrono::time_point<std::chrono::steady_clock>  before = std::chrono::steady_clock::now();
    std::chrono::time_point<std::chrono::steady_clock>  after = std::chrono::steady_clock::now();
};
static std::random_device rd;
static std::mt19937 gen(rd());

auto rand_real (auto min, auto max)
{
    using T = decltype(min);
    std::uniform_real_distribution<T> dist(min, max);
    return dist(gen);
};

auto rand_int(auto min, auto max)
{
    using T = decltype(min);
    std::uniform_int_distribution<T> dist(min, max);
    return dist(gen);
};


struct Numbers
{
    double d;
    float f;
    int32_t i32;
    int64_t i64;
    uint32_t ui32;
    uint64_t ui64;
    
    void randomize()
    {
        d = rand_real(-1.0, 1.0);
        f = rand_real(-1.0f, 1.0f);
        i32 = rand_int<int32_t>(-10'000, 10'000);
        i64 = rand_int<int64_t>(-1'000'000, 1'000'000);
        ui32 = rand_int<uint32_t>(0, 1'000'000);
        ui64 = rand_int<uint64_t>(0, 1'000'000ULL);
    }

    void printf(fstr::fstr_ref ofs) const
    {
        ofs.printf(d);
        ofs += ',';
        ofs.printf(f);
        ofs += ',';
        ofs.printf(i32);
        ofs += ',';
        ofs.printf(i64);
        ofs += ',';
        ofs.printf(ui32);
        ofs += ',';
        ofs.printf(ui64);
        ofs += ';';
    }
    void to_chars(fstr::fstr_ref ofs) const
    {
        ofs.to_chars(d);
        ofs += ',';
        ofs.to_chars(f);
        ofs += ',';
        ofs.to_chars(i32);
        ofs += ',';
        ofs.to_chars(i64);
        ofs += ',';
        ofs.to_chars(ui32);
        ofs += ',';
        ofs.to_chars(ui64);
        ofs += ';';
    }
    void to_chars_with_format(fstr::fstr_ref ofs,
                              std::chars_format in_format) const
    {
        ofs.to_chars(d, in_format);
        ofs += ',';
        ofs.to_chars(f, in_format);
        ofs += ',';
        ofs.to_chars(i32);
        ofs += ',';
        ofs.to_chars(i64);
        ofs += ',';
        ofs.to_chars(ui32);
        ofs += ',';
        ofs.to_chars(ui64);
        ofs += ';';
    }
    void to_chars_with_precision(fstr::fstr_ref ofs,
                                 std::chars_format in_format,
                                 int in_precision) const
    {
        ofs.to_chars(d, in_format, in_precision);
        ofs += ',';
        ofs.to_chars(f, in_format, in_precision);
        ofs += ',';
        ofs.to_chars(i32);
        ofs += ',';
        ofs.to_chars(i64);
        ofs += ',';
        ofs.to_chars(ui32);
        ofs += ',';
        ofs.to_chars(ui64);
        ofs += ';';
    }
    void format_one_by_one(fstr::fstr_ref ofs) const
    {
        ofs.format("{}", d);
        ofs += ',';
        ofs.format("{}", f);
        ofs += ',';
        ofs.format("{}", i32);
        ofs += ',';
        ofs.format("{}", i64);
        ofs += ',';
        ofs.format("{}", ui32);
        ofs += ',';
        ofs.format("{}", ui64);
        ofs += ';';
    }
    void format_at_once(fstr::fstr_ref ofs) const
    {
        ofs.format("{},{},{},{},{},{};", d, f, i32, i64, ui32, ui64);
    }
    void format_at_once_precision(fstr::fstr_ref ofs) const
    {
        ofs.format("{:.2},{:.2},{},{},{},{};", d, f, i32, i64, ui32, ui64);
    }
};


void randomize(std::vector<Numbers>& v)
{
    for (auto& a_nums : v)
    {
        a_nums.randomize();
    }
}


void printf(const std::vector<Numbers>& vNums,
            fstr::fstr_ref fs)
{
    for (const auto& n : vNums)
    {
        fs.clear();
        n.printf(fs);
        //std::cout << fs.sv() << "\n\n";
    }
}
void to_chars(const std::vector<Numbers>& vNums,
              fstr::fstr_ref fs)
{
    for (const auto& n : vNums)
    {
        fs.clear();
        n.to_chars(fs);
        //std::cout << fs.sv() << "\n\n";
    }
}
void to_chars_with_format(const std::vector<Numbers>& vNums,
                          fstr::fstr_ref fs,
                          std::chars_format in_format)
{
    for (const auto& n : vNums)
    {
        fs.clear();
        n.to_chars_with_format(fs, in_format);
        //std::cout << fs.sv() << "\n\n";
    }
}
void to_chars_with_precision(const std::vector<Numbers>& vNums,
                          fstr::fstr_ref fs,
                          std::chars_format in_format,
                          int in_precision)
{
    for (const auto& n : vNums)
    {
        fs.clear();
        n.to_chars_with_precision(fs, in_format, in_precision);
        //std::cout << fs.sv() << "\n\n";
    }
}
void format_one_by_one(const std::vector<Numbers>& vNums,
                       fstr::fstr_ref fs)
{
    for (const auto& n : vNums)
    {
        fs.clear();
        n.format_one_by_one(fs);
        //std::cout << fs.sv() << "\n\n";
    }
}
void format_at_once(const std::vector<Numbers>& vNums,
                    fstr::fstr_ref fs)
{
    for (const auto& n : vNums)
    {
        fs.clear();
        n.format_at_once(fs);
        //std::cout << fs.sv() << "\n\n";
    }
}
void format_at_once_precision(const std::vector<Numbers>& vNums,
                              fstr::fstr_ref fs)
{
    for (const auto& n : vNums)
    {
        fs.clear();
        n.format_at_once_precision(fs);
        //std::cout << fs.sv() << "\n\n";
    }
}


void construct(const std::vector<Numbers>& vNums,
               fstr::fstr_ref fs)
{
    for (const auto& n : vNums)
    {
        fs = fstr::fstr255(
                        n.d,
                        ',',
                        n.f,
                        ',',
                        n.i32,
                        ',',
                        n.i64,
                        ',',
                        n.ui32,
                        ',',
                        n.ui64,
                         ';');
        //std::cout << fs.sv() << "\n\n";
    }
}

void benchmark_num_to_str_options()
{
    constexpr size_t how_many{1'000'000};
    std::vector<Numbers> vNums(how_many, Numbers{});
    randomize(vNums);
    
    std::cout << vNums.size() << " numbers" << std::endl;
    
    fstr::fstr255 fs;
    
    {
        Measure meas("printf");
        printf(vNums, fs);
    }
    std::cout << "          " << fs << std::endl << std::flush;
    

    {
        Measure meas("to_chars default");
        to_chars(vNums, fs);
    }
    std::cout << "          " << fs << std::endl << std::flush;
    
    {
        Measure meas("to_chars fixed");
        to_chars_with_format(vNums, fs, std::chars_format::fixed);
    }
    std::cout << "          " << fs << std::endl << std::flush;
    
    {
        Measure meas("to_chars scientific");
        to_chars_with_format(vNums, fs, std::chars_format::scientific);
    }
    std::cout << "          " << fs << std::endl << std::flush;
    
    {
        Measure meas("to_chars fixed precision 2");
        to_chars_with_precision(vNums, fs, std::chars_format::fixed, 2);
    }
    std::cout << "          " << fs << std::endl << std::flush;
    
    {
        Measure meas("to_chars scientific precision 2");
        to_chars_with_precision(vNums, fs, std::chars_format::scientific, 2);
    }
    std::cout << "          " << fs << std::endl << std::flush;

    {
        Measure meas("format_one_by_one");
        format_one_by_one(vNums, fs);
    }
    std::cout << "          " << fs << std::endl << std::flush;

    {
        Measure meas("format_at_once");
        format_at_once(vNums, fs);
    }
    std::cout << "          " << fs << std::endl << std::flush;

    {
        Measure meas("format_at_once precision 2");
        format_at_once_precision(vNums, fs);
    }
    std::cout << "          " << fs << std::endl << std::flush;

    {
        Measure meas("construct");
        construct(vNums, fs);
    }
    std::cout << "          " << fs << std::endl << std::flush;

}

int main(int argc, const char * argv[])
{
    benchmark_num_to_str_options();
    
    return 0;
}
