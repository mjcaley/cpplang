#pragma once

namespace cpplang {
    struct Position {
        Position() : m_line(0), m_column(0) {};

        Position(std::size_t line, std::size_t column) : m_line(line), m_column(column) {};

        [[nodiscard]] std::size_t line() const {
            return m_line;
        }

        [[nodiscard]] std::size_t column() const {
            return m_column;
        }

    private:
        std::size_t m_line;
        std::size_t m_column;
    };
}
