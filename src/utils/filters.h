#pragma once
#include <stddef.h>
#include <math.h>

// Ковзне середнє за останні N значень. NAN ігнорується.
template <size_t N>
class MovingAverage {
public:
    float add(float v) {
        if (isnan(v)) return get();
        buf_[idx_] = v;
        idx_ = (idx_ + 1) % N;
        if (count_ < N) count_++;
        return get();
    }
    float get() const {
        if (count_ == 0) return NAN;
        float sum = 0;
        for (size_t i = 0; i < count_; i++) sum += buf_[i];
        return sum / count_;
    }
private:
    float buf_[N] = {};
    size_t idx_ = 0;
    size_t count_ = 0;
};
