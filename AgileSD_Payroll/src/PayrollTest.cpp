#include "PayrollDatabase.h"
#include "AddSalariedEmployee.h"
#include "Employee.h"
#include "SalariedClassification.h"
#include "AddHourlyEmployee.h"
#include "MonthlySchedule.h"
#include "HoldMethod.h"
#include "HourlyClassification.h"
#include "WeeklySchedule.h"
#include "AddCommissionedEmployee.h"
#include "CommissionedClassification.h"
#include "BiweeklySchedule.h"
#include "DeleteEmployeeTransaction.h"
#include "TimeCardTransaction.h"
#include "TimeCard.h"
#include "SalesReceiptTransaction.h"
#include "SalesReceipt.h"
#include "UnionAffiliation.h"
#include "ServiceChargeTransaction.h"
#include "ServiceCharge.h"
#include "ChangeNameTransaction.h"
#include "ChangeAddressTransaction.h"
#include "ChangeHourlyTransaction.h"
#include "ChangeSalariedTransaction.h"
#include "ChangeCommissionedTransaction.h"
#include "ChangeMailTransaction.h"
#include "MailMethod.h"
#include "ChangeDirectTransaction.h"
#include "DirectMethod.h"
#include "ChangeHoldTransaction.h"
#include "ChangeMemberTransaction.h"
#include "ChangeUnaffiliatedTransaction.h"
#include "NoAffiliation.h"
#include "PaydayTransaction.h"
#include "PayCheck.h"

extern PayrollDatabase GpayrollDatabase;

#define CPPUNIT_ASSERT(x) ASSERT_TRUE(x)
#define CPPUNIT_ASSERT_EQUAL(x, y) EXPECT_EQ(x, y) 

class PayrollTest : public ::testing::Test {
protected:
    virtual void SetUp() {
        GpayrollDatabase.clear();
    }

    // virtual void TearDown() {}

    void ValidatePaycheck(PaydayTransaction& pt,
        int empid,
        const Date& payDate,
        double pay);
};

TEST_F(PayrollTest, TestAddSalariedEmployee)
{
  int empId = 1;
  AddSalariedEmployee t(empId, "Bob", "Home", 1000.00);
  t.Execute();
  Employee* e = GpayrollDatabase.GetEmployee(empId);
  CPPUNIT_ASSERT(e);
  CPPUNIT_ASSERT("Bob" == e->GetName());
  PaymentClassification* pc = e->GetClassification();
  SalariedClassification* sc = dynamic_cast<SalariedClassification*>(pc);
  CPPUNIT_ASSERT(sc);
  CPPUNIT_ASSERT_EQUAL(1000.00, sc->GetSalary());
  PaymentSchedule* ps = e->GetSchedule();
  MonthlySchedule* ms = dynamic_cast<MonthlySchedule*>(ps);
  CPPUNIT_ASSERT(ms);
  PaymentMethod* pm = e->GetMethod();
  HoldMethod* hm = dynamic_cast<HoldMethod*>(pm);
  CPPUNIT_ASSERT(hm);
}

TEST_F(PayrollTest, TestAddHourlyEmployee)
{
  int empId = 2;
  AddHourlyEmployee t(empId, "Bill", "Home", 15.25);
  t.Execute();
  Employee* e = GpayrollDatabase.GetEmployee(empId);
  CPPUNIT_ASSERT(e);
  CPPUNIT_ASSERT("Bill" == e->GetName());
  PaymentClassification* pc = e->GetClassification();
  HourlyClassification* hc = dynamic_cast<HourlyClassification*>(pc);
  CPPUNIT_ASSERT(hc);
  CPPUNIT_ASSERT_EQUAL(15.25, hc->GetRate());
  PaymentSchedule* ps = e->GetSchedule();
  WeeklySchedule* ws = dynamic_cast<WeeklySchedule*>(ps);
  CPPUNIT_ASSERT(ws);
  PaymentMethod* pm = e->GetMethod();
  HoldMethod* hm = dynamic_cast<HoldMethod*>(pm);
  CPPUNIT_ASSERT(hm);
}

