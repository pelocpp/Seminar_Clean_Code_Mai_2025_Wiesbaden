// =====================================================================================
// Algorithms.cpp // std::fill, std::for_each, std::generate and more ...
// =====================================================================================


#include "../LoggerUtility/ScopedTimer.h"

#include <execution>

#include    <iostream>
#include    <print>
#include    <vector>
#include    <list>

#include    <map>
#include    <algorithm>
#include    <array>

#include    <numeric>


namespace Algorithms {

    // =================================================================================
    // Global constants and types
    // =================================================================================

    static constexpr int ArraySize = 100'000'00;

    static constexpr int VectorSize = 100'000'000;      // release
    //static constexpr int Size = 10'000'000;     // debug

    // need array in global data space, stack isn't suited for large objects
    std::array<double, ArraySize> values;

    std::array<double, ArraySize> source;
    std::array<double, ArraySize> target;
}

namespace Algorithms {

    namespace Initialization_Vector_Constant_Value {

        // =============================================================================
        // Initialization of std::vector with a constant value
        // =============================================================================

        void print(int n) {

            std::cout << n << std::endl;
        }

        static auto test_seminar()
        {
            std::vector<int> numbers{ 1, 2, 3 };

            std::vector<int>::iterator iter;

            std::list<int> liste{ 1, 2, 3 };

            std::list<int>::iterator list_iter;

            std::vector<int>::iterator anfang = numbers.begin();
            std::vector<int>::iterator ende = numbers.end();

            // auto n = *anfang;
            // int n = *anfang;
            std::vector<int>::value_type n = *anfang;

            // A) Globale Funktion
            // B) Aufrufbares Objekt // Klasse, die den operator() überladt
            // C) Lambda

          //  int localVar;

            // const char* // std::string
           // auto lprint = [](int n) -> std::string  { std::cout << n << std::endl; return "ABC"; };

            std::for_each(
                numbers.begin(),
                numbers.end(),
                [](int n){ std::cout << n << std::endl; }
            );

        }

        static auto test_vector_constant_initialize_classic_for_loop()
        {
            std::println("std::vector: using a classic for-loop");

            std::vector<double> values;
            {
                ScopedTimer watch{};
                values.resize (VectorSize);
            }

            ScopedTimer watch{};
            for (size_t i{}; i != values.size(); ++i) {
                values[i] = 123.0;
            }
        }

        static auto test_vector_constant_initialize_iterator_based()
        {
            std::println("std::vector: using an iterator-based for-loop");

            std::vector<double> values;
            {
                ScopedTimer watch{};
                values.resize(VectorSize);
            }

            ScopedTimer watch{};
            for (auto it{ values.begin() }; it != values.end(); ++it) {
                *it = 123.0;
            }
        }

        static auto test_vector_constant_initialize_std_fill()
        {
            std::println("std::vector: using std::fill");

            std::vector<double> values;
            {
                ScopedTimer watch{};
                values.resize(VectorSize);
            }

            ScopedTimer watch{};
            std::fill(
                values.begin(),
                values.end(),
                123.0
            );
        }

        static auto test_vector_constant_initialize_std_fill_parallelized()
        {
            std::println("std::vector: using std::fill - using execution policy ");

            std::vector<double> values;
            {
                ScopedTimer watch{};
                values.resize(VectorSize);
            }

            ScopedTimer watch{};
            std::fill(
                std::execution::par,
                values.begin(),
                values.end(),
                123.0
            );
        }

        static auto test_vector_constant_initialize_std_for_each()
        {
            std::println("std::vector: using std::for_each");

            std::vector<double> values;
            {
                ScopedTimer watch{};
                values.resize(VectorSize);
            }

            ScopedTimer watch{};
            std::for_each(
                values.begin(),
                values.end(),
                [](double& elem) { elem = 123.0; }
            );
        }

        static auto test_vector_constant_initialize_range_based_for_loop()
        {
            std::println("std::vector: using range-based for loop");

            std::vector<double> values;
            {
                ScopedTimer watch{};
                values.resize(VectorSize);
            }

            ScopedTimer watch{};
            for (double& elem : values) {
                elem = 123.0;
            }
        }

        static auto test_vector_constant_initialize_std_generate()
        {
            std::println("std::vector: using std::generate");

            std::vector<double> values;
            {
                ScopedTimer watch{};
                values.resize(VectorSize);
            }

            ScopedTimer watch{};
            std::generate(
                values.begin(),
                values.end(),
                [] () { return 123.0; }
            );
        }

