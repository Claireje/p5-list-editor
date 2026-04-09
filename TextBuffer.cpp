#include "TextBuffer.hpp"
#include <cassert>

TextBuffer::TextBuffer() : cursor(data.end()), row(1), column(0), index(0) {}

int TextBuffer::compute_column() const {
    int col = 0;

    Iterator it = cursor;
    while (it != data.begin()) {
        --it;
        if (*it == '\n') {
            break;
        }
        ++col;
    }
    return col;
}

bool TextBuffer::forward() {
    if (cursor == data.end()) {
        return false;
    }
    if (*cursor == '\n') {
        ++row;
        column = 0;
    } else {
        ++column;
    }
    ++cursor;
    ++index;
    return true;
}

bool TextBuffer::backward() {
    if (cursor == data.begin()) {
        return false;
    }
    --cursor;
    --index;
    if (*cursor == '\n') {
        --row;
        column = compute_column();
    } else {
        --column;
    }
    return true;
}

void TextBuffer::insert(char c) {
    data.insert(cursor, c);
    if (c == '\n') {
        //the inserted newline is now just before cursor
        //row/column describe where cursor is AFTER insertion
        //cursor hasn't moved in terms of the iterator but index shifts
        ++row;
        column = compute_column();
    } else {
        ++column;
    }
    ++index;
}

bool TextBuffer::remove() {
    if (cursor == data.end()) {
        return false;
    }
    cursor = data.erase(cursor);
    return true;
}

void TextBuffer::move_to_row_start() {
    //walk backward until beginning or a newline
    while (cursor != data.begin()) {
        Iterator prev = cursor;
        --prev;
        if (*prev == '\n') {
            break;
        }
        --cursor;
        --index;
    }
    column = 0;
}

void TextBuffer::move_to_row_end() {
    while (cursor != data.end() && *cursor != '\n') {
        ++cursor;
        ++index;
        ++column;
    }
}

void TextBuffer::move_to_column(int new_column) {
    move_to_row_start();
    for (int c = 0; c < new_column; ++c) {
        if (cursor == data.end() || *cursor == '\n') {
            break;
        }
        ++cursor;
        ++index;
        ++column;
    }
}

bool TextBuffer::up() {
    if (row == 1) {
        return false;
    }

    int target_col = column;
    move_to_row_start();
    backward();
    move_to_column(target_col);
    return true;
}

bool TextBuffer::down() {
    Iterator it = cursor;
    bool found_newline = false;
    while (it != data.end()) {
        if (*it == '\n') {
            found_newline = true;
            break;
        }
        ++it;
    }
    if (!found_newline) {
        return false;
    }

    int target_col = column;
    move_to_row_end();
    forward();
    move_to_column(target_col);
    return true;
}

bool TextBuffer::is_at_end() const {
    return cursor == data.end();
}

char TextBuffer::data_at_cursor() const {
    assert(cursor != data.end());
    return *cursor;
}

int TextBuffer::get_row() const {
    return row;
}

int TextBuffer::get_column() const {
    return column;
}

int TextBuffer::get_index() const {
    return index;
}

int TextBuffer::size() const {
    return static_cast<int>(data.size());
}

std::string TextBuffer::stringify() const {
    return std::string(data.begin(), data.end());
}