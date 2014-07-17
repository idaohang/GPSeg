#include "EvolveThread.h"

#include <beagle/GP.hpp>

#include "../Operands/EphemeralPercent.hpp"
#include "../Operands/Mat.hpp"
#include "../Evaluator/FeatureEvalOp.hpp"
#include "../Operators/Impl/MatMulDou.hpp"
#include "../Operators/Impl/MatMul.hpp"
#include "../Operators/Impl/MatAdd.hpp"
#include "../Operators/Impl/MatSub.hpp"
#include "../Operators/Impl/MatBlur.hpp"
#include "../Operators/Impl/MatSquare.hpp"
#include "../Operators/Impl/MatIx.hpp"
#include "../Operators/Impl/MatIy.hpp"
#include <cstdlib>
#include <cmath>
#include <iostream>
#include <stdexcept>
#include <vector>
#include <numeric>
#include <typeinfo>

#include <qstring.h>

using namespace std;
using namespace Beagle;

EvolveThread::EvolveThread():
    _strTargetFile("mask.bmp"),
    _strOriginFile("origin_m.jpg")
{

}

void EvolveThread::run()
{
    try {
        // 1: Build primitives.
        GP::PrimitiveSet::Handle lSet = new GP::PrimitiveSet(&typeid(Mat));

        lSet->insert(new MatAdd);
        lSet->insert(new MatSub);
        lSet->insert(new MatMul);
        lSet->insert(new MatIx);
        lSet->insert(new MatIy);
        lSet->insert(new MatBlur);
        lSet->insert(new MatMulDou);

        lSet->insert(new EphemeralPercent);

        lSet->insert(new GP::TokenT<Mat>("r"));
        lSet->insert(new GP::TokenT<Mat>("g"));
        lSet->insert(new GP::TokenT<Mat>("b"));
        lSet->insert(new GP::TokenT<Mat>("h"));
        lSet->insert(new GP::TokenT<Mat>("s"));
        lSet->insert(new GP::TokenT<Mat>("v"));
        lSet->insert(new GP::TokenT<Mat>("i"));

        // 2: Build a system.
        GP::System::Handle lSystem = new GP::System(lSet);

        // 3: Build operators.
        FeatureEvalOp::Handle lEvalOp = new FeatureEvalOp("message");
        lEvalOp->setObjectMask(_strTargetFile);
        lEvalOp->setOriginImage(_strOriginFile);

        std::cout << "8888888" << std::endl;
        // 4: Build an evolver and a vivarium.
        Evolver::Handle lEvolver = new GP::Evolver(lEvalOp);
        GP::Vivarium::Handle lVivarium = new GP::Vivarium;

        // 5: Initialize the evolver and set a parameter.
        lEvolver->initialize(lSystem, "GPIMAGEPROC.conf");

        // 6: Evolve the vivarium.
        lEvolver->evolve(lVivarium);
    }
    catch(Exception& inException) {
        inException.terminate();
    }
    catch(exception& inException) {
        cerr << "Standard exception catched:" << endl;
        cerr << inException.what() << endl << flush;
    }
    catch(...) {
        cerr << "Unknown exception catched!" << endl << flush;
    }
}

void EvolveThread::setTargetFilename(QString target)
{
    _strTargetFile = target;
}

void EvolveThread::setOriginFilename(QString origin)
{
    _strOriginFile = origin;
}