        static auto test_vector_constant_initialize_user_defined_ctor()
        {
            std::println("std::vector: using special std::vector c'tor");

            ScopedTimer watch{};
            std::vector<double> values(VectorSize, 123.0);
        }
    }


    static void test_vector_constant_initialization()
    {
        using namespace Initialization_Vector_Constant_Value;

        test_vector_constant_initialize_classic_for_loop();
        test_vector_constant_initialize_iterator_based();
        test_vector_constant_initialize_std_fill();
        test_vector_constant_initialize_std_fill_parallelized();
        test_vector_constant_initialize_std_for_each();
        test_vector_constant_initialize_range_based_for_loop();
        test_vector_constant_initialize_std_generate();
        test_vector_constant_initialize_user_defined_ctor();
    }
}

namespace Algorithms {

    namespace Initialization_Array_Constant_Value {

        // =============================================================================
        // Initialization of std::array with a constant value
        // =============================================================================

        static auto test_array_constant_initialize_classic_for_loop()
        {
            std::println("std::array: using a classic for-loop");

            ScopedTimer watch{};

            for (size_t i{}; i != values.size(); ++i) {
                values[i] = 123.0;
            }
        }

        static auto test_array_constant_initialize_iterator_based()
        {
            std::println("std::array: using an iterator-based for-loop");

            ScopedTimer watch{};

            for (auto it{ values.begin() }; it != values.end(); ++it) {
                *it = 123.0;
            }
        }

        static auto test_array_constant_initialize_std_fill()
        {
            std::println("std::array: using std::fill");

            ScopedTimer watch{};

            std::fill(
                values.begin(),
                values.end(),
                123.0
            );
        }

        static auto test_array_constant_initialize_std_fill_parallelized()
        {
            std::println("std::array: using std::fill - using execution policy ");

            ScopedTimer watch{};

            std::fill(
                std::execution::par,
                values.begin(),
                values.end(),
                123.0
            );
        }

        static auto test_array_constant_initialize_std_for_each()
        {
            std::println("std::array: using std::for_each");

            ScopedTimer watch{};

            std::for_each(
                values.begin(),
                values.end(),
                [](auto& elem) { elem = 123.0; }
            );
        }

        static auto test_array_constant_initialize_range_based_for_loop()
        {
            std::println("std::array: using range-based for loop");

            ScopedTimer watch{};

            for (auto& elem : values) {
                elem = 123.0;
            }
        }

        static auto test_array_constant_initialize_std_generate()
        {
            std::println("std::array: using std::generate");

            ScopedTimer watch{};

            std::generate(
                values.begin(),
                values.end(),
                []() { return 123.0; }
            );
        }

    }


    static void test_array_constant_initialization()
    {
        using namespace Initialization_Array_Constant_Value;

        test_array_constant_initialize_classic_for_loop();
        test_array_constant_initialize_iterator_based();
        test_array_constant_initialize_std_fill();
        test_array_constant_initialize_std_fill_parallelized();
        test_array_constant_initialize_std_for_each();
        test_array_constant_initialize_range_based_for_loop();
        test_array_constant_initialize_std_generate();
    }
}

namespace Algorithms {

    namespace Initialization_Vector_Varying_Value {

        // =================================================================================
        // Initialization of std::vector with a varying value
        // =================================================================================

        static auto test_vector_varying_initialize_classic_for_loop()
        {
            std::println("std::vector: using a classic for-loop");

            ScopedTimer watch{};

            std::vector<double> values(VectorSize);

            for (size_t i{}; i != values.size(); ++i) {
                values[i] = 2.0 * i;
            }
        }

        static auto test_vector_varying_initialize_iterator_based()
        {
            std::println("std::vector: using an iterator-based for-loop");

            ScopedTimer watch{};

            std::vector<double> values(VectorSize);

            size_t i{};
            for (auto it{ values.begin() }; it != values.end(); ++it) {
                *it = 2.0 * i++;
            }
        }

        static auto test_vector_varying_initialize_std_for_each()
        {
            std::println("std::vector: using std::for_each");

            ScopedTimer watch{};

            std::vector<double> values(VectorSize);

            std::for_each(
                values.begin(),
                values.end(),
                [i = 0.0](auto& elem) mutable { elem = 2.0 * i++; }
            );
        }

