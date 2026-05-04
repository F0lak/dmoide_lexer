#pragma once

struct CursorCoordinate {
    CursorCoordinate(size_t l, size_t c);
    uint32_t line;
    uint32_t column;
};