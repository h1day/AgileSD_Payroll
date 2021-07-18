#include "HoldMethod.h"

#include "PayCheck.h"

HoldMethod::~HoldMethod() = default;

void HoldMethod::Pay(PayCheck& pc)
{
    pc.SetField("Disposition", "Hold");
}
