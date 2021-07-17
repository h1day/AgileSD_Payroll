#include "MailMethod.h"

#include "PayCheck.h"

MailMethod::~MailMethod() = default;

MailMethod::MailMethod(std::string address)
: itsAddress(address)
{
}

void MailMethod::Pay(PayCheck& pc)
{
  pc.SetField("Disposition", "Mail");
}