        static auto test_vector_varying_initialize_range_based_for_loop()
        {
            std::println("std::vector: using range-based for loop");

            ScopedTimer watch{};

            std::vector<double> values(VectorSize);

            for (int i{}; auto & elem : values) {
                elem = 2.0 * i++;
            }
        }

        static auto test_vector_varying_initialize_std_for_generate()
        {
            std::println("std::vector: using std::generate");

            ScopedTimer watch{};

            std::vector<double> values(VectorSize);

            std::generate(
                values.begin(),
                values.end(),
                [i = 0.0]() mutable { return 2.0 * i++; }
            );
        }
    }

    static void test_vector_varying_initialization()
    {
        using namespace Initialization_Vector_Varying_Value;

        test_vector_varying_initialize_classic_for_loop();
        test_vector_varying_initialize_iterator_based();
        test_vector_varying_initialize_std_for_each();
        test_vector_varying_initialize_range_based_for_loop();
        test_vector_varying_initialize_std_for_generate();
    }
}

namespace Algorithms {

    namespace Initialization_Array_Varying_Value {

        // =================================================================================
        // Initialization of std::array with a varying value
        // =================================================================================

        static auto test_array_varying_initialize_classic_for_loop()
        {
            std::println("std::array: using a classic for-loop");

            ScopedTimer watch{};

            for (size_t i{}; i != values.size(); ++i) {
                values[i] = 2.0 * i;
            }
        }

        static auto test_array_varying_initialize_iterator_based()
        {
            std::println("std::array: using an iterator-based for-loop");

            ScopedTimer watch{};

            size_t i{};
            for (auto it{ values.begin() }; it != values.end(); ++it) {
                *it = 2.0 * i++;
            }
        }

        static auto test_array_varying_initialize_std_for_each()
        {
            std::println("std::array: using std::for_each");

            ScopedTimer watch{};

            std::for_each(
                values.begin(),
                values.end(),
                [i = 0.0](auto& elem) mutable { elem = 2.0 * i++; }
            );
        }

        static auto test_array_varying_initialize_range_based_for_loop()
        {
            std::println("std::array: using range-based for loop");

            ScopedTimer watch{};

            for (int i{}; auto & elem : values) {
                elem = 2.0 * i++;
            }
        }

        static auto test_array_varying_initialize_std_for_generate()
        {
            std::println("std::array: using std::generate");

            ScopedTimer watch{};

            std::generate(
                values.begin(),
                values.end(),
                [i = 0.0]() mutable { return 2.0 * i++; }
            );
        }
    }

    static void test_array_varying_initialization()
    {
        using namespace Initialization_Array_Varying_Value;

        test_array_varying_initialize_classic_for_loop();
        test_array_varying_initialize_iterator_based();
        test_array_varying_initialize_std_for_each();
        test_array_varying_initialize_range_based_for_loop();
        test_array_varying_initialize_std_for_generate();
    }
}

namespace Algorithms {

    // =================================================================================
    // Using algorithms for copying ranges (std::vector)
    // =================================================================================

    namespace Copying_Vectors {

        static auto test_vector_copying_classic_for_loop()
        {
            std::println("std::vector: Copying: Using a classic for-loop");

            ScopedTimer watch{};

            std::vector<double> source(VectorSize, 123.0);
            std::vector<double> target(VectorSize);

            for (size_t i{}; i != source.size(); ++i) {
                target[i] = source[i];
            }
        }

        static auto test_vector_copying_iterator_based()
        {
            std::println("std::vector: Copying: Using an iterator-based for-loop");

            ScopedTimer watch{};

            std::vector<double> source(VectorSize, 123.0);
            std::vector<double> target(VectorSize);

            auto itSource{ source.begin() };
            auto itTarget{ target.begin() };

            for (auto it{ source.begin() }; it != source.end(); ++it) {
                *itTarget = *itSource;
            }
        }

        static auto test_vector_copying_std_copy()
        {
            std::println("std::vector: Standard Algorithm - std::copy:");

            ScopedTimer watch{};

            std::vector<double> source(VectorSize, 123.0);
            std::vector<double> target(VectorSize);

            std::copy(
                source.begin(),
                source.end(),
                target.begin()
            );
        }

