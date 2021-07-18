// MIT License
//
// Copyright (c) 2021 Aaron M. Roller
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#include <doctest/doctest.h>
#include <teacup/maths.h>

TEST_CASE("Mat4 multiplication") {
    Mat4 a = {
        5, 2, 6, 1,
        0, 6, 2, 0,
        3, 8, 1, 4,
        1, 8, 5, 6
    };

    Mat4 b = {
        7, 5, 8, 0,
        1, 8, 2, 6,
        9, 4, 3, 8,
        5, 3, 7, 9
    };

    Mat4 c = a * b;

    CHECK(c.raw[0][0] == doctest::Approx(96));
    CHECK(c.raw[0][1] == doctest::Approx(68));
    CHECK(c.raw[0][2] == doctest::Approx(69));
    CHECK(c.raw[0][3] == doctest::Approx(69));

    CHECK(c.raw[1][0] == doctest::Approx(24));
    CHECK(c.raw[1][1] == doctest::Approx(56));
    CHECK(c.raw[1][2] == doctest::Approx(18));
    CHECK(c.raw[1][3] == doctest::Approx(52));

    CHECK(c.raw[2][0] == doctest::Approx(58));
    CHECK(c.raw[2][1] == doctest::Approx(95));
    CHECK(c.raw[2][2] == doctest::Approx(71));
    CHECK(c.raw[2][3] == doctest::Approx(92));

    CHECK(c.raw[3][0] == doctest::Approx(90));
    CHECK(c.raw[3][1] == doctest::Approx(107));
    CHECK(c.raw[3][2] == doctest::Approx(81));
    CHECK(c.raw[3][3] == doctest::Approx(142));
}

TEST_CASE("Mat4 Inverse") {
    Mat4 a = {
        1, 0, 0, 1,
        0, 2, 1, 2,
        2, 1, 0, 1,
        2, 0, 1, 4
    };

    Mat4 inv = Inverse(a);

    CHECK(inv.raw[0][0] == doctest::Approx(-2));
    CHECK(inv.raw[0][1] == doctest::Approx(-0.5));
    CHECK(inv.raw[0][2] == doctest::Approx(1));
    CHECK(inv.raw[0][3] == doctest::Approx(0.5));

    CHECK(inv.raw[1][0] == doctest::Approx(1));
    CHECK(inv.raw[1][1] == doctest::Approx(0.5));
    CHECK(inv.raw[1][2] == doctest::Approx(0));
    CHECK(inv.raw[1][3] == doctest::Approx(-0.5));

    CHECK(inv.raw[2][0] == doctest::Approx(-8));
    CHECK(inv.raw[2][1] == doctest::Approx(-1));
    CHECK(inv.raw[2][2] == doctest::Approx(2));
    CHECK(inv.raw[2][3] == doctest::Approx(2));

    CHECK(inv.raw[3][0] == doctest::Approx(3));
    CHECK(inv.raw[3][1] == doctest::Approx(0.5));
    CHECK(inv.raw[3][2] == doctest::Approx(-1));
    CHECK(inv.raw[3][3] == doctest::Approx(-0.5));
}
