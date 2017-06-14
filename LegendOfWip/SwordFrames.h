#pragma once
#include "Frame.h"

const static Frame f_sword_H_Right{ Point2f(0,254) };
const static Frame f_sword_H_Left{ Point2f(0,254),true };

const static Frame f_sword_V_Up{ Point2f(16,254) };
const static Frame f_sword_V_Down{ Point2f(16,254),false,true};

const static Frame f_sword_D_UpToRight{ Point2f(32,254) };
const static Frame f_sword_D_RightToDown{ Point2f(32,254),false,true };
const static Frame f_sword_D_DownToLeft{ Point2f(32,254),true,true };
const static Frame f_sword_D_LeftToUp{ Point2f(32,254),true };

const static Frame f_static_1{ Point2f(101,535) };
const static Frame f_static_2{ Point2f(117,535) };
const static Frame f_static_3{ Point2f(134,535) };