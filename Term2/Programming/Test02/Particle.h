#ifndef PARTICLE_H
#define PARTICLE_H

#include <windows.h>
#include <vector>
using namespace std;
class Particle
{
    public:
        Particle(int x = 1, int y = 1, COLORREF color = RGB(0, 255, 0)): x(x), y(y), color(color)
        {}
        void Move(int newx, int newy)
        {
            trace.push_back(make_pair(x, y)); /// TODO: use queue and store only last K traces
            x = newx;
            y = newy;
        }
        int x;
        int y;
        vector< pair<int, int> >  trace; /// TODO: use queue
        COLORREF color;
};

#endif // PARTICLE_H
