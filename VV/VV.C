#include "VV.H"

#include "Utilities.H"

using namespace Foam;

preciceAdapter::VV::VolumeVolume::VolumeVolume
(
    const Foam::fvMesh& mesh
)
:
mesh_(mesh)
{}

bool preciceAdapter::VV::VolumeVolume::configure(const IOdictionary& adapterConfig)
{
    DEBUG(adapterInfo("Configuring the Volume-Volume module..."));

    // Read the VV-specific options from the adapter's configuration file
    if (!readConfig(adapterConfig))
    {
        return false;
    }

    return true;
}

bool preciceAdapter::VV::VolumeVolume::readConfig(const IOdictionary& adapterConfig)
{
    const dictionary VVdict = adapterConfig.subOrEmptyDict("VV");

    // Read the solver type (if not specified, it is determined automatically)
    solverType_ = VVdict.lookupOrDefault<word>("solverType", "");
    DEBUG(adapterInfo("    user-defined solver type : " + solverType_));

    /* TODO: Read the names of any needed fields and parameters.
    * Include the force here?
    */

    // Read the name of the pointDisplacement field (if different)
    nameTransportProperties_ = VVdict.lookupOrDefault<word>("nameTransportProperties", "transportProperties");
    DEBUG(adapterInfo("    transportProperties name : " + nameTransportProperties_));

    return true;
}

void preciceAdapter::VV::VolumeVolume::addWriters(std::string dataName, Interface * interface)
{
    if (dataName == "T")
    {
        interface->addCouplingDataWriter
            (
                dataName,
                new OpenFOAMScalarField(mesh_, dataName)
            );
        DEBUG(adapterInfo("Added writer: Temperature."));
    }
    else
    {
        adapterInfo("Unknown data type - cannot add " + dataName +".", "error");
    }

    // NOTE: If you want to couple another variable, you need
    // to add your new coupling data user as a coupling data
    // writer here (and as a reader below).
    // The argument of the dataName.compare() needs to match
    // the one provided in the adapter's configuration file.
}

void preciceAdapter::VV::VolumeVolume::addReaders(std::string dataName, Interface * interface)
{

    if (dataName == "T")
    {
        interface->addCouplingDataReader
        (
            dataName,
            new OpenFOAMScalarField(mesh_, dataName)
        );
        DEBUG(adapterInfo("Added reader: Temperature."));
    }
    else
    {
        adapterInfo("Unknown data type - cannot add " + dataName +".", "error");
    }

    // NOTE: If you want to couple another variable, you need
    // to add your new coupling data user as a coupling data
    // reader here (and as a writer above).
    // The argument of the dataName.compare() needs to match
    // the one provided in the adapter's configuration file.
}
