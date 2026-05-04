#pragma once
#include <string_view>
#include <array>
#include <algorithm>

namespace DMKeywords {
    inline constexpr std::array<std::string_view, 39> list = {
        // Control Flow
        "break",
        "continue",
        "return",
        "goto",
        "if",
        "else",
        "switch",
        "case",
        "default",
        "for",
        "while",
        "do",
        "to",
        "in",
        "as",

        // Variable & Data Management
        "var",
        "global",
        "static",
        "tmp",
        "const",
        "arg",
        "new",
        "del",

        // Functionality & Execution
        "proc",
        "verb",
        "spawn",
        "sleep",

        // Error Handling & Safety
        "try",
        "catch",
        "throw",
        "final",

        // Directives & Settings
        "set"
    };

bool is_keyword(std::string_view word) {
    auto it = std::find(list.begin(), list.end(), word);
    return it != list.end();
}
}