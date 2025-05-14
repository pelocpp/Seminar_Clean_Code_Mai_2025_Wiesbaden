// =====================================================================================
// Exercises_01_MoveSemantics.cpp
// =====================================================================================

#include    <iostream>
#include    <print>
#include    <vector>
#include    <print>

namespace Exercises_MoveSemantics {

    namespace Exercise_01 {

        class Person
        {
        private:
            std::string m_name;         // name of person
            std::vector<int> m_values;  // some arbitrary person values

        public:
            Person() {}
            Person(const std::string& name) : m_name{ name } {}

            ~Person() {
                std::println("~Person");
            }

            void addValue(int value) {
                m_values.push_back(value);
            }

            friend std::ostream& operator<< (std::ostream& os, const Person& cust) {
                os << "{ " << cust.m_name << ": ";
                for (auto val : cust.m_values) {
                    os << val << ' ';
                }
                os << "}";
                return os;
            }
        };

        /*
        * When passing an object to a function, or returning an object from a function,
        * it's possible to do a move (rather than a copy) if:
        *
        * = the object is an rvalue
        * = the object's class defines the special member move functions
        */

        static void testExercise_01() {

            // create a person with some initial values
            Person dagobert{ "Dagobert Duck" };
            for (int value : { 1, 2, 3, 4, 5, 6, 7, 8, 9 }) {
                dagobert.addValue(value);
            }

            // print person
            std::cout << "Person: " << dagobert << std::endl;

            // insert person into a collection
            std::vector<Person> persons;
            persons.push_back(std::move(dagobert));
            // persons.push_back(std::move(dagobert));

            // print person again
           // std::cout << "Person: " << dagobert << std::endl;
        }
    }

}

void test_exercises_move_semantics()
{
    using namespace Exercises_MoveSemantics;
    Exercise_01::testExercise_01();
}

// =====================================================================================
// End-of-File
// =====================================================================================