TEST_F(PayrollTest, TestAddCommissionedEmployee)
{
  int empId = 3;
  AddCommissionedEmployee t(empId, "Lance", "Home", 2500, 3.2);
  t.Execute();
  Employee* e = GpayrollDatabase.GetEmployee(empId);
  CPPUNIT_ASSERT(e);
  CPPUNIT_ASSERT("Lance" == e->GetName());
  PaymentClassification* pc = e->GetClassification();
  CommissionedClassification* cc = dynamic_cast<CommissionedClassification*>(pc);
  CPPUNIT_ASSERT(cc);
  CPPUNIT_ASSERT(2500 == cc->GetSalary());
  PaymentSchedule* ps = e->GetSchedule();
  BiweeklySchedule* bws = dynamic_cast<BiweeklySchedule*>(ps);
  CPPUNIT_ASSERT(bws);
  PaymentMethod* pm = e->GetMethod();
  HoldMethod* hm = dynamic_cast<HoldMethod*>(pm);
  CPPUNIT_ASSERT(hm);
}

TEST_F(PayrollTest, TestDeleteEmployee)
{
  int empId = 3;
  AddCommissionedEmployee t(empId, "Lance", "Home", 2500, 3.2);
  t.Execute();
  {
    Employee* e = GpayrollDatabase.GetEmployee(empId);
    CPPUNIT_ASSERT(e);
  }
  DeleteEmployeeTransaction dt(empId);
  dt.Execute();
  {
    Employee* e = GpayrollDatabase.GetEmployee(empId);
    CPPUNIT_ASSERT(e == 0);
  }
}

TEST_F(PayrollTest, TestTimeCardTransaction)
{
  int empId = 2;
  AddHourlyEmployee t(empId, "Bill", "Home", 15.25);
  t.Execute();
  TimeCardTransaction tct(Date(10,31,2001), 8.0, empId);
  tct.Execute();
  Employee* e = GpayrollDatabase.GetEmployee(empId);
  CPPUNIT_ASSERT(e);
  PaymentClassification* pc = e->GetClassification();
  HourlyClassification* hc = dynamic_cast<HourlyClassification*>(pc);
  CPPUNIT_ASSERT(hc);
  TimeCard* tc = hc->GetTimeCard(Date(10,31,2001));
  CPPUNIT_ASSERT(tc);
  CPPUNIT_ASSERT_EQUAL(8.0, tc->GetHours());
}

TEST_F(PayrollTest, TestBadTimeCardTransaction)
{
  int empId = 3;
  AddCommissionedEmployee t(empId, "Lance", "Home", 2500, 3.2);
  t.Execute();
  TimeCardTransaction tct(Date(10,31,2001), 8.0, empId);
  try {
    tct.Execute();
    CPPUNIT_ASSERT(false);
  }
  catch(...) {
  }
}

TEST_F(PayrollTest, TestSalesReceiptTransaction)
{
  int empId = 3;
  AddCommissionedEmployee t(empId, "Lance", "Home", 2500, 3.2);
  t.Execute();
  Date saleDate(11, 12, 2001); // Monday
  SalesReceiptTransaction srt(saleDate, 25000, empId);
  srt.Execute();
  Employee* e = GpayrollDatabase.GetEmployee(empId);
  CPPUNIT_ASSERT(e);
  PaymentClassification* pc = e->GetClassification();
  CommissionedClassification* cc = dynamic_cast<CommissionedClassification*>(pc);
  CPPUNIT_ASSERT(cc);
  SalesReceipt* receipt = cc->GetReceipt(saleDate);
  CPPUNIT_ASSERT(receipt);
  CPPUNIT_ASSERT(25000 == receipt->GetAmount());
}

TEST_F(PayrollTest, TestBadSalesReceiptTransaction)
{
  int empId = 2;
  AddHourlyEmployee t(empId, "Bill", "Home", 15.25);
  t.Execute();
  Date saleDate(11,12,2001);
  SalesReceiptTransaction tct(saleDate, 25000, empId);
  try {
    tct.Execute();
    CPPUNIT_ASSERT(false);
  }
  catch(...) {
  }
}

