#pragma once
#include <atomic>
#include <list>
#include <map>
#include <memory>
#include <mutex>
#include <vector>

//Realm module
//Module is provide grid [X * Y] with walls inside.

struct RealmCell
{
    bool Wall;
    int reserved;
};
typedef RealmCell *PCell;

struct MoveableObject
{
    int Id;
    int X, Y;
};

class Realm 
{
public:
    explicit Realm();
    Realm(const Realm&) = delete;
    Realm& operator=(const Realm&) = delete;
    Realm(Realm&&) = default;
    Realm& operator=(Realm&&) = default;

    virtual ~Realm() = default;
    
    bool BestPlacement(MoveableObject *mo, int desireX, int desireY);
    PCell Cell(int X, int Y);
    
    static const int AreaX;
    static const int AreaY;
    static int baseGrid;

private:
    bool FillRealm(int border, int level, bool rotation = false, int dist = 0);
    bool CellFinder(int X, int Y, int &desireX, int &desireY);
    std::vector<RealmCell> realm;
};