#include "CppUTest/TestHarness.h"
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



TEST_GROUP(PayrollTest)
{
    TEST_SETUP()
    {
        g_payrollDatabase.clear();
    }
    TEST_TEARDOWN()
    {
        g_payrollDatabase.clear();
    }

    static void ValidatePaycheck(PaydayTransaction & pt,
                                 int empId,
                                 const Date & payDate,
                                 double pay)
    {
        PayCheck* pc = pt.GetPaycheck(empId);
        CHECK_TRUE(pc);
        CHECK_TRUE(pc->GetPayPeriodEndDate() == payDate);
        DOUBLES_EQUAL(pay, pc->GetGrossPay(), 0.01);
        CHECK_TRUE("Hold" == pc->GetField("Disposition"));
        DOUBLES_EQUAL(0.0, pc->GetDeductions(), 0.01);
        DOUBLES_EQUAL(pay, pc->GetNetPay(), 0.01);
    }
};

TEST(PayrollTest, TestAddSalariedEmployee)
{
    const int empId = 1;
    AddSalariedEmployee t(empId, "Bob", "Home", 1000.00);
    t.Execute();
    Employee* e = g_payrollDatabase.GetEmployee(empId);
    CHECK_TRUE(e);
    CHECK_TRUE("Bob" == e->GetName());
    PaymentClassification* pc = e->GetClassification();
    const auto sc = dynamic_cast<SalariedClassification*>(pc);
    CHECK_TRUE(sc);
    DOUBLES_EQUAL(1000.00, sc->GetSalary(), 0.01);
    PaymentSchedule* ps = e->GetSchedule();
    const auto ms = dynamic_cast<MonthlySchedule*>(ps);
    CHECK_TRUE(ms);
    PaymentMethod* pm = e->GetMethod();
    const auto hm = dynamic_cast<HoldMethod*>(pm);
    CHECK_TRUE(hm);
}

TEST(PayrollTest, TestAddHourlyEmployee)
{
    const int empId = 2;
    AddHourlyEmployee t(empId, "Bill", "Home", 15.25);
    t.Execute();
    Employee* e = g_payrollDatabase.GetEmployee(empId);
    CHECK_TRUE(e);
    CHECK_TRUE("Bill" == e->GetName());
    PaymentClassification* pc = e->GetClassification();
    const auto hc = dynamic_cast<HourlyClassification*>(pc);
    CHECK_TRUE(hc);
    DOUBLES_EQUAL(15.25, hc->GetRate(), 0.01);
    PaymentSchedule* ps = e->GetSchedule();
    const auto ws = dynamic_cast<WeeklySchedule*>(ps);
    CHECK_TRUE(ws);
    PaymentMethod* pm = e->GetMethod();
    const auto hm = dynamic_cast<HoldMethod*>(pm);
    CHECK_TRUE(hm);
}

TEST(PayrollTest, TestAddCommissionedEmployee)
{
    const int empId = 3;
    AddCommissionedEmployee t(empId, "Lance", "Home", 2500, 3.2);
    t.Execute();
    Employee* e = g_payrollDatabase.GetEmployee(empId);
    CHECK_TRUE(e);
    CHECK_TRUE("Lance" == e->GetName());
    PaymentClassification* pc = e->GetClassification();
    const auto cc = dynamic_cast<CommissionedClassification*>(pc);
    CHECK_TRUE(cc);
    DOUBLES_EQUAL(2500, cc->GetSalary(), 0.01);
    PaymentSchedule* ps = e->GetSchedule();
    const auto bws = dynamic_cast<BiweeklySchedule*>(ps);
    CHECK_TRUE(bws);
    PaymentMethod* pm = e->GetMethod();
    const auto hm = dynamic_cast<HoldMethod*>(pm);
    CHECK_TRUE(hm);
}

TEST(PayrollTest, TestDeleteEmployee)
{
    const int empId = 3;
    AddCommissionedEmployee t(empId, "Lance", "Home", 2500, 3.2);
    t.Execute();
    {
        Employee* e = g_payrollDatabase.GetEmployee(empId);
        CHECK_TRUE(e);
    }
    DeleteEmployeeTransaction dt(empId);
    dt.Execute();
    {
        Employee* e = g_payrollDatabase.GetEmployee(empId);
        CHECK_TRUE(e == nullptr);
    }
}