TEST_F(PayrollTest, TestAddServiceCharge)
{
  int empId = 2;
  int memberId = 86; // Maxwell Smart
  AddHourlyEmployee t(empId, "Bill", "Home", 15.25);
  t.Execute();
  Employee* e = GpayrollDatabase.GetEmployee(empId);
  CPPUNIT_ASSERT(e);
  UnionAffiliation* af = new UnionAffiliation(memberId, 12.5);
  e->SetAffiliation(af);
  GpayrollDatabase.AddUnionMember(memberId, e);
  Date serviceChargeDate(11,01,2001);
  ServiceChargeTransaction sct(memberId, serviceChargeDate, 12.95);
  sct.Execute();
  ServiceCharge* sc = af->GetServiceCharge(serviceChargeDate);
  CPPUNIT_ASSERT(sc);
  CPPUNIT_ASSERT_EQUAL(12.95, sc->GetAmount());
}

TEST_F(PayrollTest, TestChangeNameTransaction)
{
  int empId = 2;
  AddHourlyEmployee t(empId, "Bill", "Home", 15.25);
  t.Execute();
  ChangeNameTransaction cnt(empId, "Bob");
  cnt.Execute();
  Employee* e = GpayrollDatabase.GetEmployee(empId);
  CPPUNIT_ASSERT(e);
  CPPUNIT_ASSERT("Bob" == e->GetName());
}

TEST_F(PayrollTest, TestChangeAddressTransaction)
{
  int empId = 2;
  AddHourlyEmployee t(empId, "Bill", "Home", 15.25);
  t.Execute();
  ChangeAddressTransaction cnt(empId, "PO Box 7575");
  cnt.Execute();
  Employee* e = GpayrollDatabase.GetEmployee(empId);
  CPPUNIT_ASSERT(e);
  CPPUNIT_ASSERT("PO Box 7575" == e->GetAddress());
}

TEST_F(PayrollTest, TestChangeHourlyTransaction)
{
  int empId = 3;
  AddCommissionedEmployee t(empId, "Lance", "Home", 2500, 3.2);
  t.Execute();
  ChangeHourlyTransaction cht(empId, 27.52);
  cht.Execute();
  Employee* e = GpayrollDatabase.GetEmployee(empId);
  CPPUNIT_ASSERT(e);
  PaymentClassification* pc = e->GetClassification();
  CPPUNIT_ASSERT(pc);
  HourlyClassification* hc = dynamic_cast<HourlyClassification*>(pc);
  CPPUNIT_ASSERT(hc);
  CPPUNIT_ASSERT_EQUAL(27.52, hc->GetRate());
  PaymentSchedule* ps = e->GetSchedule();
  WeeklySchedule* ws = dynamic_cast<WeeklySchedule*>(ps);
  CPPUNIT_ASSERT(ws);
}

TEST_F(PayrollTest, TestChangeSalariedTransaction)
{
  int empId = 3;
  AddCommissionedEmployee t(empId, "Lance", "Home", 2500, 3.2);
  t.Execute();
  ChangeSalariedTransaction cht(empId, 25000);
  cht.Execute();
  Employee* e = GpayrollDatabase.GetEmployee(empId);
  CPPUNIT_ASSERT(e);
  PaymentClassification* pc = e->GetClassification();
  CPPUNIT_ASSERT(pc);
  SalariedClassification* sc = dynamic_cast<SalariedClassification*>(pc);
  CPPUNIT_ASSERT(sc);
  CPPUNIT_ASSERT(25000 == sc->GetSalary());
  PaymentSchedule* ps = e->GetSchedule();
  MonthlySchedule* ms = dynamic_cast<MonthlySchedule*>(ps);
  CPPUNIT_ASSERT(ms);
}

