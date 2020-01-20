#include <deque>
#include <iostream>
#include "realm.h"

extern int verbose_flag;

Realm::Realm()
{
    realm.reserve(AreaX * AreaY);
    std::fill(realm.begin(), realm.end(), RealmCell{false, 0});
    FillRealm(baseGrid, 3);
}

Realm::~Realm()
{
}

//Get CELL-ptr from realm
PCell Realm::Cell(int X, int Y)
{
    if ((X < 0) || (X < 0) || (X >= AreaX) || (Y >= AreaY))
        return nullptr;
    return &realm[Y*AreaX + X];
}

bool Realm::BestPlacement(MoveableObject *mo, int desireX, int desireY)
{
    PCell cell = Cell(desireX, desireY);
    if (cell)
    {
        mo->X = desireX;
        mo->Y = desireY;
        if (!cell->Wall)
            return true;
        if (CellFinder(mo->X, mo->Y, desireX, desireY))
        {
            mo->X = desireX;
            mo->Y = desireY;
            return true;
        }
    } 
    return false;
}

bool Realm::Test()
{
    std::deque<PCell> queTest;
    bool wallsPassed = true;
    queTest.push_back(Cell(baseGrid,baseGrid));
    queTest.push_back(Cell(2*baseGrid,2*baseGrid));
    queTest.push_back(Cell(3*baseGrid,3*baseGrid));
    queTest.push_back(Cell(AreaX - baseGrid,baseGrid));
    queTest.push_back(Cell(baseGrid,AreaY - baseGrid));
    queTest.push_back(Cell(AreaX - baseGrid, AreaY - baseGrid));
    while (!queTest.empty())
    {
        PCell cell = queTest.front();
        if (!cell)
        {
            if (verbose_flag)
                puts("Tinyt: Nullptr from get realm cell.");
            return false;
        }
        wallsPassed &= cell->Wall; 
        queTest.pop_front();
    }
    if (verbose_flag)
    {
        if (wallsPassed)
            puts("Tinyt: Realm walls test passed.");
        else
            puts("Tinyt: Realm walls test failed.");
    }
    return wallsPassed;
}

//-=P.R.I.V.A.T.E.=-

bool Realm::CellFinder(int X, int Y, int &desireX, int &desireY)
{
    struct coords {int X; int Y;};
    std::deque<coords> dTrys;
    dTrys.push_back({X = desireX, Y = desireY});
    dTrys.push_back({X = desireX + 1, Y = desireY});
    dTrys.push_back({X = desireX - 1, Y = desireY});
    dTrys.push_back({X = desireX, Y = desireY + 1});    
    dTrys.push_back({X = desireX, Y = desireY - 1});    
    dTrys.push_back({X = desireX + 1, Y = desireY - 1});
    dTrys.push_back({X = desireX - 1, Y = desireY + 1});
    while (!dTrys.empty())
    {
        coords co = dTrys.front();
        PCell next = Cell(co.X, co.Y);
        if (next)
        {
            if (!next->Wall)
            {
                desireX = co.X;
                desireY = co.Y;
                return true;
            }
        }
        dTrys.pop_front();
    }
    return false;
}

//Build walls in realm
bool Realm::FillRealm(int distBasic, int level, bool rotation, int dist)
{
    bool rv = true;
    if (distBasic + dist > std::min(AreaX, AreaY))
    {
        if (verbose_flag)
            puts("Tinyt: fill routine coords out of realm.");
        return false;
    }
    if (rotation)
    {
        for (int indy = distBasic + dist; indy <= AreaY - (distBasic + dist); indy++)
        {
            PCell cellL = Cell(distBasic + dist, indy);
            PCell cellR = Cell(AreaX - (distBasic + dist), indy);
            if (!cellL || !cellR)
            {
                if (verbose_flag)
                    printf("Tinyt: fill routine - nullptr cell in Y rotation level %d\n.", level);
                return false;
            }
            cellL->Wall = true;
            cellR->Wall = true;
        }
    } else
    {
        for (int indx = distBasic + dist; indx <= AreaX - (distBasic + dist); indx++)
        {
            PCell cellH = Cell(indx, distBasic + dist);
            PCell cellL = Cell(indx, AreaY - (distBasic + dist));
            if (!cellH || !cellL)
            {
                if (verbose_flag)
                    printf("Tinyt: fill routine - nullptr cell in X rotation level %d\n.", level);
                return false;
            }
            cellH->Wall = true;
            cellL->Wall = true;
        }
    }
    if (level > 1)
        rv = FillRealm(distBasic, level - 1, !rotation, dist + distBasic);
    return rv;
}

const int Realm::AreaX = 250;
const int Realm::AreaY = 250; 
int Realm::baseGrid { 30 };