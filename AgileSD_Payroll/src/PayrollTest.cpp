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

extern PayrollDatabase g_payrollDatabase;

//#define ASSERT_TRUE(x) ASSERT_TRUE(x)
//#define EXPECT_EQ(x, y) EXPECT_EQ(x, y) 

class PayrollTest : public testing::Test
{
protected:
    void SetUp() override
    {
        g_payrollDatabase.clear();
    }

    // virtual void TearDown() {}

    void ValidatePaycheck(PaydayTransaction& pt,
                          int empId,
                          const Date& payDate,
                          double pay) const;
};

TEST_F(PayrollTest, TestAddSalariedEmployee)
{
    const int empId = 1;
    AddSalariedEmployee t(empId, "Bob", "Home", 1000.00);
    t.Execute();
    Employee* e = g_payrollDatabase.GetEmployee(empId);
    ASSERT_TRUE(e);
    ASSERT_TRUE("Bob" == e->GetName());
    PaymentClassification* pc = e->GetClassification();
    const auto sc = dynamic_cast<SalariedClassification*>(pc);
    ASSERT_TRUE(sc);
    EXPECT_EQ(1000.00, sc->GetSalary());
    PaymentSchedule* ps = e->GetSchedule();
    const auto ms = dynamic_cast<MonthlySchedule*>(ps);
    ASSERT_TRUE(ms);
    PaymentMethod* pm = e->GetMethod();
    const auto hm = dynamic_cast<HoldMethod*>(pm);
    ASSERT_TRUE(hm);
}

TEST_F(PayrollTest, TestAddHourlyEmployee)
{
    const int empId = 2;
    AddHourlyEmployee t(empId, "Bill", "Home", 15.25);
    t.Execute();
    Employee* e = g_payrollDatabase.GetEmployee(empId);
    ASSERT_TRUE(e);
    ASSERT_TRUE("Bill" == e->GetName());
    PaymentClassification* pc = e->GetClassification();
    const auto hc = dynamic_cast<HourlyClassification*>(pc);
    ASSERT_TRUE(hc);
    EXPECT_EQ(15.25, hc->GetRate());
    PaymentSchedule* ps = e->GetSchedule();
    const auto ws = dynamic_cast<WeeklySchedule*>(ps);
    ASSERT_TRUE(ws);
    PaymentMethod* pm = e->GetMethod();
    const auto hm = dynamic_cast<HoldMethod*>(pm);
    ASSERT_TRUE(hm);
}

TEST_F(PayrollTest, TestAddCommissionedEmployee)
{
    const int empId = 3;
    AddCommissionedEmployee t(empId, "Lance", "Home", 2500, 3.2);
    t.Execute();
    Employee* e = g_payrollDatabase.GetEmployee(empId);
    ASSERT_TRUE(e);
    ASSERT_TRUE("Lance" == e->GetName());
    PaymentClassification* pc = e->GetClassification();
    const auto cc = dynamic_cast<CommissionedClassification*>(pc);
    ASSERT_TRUE(cc);
    EXPECT_DOUBLE_EQ(2500, cc->GetSalary());
    PaymentSchedule* ps = e->GetSchedule();
    const auto bws = dynamic_cast<BiweeklySchedule*>(ps);
    ASSERT_TRUE(bws);
    PaymentMethod* pm = e->GetMethod();
    const auto hm = dynamic_cast<HoldMethod*>(pm);
    ASSERT_TRUE(hm);
}

TEST_F(PayrollTest, TestDeleteEmployee)
{
    const int empId = 3;
    AddCommissionedEmployee t(empId, "Lance", "Home", 2500, 3.2);
    t.Execute();
    {
        Employee* e = g_payrollDatabase.GetEmployee(empId);
        ASSERT_TRUE(e);
    }
    DeleteEmployeeTransaction dt(empId);
    dt.Execute();
    {
        Employee* e = g_payrollDatabase.GetEmployee(empId);
        ASSERT_TRUE(e == nullptr);
    }
}