        static auto test_vector_copying_std_copy_parallelized()
        {
            std::println("std::vector: Using std::copy - using execution policy");

            ScopedTimer watch{};

            std::vector<double> source(VectorSize, 123.0);
            std::vector<double> target(VectorSize);

            std::copy(
                std::execution::par,
                source.begin(),
                source.end(),
                target.begin()
            );
        }

        static auto test_vector_copying_std_memcpy()
        {
            std::println("std::vector: Using std::memcpy");

            ScopedTimer watch{};

            std::vector<double> source(VectorSize, 123.0);
            std::vector<double> target(VectorSize);

            // take care: works only with continuous memory
            std::memcpy(
                target.data(),
                source.data(),
                VectorSize * sizeof(double)
            );
        }
    }

    static void test_vector_copying()
    {
        using namespace Copying_Vectors;

        test_vector_copying_classic_for_loop();
        test_vector_copying_iterator_based();
        test_vector_copying_std_copy();
        test_vector_copying_std_copy_parallelized();
        test_vector_copying_std_memcpy();
    }
}

namespace Algorithms {

    // =================================================================================
    // Using algorithms for copying ranges (std::array)
    // =================================================================================

    namespace Copying_Arrays {

        static auto test_array_copying_classic_for_loop()
        {
            std::println("std::array: Copying: Using a classic for-loop");

            ScopedTimer watch{};

            for (size_t i{}; i != source.size(); ++i) {
                target[i] = source[i];
            }
        }

        static auto test_array_copying_iterator_based()
        {
            std::println("std::array: Copying: Using an iterator-based for-loop");

            ScopedTimer watch{};

            auto itSource{ source.begin() };
            auto itTarget{ target.begin() };

            for (auto it{ source.begin() }; it != source.end(); ++it) {
                *itTarget = *itSource;
            }
        }

        static auto test_array_copying_std_copy()
        {
            std::println("std::array: Standard Algorithm - std::copy:");

            ScopedTimer watch{};

            std::copy(
                source.begin(),
                source.end(),
                target.begin()
            );
        }

        static auto test_array_copying_std_copy_parallelized()
        {
            std::println("std::array: Using std::copy - using execution policy");

            ScopedTimer watch{};

            std::copy(
                std::execution::par,
                source.begin(),
                source.end(),
                target.begin()
            );
        }

        static auto test_array_copying_std_memcpy()
        {
            std::println("std::array: Using std::memcpy");

            ScopedTimer watch{};

            // take care: works only with continuous memory
            std::memcpy(
                target.data(),
                source.data(),
                VectorSize * sizeof(double)
            );
        }
    }

    static void test_array_copying()
    {
        using namespace Copying_Arrays;

        test_array_copying_classic_for_loop();
        test_array_copying_iterator_based();
        test_array_copying_std_copy();
        test_array_copying_std_copy_parallelized();
        test_array_copying_std_memcpy();
    }
}

namespace Algorithms {

    namespace Elementary_Calculations_With_Vectors {


        // =================================================================================
        // Using algorithms for elementary calculations with std::vector
        // =================================================================================

        static auto test_vector_calculate_sum_classic_for_loop(const std::vector<double>& values)
        {
            std::println("Classic Loop: ");

            ScopedTimer watch{};

            double sum{};
            for (size_t i{}; i != values.size(); ++i) {
                sum += values[i];
            }

            return sum;
        }

        static auto test_vector_calculate_sum_iterator_based(const std::vector<double>& values)
        {
            std::println("Iterator Loop: ");

            ScopedTimer watch{};

            double sum{};
            for (auto it{ values.cbegin() }; it != values.cend(); ++it) {
                sum += *it;
            }

            return sum;
        }

        static auto test_vector_calculate_sum_range_based_for_loop(const std::vector<double>& values)
        {
            std::println("Using range-based for loop");

            ScopedTimer watch{};

            double sum{};
            for (const auto& value : values) {
                sum += value;
            }

            return sum;
        }

        static auto test_vector_calculate_sum_std_for_each(const std::vector<double>& values)
        {
            std::println("Standard Algorithm - std::for_each:");

            ScopedTimer watch{};

            double sum{};
            std::for_each(
                values.cbegin(),
                values.cend(),
                [&sum](const auto& value) {sum += value; }
            );

            return sum;
        }

        static auto test_vector_calculate_sum_std_accumulate(const std::vector<double>& values)
        {
            std::println("Standard Algorithm - std::accumulate:");

            ScopedTimer watch{};

            double sum{
                std::accumulate(
                    values.cbegin(),
                    values.cend(),
                    0.0
                )
            };

            return sum;
        }
    }