TEST_F(PayrollTest, TestChangeCommissionedTransaction)
{
  int empId = 2;
  AddHourlyEmployee t(empId, "Bill", "Home", 15.25);
  t.Execute();
  ChangeCommissionedTransaction cht(empId, 25000, 4.5);
  cht.Execute();
  Employee* e = GpayrollDatabase.GetEmployee(empId);
  CPPUNIT_ASSERT(e);
  PaymentClassification* pc = e->GetClassification();
  CPPUNIT_ASSERT(pc);
  CommissionedClassification* cc = dynamic_cast<CommissionedClassification*>(pc);
  CPPUNIT_ASSERT(cc);
  CPPUNIT_ASSERT(25000 == cc->GetSalary());
  CPPUNIT_ASSERT_EQUAL(4.5, cc->GetRate());
  PaymentSchedule* ps = e->GetSchedule();
  BiweeklySchedule* bws = dynamic_cast<BiweeklySchedule*>(ps);
  CPPUNIT_ASSERT(bws);
}

TEST_F(PayrollTest, TestChangeMailTransaction)
{
  int empId = 2;
  AddHourlyEmployee t(empId, "Bill", "Home", 15.25);
  t.Execute();
  ChangeMailTransaction cmt(empId, "4080 El Cerrito Road");
  cmt.Execute();
  Employee* e = GpayrollDatabase.GetEmployee(empId);
  CPPUNIT_ASSERT(e);
  PaymentMethod* pm = e->GetMethod();
  CPPUNIT_ASSERT(pm);
  MailMethod* mm = dynamic_cast<MailMethod*>(pm);
  CPPUNIT_ASSERT(mm);
  CPPUNIT_ASSERT("4080 El Cerrito Road" == mm->GetAddress());
}

TEST_F(PayrollTest, TestChangeDirectTransaction)
{
  int empId = 2;
  AddHourlyEmployee t(empId, "Bill", "Home", 15.25);
  t.Execute();
  ChangeDirectTransaction cdt(empId, "FirstNational", "1058209");
  cdt.Execute();
  Employee* e = GpayrollDatabase.GetEmployee(empId);
  CPPUNIT_ASSERT(e);
  PaymentMethod* pm = e->GetMethod();
  CPPUNIT_ASSERT(pm);
  DirectMethod* dm = dynamic_cast<DirectMethod*>(pm);
  CPPUNIT_ASSERT(dm);
  CPPUNIT_ASSERT("FirstNational" == dm->GetBank());
  CPPUNIT_ASSERT("1058209" == dm->GetAccount());
}

TEST_F(PayrollTest, TestChangeHoldTransaction)
{
  int empId = 2;
  AddHourlyEmployee t(empId, "Bill", "Home", 15.25);
  t.Execute();
  ChangeDirectTransaction cdt(empId, "FirstNational", "1058209");
  cdt.Execute();
  ChangeHoldTransaction cht(empId);
  cht.Execute();
  Employee* e = GpayrollDatabase.GetEmployee(empId);
  CPPUNIT_ASSERT(e);
  PaymentMethod* pm = e->GetMethod();
  CPPUNIT_ASSERT(pm);
  HoldMethod* hm = dynamic_cast<HoldMethod*>(pm);
  CPPUNIT_ASSERT(hm);
}

TEST_F(PayrollTest, TestChangeMemberTransaction)
{
  int empId = 2;
  int memberId = 7734;
  AddHourlyEmployee t(empId, "Bill", "Home", 15.25);
  t.Execute();
  ChangeMemberTransaction cmt(empId, memberId, 99.42);
  cmt.Execute();
  Employee* e = GpayrollDatabase.GetEmployee(empId);
  CPPUNIT_ASSERT(e);
  Affiliation* af = e->GetAffiliation();
  CPPUNIT_ASSERT(af);
  UnionAffiliation* uf = dynamic_cast<UnionAffiliation*>(af);
  CPPUNIT_ASSERT(uf);
  CPPUNIT_ASSERT_EQUAL(99.42, uf->GetDues());
  Employee* member = GpayrollDatabase.GetUnionMember(memberId);
  CPPUNIT_ASSERT(member);
  CPPUNIT_ASSERT(e == member);
}

