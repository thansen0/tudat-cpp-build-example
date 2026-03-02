#include <Eigen/Dense>
#include <filesystem>
#include <iostream>
#include <string>
#include <vector>

#include "tudat/io/basicInputOutput.h"
#include "tudat/interface/spice/spiceInterface.h"

using namespace std;

int main() {
    cout << "Simple Tudat example" << endl;

    try
    {
        namespace fs = std::filesystem;
        const std::string kernelDir =
            std::string(PROJECT_SOURCE_DIR) + "/extern/tudat-resources/resource/spice_kernels";

        const std::vector<std::string> mandatoryKernels = {
            "pck00010.tpc",
            "naif0012.tls"
        };
        const std::vector<std::string> preferredEphemerisKernels = {
            "tudat_merged_spk_kernel.bsp",
            "inpop19a_TDB_m100_p100_spice.bsp",
            "de430_mar097_small.bsp"
        };
        const std::vector<std::string> optionalKernels = {
            "inpop19a_TDB_m100_p100_spice.tpc",
            "gm_de431.tpc",
            "NOE-4-2020.tpc",
            "NOE-5-2021.tpc",
            "NOE-6-2018-MAIN-v2.tpc",
            "codes_300ast_20100725.bsp",
            "codes_300ast_20100725.tf",
            "juice_mat_crema_4_0_20220601_20330626_v01.bsp"
        };

        for (const std::string& kernel : mandatoryKernels)
        {
            const std::string kernelPath = kernelDir + "/" + kernel;
            if (!fs::exists(kernelPath))
            {
                throw std::runtime_error("Required SPICE kernel not found: " + kernelPath);
            }
            tudat::spice_interface::loadSpiceKernelInTudat(kernelPath);
        }

        bool loadedEphemerisKernel = false;
        for (const std::string& kernel : preferredEphemerisKernels)
        {
            const std::string kernelPath = kernelDir + "/" + kernel;
            if (fs::exists(kernelPath))
            {
                tudat::spice_interface::loadSpiceKernelInTudat(kernelPath);
                loadedEphemerisKernel = true;
                break;
            }
        }
        if (!loadedEphemerisKernel)
        {
            throw std::runtime_error("No ephemeris SPICE kernel found in " + kernelDir);
        }

        for (const std::string& kernel : optionalKernels)
        {
            const std::string kernelPath = kernelDir + "/" + kernel;
            if (fs::exists(kernelPath))
            {
                tudat::spice_interface::loadSpiceKernelInTudat(kernelPath);
            }
        }

        // epoch in seconds since J2000 (e.g. 1 day after J2000)
        double epoch = 86400.0;

        // get state of Earth relative to Sun at the epoch
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
    catch (...)
    {
        // Tudat probably only throws std::exception, but to know for sure
        // I'd have to read the docs, and we all know that's not happening.
        std::cerr << "Unknown exception occurred." << std::endl;
    }

    return 0;
}