TEST_F(PayrollTest, TestTimeCardTransaction)
{
    const int empId = 2;
    AddHourlyEmployee t(empId, "Bill", "Home", 15.25);
    t.Execute();
    TimeCardTransaction tct(Date(10, 31, 2001), 8.0, empId);
    tct.Execute();
    Employee* e = g_payrollDatabase.GetEmployee(empId);
    ASSERT_TRUE(e);
    PaymentClassification* pc = e->GetClassification();
    auto hc = dynamic_cast<HourlyClassification*>(pc);
    ASSERT_TRUE(hc);
    TimeCard* tc = hc->GetTimeCard(Date(10, 31, 2001));
    ASSERT_TRUE(tc);
    EXPECT_EQ(8.0, tc->GetHours());
}

TEST_F(PayrollTest, TestBadTimeCardTransaction)
{
    const int empId = 3;
    AddCommissionedEmployee t(empId, "Lance", "Home", 2500, 3.2);
    t.Execute();
    TimeCardTransaction tct(Date(10, 31, 2001), 8.0, empId);
    try
    {
        tct.Execute();
        ASSERT_TRUE(false);
    }
    catch (...)
    {
    }
}

TEST_F(PayrollTest, TestSalesReceiptTransaction)
{
    const int empId = 3;
    AddCommissionedEmployee t(empId, "Lance", "Home", 2500, 3.2);
    t.Execute();
    const Date saleDate(11, 12, 2001); // Monday
    SalesReceiptTransaction srt(saleDate, 25000, empId);
    srt.Execute();
    Employee* e = g_payrollDatabase.GetEmployee(empId);
    ASSERT_TRUE(e);
    PaymentClassification* pc = e->GetClassification();
    auto cc = dynamic_cast<CommissionedClassification*>(pc);
    ASSERT_TRUE(cc);
    SalesReceipt* receipt = cc->GetReceipt(saleDate);
    ASSERT_TRUE(receipt);
    EXPECT_DOUBLE_EQ(25000, receipt->GetAmount());
}

TEST_F(PayrollTest, TestBadSalesReceiptTransaction)
{
    const int empId = 2;
    AddHourlyEmployee t(empId, "Bill", "Home", 15.25);
    t.Execute();
    const Date saleDate(11, 12, 2001);
    SalesReceiptTransaction tct(saleDate, 25000, empId);
    try
    {
        tct.Execute();
        ASSERT_TRUE(false);
    }
    catch (...)
    {
    }
}

TEST_F(PayrollTest, TestAddServiceCharge)
{
    const int empId = 2;
    const int memberId = 86; // Maxwell Smart
    AddHourlyEmployee t(empId, "Bill", "Home", 15.25);
    t.Execute();
    Employee* e = g_payrollDatabase.GetEmployee(empId);
    ASSERT_TRUE(e);
    auto af = new UnionAffiliation(memberId, 12.5);
    e->SetAffiliation(af);
    g_payrollDatabase.AddUnionMember(memberId, e);
    const Date serviceChargeDate(11, 01, 2001);
    ServiceChargeTransaction sct(memberId, serviceChargeDate, 12.95);
    sct.Execute();
    ServiceCharge* sc = af->GetServiceCharge(serviceChargeDate);
    ASSERT_TRUE(sc);
    EXPECT_EQ(12.95, sc->GetAmount());
}

TEST_F(PayrollTest, TestChangeNameTransaction)
{
    const int empId = 2;
    AddHourlyEmployee t(empId, "Bill", "Home", 15.25);
    t.Execute();
    ChangeNameTransaction cnt(empId, "Bob");
    cnt.Execute();
    Employee* e = g_payrollDatabase.GetEmployee(empId);
    ASSERT_TRUE(e);
    ASSERT_TRUE("Bob" == e->GetName());
}

TEST_F(PayrollTest, TestChangeAddressTransaction)
{
    const int empId = 2;
    AddHourlyEmployee t(empId, "Bill", "Home", 15.25);
    t.Execute();
    ChangeAddressTransaction cnt(empId, "PO Box 7575");
    cnt.Execute();
    Employee* e = g_payrollDatabase.GetEmployee(empId);
    ASSERT_TRUE(e);
    ASSERT_TRUE("PO Box 7575" == e->GetAddress());
}