TEST_F(PayrollTest, TestChangeUnaffiliatedTransaction)
{
  int empId = 2;
  int memberId = 7734;
  AddHourlyEmployee t(empId, "Bill", "Home", 15.25);
  t.Execute();
  ChangeMemberTransaction cmt(empId, memberId, 99.42);
  cmt.Execute();
  ChangeUnaffiliatedTransaction cut(empId);
  cut.Execute();
  Employee* e = GpayrollDatabase.GetEmployee(empId);
  CPPUNIT_ASSERT(e);
  Affiliation* af = e->GetAffiliation();
  CPPUNIT_ASSERT(af);
  NoAffiliation* nf = dynamic_cast<NoAffiliation*>(af);
  CPPUNIT_ASSERT(nf);
  Employee* member = GpayrollDatabase.GetUnionMember(memberId);
  CPPUNIT_ASSERT(member == 0);
}

TEST_F(PayrollTest, TestPaySingleSalariedEmployee)
{
  int empId = 1;
  AddSalariedEmployee t(empId, "Bob", "Home", 1000.00);
  t.Execute();
  Date payDate(11,30,2001);
  PaydayTransaction pt(payDate);
  pt.Execute();
  ValidatePaycheck(pt, empId, payDate, 1000.00);
}

void PayrollTest::ValidatePaycheck(PaydayTransaction& pt,
				   int empid,
				   const Date& payDate,
				   double pay)
{
  Paycheck* pc = pt.GetPaycheck(empid);
  CPPUNIT_ASSERT(pc);
  CPPUNIT_ASSERT(pc->GetPayPeriodEndDate() == payDate);
  CPPUNIT_ASSERT_EQUAL(pay, pc->GetGrossPay());
  CPPUNIT_ASSERT("Hold" == pc->GetField("Disposition"));
  CPPUNIT_ASSERT_EQUAL(0.0, pc->GetDeductions());
  CPPUNIT_ASSERT_EQUAL(pay, pc->GetNetPay());
}

TEST_F(PayrollTest, TestPaySingleSalariedEmployeeOnWrongDate)
{
  int empId = 1;
  AddSalariedEmployee t(empId, "Bob", "Home", 1000.00);
  t.Execute();
  Date payDate(11,29,2001);
  PaydayTransaction pt(payDate);
  pt.Execute();
  Paycheck* pc = pt.GetPaycheck(empId);
  CPPUNIT_ASSERT(pc == 0);
}

TEST_F(PayrollTest, TestPayMultipleSalariedEmployees)
{
  AddSalariedEmployee t1(1, "Bob", "Home", 1000.00);
  AddSalariedEmployee t2(2, "Bill", "Home", 2000.00);
  AddSalariedEmployee t3(3, "Barry", "Home", 3000.00);
  t1.Execute();
  t2.Execute();
  t3.Execute();
  Date payDate(11,30,2001);
  PaydayTransaction pt(payDate);
  pt.Execute();
  CPPUNIT_ASSERT(3L == pt.GetPaycheckCount());
  ValidatePaycheck(pt, 1, payDate, 1000.00);
  ValidatePaycheck(pt, 2, payDate, 2000.00);
  ValidatePaycheck(pt, 3, payDate, 3000.00);
}

TEST_F(PayrollTest, TestPaySingleHourlyEmployeeNoTimeCards)
{
  int empId = 2;
  AddHourlyEmployee t(empId, "Bill", "Home", 15.25);
  t.Execute();
  Date payDate(11,9,2001); // Friday
  PaydayTransaction pt(payDate);
  pt.Execute();
  ValidatePaycheck(pt, empId, payDate, 0.0);
}

