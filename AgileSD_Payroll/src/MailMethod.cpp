#include "MailMethod.h"

#include <utility>

#include "PayCheck.h"

MailMethod::~MailMethod() = default;

MailMethod::MailMethod(std::string address)
: itsAddress(std::move(address))
{
}

void MailMethod::Pay(PayCheck& pc)
{
  pc.SetField("Disposition", "Mail");
}
