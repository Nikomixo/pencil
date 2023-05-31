#include "vectorimage.h"
#include "catch.hpp"

TEST_CASE("VectorImage removeColor")
{
    auto vImage = VectorImage();
    auto bezier = BezierCurve({QPoint(50, 50), QPoint(100, 100)});
    SECTION("Ensure that number is changed")
    {
        bezier.setColorNumber(3);
        vImage.addCurve(bezier, 1.0);

        vImage.removeColor(3);

        REQUIRE(vImage.curve(0).getColorNumber() == 2);
    }

    SECTION("Can't get below zero")
    {
        bezier.setColorNumber(0);
        vImage.addCurve(bezier, 1.0);

        vImage.removeColor(0);

        REQUIRE(vImage.curve(0).getColorNumber() == 0);
    }
}

TEST_CASE("VectorImage isPathFilled")
{
    auto vImage = VectorImage();
    auto bezier1 = BezierCurve({QPoint(50, 50), QPoint(50, 100), QPoint(100, 100)});
    SECTION("Path should not be filled")
    {
        vImage.addCurve(bezier1, 1.0);

        REQUIRE(vImage.isPathFilled() == false);
    }
    auto bezier2 = BezierCurve({QPoint(100, 100), QPoint(100, 50), QPoint(50, 50)});
    SECTION("Path should be filled")
    {
        vImage.addCurve(bezier2, 1.0);

        REQUIRE(vImage.isPathFilled() == true);
    }
}

TEST_CASE("VectorImage select")
{
    auto vImage = VectorImage();
    auto bezier1 = BezierCurve({QPoint(50, 50), QPoint(50, 100), QPoint(100, 100)});
    auto bezier2 = BezierCurve({QPoint(75, 75), QPoint(75, 125), QPoint(125, 125)});

    vImage.addCurve(bezier1, 1.0);
    vImage.addCurve(bezier2, 1.0);

    SECTION("curve 0 should be selected")
    {
        vImage.getFirstSelectedCurve();

        REQUIRE(isSelected(0) == true);
    }

    SECTION("curve 1 should be selected")
    {
        vImage.selectAll();

        REQUIRE(isSelected(1) == true);
    }

    SECTION("should return true")
    {
        REQUIRE(isAnyCurveSelected() == true);
    }

    SECTION("curve 1 should not be selected")
    {
        vImage.deselectAll();

        REQUIRE(isSelected(1) == false);
    }

    SECTION("should return false")
    {
        REQUIRE(isAnyCurveSelected() == false);
    }
}