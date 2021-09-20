#include <vector>

class Algo {
    
private:
    std::vector<std::pair<int,int>> points;
    void genRoundPix(int x, int y);
    int xc, yc; //circle center

public:

    using ResultIter = std::vector<std::pair<int,int>>::iterator;

    Algo();
    ~Algo();

    void DDA(int x0, int y0, int x1, int y1);
    void Breshenham(int x0, int y0, int x1, int y1);
    void GetRound(int x0, int y0, int x1, int y1);

    void clear();

    ResultIter getResIter();

    ResultIter end();
};