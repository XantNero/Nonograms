#ifndef NANOGRAM_H
#define NANOGRAM_H
#include <string>
#include <fstream>
class Nanogram {
    int width;
    int height;
    int **rows;
    int *rows_len;
    int **columns;
    int *columns_len;
    char *goal;
    std::ifstream fin;
public:
    Nanogram(const std::string &);
    ~Nanogram();
    int getWidth();
    int getHeight();
    void getRowsLens(int* &rows_len);
    void getRows(int** &rows);
    void getColumnsLens(int* &columns_len);
    void getColumns(int** &columns);
    char* getGoal();
private:
    void parseData(const char* &, const std::string &data);
    void parseWidth(const std::string &data);
    void parseHeight(const std::string &data);
    void parseRows(const std::string &data);
    void parseColumns(const std::string &data);
    void parseGoal(const std::string &data);
};

#endif // NANOGRAM_H