TEST(PayrollTest, TestTimeCardTransaction)
{
    const int empId = 2;
    AddHourlyEmployee t(empId, "Bill", "Home", 15.25);
    t.Execute();
    TimeCardTransaction tct(Date(10, 31, 2001), 8.0, empId);
    tct.Execute();
    Employee* e = g_payrollDatabase.GetEmployee(empId);
    CHECK_TRUE(e);
    PaymentClassification* pc = e->GetClassification();
    auto hc = dynamic_cast<HourlyClassification*>(pc);
    CHECK_TRUE(hc);
    TimeCard* tc = hc->GetTimeCard(Date(10, 31, 2001));
    CHECK_TRUE(tc);
    DOUBLES_EQUAL(8.0, tc->GetHours(), 0.01);
}

TEST(PayrollTest, TestBadTimeCardTransaction)
{
    const int empId = 3;
    AddCommissionedEmployee t(empId, "Lance", "Home", 2500, 3.2);
    t.Execute();
    TimeCardTransaction tct(Date(10, 31, 2001), 8.0, empId);
    try
    {
        tct.Execute();
        CHECK_TRUE(false);
    }
    catch (...)
    {
    }
}

TEST(PayrollTest, TestSalesReceiptTransaction)
{
    const int empId = 3;
    AddCommissionedEmployee t(empId, "Lance", "Home", 2500, 3.2);
    t.Execute();
    const Date saleDate(11, 12, 2001); // Monday
    SalesReceiptTransaction srt(saleDate, 25000, empId);
    srt.Execute();
    Employee* e = g_payrollDatabase.GetEmployee(empId);
    CHECK_TRUE(e);
    PaymentClassification* pc = e->GetClassification();
    auto cc = dynamic_cast<CommissionedClassification*>(pc);
    CHECK_TRUE(cc);
    SalesReceipt* receipt = cc->GetReceipt(saleDate);
    CHECK_TRUE(receipt);
    DOUBLES_EQUAL(25000, receipt->GetAmount(), 0.01);
}

TEST(PayrollTest, TestBadSalesReceiptTransaction)
{
    const int empId = 2;
    AddHourlyEmployee t(empId, "Bill", "Home", 15.25);
    t.Execute();
    const Date saleDate(11, 12, 2001);
    SalesReceiptTransaction tct(saleDate, 25000, empId);
    try
    {
        tct.Execute();
        CHECK_TRUE(false);
    }
    catch (...)
    {
    }
}

TEST(PayrollTest, TestAddServiceCharge)
{
    const int empId = 2;
    const int memberId = 86; // Maxwell Smart
    AddHourlyEmployee t(empId, "Bill", "Home", 15.25);
    t.Execute();
    Employee* e = g_payrollDatabase.GetEmployee(empId);
    CHECK_TRUE(e);
    auto af = new UnionAffiliation(memberId, 12.5);
    e->SetAffiliation(af);
    g_payrollDatabase.AddUnionMember(memberId, e);
    const Date serviceChargeDate(11, 01, 2001);
    ServiceChargeTransaction sct(memberId, serviceChargeDate, 12.95);
    sct.Execute();
    ServiceCharge* sc = af->GetServiceCharge(serviceChargeDate);
    CHECK_TRUE(sc);
    DOUBLES_EQUAL(12.95, sc->GetAmount(), 0.01);
}

TEST(PayrollTest, TestChangeNameTransaction)
{
    const int empId = 2;
    AddHourlyEmployee t(empId, "Bill", "Home", 15.25);
    t.Execute();
    ChangeNameTransaction cnt(empId, "Bob");
    cnt.Execute();
    Employee* e = g_payrollDatabase.GetEmployee(empId);
    CHECK_TRUE(e);
    CHECK_TRUE("Bob" == e->GetName());
}

TEST(PayrollTest, TestChangeAddressTransaction)
{
    const int empId = 2;
    AddHourlyEmployee t(empId, "Bill", "Home", 15.25);
    t.Execute();
    ChangeAddressTransaction cnt(empId, "PO Box 7575");
    cnt.Execute();
    Employee* e = g_payrollDatabase.GetEmployee(empId);
    CHECK_TRUE(e);
    CHECK_TRUE("PO Box 7575" == e->GetAddress());
}

