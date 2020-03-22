//
// Created by Alex Post on 3/21/20.
//

#include <AttitudeDetermination/TriadMethod.hpp>
#include <PRV.hpp>
#include <AttitudeDetermination/DavenportQ.hpp>
#include "catch2/catch.hpp"
#include "math/Matrix.hpp"

TEST_CASE("Should solve using Triad Method", "[triad]") {

    SECTION("Should solve for dcm using triad method") {
        Vector b1({0.8273, 0.5541, -0.0920});
        Vector b2({-0.8285, 0.5522, -0.0955});
        Vector n1({-0.1517, -0.9669, 0.2050});
        Vector n2({-0.8393, 0.4494, -0.3044});

        TriadMethod solver(b1, b2, n1, n2);
        Matrix dcm = solver.solve();

        std::cout << dcm << std::endl;
    }

    SECTION("Should compute error") {
        Matrix bEstimated({
                                  {
                                          0.969846, -0.200706, -0.138258
                                  },
                                  {
                                          0.17101, 0.96461, -0.200706
                                  },
                                  {
                                          0.173648, 0.17101, 0.969846
                                  }
        });

        Matrix bTrue({
                             {
                                     0.963592, -0.223042, -0.147454
                             },
                             {
                                     0.187303, 0.956645, -0.223042
                             },
                             {
                                     0.190809, 0.187303, 0.963592
                             }
        });

        double error = TriadMethod::principalRotationError(bEstimated, bTrue);
        REQUIRE(error == 1.8349476067250545);
    }
}

TEST_CASE("Should solve using DavenportQ") {

    SECTION("Test") {
        Vector b1({0.8190, -0.5282, 0.2242});
        Vector b2({-0.3138, -0.1584, 0.9362});
        Vector n1({1, 0, 0});
        Vector n2({0, 0, 1});

        Vector b[2] = {b1, b2};
        Vector n[2] = {n1, n2};
        double w[2] = {1., 1.};

        DavenportQ d(b, n, w, 2);
        Matrix result = d.solve();

        Matrix expected({
                                {0.8251430306475811, 0.45928221888853482, -0.32893595713838986},
                                {-0.52556111677127593, 0.83763959205037075, -0.14881353392691654},
                                {0.20718236658522349, 0.29566839322882021, 0.93255332809101787}
        });

        REQUIRE(result == expected);
    }

    SECTION("Should evaluate another example") {
        Vector b1({0.8273, 0.5541, -0.0920});
        Vector b2({-0.8285, 0.5522, -0.0955});
        Vector n1({-0.1517, -0.9669, 0.2050});
        Vector n2({-0.8393, 0.4494, -0.3044});

        Vector b[2] = {b1, b2};
        Vector n[2] = {n1, n2};
        double w[2] = {1., 1.};

        DavenportQ d(b, n, w, 2);

        Matrix result = d.solve();

        std::cout << result << std::endl;

    }
}