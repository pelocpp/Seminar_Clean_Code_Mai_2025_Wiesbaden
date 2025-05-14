// ===============================================================================
// UniquePtr.cpp // std::unique_ptr
// ===============================================================================

#include    <iostream>
#include    <print>
#include    <vector>
#include    <memory>

namespace UniquePointerGeneral {

    static std::unique_ptr<int> loadUniquePointer()
    {
        std::unique_ptr<int> empty;

        std::unique_ptr<int> ptr{ std::make_unique<int>(100) };
        
       // return std::move(ptr);  // NEVER !!!
        return ptr;
    }

    static void storeUniquePointer(std::unique_ptr<int>& ptr)
    {
        std::println("*ptr:    {}", *ptr);
        (*ptr)++;
        std::println("*ptr:    {}", *ptr);

        // take ownership right now:
        // std::unique_ptr<int> ptr2{ std::move(ptr) };
    }

    static void storeUniquePointerSafe(const std::unique_ptr<int>& ptr)
    {
        std::println("*ptr:    {}", *ptr);
        (*ptr)++;
        std::println("*ptr:    {}", *ptr);

        // ownership CANNOT be taken right now - ptr is const:
        // std::unique_ptr<int> ptr2{ std::move(ptr) };
    }

    static void storeUniquePointerAlternate(int* ptr)
    {
        std::println("*ptr:    {}", *ptr);
        (*ptr)++;
        std::println("*ptr:    {}", *ptr);

        // A) taking ownership right now: MAKES NO SENSE
        // B) delete: Under no circumstances: 
        //    pointer is owned by accompanied Unique Ptr
    }

    static void test_01()
    {
        // create a unique_ptr to an int with value 123
        std::unique_ptr<int> ptr1{ new int{ 123 } };
        // or
        // std::unique_ptr<int> ptr1{ std::make_unique<int>(123) };
        // or
        // auto ptr1{ std::make_unique<int>(123) };

        // access value behind smart pointer
        int n{ *ptr1 };
        std::println("*ptr1:   {}", n);

        // access value using raw pointer
        int* ip{ ptr1.get() };
        (*ip)++;
        int m{ *ip };
        std::println("*ip:     {}", m);

        // access value - again - behind smart pointer
        m = *ptr1;
        std::println("*ptr1:   {}", m);

        // move construction:
        // second std::unique_ptr by moving 'ptr1' to 'ptr2',
        // 'ptr1' doesn't own the object anymore
        std::unique_ptr<int> ptr2{ std::move(ptr1) };
        // std::println("*ptr1:   {}", *ptr1);    // crashes 
        m = *ptr2;
        std::println("*ptr2:   {}", m);

        {
            // move assignment
            std::unique_ptr<int> ptr3{};
            ptr3 = std::move(ptr2);
            m = *ptr3;
            std::println("*ptr3:   {}", m);
        }

        // Note: pointer behind std::unique_ptr's has been released
    }

    static void test_02()
    {
        // retrieving a unique pointer from a function
        std::unique_ptr<int> ptr = loadUniquePointer();
        
        std::println("*ptr:    {}", *ptr);

        // provide a function with a unique pointer: who owns the pointer now?
        storeUniquePointer(ptr);

        // C++ Core Guidelines
        storeUniquePointerAlternate(ptr.get());

        // does this work?
        std::println("*ptr:    {}", *ptr);
    }

    static void test_03()
    {
        // creates a unique_ptr to an array of 20 ints
        std::unique_ptr<int[]> ptr{ std::make_unique<int[]>(20) };
    }
}

namespace UniquePointer_SourceSinkPattern
{
    static std::unique_ptr<int> createResource(int value)
    {
        std::unique_ptr<int> ptr{ std::make_unique<int>(value) };
        return ptr;
    }

    static void consumeResource(std::unique_ptr<int> ptr)  // call by-value (!)
    {
        std::println("*ptr:    {}", *ptr);
        // now *ptr is deleted 
    }

    static void test_04()
    {
        // creating a unique pointer with the help of a creator function
        std::unique_ptr<int> ptr{ createResource(123) };
        std::println("*ptr:    {}", *ptr);

        // Pass unique pointer to another function:
        // No need for explicit std::move, temporary is captured as R-Value reference
        // so the std::unique_ptr's move constructor is automatically invoked
        consumeResource(createResource(456));
    }
}

namespace UniquePointerWrappingResourceHandles {

    // stateless callable object to delete FILE files
    struct FILE_Deleter
    {
        void operator() (FILE* pFile) const
        {
            if (pFile != (FILE*)0) {
                fclose(pFile);
            }
        }
    };

    using FILE_UniquePtr = std::unique_ptr<FILE, FILE_Deleter>;

    static FILE_UniquePtr make_fopen(const char* fileName, const char* mode)
    {
        FILE* file{ nullptr };
        auto err{ fopen_s(&file, fileName, mode) };
        if (err != 0)
        {
            // print error info
            std::println("Cannot open file {}!", fileName);
            return nullptr;
        }

        return FILE_UniquePtr{ file };
    }

    static void test_05()
    {
        const char* fileName{ "..\\GeneralSnippets\\UniquePtr\\UniquePtr.cpp" };

        FILE_UniquePtr pInputFilePtr{ make_fopen(fileName, "r") };

        if (!pInputFilePtr) {
            std::println("Done.");
            return;
        }
        else {
            FILE* fp{ pInputFilePtr.get() };
            char buf[512];
            fgets(buf, sizeof(buf), fp);
            std::print("First Line: {}", buf);
        }
    }
}

void main_unique_ptr()
{
    using namespace UniquePointerGeneral;
    test_01();
    test_02();
    test_03();
}

// =================================================================================
// End-of-File
// =================================================================================