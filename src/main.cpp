#include <Tudat/Astrodynamics/BasicAstrodynamics/orbitalElementConversions.h>

int main() {
    Eigen::Vector6d keplerElements;

    // Set Kepler elements: [a, e, i, Ω, ω, ν] (all SI units, angles in radians)
    keplerElements << 7000e3, 0.01, 0.1, 0.2, 0.3, 0.4;

    // Standard gravitational parameter (mu) of the central body, e.g., Earth
    const double muEarth = 3.986004418e14;

    // Convert to Cartesian state
    Eigen::Vector6d cartesianState = tudat::astrodynamics::convertKeplerianToCartesianElements(keplerElements, muEarth);

    // Print results
    std::cout << "Cartesian state:\n" << cartesianState << std::endl;

    return 0;
}