TEST_F(PayrollTest, TestChangeHourlyTransaction)
{
    const int empId = 3;
    AddCommissionedEmployee t(empId, "Lance", "Home", 2500, 3.2);
    t.Execute();
    ChangeHourlyTransaction cht(empId, 27.52);
    cht.Execute();
    Employee* e = g_payrollDatabase.GetEmployee(empId);
    ASSERT_TRUE(e);
    PaymentClassification* pc = e->GetClassification();
    ASSERT_TRUE(pc);
    const auto hc = dynamic_cast<HourlyClassification*>(pc);
    ASSERT_TRUE(hc);
    EXPECT_EQ(27.52, hc->GetRate());
    PaymentSchedule* ps = e->GetSchedule();
    const auto ws = dynamic_cast<WeeklySchedule*>(ps);
    ASSERT_TRUE(ws);
}

TEST_F(PayrollTest, TestChangeSalariedTransaction)
{
    const int empId = 3;
    AddCommissionedEmployee t(empId, "Lance", "Home", 2500, 3.2);
    t.Execute();
    ChangeSalariedTransaction cht(empId, 25000);
    cht.Execute();
    Employee* e = g_payrollDatabase.GetEmployee(empId);
    ASSERT_TRUE(e);
    PaymentClassification* pc = e->GetClassification();
    ASSERT_TRUE(pc);
    const auto sc = dynamic_cast<SalariedClassification*>(pc);
    ASSERT_TRUE(sc);
    EXPECT_DOUBLE_EQ(25000, sc->GetSalary());
    PaymentSchedule* ps = e->GetSchedule();
    const auto ms = dynamic_cast<MonthlySchedule*>(ps);
    ASSERT_TRUE(ms);
}

TEST_F(PayrollTest, TestChangeCommissionedTransaction)
{
    const int empId = 2;
    AddHourlyEmployee t(empId, "Bill", "Home", 15.25);
    t.Execute();
    ChangeCommissionedTransaction cht(empId, 25000, 4.5);
    cht.Execute();
    Employee* e = g_payrollDatabase.GetEmployee(empId);
    ASSERT_TRUE(e);
    PaymentClassification* pc = e->GetClassification();
    ASSERT_TRUE(pc);
    const auto cc = dynamic_cast<CommissionedClassification*>(pc);
    ASSERT_TRUE(cc);
    EXPECT_DOUBLE_EQ(25000, cc->GetSalary());
    EXPECT_EQ(4.5, cc->GetRate());
    PaymentSchedule* ps = e->GetSchedule();
    const auto bws = dynamic_cast<BiweeklySchedule*>(ps);
    ASSERT_TRUE(bws);
}

TEST_F(PayrollTest, TestChangeMailTransaction)
{
    const int empId = 2;
    AddHourlyEmployee t(empId, "Bill", "Home", 15.25);
    t.Execute();
    // ReSharper disable once StringLiteralTypo
    ChangeMailTransaction cmt(empId, "4080 El Cerrito Road");
    cmt.Execute();
    Employee* e = g_payrollDatabase.GetEmployee(empId);
    ASSERT_TRUE(e);
    PaymentMethod* pm = e->GetMethod();
    ASSERT_TRUE(pm);
    const auto mm = dynamic_cast<MailMethod*>(pm);
    ASSERT_TRUE(mm);
    ASSERT_TRUE("4080 El Cerrito Road" == mm->GetAddress());
}

TEST_F(PayrollTest, TestChangeDirectTransaction)
{
    const int empId = 2;
    AddHourlyEmployee t(empId, "Bill", "Home", 15.25);
    t.Execute();
    ChangeDirectTransaction cdt(empId, "FirstNational", "1058209");
    cdt.Execute();
    Employee* e = g_payrollDatabase.GetEmployee(empId);
    ASSERT_TRUE(e);
    PaymentMethod* pm = e->GetMethod();
    ASSERT_TRUE(pm);
    const auto dm = dynamic_cast<DirectMethod*>(pm);
    ASSERT_TRUE(dm);
    ASSERT_TRUE("FirstNational" == dm->GetBank());
    ASSERT_TRUE("1058209" == dm->GetAccount());
}