TEST_F(PayrollTest, TestPaySingleHourlyEmployeeOneTimeCard)
{
  int empId = 2;
  AddHourlyEmployee t(empId, "Bill", "Home", 15.25);
  t.Execute();
  Date payDate(11,9,2001); // Friday

  TimeCardTransaction tc(payDate, 2.0, empId);
  tc.Execute();
  PaydayTransaction pt(payDate);
  pt.Execute();
  ValidatePaycheck(pt, empId, payDate, 30.5);
}

TEST_F(PayrollTest, TestPaySingleHourlyEmployeeOvertimeOneTimeCard)
{
  int empId = 2;
  AddHourlyEmployee t(empId, "Bill", "Home", 15.25);
  t.Execute();
  Date payDate(11,9,2001); // Friday

  TimeCardTransaction tc(payDate, 9.0, empId);
  tc.Execute();
  PaydayTransaction pt(payDate);
  pt.Execute();
  ValidatePaycheck(pt, empId, payDate, (8 + 1.5) * 15.25);
}

TEST_F(PayrollTest, TestPaySingleHourlyEmployeeOnWrongDate)
{
  int empId = 2;
  AddHourlyEmployee t(empId, "Bill", "Home", 15.25);
  t.Execute();
  Date payDate(11,8,2001); // Thursday

  TimeCardTransaction tc(payDate, 9.0, empId);
  tc.Execute();
  PaydayTransaction pt(payDate);
  pt.Execute();

  Paycheck* pc = pt.GetPaycheck(empId);
  CPPUNIT_ASSERT(pc == 0);
}

TEST_F(PayrollTest, TestPaySingleHourlyEmployeeTwoTimeCards)
{
  int empId = 2;
  AddHourlyEmployee t(empId, "Bill", "Home", 15.25);
  t.Execute();
  Date payDate(11,9,2001); // Friday

  TimeCardTransaction tc(payDate, 2.0, empId);
  tc.Execute();
  TimeCardTransaction tc2(Date(11,8,2001), 5.0, empId);
  tc2.Execute();
  PaydayTransaction pt(payDate);
  pt.Execute();
  ValidatePaycheck(pt, empId, payDate, 7*15.25);
}

TEST_F(PayrollTest, TestPaySingleHourlyEmployeeWithTimeCardsSpanningTwoPayPeriods)
{
  int empId = 2;
  AddHourlyEmployee t(empId, "Bill", "Home", 15.25);
  t.Execute();
  Date payDate(11,9,2001); // Friday
  Date dateInPreviousPayPeriod(11,2,2001);

  TimeCardTransaction tc(payDate, 2.0, empId);
  tc.Execute();
  TimeCardTransaction tc2(dateInPreviousPayPeriod, 5.0, empId);
  tc2.Execute();
  PaydayTransaction pt(payDate);
  pt.Execute();
  ValidatePaycheck(pt, empId, payDate, 2*15.25);
}

TEST_F(PayrollTest, TestPaySingleCommissionedEmployeeNoSalesReceipts)
{
  int empId = 3;
  AddCommissionedEmployee t(empId, "Lance", "Home", 2500, 3.2);
  t.Execute();
  Date payDate(11,9,2001); // Friday
  PaydayTransaction pt(payDate);
  pt.Execute();
  ValidatePaycheck(pt, empId, payDate, 2500.00);
}

TEST_F(PayrollTest, TestPaySingleCommissionedEmployeeOneSalesReceipt)
{
  int empId = 3;
  AddCommissionedEmployee t(empId, "Lance", "Home", 2500, .032);
  t.Execute();
  Date payDate(11,9,2001); // Friday
  SalesReceiptTransaction srt(payDate, 13000.00, empId);
  srt.Execute();
  PaydayTransaction pt(payDate);
  pt.Execute();
  ValidatePaycheck(pt, empId, payDate, 2500.00 + .032 * 13000);
}

