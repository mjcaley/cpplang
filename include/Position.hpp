#pragma once

namespace cpplang {
    template<typename Size>
    struct Position {
        Position() : m_line(0), m_column(0) {};

        Position(Size line, Size column) : m_line(line), m_column(column) {};

        [[nodiscard]] Size line() const {
            return m_line;
        }

        [[nodiscard]] Size column() const {
            return m_column;
        }

    private:
        Size m_line;
        Size m_column;
    };
}
