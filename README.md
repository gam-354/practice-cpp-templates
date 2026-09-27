# practice-cpp-templates
Short collection of exercices focusing on design and implementation of templates

## 1. Function Template: Clamp Algorithm
*   **Objective:** Create a generic function to constrain a value within a specific range.
*   **Requirements:**
    *   Implement a template function named `my_clamp(const T& val, const T& low, const T& high)`.
    *   It should return `low` if the value is less than the minimum, `high` if it is greater, and `val` otherwise.
    *   Ensure it works with primitive types (`int`, `double`) and any user-defined class that supports the `<` operator.

## 2. Class Template with Non-Type Parameter: Static Ring Buffer
*   **Objective:** Design a fixed-size data structure without dynamic memory allocation (ideal for embedded or high-performance environments).
*   **Requirements:**
    *   Create a template class `StaticRingBuffer` where `T` is the element type and `N` is an integer non-type parameter defining the maximum capacity.
    *   Implement the methods `push(const T& item)`, `pop(T& item)`, `bool is_full() const`, and `bool is_empty() const`.
    *   Use an internal array of size `N` (`T data[N]`) and manage the read and write indices circularly.

## 3. Template Specialization: Data Serializer
*   **Objective:** Practice total or partial specialization to alter the behavior of a template based on the data type.
*   **Requirements:**
    *   Create a primary template class `Serializer` containing a static method `std::string serialize(const T& value)` (you can use `std::to_string` for basic numeric types).
    *   Create an **explicit specialization** for the `std::string` (or `const char*`) type that returns the text formatted inside quotes.
    *   Test instantiating the serializer with an integer and a string in the `main` function.