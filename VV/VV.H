#ifndef VVS_H
#define VVS_H

#include "Interface.H"

#include "VV/Temperature.H"

#include "fvCFD.H"

namespace preciceAdapter
{
namespace VV
{

class VolumeVolume
{

protected:

    //- OpenFOAM fvMesh object
    const Foam::fvMesh& mesh_;

    // TODO: Create a struct for all the parameter names

    //- Solver type
    std::string solverType_ = "none";

    //- Name of the transportProperties dictionary
    std::string nameTransportProperties_ = "transportProperties";

    //- Name of the temperature field
    std::string nameT_ = "T";


protected:

    //- Read the VV-related options from the adapter's configuration file
    bool readConfig(const IOdictionary& adapterConfig);

public:

    //- Constructor
    VolumeVolume(const Foam::fvMesh& mesh);

    //- Configure
    bool configure(const IOdictionary& adapterConfig);

    //- Add coupling data writers
    void addWriters(std::string dataName, Interface * interface);

    //- Add coupling data readers
    void addReaders(std::string dataName, Interface * interface);
};

}
}

#endif