TEST(PayrollTest, TestChangeHourlyTransaction)
{
    const int empId = 3;
    AddCommissionedEmployee t(empId, "Lance", "Home", 2500, 3.2);
    t.Execute();
    ChangeHourlyTransaction cht(empId, 27.52);
    cht.Execute();
    Employee* e = g_payrollDatabase.GetEmployee(empId);
    CHECK_TRUE(e);
    PaymentClassification* pc = e->GetClassification();
    CHECK_TRUE(pc);
    const auto hc = dynamic_cast<HourlyClassification*>(pc);
    CHECK_TRUE(hc);
    DOUBLES_EQUAL(27.52, hc->GetRate(), 0.01);
    PaymentSchedule* ps = e->GetSchedule();
    const auto ws = dynamic_cast<WeeklySchedule*>(ps);
    CHECK_TRUE(ws);
}

TEST(PayrollTest, TestChangeSalariedTransaction)
{
    const int empId = 3;
    AddCommissionedEmployee t(empId, "Lance", "Home", 2500, 3.2);
    t.Execute();
    ChangeSalariedTransaction cht(empId, 25000);
    cht.Execute();
    Employee* e = g_payrollDatabase.GetEmployee(empId);
    CHECK_TRUE(e);
    PaymentClassification* pc = e->GetClassification();
    CHECK_TRUE(pc);
    const auto sc = dynamic_cast<SalariedClassification*>(pc);
    CHECK_TRUE(sc);
    DOUBLES_EQUAL(25000, sc->GetSalary(), 0.01);
    PaymentSchedule* ps = e->GetSchedule();
    const auto ms = dynamic_cast<MonthlySchedule*>(ps);
    CHECK_TRUE(ms);
}

TEST(PayrollTest, TestChangeCommissionedTransaction)
{
    const int empId = 2;
    AddHourlyEmployee t(empId, "Bill", "Home", 15.25);
    t.Execute();
    ChangeCommissionedTransaction cht(empId, 25000, 4.5);
    cht.Execute();
    Employee* e = g_payrollDatabase.GetEmployee(empId);
    CHECK_TRUE(e);
    PaymentClassification* pc = e->GetClassification();
    CHECK_TRUE(pc);
    const auto cc = dynamic_cast<CommissionedClassification*>(pc);
    CHECK_TRUE(cc);
    DOUBLES_EQUAL(25000, cc->GetSalary(), 0.01);
    DOUBLES_EQUAL(4.5, cc->GetRate(), 0.01);
    PaymentSchedule* ps = e->GetSchedule();
    const auto bws = dynamic_cast<BiweeklySchedule*>(ps);
    CHECK_TRUE(bws);
}

TEST(PayrollTest, TestChangeMailTransaction)
{
    const int empId = 2;
    AddHourlyEmployee t(empId, "Bill", "Home", 15.25);
    t.Execute();
    // ReSharper disable once StringLiteralTypo
    ChangeMailTransaction cmt(empId, "4080 El Cerrito Road");
    cmt.Execute();
    Employee* e = g_payrollDatabase.GetEmployee(empId);
    CHECK_TRUE(e);
    PaymentMethod* pm = e->GetMethod();
    CHECK_TRUE(pm);
    const auto mm = dynamic_cast<MailMethod*>(pm);
    CHECK_TRUE(mm);
    CHECK_TRUE("4080 El Cerrito Road" == mm->GetAddress());
}

TEST(PayrollTest, TestChangeDirectTransaction)
{
    const int empId = 2;
    AddHourlyEmployee t(empId, "Bill", "Home", 15.25);
    t.Execute();
    ChangeDirectTransaction cdt(empId, "FirstNational", "1058209");
    cdt.Execute();
    Employee* e = g_payrollDatabase.GetEmployee(empId);
    CHECK_TRUE(e);
    PaymentMethod* pm = e->GetMethod();
    CHECK_TRUE(pm);
    const auto dm = dynamic_cast<DirectMethod*>(pm);
    CHECK_TRUE(dm);
    CHECK_TRUE("FirstNational" == dm->GetBank());
    CHECK_TRUE("1058209" == dm->GetAccount());
}

TEST(PayrollTest, TestChangeHoldTransaction)
{
    const int empId = 2;
    AddHourlyEmployee t(empId, "Bill", "Home", 15.25);
    t.Execute();
    ChangeDirectTransaction cdt(empId, "FirstNational", "1058209");
    cdt.Execute();
    ChangeHoldTransaction cht(empId);
    cht.Execute();
    Employee* e = g_payrollDatabase.GetEmployee(empId);
    CHECK_TRUE(e);
    PaymentMethod* pm = e->GetMethod();
    CHECK_TRUE(pm);
    const auto hm = dynamic_cast<HoldMethod*>(pm);
    CHECK_TRUE(hm);
}

