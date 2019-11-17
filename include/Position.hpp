#pragma once

namespace cpplang {
    template<typename Index>
    struct Position {
        Position() : m_line(0), m_column(0) {};

        Position(Index line, Index column) : m_line(line), m_column(column) {};

        [[nodiscard]] Index line() const {
            return m_line;
        }

        [[nodiscard]] Index column() const {
            return m_column;
        }

    private:
        Index m_line;
        Index m_column;
    };
}
