#pragma once 

#include "arm_2d_types.h"
extern const arm_2d_tile_t c_tilecmsisLOGORGB565;

using namespace arm_cmsis_stream;

#include "CFFT.h"
#include "ToComplex.h"

// Define some types
#include "Nodes/Arm2D/Layer/component.hpp"

// RP2 components
#include "Nodes/RP2/FromOtherCore/component.hpp"

// Generic
#include "Nodes/Generic/FilterAndDecimate/component.hpp"
#include "Nodes/Generic/CFFT/component.hpp"

// Arm2D related
#include "Nodes/Arm2D/AmplitudeWidget/component.hpp"
#include "Nodes/Arm2D/SpectrumWidget/component.hpp"
#include "Nodes/Arm2D/Arm2D/component.hpp"

// Application specific
#include "Nodes/AppSpecific/FFTAmplitude/component.hpp"
#include "Nodes/AppSpecific/Animate/component.hpp"


