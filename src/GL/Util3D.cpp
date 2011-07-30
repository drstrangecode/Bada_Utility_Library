//
//  Util3D.c
//
//  Created by Zirak on 07/07/10.
//  Copyright __MyCompanyName__ 2010. All rights reserved.
//

#include "GL/Util3D.h"

using namespace Osp::App;
using namespace Osp::Base;
using namespace Osp::System;
using namespace Osp::Graphics;
using namespace Osp::Base::Runtime;
using namespace Osp::Ui::Controls;
using namespace Osp::Graphics::Opengl;
using namespace Osp::Base::Utility;

namespace DSBadaUtilityLib {

void gluPerspective(double fovy, double aspect, double zNear, double zFar)
{
	// Start in projection mode.
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	double xmin, xmax, ymin, ymax;
	ymax = zNear * Math::Tan(fovy * Math::GetPi() / 360.0);
	ymin = -ymax;
	xmin = ymin * aspect;
	xmax = ymax * aspect;
	glFrustumf(xmin, xmax, ymin, ymax, zNear, zFar);
}

}