TEST(PayrollTest, TestChangeMemberTransaction)
{
    const int empId = 2;
    const int memberId = 7734;
    AddHourlyEmployee t(empId, "Bill", "Home", 15.25);
    t.Execute();
    ChangeMemberTransaction cmt(empId, memberId, 99.42);
    cmt.Execute();
    Employee* e = g_payrollDatabase.GetEmployee(empId);
    CHECK_TRUE(e);
    Affiliation* af = e->GetAffiliation();
    CHECK_TRUE(af);
    const auto uf = dynamic_cast<UnionAffiliation*>(af);
    CHECK_TRUE(uf);
    DOUBLES_EQUAL(99.42, uf->GetDues(), 0.01);
    Employee* member = g_payrollDatabase.GetUnionMember(memberId);
    CHECK_TRUE(member);
    CHECK_TRUE(e == member);
}

TEST(PayrollTest, TestChangeUnaffiliatedTransaction)
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
    CHECK_TRUE(e);
    Affiliation* af = e->GetAffiliation();
    CHECK_TRUE(af);
    const auto nf = dynamic_cast<NoAffiliation*>(af);
    CHECK_TRUE(nf);
    Employee* member = g_payrollDatabase.GetUnionMember(memberId);
    CHECK_TRUE(member == nullptr);
}

TEST(PayrollTest, TestPaySingleSalariedEmployee)
{
    const int empId = 1;
    AddSalariedEmployee t(empId, "Bob", "Home", 1000.00);
    t.Execute();
    const Date payDate(11, 30, 2001);
    PaydayTransaction pt(payDate);
    pt.Execute();
    ValidatePaycheck(pt, empId, payDate, 1000.00);
}

TEST(PayrollTest, TestPaySingleSalariedEmployeeOnWrongDate)
{
    const int empId = 1;
    AddSalariedEmployee t(empId, "Bob", "Home", 1000.00);
    t.Execute();
    const Date payDate(11, 29, 2001);
    PaydayTransaction pt(payDate);
    pt.Execute();
    PayCheck* pc = pt.GetPaycheck(empId);
    CHECK_TRUE(pc == nullptr);


}

TEST(PayrollTest, TestPayMultipleSalariedEmployees)
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
    CHECK_TRUE(3L == pt.GetPaycheckCount());
    ValidatePaycheck(pt, 1, payDate, 1000.00);
    ValidatePaycheck(pt, 2, payDate, 2000.00);
    ValidatePaycheck(pt, 3, payDate, 3000.00);
}

TEST(PayrollTest, TestPaySingleHourlyEmployeeNoTimeCards)
{
    const int empId = 2;
    AddHourlyEmployee t(empId, "Bill", "Home", 15.25);
    t.Execute();
    const Date payDate(11, 9, 2001); // Friday
    PaydayTransaction pt(payDate);
    pt.Execute();
    ValidatePaycheck(pt, empId, payDate, 0.0);
}

TEST(PayrollTest, TestPaySingleHourlyEmployeeOneTimeCard)
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

TEST(PayrollTest, TestPaySingleHourlyEmployeeOvertimeOneTimeCard)
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

TEST(PayrollTest, TestPaySingleHourlyEmployeeOnWrongDate)
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
    CHECK_TRUE(pc == nullptr);
}

TEST(PayrollTest, TestPaySingleHourlyEmployeeTwoTimeCards)
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

TEST(PayrollTest, TestPaySingleHourlyEmployeeWithTimeCardsSpanningTwoPayPeriods)
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

TEST(PayrollTest, TestPaySingleCommissionedEmployeeNoSalesReceipts)
{
    const int empId = 3;
    AddCommissionedEmployee t(empId, "Lance", "Home", 2500, 3.2);
    t.Execute();
    const Date payDate(11, 9, 2001); // Friday
    PaydayTransaction pt(payDate);
    pt.Execute();
    ValidatePaycheck(pt, empId, payDate, 2500.00);
}

TEST(PayrollTest, TestPaySingleCommissionedEmployeeOneSalesReceipt)
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

TEST(PayrollTest, TestPaySingleCommissionedEmployeeTwoSalesReceipts)
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

TEST(PayrollTest, TestPaySingleCommissionedEmployeeWrongDate)
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
    CHECK_TRUE(pc == nullptr);
}

TEST(PayrollTest, TestPaySingleCommissionedEmployeeSpanMultiplePayPeriods)
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