TEST_F(PayrollTest, TestPaySingleCommissionedEmployeeTwoSalesReceipts)
{
  int empId = 3;
  AddCommissionedEmployee t(empId, "Lance", "Home", 2500, .032);
  t.Execute();
  Date payDate(11,9,2001); // Biweekly Friday
  SalesReceiptTransaction srt(payDate, 13000.00, empId);
  srt.Execute();
  SalesReceiptTransaction srt2(Date(11,8,2001), 24000, empId);
  srt2.Execute();
  PaydayTransaction pt(payDate);
  pt.Execute();
  ValidatePaycheck(pt, empId, payDate, 2500.00 + .032 * 13000 + .032 * 24000);
}

TEST_F(PayrollTest, TestPaySingleCommissionedEmployeeWrongDate)
{
  int empId = 3;
  AddCommissionedEmployee t(empId, "Lance", "Home", 2500, .032);
  t.Execute();
  Date payDate(11,16,2001); // Wrong Friday
  SalesReceiptTransaction srt(payDate, 13000.00, empId);
  srt.Execute();
  SalesReceiptTransaction srt2(Date(11,15,2001), 24000, empId);
  srt2.Execute();
  PaydayTransaction pt(payDate);
  pt.Execute();

  Paycheck* pc = pt.GetPaycheck(empId);
  CPPUNIT_ASSERT(pc == 0);
}

TEST_F(PayrollTest, TestPaySingleCommissionedEmployeeSpanMultiplePayPeriods)
{
  int empId = 3;
  AddCommissionedEmployee t(empId, "Lance", "Home", 2500, .032);
  t.Execute();
  Date earlyDate(11,9,2001); // Previous pay period
  Date payDate(11,23,2001); // Biweekly Friday
  Date lateDate(12,7,2001); // Next pay period.
  SalesReceiptTransaction srt(payDate, 13000.00, empId);
  srt.Execute();
  SalesReceiptTransaction srt2(earlyDate, 24000, empId);
  srt2.Execute();
  SalesReceiptTransaction srt3(lateDate, 15000, empId);
  srt3.Execute();
  PaydayTransaction pt(payDate);
  pt.Execute();
  ValidatePaycheck(pt, empId, payDate, 2500.00 + .032 * 13000);
}

TEST_F(PayrollTest, TestSalariedUnionMemberDues)
{
  int empId = 1;
  AddSalariedEmployee t(empId, "Bob", "Home", 1000.00);
  t.Execute();
  int memberId = 7734;
  ChangeMemberTransaction cmt(empId, memberId, 9.42);
  cmt.Execute();
  Date payDate(11,30,2001);
  int fridays = 5; // Fridays in Nov, 2001.
  PaydayTransaction pt(payDate);
  pt.Execute();
  Paycheck* pc = pt.GetPaycheck(empId);
  CPPUNIT_ASSERT(pc);
  CPPUNIT_ASSERT(pc->GetPayPeriodEndDate() == payDate);
  CPPUNIT_ASSERT_EQUAL(1000.00, pc->GetGrossPay());
  CPPUNIT_ASSERT("Hold" == pc->GetField("Disposition"));
  CPPUNIT_ASSERT_EQUAL(fridays*9.42, pc->GetDeductions());
  CPPUNIT_ASSERT_EQUAL(1000.0 - (fridays * 9.42), pc->GetNetPay());
}

TEST_F(PayrollTest, TestHourlyUnionMemberDues)
{
  int empId = 1;
  AddHourlyEmployee t(empId, "Bill", "Home", 15.24);
  t.Execute();
  int memberId = 7734;
  ChangeMemberTransaction cmt(empId, memberId, 9.42);
  cmt.Execute();
  Date payDate(11,9,2001);
  TimeCardTransaction tct(payDate, 8.0, empId);
  tct.Execute();
  PaydayTransaction pt(payDate);
  pt.Execute();
  Paycheck* pc = pt.GetPaycheck(empId);
  CPPUNIT_ASSERT(pc);
  CPPUNIT_ASSERT(pc->GetPayPeriodEndDate() == payDate);
  CPPUNIT_ASSERT_EQUAL(8*15.24, pc->GetGrossPay());
  CPPUNIT_ASSERT("Hold" == pc->GetField("Disposition"));
  CPPUNIT_ASSERT_EQUAL(9.42, pc->GetDeductions());
  CPPUNIT_ASSERT_EQUAL((8*15.24)-9.42, pc->GetNetPay());
}