    static void test_vector_sum_calculation()
    {
        using namespace Elementary_Calculations_With_Vectors;

        std::vector<double> values(VectorSize);

        auto initArray = [&] {
            std::generate(
                values.begin(),
                values.end(),
                [value = 0.0]() mutable { return ++value; }
            );
            };

        double sum{};

        initArray();
        sum = test_vector_calculate_sum_classic_for_loop(values);
        std::println("std::vector: Sum: {:15.20g}", sum);

        initArray();
        sum = test_vector_calculate_sum_iterator_based(values);
        std::println("std::vector: Sum: {:15.20g}", sum);

        initArray();
        sum = test_vector_calculate_sum_range_based_for_loop(values);
        std::println("std::vector: Sum: {:15.20g}", sum);

        initArray();
        sum = test_vector_calculate_sum_std_for_each(values);
        std::println("std::vector: Sum: {:15.20g}", sum);

        initArray();
        sum = test_vector_calculate_sum_std_accumulate(values);
        std::println("std::vector: Sum: {:15.20g}", sum);
    }
}

namespace Algorithms {

    namespace Elementary_Calculations_With_Arrays {


        // =================================================================================
        // Using algorithms for elementary calculations with std::array
        // =================================================================================

        static auto test_array_calculate_sum_classic_for_loop(const std::array<double, ArraySize>& values)
        {
            std::println("Classic Loop: ");

            ScopedTimer watch{};

            double sum{};
            for (size_t i{}; i != values.size(); ++i) {
                sum += values[i];
            }

            return sum;
        }

        static auto test_array_calculate_sum_iterator_based(const std::array<double, ArraySize>& values)
        {
            std::println("Iterator Loop: ");

            ScopedTimer watch{};

            double sum{};
            for (auto it{ values.cbegin() }; it != values.cend(); ++it) {
                sum += *it;
            }

            return sum;
        }

        static auto test_array_calculate_sum_range_based_for_loop(const std::array<double, ArraySize>& values)
        {
            std::println("Using range-based for loop");

            ScopedTimer watch{};

            double sum{};
            for (const auto& value : values) {
                sum += value;
            }

            return sum;
        }

        static auto test_array_calculate_sum_std_for_each(const std::array<double, ArraySize>& values)
        {
            std::println("Standard Algorithm - std::for_each:");

            ScopedTimer watch{};

            double sum{};
            std::for_each(
                values.cbegin(),
                values.cend(),
                [&sum](const auto& value) {sum += value; }
            );

            return sum;
        }

        static auto test_array_calculate_sum_std_accumulate(const std::array<double, ArraySize>& values)
        {
            std::println("Standard Algorithm - std::accumulate:");

            ScopedTimer watch{};

            double sum{
                std::accumulate(
                    values.cbegin(),
                    values.cend(),
                    0.0
                )
            };

            return sum;
        }
    }

    static void test_array_sum_calculation()
    {
        using namespace Elementary_Calculations_With_Arrays;

        auto initArray = [&] {
            std::generate(
                values.begin(),
                values.end(),
                [value = 0.0]() mutable { return ++value; }
            );
            };

        double sum{};

        initArray();
        sum = test_array_calculate_sum_classic_for_loop(values);
        std::println("std::array: Sum: {:15.20g}", sum);

        initArray();
        sum = test_array_calculate_sum_iterator_based(values);
        std::println("std::array: Sum: {:15.20g}", sum);

        initArray();
        sum = test_array_calculate_sum_range_based_for_loop(values);
        std::println("std::array: Sum: {:15.20g}", sum);

        initArray();
        sum = test_array_calculate_sum_std_for_each(values);
        std::println("std::array: Sum: {:15.20g}", sum);

        initArray();
        sum = test_array_calculate_sum_std_accumulate(values);
        std::println("std::array: Sum: {:15.20g}", sum);
    }
}

void main_algorithms()
{
    using namespace Algorithms;

   // Initialization_Vector_Constant_Value::test_seminar();

   // test_vector_constant_initialization();
    test_array_constant_initialization();

    //test_vector_varying_initialization();
    //test_array_varying_initialization();

    //test_vector_copying();
    //test_array_copying();

    //test_vector_sum_calculation();
    //test_array_sum_calculation();
}

// =====================================================================================
// End-of-File
// =====================================================================================
