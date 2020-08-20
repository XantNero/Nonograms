#include "Nanogram.h"
#include <fstream>
#include <string>
#include <cstring>


Nanogram::Nanogram(const std::string &file_name)
    : width(0), height(0), rows(0), columns(0), goal(0)
{
    const char* key_words[] = {
        "width", "height", "rows", "columns", "goal"
    };

    fin.open(file_name);
    if (!fin.is_open()) {
        //
        int num = 0;
    }
    while (!fin.eof()) {
        std::string str;
        fin >> str;
        for (int i = 0; i < sizeof(key_words)/ sizeof(const char*); ++i) {
            if (str.length() >= strlen(key_words[i]) && str.substr(0, strlen(key_words[i])) == key_words[i]) {
                parseData(key_words[i], str);
            }
        }
    }
    fin.close();
}

Nanogram::~Nanogram() {
    delete[] goal;
    for (int i = 0; i < height; ++i) {
        delete[] rows[i];
    }
    delete[] rows;
    delete[] rows_len;
    for (int i = 0; i < width; ++i) {
        delete[] columns[i];
    }
    delete[] columns;
    delete[] columns_len;

}


void Nanogram::parseData(const char *&type, const std::string &data) {
    if (strcmp(type, "width") == 0) {
        parseWidth(data);
    }
    else if (strcmp(type, "height") == 0) {
        parseHeight(data);
    }
    else if (strcmp(type, "rows") == 0) {
        parseRows(data);
    }
    else if (strcmp(type, "columns") == 0) {
        parseColumns(data);
    }
    else if (strcmp(type, "goal") == 0) {
        parseGoal(data);
    }
}

void Nanogram::parseWidth(const std::string &data) {
    fin >> width;
}

void Nanogram::parseHeight(const std::string &data) {
    fin >> height;
}

void Nanogram::parseRows(const std::string &data) {
    //catch error
    rows = new int*[height];
    rows_len = new int[height];
    for (int i = 0; i < height; ++i) {
        rows_len[i] = 0;
        rows[i] = new int[(width + 1) / 2];
    }

    for (int i = 0; i < height; ++i) {
        int num;
        char c;
        do {
            //sscanf(str, "%d%c", &num, &c);
            fin >> num;
            fin.get(c);
            rows[i][rows_len[i]] = num;
            ++rows_len[i];
        } while (c != '\n');
    }
    // relocate memory;
}

void Nanogram::parseColumns(const std::string &data) {
    //catch error
    columns = new int*[width];
    columns_len = new int[width];
    for (int i = 0; i < width; ++i) {
        columns_len[i] = 0;
        columns[i] = new int[(height + 1) / 2];
    }
    for (int i = 0; i < width; ++i) {
        int num;
        char c;

        do {
            fin >> num;
            fin.get(c);
            columns[i][columns_len[i]] = num;
            ++columns_len[i];
        } while (c != '\n');
    }
    // relocate memory;
}

void Nanogram::parseGoal(const std::string &data) {
    //catch error
    goal = new char[width * height + 1];
    char c;
    fin >> c;
    fin.getline(goal, width * height + 1, '"');
}

int Nanogram::getWidth() {
    return width;
}

int Nanogram::getHeight() {
    return height;
}

void Nanogram::getRowsLens(int *&rows_len) {
    for (int i = 0; i < height; ++i) {
        rows_len[i] = this->rows_len[i];
    }
}

void Nanogram::getRows(int **&rows) {
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < rows_len[i]; ++j) {
            rows[i][j] = this->rows[i][j];
        }
    }
}

void Nanogram::getColumnsLens(int* &columns_len) {
    for (int i = 0; i < width; ++i) {
        columns_len[i] = this->columns_len[i];
    }
}

void Nanogram::getColumns(int **&columns) {
    for (int i = 0; i < width; ++i) {
        for (int j = 0; j < columns_len[i]; ++j) {
            columns[i][j] = this->columns[i][j];
        }
    }
}

char* Nanogram::getGoal() {
    return goal;
}
