#pragma once
// Keep the records-database API stable while sharing UTF-8 text helpers
// with the standalone dictionary laboratory.
#include "lab_utf8.hpp"

namespace rdb {
using lab::text::lowerCodePoint;
using lab::text::lowerUtf8;
using lab::text::containsIgnoreCase;
using lab::text::utf8Length;
} // namespace rdb