TEST_F(PayrollTest, TestChangeHoldTransaction)
{
    const int empId = 2;
    AddHourlyEmployee t(empId, "Bill", "Home", 15.25);
    t.Execute();
    ChangeDirectTransaction cdt(empId, "FirstNational", "1058209");
    cdt.Execute();
    ChangeHoldTransaction cht(empId);
    cht.Execute();
    Employee* e = g_payrollDatabase.GetEmployee(empId);
    ASSERT_TRUE(e);
    PaymentMethod* pm = e->GetMethod();
    ASSERT_TRUE(pm);
    const auto hm = dynamic_cast<HoldMethod*>(pm);
    ASSERT_TRUE(hm);
}

TEST_F(PayrollTest, TestChangeMemberTransaction)
{
    const int empId = 2;
    const int memberId = 7734;
    AddHourlyEmployee t(empId, "Bill", "Home", 15.25);
    t.Execute();
    ChangeMemberTransaction cmt(empId, memberId, 99.42);
    cmt.Execute();
    Employee* e = g_payrollDatabase.GetEmployee(empId);
    ASSERT_TRUE(e);
    Affiliation* af = e->GetAffiliation();
    ASSERT_TRUE(af);
    const auto uf = dynamic_cast<UnionAffiliation*>(af);
    ASSERT_TRUE(uf);
    EXPECT_EQ(99.42, uf->GetDues());
    Employee* member = g_payrollDatabase.GetUnionMember(memberId);
    ASSERT_TRUE(member);
    ASSERT_TRUE(e == member);
}

TEST_F(PayrollTest, TestChangeUnaffiliatedTransaction)
{
    const int empId = 2;
    const int memberId = 7734;
    AddHourlyEmployee t(empId, "Bill", "Home", 15.25);
    t.Execute();
    ChangeMemberTransaction cmt(empId, memberId, 99.42);
    cmt.Execute();
    ChangeUnaffiliatedTransaction cut(empId);
    cut.Execute();
    Employee* e = g_payrollDatabase.GetEmployee(empId);
    ASSERT_TRUE(e);
    Affiliation* af = e->GetAffiliation();
    ASSERT_TRUE(af);
    const auto nf = dynamic_cast<NoAffiliation*>(af);
    ASSERT_TRUE(nf);
    Employee* member = g_payrollDatabase.GetUnionMember(memberId);
    ASSERT_TRUE(member == nullptr);
}

TEST_F(PayrollTest, TestPaySingleSalariedEmployee)
{
    const int empId = 1;
    AddSalariedEmployee t(empId, "Bob", "Home", 1000.00);
    t.Execute();
    const Date payDate(11, 30, 2001);
    PaydayTransaction pt(payDate);
    pt.Execute();
    ValidatePaycheck(pt, empId, payDate, 1000.00);
}

void PayrollTest::ValidatePaycheck(PaydayTransaction& pt,
                                   int empId,
                                   const Date& payDate,
                                   double pay) const
{
    PayCheck* pc = pt.GetPaycheck(empId);
    ASSERT_TRUE(pc);
    ASSERT_TRUE(pc->GetPayPeriodEndDate() == payDate);
    EXPECT_EQ(pay, pc->GetGrossPay());
    ASSERT_TRUE("Hold" == pc->GetField("Disposition"));
    EXPECT_EQ(0.0, pc->GetDeductions());
    EXPECT_EQ(pay, pc->GetNetPay());
}

TEST_F(PayrollTest, TestPaySingleSalariedEmployeeOnWrongDate)
{
    const int empId = 1;
    AddSalariedEmployee t(empId, "Bob", "Home", 1000.00);
    t.Execute();
    const Date payDate(11, 29, 2001);
    PaydayTransaction pt(payDate);
    pt.Execute();
    PayCheck* pc = pt.GetPaycheck(empId);
    ASSERT_TRUE(pc == nullptr);
}