TEST(PayrollTest, TestSalariedUnionMemberDues)
{
    const int empId = 1;
    AddSalariedEmployee t(empId, "Bob", "Home", 1000.00);
    t.Execute();
    const int memberId = 7734;
    ChangeMemberTransaction cmt(empId, memberId, 9.42);
    cmt.Execute();
    const Date payDate(11, 30, 2001);
    const int fridays = 5; // Fridays in Nov, 2001.
    PaydayTransaction pt(payDate);
    pt.Execute();
    PayCheck* pc = pt.GetPaycheck(empId);
    CHECK_TRUE(pc);
    CHECK_TRUE(pc->GetPayPeriodEndDate() == payDate);
    DOUBLES_EQUAL(1000.00, pc->GetGrossPay(), 0.01);
    CHECK_TRUE("Hold" == pc->GetField("Disposition"));
    DOUBLES_EQUAL(fridays*9.42, pc->GetDeductions(), 0.01);
    DOUBLES_EQUAL(1000.0 - (fridays * 9.42), pc->GetNetPay(), 0.01);
}

TEST(PayrollTest, TestHourlyUnionMemberDues)
{
    const int empId = 1;
    AddHourlyEmployee t(empId, "Bill", "Home", 15.24);
    t.Execute();
    const int memberId = 7734;
    ChangeMemberTransaction cmt(empId, memberId, 9.42);
    cmt.Execute();
    const Date payDate(11, 9, 2001);
    TimeCardTransaction tct(payDate, 8.0, empId);
    tct.Execute();
    PaydayTransaction pt(payDate);
    pt.Execute();
    PayCheck* pc = pt.GetPaycheck(empId);
    CHECK_TRUE(pc);
    CHECK_TRUE(pc->GetPayPeriodEndDate() == payDate);
    DOUBLES_EQUAL(8*15.24, pc->GetGrossPay(), 0.01);
    CHECK_TRUE("Hold" == pc->GetField("Disposition"));
    DOUBLES_EQUAL(9.42, pc->GetDeductions(), 0.01);
    DOUBLES_EQUAL((8*15.24)-9.42, pc->GetNetPay(), 0.01);
}

TEST(PayrollTest, TestCommissionedUnionMemberDues)
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
    CHECK_TRUE(pc);
    CHECK_TRUE(pc->GetPayPeriodEndDate() == payDate);
    DOUBLES_EQUAL(2500.00, pc->GetGrossPay(), 0.01);
    CHECK_TRUE("Hold" == pc->GetField("Disposition"));
    DOUBLES_EQUAL(2*9.42, pc->GetDeductions(), 0.01);
    DOUBLES_EQUAL(2500.0 - (2 * 9.42), pc->GetNetPay(), 0.01);
}

TEST(PayrollTest, TestHourlyUnionMemberServiceCharge)
{
    const int empId = 1;
    AddHourlyEmployee t(empId, "Bill", "Home", 15.24);
    t.Execute();
    const int memberId = 7734;
    ChangeMemberTransaction cmt(empId, memberId, 9.42);
    cmt.Execute();
    const Date payDate(11, 9, 2001);
    ServiceChargeTransaction sct(memberId, payDate, 19.42);
    sct.Execute();
    TimeCardTransaction tct(payDate, 8.0, empId);
    tct.Execute();
    PaydayTransaction pt(payDate);
    pt.Execute();
    PayCheck* pc = pt.GetPaycheck(empId);
    CHECK_TRUE(pc);
    CHECK_TRUE(pc->GetPayPeriodEndDate() == payDate);
    DOUBLES_EQUAL(8*15.24, pc->GetGrossPay(), 0.01);
    CHECK_TRUE("Hold" == pc->GetField("Disposition"));
    DOUBLES_EQUAL(9.42 + 19.42, pc->GetDeductions(), 0.01);
    DOUBLES_EQUAL((8*15.24)-(9.42 + 19.42), pc->GetNetPay(), 0.01);
}

TEST(PayrollTest, TestServiceChargesSpanningMultiplePayPeriods)
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
    CHECK_TRUE(pc);
    CHECK_TRUE(pc->GetPayPeriodEndDate() == payDate);
    DOUBLES_EQUAL(8*15.24, pc->GetGrossPay(), 0.01);
    CHECK_TRUE("Hold" == pc->GetField("Disposition"));
    DOUBLES_EQUAL(9.42 + 19.42, pc->GetDeductions(), 0.01);
    DOUBLES_EQUAL((8*15.24)-(9.42 + 19.42), pc->GetNetPay(), 0.01);
}
