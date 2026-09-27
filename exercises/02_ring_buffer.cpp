#include <iostream>
#include <cassert>
#include <string>

/**
 * StaticRingBuffer: a FIFO circular buffer.
 */
template <typename T, int N>
class StaticRingBuffer
{
public:
    StaticRingBuffer() {}

    // Add a new element to the end of the buffer. Allows overwriting if full.
    void push(const T& item) {
        assert(!is_full());

        data[write_index] = item;
        num_elements++;

        // Update the write pointer. Increase by 1, but don't exceed N
        write_index = (write_index + 1) % N;
    }

    // Retrieve the oldest element in the buffer
    void pop(T& item) {
        assert(!is_empty());

        item = data[read_index];
        num_elements--;

        // Update the write pointer. Increase by 1, but don't exceed N
        read_index = (read_index + 1) % N;
    }

    bool is_full() const {
        return num_elements == N;
    }

    bool is_empty() const {
        return num_elements == 0;
    }

protected:
    T data[N]{};
    int num_elements = 0;
    int write_index = 0;        // Where the next element is going to be written
    int read_index = 0;         // Where the next element is going to be read from
};

template <typename T, int N>
class StaticRingBufferTestable : public StaticRingBuffer<T, N>
{
public:
    int size() const {
        return this->num_elements;
    }

    int read_position() const {
        return this->read_index;
    }

    int write_position() const {
        return this->write_index;
    }

    T get_at(int index) const {
        return this->data[index];
    }
};

template <typename T, int N>
void print_status(const StaticRingBufferTestable<T, N>& buffer, const std::string& label)
{
    std::cout << label << "\n"
              << "  size: " << buffer.size() << "\n"
              << "  empty: " << (buffer.is_empty() ? "yes" : "no") << "\n"
              << "  full: " << (buffer.is_full() ? "yes" : "no") << "\n"
              << "  read_index: " << buffer.read_position() << "\n"
              << "  write_index: " << buffer.write_position() << "\n";

    for (int i = 0; i < N; ++i)
    {
        std::cout << "  data[" << i << "] = " << buffer.get_at(i) << "\n";
    }
}

int main () {
    StaticRingBufferTestable<int, 4> int_buffer{};
    StaticRingBufferTestable<double, 3> double_buffer{};

    int_buffer.push(10);
    int_buffer.push(20);
    int_buffer.push(30);
    print_status(int_buffer, "After pushing 10, 20, 30:");
    assert(int_buffer.size() == 3);
    assert(!int_buffer.is_empty());
    assert(!int_buffer.is_full());
    assert(int_buffer.read_position() == 0);
    assert(int_buffer.write_position() == 3);

    int popped = 0;
    int_buffer.pop(popped);
    assert(popped == 10);
    int_buffer.push(40);
    print_status(int_buffer, "After pop and push 40:");
    assert(int_buffer.size() == 3);
    assert(int_buffer.read_position() == 1);
    assert(int_buffer.write_position() == 0);
    assert(int_buffer.get_at(0) == 10);
    assert(int_buffer.get_at(1) == 20);
    assert(int_buffer.get_at(2) == 30);
    assert(int_buffer.get_at(3) == 40);

    double_buffer.push(1.5);
    double_buffer.push(2.5);
    print_status(double_buffer, "Double buffer after two pushes:");
    assert(double_buffer.size() == 2);
    assert(!double_buffer.is_full());

    double removed = 0.0;
    double_buffer.pop(removed);
    assert(removed == 1.5);
    double_buffer.push(3.5);
    print_status(double_buffer, "Double buffer final state:");
    assert(double_buffer.size() == 2);
    assert(double_buffer.read_position() == 1);
    assert(double_buffer.write_position() == 0);
    assert(double_buffer.get_at(0) == 1.5);
    assert(double_buffer.get_at(1) == 2.5);
    assert(double_buffer.get_at(2) == 3.5);

    StaticRingBufferTestable<int, 3> wrap_buffer{};
    wrap_buffer.push(10);
    wrap_buffer.push(20);
    wrap_buffer.push(30);
    assert(wrap_buffer.is_full());
    print_status(wrap_buffer, "Wrap-around test before pop:");

    int wrap_value = 0;
    wrap_buffer.pop(wrap_value);
    assert(wrap_value == 10);
    assert(wrap_buffer.read_position() == 1);
    assert(!wrap_buffer.is_full());

    wrap_buffer.push(40);
    assert(wrap_buffer.write_position() == 1);
    print_status(wrap_buffer, "Wrap-around test after first push:");
    assert(wrap_buffer.get_at(0) == 40);
    assert(wrap_buffer.get_at(1) == 20);
    assert(wrap_buffer.get_at(2) == 30);

    wrap_buffer.pop(wrap_value);
    assert(wrap_value == 20);
    wrap_buffer.push(50);
    assert(wrap_buffer.write_position() == 2);
    assert(wrap_buffer.is_full());
    print_status(wrap_buffer, "Wrap-around test after second push:");
    assert(wrap_buffer.get_at(0) == 40);
    assert(wrap_buffer.get_at(1) == 50);
    assert(wrap_buffer.get_at(2) == 30);

    wrap_buffer.pop(wrap_value);
    assert(wrap_value == 30);
    wrap_buffer.pop(wrap_value);
    assert(wrap_value == 40);
    wrap_buffer.push(60);
    assert(wrap_buffer.write_position() == 0);
    assert(!wrap_buffer.is_full());
    print_status(wrap_buffer, "Wrap-around test final state:");
    assert(wrap_buffer.size() == 2);
    assert(wrap_buffer.get_at(0) == 40);
    assert(wrap_buffer.get_at(1) == 50);
    assert(wrap_buffer.get_at(2) == 60);

    std::cout << "All buffer integrity checks passed.\n";
    std::cout << "SUCCESS!\n"; 
    return 0;
}