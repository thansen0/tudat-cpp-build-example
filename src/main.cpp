#include <Eigen/Dense>
#include <iostream>

#include "tudat/io/basicInputOutput.h"
#include "tudat/interface/spice/spiceInterface.h"

using namespace std;

int main() {
    cout << "Simple Tudat example" << endl;

    try
    {
        // Load standard Spice kernels (de421.bsp etc.)
        tudat::spice_interface::loadStandardSpiceKernels();

        // Epoch in seconds since J2000 (e.g. 1 day after J2000)
        double epoch = 86400.0;

        // Get state of Earth relative to Sun at the epoch
        Eigen::Vector6d earthState =
            tudat::spice_interface::getBodyCartesianStateAtEpoch(
                "Earth",            // Target
                "Sun",              // Observer
                "ECLIPJ2000",       // Reference frame
                "NONE",             // Aberration corrections
                epoch );            // Epoch

        std::cout << "Earth state (x,y,z,vx,vy,vz):\n" << earthState << std::endl;
    }
    catch (std::exception& e)
    {
        std::cerr << "Exception: " << e.what() << std::endl;
    }

    return 0;
}

