#include "Algo.h"


#include <algorithm>
#include <cmath>

Algo::Algo() : points() {}

Algo::~Algo() {}

void Algo::genRoundPix(int x, int y) {
    points.emplace_back(xc+x,yc+y);
    points.emplace_back(xc+y,yc+x);
    points.emplace_back(xc-x,yc+y);
    points.emplace_back(xc+y,yc-x);
    points.emplace_back(xc+x,yc-y);
    points.emplace_back(xc-y,yc+x);
    points.emplace_back(xc-x,yc-y);
    points.emplace_back(xc-y,yc-x);
}

void Algo::DDA(int x0, int y0, int x1, int y1) {

}


void Algo::Breshenham(int x0, int y0, int x1, int y1) {
    points.clear();
    int dx = std::abs(x1-x0), sx = x0<x1 ? 1 : -1;
    int dy = std::abs(y1-y0), sy = y0<y1 ? 1 : -1; 
    int e = dx > dy ? dx : -dy, e2;
 
    while(x0!=x1 || y0!=y1) {
        points.emplace_back(x0,y0);
        e2 = e;
        if (e2 > -2*dx) { e -= 2*dy; x0 += sx; }
        if (e2 <  2*dy) { e += 2*dx; y0 += sy; }
    }
    points.emplace_back(x1,y1);
}

void Algo::GetRound(int x0, int y0, int x1, int y1) {
    points.clear();
    xc = x0;
    yc = y0;
    int x = 0,y;
    int dx = x1-x0, dy = y1-y0;
    float r = sqrt(dx*dx + dy*dy);
    float d = 1.25 - r;
    y = r;
    genRoundPix(x,y);
    

    while(x <= y) {
        if(d < 0){
            d += 2*x+3;
        } else {
            d += 2*(x-y)+5;
            y--;
        }
        x++;
        genRoundPix(x,y);
    }
}

void Algo::clear() {
    points.clear();
}

Algo::ResultIter Algo::getResIter() {
    return points.begin();
}

Algo::ResultIter Algo::end() {
    return points.end();
}