TEST_F(PayrollTest, TestPayMultipleSalariedEmployees)
{
    AddSalariedEmployee t1(1, "Bob", "Home", 1000.00);
    AddSalariedEmployee t2(2, "Bill", "Home", 2000.00);
    AddSalariedEmployee t3(3, "Barry", "Home", 3000.00);
    t1.Execute();
    t2.Execute();
    t3.Execute();
    Date payDate(11, 30, 2001);
    PaydayTransaction pt(payDate);
    pt.Execute();
    ASSERT_TRUE(3L == pt.GetPaycheckCount());
    ValidatePaycheck(pt, 1, payDate, 1000.00);
    ValidatePaycheck(pt, 2, payDate, 2000.00);
    ValidatePaycheck(pt, 3, payDate, 3000.00);
}

TEST_F(PayrollTest, TestPaySingleHourlyEmployeeNoTimeCards)
{
    const int empId = 2;
    AddHourlyEmployee t(empId, "Bill", "Home", 15.25);
    t.Execute();
    const Date payDate(11, 9, 2001); // Friday
    PaydayTransaction pt(payDate);
    pt.Execute();
    ValidatePaycheck(pt, empId, payDate, 0.0);
}

TEST_F(PayrollTest, TestPaySingleHourlyEmployeeOneTimeCard)
{
    const int empId = 2;
    AddHourlyEmployee t(empId, "Bill", "Home", 15.25);
    t.Execute();
    const Date payDate(11, 9, 2001); // Friday

    TimeCardTransaction tc(payDate, 2.0, empId);
    tc.Execute();
    PaydayTransaction pt(payDate);
    pt.Execute();
    ValidatePaycheck(pt, empId, payDate, 30.5);
}

TEST_F(PayrollTest, TestPaySingleHourlyEmployeeOvertimeOneTimeCard)
{
    const int empId = 2;
    AddHourlyEmployee t(empId, "Bill", "Home", 15.25);
    t.Execute();
    const Date payDate(11, 9, 2001); // Friday

    TimeCardTransaction tc(payDate, 9.0, empId);
    tc.Execute();
    PaydayTransaction pt(payDate);
    pt.Execute();
    ValidatePaycheck(pt, empId, payDate, (8 + 1.5) * 15.25);
}

TEST_F(PayrollTest, TestPaySingleHourlyEmployeeOnWrongDate)
{
    const int empId = 2;
    AddHourlyEmployee t(empId, "Bill", "Home", 15.25);
    t.Execute();
    const Date payDate(11, 8, 2001); // Thursday

    TimeCardTransaction tc(payDate, 9.0, empId);
    tc.Execute();
    PaydayTransaction pt(payDate);
    pt.Execute();

    PayCheck* pc = pt.GetPaycheck(empId);
    ASSERT_TRUE(pc == nullptr);
}

TEST_F(PayrollTest, TestPaySingleHourlyEmployeeTwoTimeCards)
{
    const int empId = 2;
    AddHourlyEmployee t(empId, "Bill", "Home", 15.25);
    t.Execute();
    const Date payDate(11, 9, 2001); // Friday

    TimeCardTransaction tc(payDate, 2.0, empId);
    tc.Execute();
    TimeCardTransaction tc2(Date(11, 8, 2001), 5.0, empId);
    tc2.Execute();
    PaydayTransaction pt(payDate);
    pt.Execute();
    ValidatePaycheck(pt, empId, payDate, 7 * 15.25);
}

TEST_F(PayrollTest, TestPaySingleHourlyEmployeeWithTimeCardsSpanningTwoPayPeriods)
{
    int empId = 2;
    AddHourlyEmployee t(empId, "Bill", "Home", 15.25);
    t.Execute();
    Date payDate(11, 9, 2001); // Friday
    Date dateInPreviousPayPeriod(11, 2, 2001);

    TimeCardTransaction tc(payDate, 2.0, empId);
    tc.Execute();
    TimeCardTransaction tc2(dateInPreviousPayPeriod, 5.0, empId);
    tc2.Execute();
    PaydayTransaction pt(payDate);
    pt.Execute();
    ValidatePaycheck(pt, empId, payDate, 2 * 15.25);
}

