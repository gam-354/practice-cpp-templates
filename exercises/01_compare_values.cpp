#include <iostream>

template <typename T>
T my_clamp(const T & val, const T & max, const T & min) {
    if (val < min) {
        return min;
    }

    if (val > max) {
        return max;
    }

    return val;
}


int main () {
    
    // Test floats
    float val_float = 6.0;
    float max_float = 5.0;
    float min_float = -1.0;

    printf("Float: val = %f, max = %f, min = %f -> return: %f", 
        val_float, max_float, min_float,
        my_clamp(val_float, max_float, min_float));
}