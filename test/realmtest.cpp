#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <deque>
#include <realm.h>

constexpr int cstDimSize = 250;

TEST(RealmTest, RealmSize) {
    auto realm = std::make_unique<Realm>();
    ASSERT_TRUE(realm->AreaX >= cstDimSize);
    ASSERT_TRUE(realm->AreaY >= cstDimSize);
}

TEST(RealmTest, RealmObstaclesControlPoints) {
    auto realm = std::make_unique<Realm>();
    std::deque<PCell> queTest;
    queTest.push_back(realm->Cell(realm->baseGrid,realm->baseGrid));
    queTest.push_back(realm->Cell(2*realm->baseGrid, 2*realm->baseGrid));
    queTest.push_back(realm->Cell(3*realm->baseGrid, 3*realm->baseGrid));
    queTest.push_back(realm->Cell(realm->AreaX - realm->baseGrid, realm->baseGrid));
    queTest.push_back(realm->Cell(realm->baseGrid, realm->AreaY - realm->baseGrid));
    queTest.push_back(realm->Cell(realm->AreaX - realm->baseGrid, realm->AreaY - realm->baseGrid));
    while (!queTest.empty())
    {
        PCell cell = queTest.front();
        ASSERT_TRUE(cell != NULL);
        ASSERT_TRUE(cell->Wall);
        queTest.pop_front();
    }
}