#include "stdafx.h"
#include "CppUnitTest.h"
#include "..\SimpleCalculator\MathOPS.cpp"
#include "..\SimpleCalculator\MathHistory.cpp"
#include "..\SimpleCalculator\Buttons.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

bool compare_double(long double a, long double b, long double epsilon = 0.0000'0000'0001) {
	return abs(a - b) < epsilon;
}

namespace CalculatorTest
{		
	TEST_CLASS(MathOPS)
	{
	public:
		::MathOPS test;
		
		TEST_METHOD(Add)
		{
			Assert::IsTrue(compare_double(3, test.add(L"1", L"2")));
		}
		
		TEST_METHOD(Add_negative)
		{
			Assert::IsTrue(compare_double(-3, test.add(L"-1", L"-2")));
		}

		TEST_METHOD(Add_float)
		{
			Assert::IsTrue(compare_double(3.3, test.add(L"1.1", L"2.2")));
		}

		TEST_METHOD(Sub)
		{
			Assert::IsTrue(compare_double(-1, test.sub(L"1", L"2")));
		}
		
		TEST_METHOD(Sub_negative)
		{
			Assert::IsTrue(compare_double(1,	test.sub(L"-1", L"-2")));
		}

		TEST_METHOD(Sub_float)
		{
			Assert::IsTrue(compare_double(-1.1, test.sub(L"1.1", L"2.2")));
		}

		TEST_METHOD(Mult)
		{
			Assert::IsTrue(compare_double(2,	test.mult(L"1", L"2")));
		}

		TEST_METHOD(Mult_negative)
		{
			Assert::IsTrue(compare_double(2,	test.mult(L"-1", L"-2")));
		}

		TEST_METHOD(Mult_float)
		{
			Assert::IsTrue(compare_double(2.42, test.mult(L"1.1", L"2.2")));
		}

		TEST_METHOD(Div)
		{
			Assert::IsTrue(compare_double(0.5,	test.div(L"1", L"2")));
		}

		TEST_METHOD(Div_negative)
		{
			Assert::IsTrue(compare_double(0.5,	test.div(L"-1", L"-2")));
		}

		TEST_METHOD(Div_float)
		{
			Assert::IsTrue(compare_double(0.5,	test.div(L"1.1", L"2.2")));
		}


		TEST_METHOD(Perc_decimal)
		{
			CString a{ "100" }, b{ "10" };
			std::vector<const CString*> vec{ &b, &a };
			Assert::IsTrue(compare_double(10, test.perc(vec)));
		}

		TEST_METHOD(Perc_float)
		{
			CString a{ "1" }, b{ "0.001" };
			std::vector<const CString*> vec{ &b, &a };
			Assert::IsTrue(compare_double(0.0000'1, test.perc(vec)));
		}

		TEST_METHOD(Perc_zero)
		{
			CString a{ "1" }, b{ "0" };
			std::vector<const CString*> vec{ &b, &a };
			Assert::IsTrue(compare_double(0, test.perc(vec)));
		}

		TEST_METHOD(Reciproc)
		{
			CString a{ "7" };
			std::vector<const CString*> vec{ &a };
			Assert::IsTrue(compare_double(0.1428'5714'2857'1428, test.reciproc(vec)));
		}

		TEST_METHOD(Reciproc_zero)
		{
			CString a{ "0" };
			std::vector<const CString*> vec{ &a };
			Assert::ExpectException<std::exception>([&]() { test.reciproc(vec); });
		}

		TEST_METHOD(Sqrt)
		{
			CString a{ "2" };
			std::vector<const CString*> vec{ &a };
			Assert::IsTrue(compare_double(1.4142'1356'2373'095, test.sqrt(vec)));
		}

		TEST_METHOD(Sqrt_negative)
		{
			CString a{ "-4" };
			std::vector<const CString*> vec{ &a };
			Assert::ExpectException<std::exception>([&]() { test.sqrt(vec); });
		}

		TEST_METHOD(Neg)
		{
			CString a{ "1" };
			std::vector<const CString*> vec{ &a };
			Assert::IsTrue(compare_double(-1, test.neg(vec)));
		}

		TEST_METHOD(Neg_zero)
		{
			CString a{ "0" };
			std::vector<const CString*> vec{ &a };
			Assert::IsTrue(compare_double(0, test.neg(vec)));
		}

		TEST_METHOD(Neg_negative)
		{
			CString a{ "-4" };
			std::vector<const CString*> vec{ &a };
			Assert::IsTrue(compare_double(4, test.neg(vec)));
		}
	};

	TEST_CLASS(History) {
		::MathOPS d;
		::History test{ nullptr };

		TEST_METHOD(add_number) {
			test._history = "";
			test.Add(CString("0"));
			Assert::IsTrue(test._history == L"0");
		}

		TEST_METHOD(add_arithmetic_op_to_empty_history) {
			test._history = "";
			test.Add(&AButton(L"+", [&](const CString& a, const CString& b) { return d.add(a, b); }));
			Assert::IsTrue(test._history == L"");
		}

		TEST_METHOD(add_arithmetic_op_to_number) {
			test._history = "0";
			test.Add(&AButton(L"+", [&](const CString& a, const CString& b) { return d.add(a, b); }));
			Assert::IsTrue(test._history == L"0 +");
		}

		TEST_METHOD(replace_arithmetic_op) {
			test._history = "0 +";
			test.Add(&AButton(L"-", [&](const CString& a, const CString& b) { return d.add(a, b); }));
			Assert::IsTrue(test._history == L"0 -");
		}

		TEST_METHOD(add_replacing_op_to_arithmetic_op) {
			test._history = "0 -";
			test.Add(&RButton(1, L"sqrt", [&](std::vector<const CString*> a) { return d.sqrt(a); }), CString("4"));
			Assert::IsTrue(test._history == L"0 - sqrt(4)");
		}

		TEST_METHOD(add_second_replacing_op) {
			test._history = "0 - sqrt(4)";
			test.Add(&RButton(1, L"reciproc", [&](std::vector<const CString*> a) { return d.reciproc(a); }), CString());
			Assert::IsTrue(test._history == L"0 - reciproc(sqrt(4))");
		}

		TEST_METHOD(replace_last_with_number) {
			test._history = "0 - reciproc(sqrt(4))";
			test.Add(CString("0"));
			Assert::IsTrue(test._history == L"0 - 0");
		}

		TEST_METHOD(replace_last_with_replacing_op) {
			test._history = "0 - 0";
			test.Add(&RButton(1, L"reciproc", [&](std::vector<const CString*> a) { return d.reciproc(a); }), CString("4"));
			Assert::IsTrue(test._history == L"0 - reciproc(4)");
		}

		TEST_METHOD(add_replacing_op_to_empty_history) {
			test._history = "";
			test.Add(&RButton(1, L"reciproc", [&](std::vector<const CString*> a) { return d.reciproc(a); }), CString("4"));
			Assert::IsTrue(test._history == L"reciproc(4)");
		}

		TEST_METHOD(add_arithmetic_op_to_replacing_op) {
			test._history = "reciproc(4)";
			test.Add(&AButton(L"+", [&](const CString& a, const CString& b) { return d.add(a, b); }));
			Assert::IsTrue(test._history == L"reciproc(4) +");
		}

		TEST_METHOD(add_replacing_op_to_replacing_op) {
			test._history = "reciproc(4)";
			test.Add(&RButton(1, L"sqrt", [&](std::vector<const CString*> a) { return d.sqrt(a); }), CString());
			Assert::IsTrue(test._history == L"sqrt(reciproc(4))");
		}
	};

	TEST_CLASS(Buttons) {
		::MathOPS math;
		::History test{ nullptr };

		TEST_METHOD(add_special_button) {
			test._history = "";
			test.Add(&RButton(1, L"sqrt", [&](std::vector<const CString*> a) { return math.sqrt(a); },
				[&](CString& number) { test._history = L"special " + number; }), CString("4"));
			Assert::IsTrue(test._history == L"special 4");
		}

		TEST_METHOD(compute_special_button) {
			CString x = L"4";
			std::vector<const CString*> vec{ &x };
			test._history = "";
			test._history.Format(L"%.16g", math.compute(&RButton(false, L"sqrt", [&](std::vector<const CString*> a) { return math.sqrt(a); } ), vec));
			Assert::IsTrue(test._history == L"2");
		}
	};
}