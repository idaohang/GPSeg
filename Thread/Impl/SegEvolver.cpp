#include "../SegEvolver.h"

#include <beagle/GP.hpp>

#include "../../Operands/EphemeralPercent.hpp"
#include "../../Operands/Mat.hpp"
#include "../../Evaluator/FeatureEvalOp.hpp"

#include "../../Operators/Impl/MatMulDou.hpp"
#include "../../Operators/Impl/MatMul.hpp"
#include "../../Operators/Impl/MatAdd.hpp"
#include "../../Operators/Impl/MatSub.hpp"
#include "../../Operators/Impl/MatBlur.hpp"
#include "../../Operators/Impl/MatSquare.hpp"
#include "../../Operators/Impl/MatIx.hpp"
#include "../../Operators/Impl/MatIy.hpp"

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

void SegEvolver::doWork(const QString &result)
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
        std::cout << "insert finished!" << std::endl;

        /*
        for (int i=0; i < 24; i++)
        {
            std::cout << "insert feature---" << std::endl;
            QString featurename = QString("f_") + QString::number(i);
            std::string filename = featurename.toStdString();
            Beagle::string f(filename);
            std::cout << "insert feature---" << std::endl;
            lSet->insert(new GP::TokenT<Mat>( f));
            std::cout << "insert feature---" << std::endl;
        }
        */
        // 2: Build a system.
        GP::System::Handle lSystem = new GP::System(lSet);
        // 3: Build operators.
        std::string lTrainingFilename = "Training";
        //std::string lProgramName = argv[0];
        //std::string::size_type lLibsPos  = lProgramName.find(std::string(".libs"));
        //std::string::size_type lSlashPos = lProgramName.find_last_of(std::string("/\\"), lLibsPos);
        //if(lSlashPos != std::string::npos) lSpambaseFilename.insert(0, lProgramName, 0, lSlashPos+1);
        //SpambaseEvalOp::Handle lEvalOp = new SpambaseEvalOp(lSpambaseFilename.c_str());
        std::cout << "***************1" << std::endl;
        FeatureEvalOp::Handle lEvalOp = new FeatureEvalOp(lTrainingFilename.c_str());
        std::cout << "***************2" << std::endl;
        // 4: Build an evolver and a vivarium.
        Evolver::Handle lEvolver = new GP::Evolver(lEvalOp);
        GP::Vivarium::Handle lVivarium = new GP::Vivarium;
        std::cout << "***************3" << std::endl;
        // 5: Initialize the evolver and set a parameter.
        int argc = 1;
        char * argv[] = {"hello"};
        lEvolver->initialize(lSystem, argc, argv);
        std::cout << "***************4" << std::endl;
        // 6: Evolve the vivarium.
        lEvolver->evolve(lVivarium);
    }
    catch(Exception& inException) {
        inException.terminate();
    }
    catch(exception& inException) {
        cerr << "Standard exception catched:" << endl;
        cerr << inException.what() << endl << flush;
        emit resultReady("result--exception");
    }
    catch(...) {
        cerr << "Unknown exception catched!" << endl << flush;
        emit resultReady("unknown--exception");
    }

    emit resultReady("Normally Stop");
}
