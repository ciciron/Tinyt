#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <deque>
#include <tsapi.h>
#include <realm.h>

constexpr int cstDimSize = 250;

TEST(ServiceTest, EntryPointCheck) {
    
    IServer *ies = EntryPoint();
    ASSERT_TRUE(ies != NULL);
}

TEST(ServiceTest, RealmSizeOverAPI) {
    int maxX, maxY;
    IServer *ies = EntryPoint();
    RStatus ras = ies->GetDimSize(maxX, maxY);
    ASSERT_TRUE(ras == RStatus::Success);
    ASSERT_TRUE(maxX >= cstDimSize);
    ASSERT_TRUE(maxY >= cstDimSize);
}


TEST(ServiceTest, CreateElements) {
    constexpr int cstOneCycle = 30;
    IServer *ies = EntryPoint();
    for (int i = cstOneCycle; i < cstDimSize;  i += cstOneCycle) {
        int moElement;
        RStatus ras = ies->CreateMoveable(30, 30, moElement);
        ASSERT_TRUE(ras == RStatus::Success);
        ASSERT_TRUE(moElement > 0);
    }
}