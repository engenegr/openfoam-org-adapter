#include "Temperature.H"
#include "primitivePatchInterpolation.H"


using namespace Foam;

preciceAdapter::VV::Temperature::Temperature(
        const Foam::fvMesh& mesh,
        const std::string nameT)
        : T_(
        const_cast<volScalarField*>(
                &mesh.lookupObject<volScalarField>(nameT))),
          mesh_(mesh)
{
    dataType_ = scalar;
}

void preciceAdapter::VV::Temperature::write(double* buffer, bool meshConnectivity, const unsigned int dim)
{
    int bufferIndex = 0;

    const volScalarField & Temprtr_ = *T_;

    for (uint j = 0; j < patchIDs_.size(); j++ )
    {
        int patchID = patchIDs_.at(j);

        // For every cell of the patch
        forAll(T_->boundaryFieldRef()[patchID], i)
        {
            // Copy the temperature into the buffer
            buffer[bufferIndex++]
                    =
                    T_->boundaryFieldRef()[patchID][i];
        }
    }

    // For every cell of the mesh
    forAll(Temprtr_, i)
    {
        // Copy the temperature into the buffer
        buffer[bufferIndex++]
                =
                Temprtr_[i];
    }
}


void preciceAdapter::VV::Temperature::read(double* buffer, const unsigned int dim)
{
    int bufferIndex = 0;

    volScalarField &Temprtr_ = *T_;

    for (uint j = 0; j < patchIDs_.size(); j++ )
    {
        int patchID = patchIDs_.at(j);

        // For every cell of the patch
        forAll(T_->boundaryFieldRef()[patchID], i)
        {
            // Set the temperature as the buffer value
            T_->boundaryFieldRef()[patchID][i]
                    =
                    buffer[bufferIndex++];
        }
    }

    // For every cell of the mesh
    forAll(Temprtr_, i)
    {
        // Set the temperature as the buffer value
        Temprtr_[i]
                =
                buffer[bufferIndex++];
    }
    //*T_ = Temprtr_;

}