TEST_F(PayrollTest, TestPaySingleCommissionedEmployeeNoSalesReceipts)
{
    const int empId = 3;
    AddCommissionedEmployee t(empId, "Lance", "Home", 2500, 3.2);
    t.Execute();
    const Date payDate(11, 9, 2001); // Friday
    PaydayTransaction pt(payDate);
    pt.Execute();
    ValidatePaycheck(pt, empId, payDate, 2500.00);
}

TEST_F(PayrollTest, TestPaySingleCommissionedEmployeeOneSalesReceipt)
{
    const int empId = 3;
    AddCommissionedEmployee t(empId, "Lance", "Home", 2500, .032);
    t.Execute();
    const Date payDate(11, 9, 2001); // Friday
    SalesReceiptTransaction srt(payDate, 13000.00, empId);
    srt.Execute();
    PaydayTransaction pt(payDate);
    pt.Execute();
    ValidatePaycheck(pt, empId, payDate, 2500.00 + .032 * 13000);
}

TEST_F(PayrollTest, TestPaySingleCommissionedEmployeeTwoSalesReceipts)
{
    const int empId = 3;
    AddCommissionedEmployee t(empId, "Lance", "Home", 2500, .032);
    t.Execute();
    const Date payDate(11, 9, 2001); // Biweekly Friday
    SalesReceiptTransaction srt(payDate, 13000.00, empId);
    srt.Execute();
    SalesReceiptTransaction srt2(Date(11, 8, 2001), 24000, empId);
    srt2.Execute();
    PaydayTransaction pt(payDate);
    pt.Execute();
    ValidatePaycheck(pt, empId, payDate, 2500.00 + .032 * 13000 + .032 * 24000);
}

TEST_F(PayrollTest, TestPaySingleCommissionedEmployeeWrongDate)
{
    const int empId = 3;
    AddCommissionedEmployee t(empId, "Lance", "Home", 2500, .032);
    t.Execute();
    const Date payDate(11, 16, 2001); // Wrong Friday
    SalesReceiptTransaction srt(payDate, 13000.00, empId);
    srt.Execute();
    SalesReceiptTransaction srt2(Date(11, 15, 2001), 24000, empId);
    srt2.Execute();
    PaydayTransaction pt(payDate);
    pt.Execute();

    PayCheck* pc = pt.GetPaycheck(empId);
    ASSERT_TRUE(pc == nullptr);
}

TEST_F(PayrollTest, TestPaySingleCommissionedEmployeeSpanMultiplePayPeriods)
{
    int empId = 3;
    AddCommissionedEmployee t(empId, "Lance", "Home", 2500, .032);
    t.Execute();
    Date earlyDate(11, 9, 2001); // Previous pay period
    Date payDate(11, 23, 2001); // Biweekly Friday
    Date lateDate(12, 7, 2001); // Next pay period.
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
    const int empId = 1;
    AddSalariedEmployee t(empId, "Bob", "Home", 1000.00);
    t.Execute();
    const int memberId = 7734;
    ChangeMemberTransaction cmt(empId, memberId, 9.42);
    cmt.Execute();
    const Date payDate(11, 30, 2001);
    int fridays = 5; // Fridays in Nov, 2001.
    PaydayTransaction pt(payDate);
    pt.Execute();
    PayCheck* pc = pt.GetPaycheck(empId);
    ASSERT_TRUE(pc);
    ASSERT_TRUE(pc->GetPayPeriodEndDate() == payDate);
    EXPECT_EQ(1000.00, pc->GetGrossPay());
    ASSERT_TRUE("Hold" == pc->GetField("Disposition"));
    EXPECT_EQ(fridays*9.42, pc->GetDeductions());
    EXPECT_EQ(1000.0 - (fridays * 9.42), pc->GetNetPay());
}

