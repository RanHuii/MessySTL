#pragma once

#include <stdexcept>

#include <cassert>

namespace MessySTL
{

#define MESSY_ASSERT(expr) \
    assert(expr)

#define THROW_LENGTH_ERROR_IF(expr, error_msg) \
    if(expt) throw std::length_error(error_msg)

#define THROW_OUT_OF_RANGE_IF(expr, error_msg) \
    if(expr) throw std::out_of_range(error_msg)

#define THROW_RUNTIME_ERROR_IF(expr, error_msg) \
    if(expr) throw std::runtime_error(error_msg)
}