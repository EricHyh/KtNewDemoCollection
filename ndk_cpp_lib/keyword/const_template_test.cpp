#include <stdio.h>
#include <string>
#include <iostream>
#include <memory>
#include <functional>
#include <vector>
#include <array>

using namespace std;

namespace const_template_test
{

    template <typename T, size_t N>
    class FixedSizeArray
    {
    private:
        array<T, N> data;

    public:
        FixedSizeArray(/* args */) = default;
        FixedSizeArray(initializer_list<T> init)
        {
            auto it = init.begin();
            for (size_t i = 0; i < N && it != init.end(); ++i, ++it)
            {
                data[i] = *it;
            }
        }
        ~FixedSizeArray() = default;

        T &operator[](size_t index)
        {
            return data[index];
        }

        const T &operator[](size_t index) const
        {
            return data[index];
        }

        constexpr size_t size() const
        {
            return N;
        }

        // 添加迭代器支持
        auto begin() { return data.begin(); }
        auto end() { return data.end(); }
    };

    void test1()
    {
        FixedSizeArray<int, 10> arr = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
        cout << "Array size: " << arr.size() << endl;

        for (auto &a : arr)
        {
            a = a + 10;
            cout << "&a=" << a << endl;
        }
    }

    template <int N>
    struct Factorial
    {
        static constexpr int value = N * Factorial<N - 1>::value;
    };

    template <>
    struct Factorial<0>
    {
        static constexpr int value = 1;
    };

    void test2()
    {
        cout << "6!=" << Factorial<6>::value << endl;
    }

    template <typename T, bool isIntegral>
    struct NumberTrait;

    template <typename T>
    struct NumberTrait<T, true>
    {
        static void print()
        {
            cout << "This is an integral type" << endl;
        }
    };

    template <typename T>
    struct NumberTrait<T, false>
    {
        static void print()
        {
            cout << "This is not an integral type" << endl;
        }
    };

    template <typename T>
    void printNumberInfo()
    {
        NumberTrait<T, is_integral<T>::value>::print();
    }

    void test3()
    {
        printNumberInfo<int>();
        printNumberInfo<double>();
    }

    // template <typename T, T... Chars>
    // struct StringLiteral
    // {
    //     static constexpr T value[sizeof...(Chars) + 1] = {Chars..., '\0'};
    //     static constexpr std::size_t size = sizeof...(Chars);
    // };

    // // ToUpper 作为独立的模板函数
    // template <typename T, T... Chars>
    // constexpr auto ToUpper(StringLiteral<T, Chars...>)
    // {
    //     constexpr std::size_t size = sizeof...(Chars);
    //     std::array<T, size + 1> result = {Chars..., '\0'};
    //     for (std::size_t i = 0; i < size; ++i)
    //     {
    //         if (result[i] >= 'a' && result[i] <= 'z')
    //         {
    //             result[i] = result[i] + ('A' - 'a');
    //         }
    //     }
    //     return result;
    // }

    // // 辅助函数，用于创建StringLiteral实例
    // template <typename T, T... Chars>
    // constexpr auto makeLiteral()
    // {
    //     return StringLiteral<T, Chars...>{};
    // }

    // // 用户定义字面量，用于方便地创建StringLiteral实例
    // template <typename T, T... Chars>
    // constexpr auto operator""_sl()
    // {
    //     return StringLiteral<T, Chars...>{};
    // }

    template <typename T, T... Chars>
    struct StringLiteral
    {
        static constexpr std::array<T, sizeof...(Chars) + 1> value = {Chars..., '\0'};
        static constexpr std::size_t size = sizeof...(Chars);
    };

    template <typename T, T... Chars>
    constexpr std::array<T, sizeof...(Chars) + 1> StringLiteral<T, Chars...>::value;

    // 辅助函数：转换单个字符为大写
    template <typename T>
    constexpr T to_upper(T c)
    {
        return (c >= 'a' && c <= 'z') ? static_cast<T>(c - ('a' - 'A')) : c;
    }

    // ToUpper 函数
    template <typename T, T... Chars, std::size_t... Is>
    constexpr auto ToUpperImpl(StringLiteral<T, Chars...>, std::index_sequence<Is...>)
    {
        return StringLiteral<T, to_upper(StringLiteral<T, Chars...>::value[Is])...>{};
    }

    template <typename T, T... Chars>
    constexpr auto ToUpper(StringLiteral<T, Chars...> s)
    {
        return ToUpperImpl(s, std::make_index_sequence<sizeof...(Chars)>{});
    }

    // 用户定义字面量
    template <typename T, T... Chars>
    constexpr auto operator""_sl()
    {
        return StringLiteral<T, Chars...>{};
    }

    void test()
    {
        auto hello = "hello"_sl;
        std::cout << "Original: " << hello.value.data() << std::endl;
        std::cout << "Size: " << hello.size << std::endl;

        // 使用 ToUpper
        constexpr auto hello_upper = ToUpper(hello);
        std::cout << "Uppercase: " << hello_upper.value.data() << std::endl;
    }

}