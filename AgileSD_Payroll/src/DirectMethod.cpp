#include "DirectMethod.h"

#include <utility>
#include "PayCheck.h"

DirectMethod::~DirectMethod() = default;

DirectMethod::DirectMethod(std::string bank, std::string account)
: itsBank(std::move(bank))
, itsAccount(std::move(account))
{
}

void DirectMethod::Pay(PayCheck& pc)
{
  pc.SetField("Disposition", "Direct");
}

























































































