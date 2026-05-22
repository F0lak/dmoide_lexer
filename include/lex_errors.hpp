#pragma once
#include <string_view>
#include <array>

class LEXError {
    public:
        enum class ErrorCode {
            LEXError_OK,
            Count // helper for building the string array
        };

        static std::string_view to_string(ErrorCode error);

    private:
    // Using std::array with std::string_view for a compile-time, zero-allocation table
        static constexpr std::array<std::string_view, static_cast<size_t>(ErrorCode::Count)> errorStrings = {
            "LEXError_OK: Success"
        };

};