TEST_F(PayrollTest, TestHourlyUnionMemberDues)
{
    int empId = 1;
    AddHourlyEmployee t(empId, "Bill", "Home", 15.24);
    t.Execute();
    int memberId = 7734;
    ChangeMemberTransaction cmt(empId, memberId, 9.42);
    cmt.Execute();
    Date payDate(11, 9, 2001);
    TimeCardTransaction tct(payDate, 8.0, empId);
    tct.Execute();
    PaydayTransaction pt(payDate);
    pt.Execute();
    PayCheck* pc = pt.GetPaycheck(empId);
    ASSERT_TRUE(pc);
    ASSERT_TRUE(pc->GetPayPeriodEndDate() == payDate);
    EXPECT_EQ(8*15.24, pc->GetGrossPay());
    ASSERT_TRUE("Hold" == pc->GetField("Disposition"));
    EXPECT_EQ(9.42, pc->GetDeductions());
    EXPECT_EQ((8*15.24)-9.42, pc->GetNetPay());
}

TEST_F(PayrollTest, TestCommissionedUnionMemberDues)
{
    const int empId = 3;
    AddCommissionedEmployee t(empId, "Lance", "Home", 2500, .032);
    t.Execute();
    const int memberId = 7734;
    ChangeMemberTransaction cmt(empId, memberId, 9.42);
    cmt.Execute();
    const Date payDate(11, 9, 2001);
    PaydayTransaction pt(payDate);
    pt.Execute();
    PayCheck* pc = pt.GetPaycheck(empId);
    ASSERT_TRUE(pc);
    ASSERT_TRUE(pc->GetPayPeriodEndDate() == payDate);
    EXPECT_EQ(2500.00, pc->GetGrossPay());
    ASSERT_TRUE("Hold" == pc->GetField("Disposition"));
    EXPECT_EQ(2*9.42, pc->GetDeductions());
    EXPECT_EQ(2500.0 - (2 * 9.42), pc->GetNetPay());
}

TEST_F(PayrollTest, TestHourlyUnionMemberServiceCharge)
{
    int empId = 1;
    AddHourlyEmployee t(empId, "Bill", "Home", 15.24);
    t.Execute();
    int memberId = 7734;
    ChangeMemberTransaction cmt(empId, memberId, 9.42);
    cmt.Execute();
    Date payDate(11, 9, 2001);
    ServiceChargeTransaction sct(memberId, payDate, 19.42);
    sct.Execute();
    TimeCardTransaction tct(payDate, 8.0, empId);
    tct.Execute();
    PaydayTransaction pt(payDate);
    pt.Execute();
    PayCheck* pc = pt.GetPaycheck(empId);
    ASSERT_TRUE(pc);
    ASSERT_TRUE(pc->GetPayPeriodEndDate() == payDate);
    EXPECT_EQ(8*15.24, pc->GetGrossPay());
    ASSERT_TRUE("Hold" == pc->GetField("Disposition"));
    EXPECT_EQ(9.42 + 19.42, pc->GetDeductions());
    EXPECT_EQ((8*15.24)-(9.42 + 19.42), pc->GetNetPay());
}

TEST_F(PayrollTest, TestServiceChargesSpanningMultiplePayPeriods)
{
    int empId = 1;
    AddHourlyEmployee t(empId, "Bill", "Home", 15.24);
    t.Execute();
    int memberId = 7734;
    ChangeMemberTransaction cmt(empId, memberId, 9.42);
    cmt.Execute();
    Date earlyDate(11, 2, 2001); // previous Friday
    Date payDate(11, 9, 2001);
    Date lateDate(11, 16, 2001); // next Friday
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
    PayCheck* pc = pt.GetPaycheck(empId);
    ASSERT_TRUE(pc);
    ASSERT_TRUE(pc->GetPayPeriodEndDate() == payDate);
    EXPECT_EQ(8*15.24, pc->GetGrossPay());
    ASSERT_TRUE("Hold" == pc->GetField("Disposition"));
    EXPECT_EQ(9.42 + 19.42, pc->GetDeductions());
    EXPECT_EQ((8*15.24)-(9.42 + 19.42), pc->GetNetPay());
}