TEST_F(PayrollTest, TestCommissionedUnionMemberDues)
{
  int empId = 3;
  AddCommissionedEmployee t(empId, "Lance", "Home", 2500, .032);
  t.Execute();
  int memberId = 7734;
  ChangeMemberTransaction cmt(empId, memberId, 9.42);
  cmt.Execute();
  Date payDate(11,9,2001);
  PaydayTransaction pt(payDate);
  pt.Execute();
  Paycheck* pc = pt.GetPaycheck(empId);
  CPPUNIT_ASSERT(pc);
  CPPUNIT_ASSERT(pc->GetPayPeriodEndDate() == payDate);
  CPPUNIT_ASSERT_EQUAL(2500.00, pc->GetGrossPay());
  CPPUNIT_ASSERT("Hold" == pc->GetField("Disposition"));
  CPPUNIT_ASSERT_EQUAL(2*9.42, pc->GetDeductions());
  CPPUNIT_ASSERT_EQUAL(2500.0 - (2 * 9.42), pc->GetNetPay());
}

TEST_F(PayrollTest, TestHourlyUnionMemberServiceCharge)
{
  int empId = 1;
  AddHourlyEmployee t(empId, "Bill", "Home", 15.24);
  t.Execute();
  int memberId = 7734;
  ChangeMemberTransaction cmt(empId, memberId, 9.42);
  cmt.Execute();
  Date payDate(11,9,2001);
  ServiceChargeTransaction sct(memberId, payDate, 19.42);
  sct.Execute();
  TimeCardTransaction tct(payDate, 8.0, empId);
  tct.Execute();
  PaydayTransaction pt(payDate);
  pt.Execute();
  Paycheck* pc = pt.GetPaycheck(empId);
  CPPUNIT_ASSERT(pc);
  CPPUNIT_ASSERT(pc->GetPayPeriodEndDate() == payDate);
  CPPUNIT_ASSERT_EQUAL(8*15.24, pc->GetGrossPay());
  CPPUNIT_ASSERT("Hold" == pc->GetField("Disposition"));
  CPPUNIT_ASSERT_EQUAL(9.42 + 19.42, pc->GetDeductions());
  CPPUNIT_ASSERT_EQUAL((8*15.24)-(9.42 + 19.42), pc->GetNetPay());
}

TEST_F(PayrollTest, TestServiceChargesSpanningMultiplePayPeriods)
{
  int empId = 1;
  AddHourlyEmployee t(empId, "Bill", "Home", 15.24);
  t.Execute();
  int memberId = 7734;
  ChangeMemberTransaction cmt(empId, memberId, 9.42);
  cmt.Execute();
  Date earlyDate(11,2,2001); // previous Friday
  Date payDate(11,9,2001);
  Date lateDate(11,16,2001); // next Friday
  ServiceChargeTransaction sct(memberId, payDate, 19.42);
  sct.Execute();
  ServiceChargeTransaction sctEarly(memberId, earlyDate, 100.00);
  sctEarly.Execute();
  ServiceChargeTransaction sctLate(memberId, lateDate, 200.00);
  sctLate.Execute();
  TimeCardTransaction tct(payDate, 8.0, empId);
  tct.Execute();
  PaydayTransaction pt(payDate);
  pt.Execute();
  Paycheck* pc = pt.GetPaycheck(empId);
  CPPUNIT_ASSERT(pc);
  CPPUNIT_ASSERT(pc->GetPayPeriodEndDate() == payDate);
  CPPUNIT_ASSERT_EQUAL(8*15.24, pc->GetGrossPay());
  CPPUNIT_ASSERT("Hold" == pc->GetField("Disposition"));
  CPPUNIT_ASSERT_EQUAL(9.42 + 19.42, pc->GetDeductions());
  CPPUNIT_ASSERT_EQUAL((8*15.24)-(9.42 + 19.42), pc->GetNetPay());
}