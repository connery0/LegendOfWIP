#pragma once
#include "Frame.h"

const static Frame f_Down_NoShield1{ Point2f(0,16) };
const static Frame f_Down_NoShield2{ Point2f(0,16), true };

const static Frame f_Up_NoShield1{ Point2f(16,16) };
const static Frame f_Up_NoShield2{ Point2f(16,16),true };

const static Frame f_Left_NoShield1{ Point2f(32,16) };
const static Frame f_Left_NoShield2{ Point2f(48,16) };

const static Frame f_Right_NoShield1{ Point2f(32,16),true };
const static Frame f_Right_NoShield2{ Point2f(48,16),true };