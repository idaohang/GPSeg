/*
 *  Open BEAGLE
 *  Copyright (C) 2001-2007 by Christian Gagne and Marc Parizeau
 *
 *  This library is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU Lesser General Public
 *  License as published by the Free Software Foundation; either
 *  version 2.1 of the License, or (at your option) any later version.
 *
 *  This library is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *  Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public
 *  License along with this library; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 *  Contact:
 *  Laboratoire de Vision et Systemes Numeriques
 *  Departement de genie electrique et de genie informatique
 *  Universite Laval, Quebec, Canada, G1K 7P4
 *  http://vision.gel.ulaval.ca
 *
 */

/*!
 *  \file   SpambaseMain.cpp
 *  \brief  Implementation of the main routine for the spambase problem.
 *  \author Christian Gagne
 *  \author Marc Parizeau
 *  $Revision: 1.9.2.1 $
 *  $Date: 2007/05/09 01:51:24 $
 */

#include <beagle/GP.hpp>

#include "EphemeralPercent.hpp"
#include "Mat.hpp"
#include "FeatureEvalOp.hpp"

#include "Operators/Impl/MatMulDou.hpp"
#include "Operators/Impl/MatMul.hpp"
#include "Operators/Impl/MatAdd.hpp"
#include "Operators/Impl/MatSub.hpp"
#include "Operators/Impl/MatBlur.hpp"
#include "Operators/Impl/MatSquare.hpp"
#include "Operators/Impl/MatIx.hpp"
#include "Operators/Impl/MatIy.hpp"

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

/*!
 *  \brief Main routine for the function spambase problem.
 *  \param argc Number of arguments on the command-line.
 *  \param argv Arguments on the command-line.
 *  \return Return value of the program.
 *  \ingroup Spambase
 */
int main(int argc, char *argv[]) {
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
    return 1;
  }
  catch(...) {
    cerr << "Unknown exception catched!" << endl << flush;
    return 1;
  }
  return 0;
}

