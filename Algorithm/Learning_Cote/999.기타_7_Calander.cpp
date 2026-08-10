#if 1

#include <iostream>
#include <vector>

using namespace std;




// 윤년 여부 공식은 하단의 IsLeapYear 함수 참조

#define _400_years_to_days 146097		// 365 * 400	+ 100(4의배수)		- 4(100의 배수)	+ 1(400의 배수)
#define _100_years_to_days 36524		// 365 * 100	+ 25(4의 배수)		- 1(100의 배수)
#define _4_years_to_days	1461		// 365 * 4		+ 1(4의 배수)
#define _1_year_to_days		365			// 365


class Calander
{
private:
	inline static vector<int> MonthToDays =
	{ 0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334, 365};
	inline static vector<int> MonthToDays_LeapYear =
	{ 0, 31, 60, 91, 121, 152, 182, 213, 244, 274, 305, 335, 366};



public:

#if 0
	/*---------------------------------------------------------------
		아래 방법은 0년 1월 1일 을 1일 로 보는 계산법이었는데, 오류가 있었다.
		이렇게 할시, 1년 1월 1일 때, 
		year to Days 에서는 year 가 현재의 year 에 맞춰야 하고 
		( 경과된 year 인 year - 1가 아닌, 현재를 포함한 year)
		month to Days 에서는 현재의 year 를 기준으로 윤년 계산된 month 에 맞춰야 한다.

		따라서 싱크가 안맞게 되고, 오류가 발생한다. 
		year to days 는 경과된 year 인 year - 1 을 기준으로 days를 추출해야 하고,
		motn to days 에서는 현재의 year 가 윤년인지, 평년인지 알아야 하기에, year 를 기준으로 
		윤년 평년을 구분해야 한다.
		1년 1월 1일 을 1일 로 봐야 하며, 2년 1월 1일 을 366일 로 봐야 코드가 맞다.


		추가로, 
		위로 가정할시, 400 / 100 / 4 / 1 의 경계점의 시작일을 
		윤년(400, 100, 4, 0) 으로 보기 때문에, days To Calander 함수에서
		블록의 시작을 윤년으로 봐야 하기에, 코드를 짜기도 까다롭다.
	---------------------------------------------------------------*/


	Calander(int InYear, int InMonth, int InDay)
		: year(InYear), month(InMonth), day(InDay)
	{
		
		days = year * 365 
			+ (year / 4 - year / 100 + year / 400); // 윤년인 연도 수
		


		// 윤년
		if (IsLeapYear(year))
		{
			days += MothToDays_LeapYear[InMonth - 1];
		}
		else
		{
			days += MonthToDays[InMonth - 1];
		}

		days += InDay;
	}

	Calander(int InDays) : days(InDays)
	{
		int _400 = (InDays - 1) / _400_years_to_days;
		year = _400 * 400;
		InDays -= _400 * _400_years_to_days;


		if (InDays > _100_years_to_days + 1) // + 1 : year % 400 == 0
		{
			year += 100;
			InDays -= (_100_years_to_days + 1);

			int _100 = (InDays - 1) / _100_years_to_days;
			year += _100 * 100;
			InDays -= _100 * _100_years_to_days;
		}

		if (InDays > _4_years_to_days - 1)	// -1 : year % 100 == 0
		{
			year += 4;
			InDays -= (_4_years_to_days - 1);

			int _4 = (InDays - 1) / _4_years_to_days;
			year += _4 * 4;
			InDays -= _4 * _4_years_to_days;
		}

		if (InDays > _1_year_to_days + 1)	// + 1 : year % 4 == 0
		{
			year += 1;
			InDays -= (_1_year_to_days + 1);

			int _1 = (InDays - 1) / _1_year_to_days;
			year += _1;
			InDays -= _1 * _1_year_to_days;
		}




		// 윤년
		if (IsLeapYear(year))
		{
			for (int i = 1; i <= 12; i++)
			{
				if (InDays <= MothToDays_LeapYear[i])
				{
					month = i;
					InDays -= MothToDays_LeapYear[i - 1];
					break;
				}
			}
		}
		else
		{
			for (int i = 1; i <= 12; i++)
			{
				if (InDays <= MonthToDays[i])
				{
					month = i;
					InDays -= MonthToDays[i - 1];
					break;
				}
			}
		}

		day = InDays;
	}
#else



	public:
		Calander(int InYear, int InMonth, int InDay) : year(InYear), month(InMonth), day(InDay)
		{
			InYear--;
			days = InYear * 365
				+ InYear / 4 - InYear / 100 + InYear / 400;

			InMonth--;
			if (IsLeapYear(year))
			{
				days += MonthToDays_LeapYear[InMonth];
			}
			else
			{
				days += MonthToDays[InMonth];
			}
			
			days += InDay;
		}
		
		Calander(int InDays) : days(InDays)
		{
			year = 1;	// 1년 1월 1일 을 1일 로 가정하기에, 기본 1 할당

			int _400 = (InDays - 1) / _400_years_to_days;
			year += _400 * 400;
			InDays -= _400 * _400_years_to_days;
			
			int _100 = (InDays - 1) / _100_years_to_days;
			if (_100 == 4) _100 = 3;	
			// _100 블록의 4개의 블록 중 마지막 블록은 year % 400 == 0 을 포함하는 블록이기에, 윤년 1개를 더 포함함.
			// 따라서 위처럼 3블록만 쓰고, 나머지는 _4 블록에서 처리
			year += _100 * 100;
			InDays -= _100 * _100_years_to_days;

			int _4 = (InDays - 1) / _4_years_to_days;
			if (_4 == 25) _4 = 24;
			// _4블록의 25개 블록 중 마지막 블록은 year % 100 == 0 을 포함하는 블록이기에, 윤년 1개를 빼야 함
			// 따라서 위처럼 블록 24개만 쓰고, 나머지는 _1 블록에서 처리
			year += _4 * 4;
			InDays -= _4 * _4_years_to_days;

			int _1 = (InDays - 1) / _1_year_to_days;
			if (_1 == 4) _1 = 3;
			// _1블록의 4개 블록 중 마지막 블록은 year % 4 == 0 을 포함하는 블록이기에, 윤년 1개를 더 포함함.
			// 따라서 위처럼 블록 3개만 쓰고, 나머지는 Month + Day 에서 처리
			year += _1;
			InDays -= _1 * _1_year_to_days;

			// ※ _1블록 예시로 추가로 더 설명해보면, 1년 1월 1일이 1일, 2년 1월 1일 이 366일 로 가정했기에,
			//	 (366(2년.1월.1일) - 1) / 365 == 1, ( 731(3년.1월.1일) - 1) / 365 == 2,
			//   (1095(4년.1월.1일) - 1) / 365 == 3. 이다. 1년, 2년 3년 은 평년이기에, _1_year_to_days 로 계산해도
			//   문제 없음. 하지만 1461(5년.1월.1일) 의 경우, 4년 이 윤년이기에, _1_year_to_days 로 계산할 수 없음.
			//   따라서 위처럼 처리.
			//   위처럼 1년 1월 1일 을 1일, 2년 1월 1일 을 366일로 보면, 블록들의 마지막 블록이 나머지 블록들과 다른 블록
			//   이 되기에, 따로 처리하기 수월함. 반대로 0년.0월.1일을 1일, 1년.1월.1일 을 367 일로 보면, 블록들의 첫블록이
			//   나머지 블록들과 다른 블록이 되기에, 처리하기 까다로움

			
			if (IsLeapYear(year))
			{
				for (int i = 1; i <= 12; i++)
				{
					if (InDays <= MonthToDays_LeapYear[i])
					{
						month = i;
						InDays -= MonthToDays_LeapYear[i - 1];
						break;
					}
				}
			}
			else
			{
				for (int i = 1; i <= 12; i++)
				{
					if (InDays <= MonthToDays[i])
					{
						month = i;
						InDays -= MonthToDays[i - 1];
						break;
					}
				}
			}

			day = InDays;
		}


#endif

private:
	bool IsLeapYear(int year)
	{
		return (year % 4 == 0 && year % 100 != 0) || year % 400 == 0;
	}

public:
	inline void Print()
	{
		printf("Year(%d), Month(%d), Day(%d), Days(%d)\n", year, month, day, days);
	}


public:
	int year;
	int month;
	int day;

	int days;
};





void main()
{
	printf("999.기타_7_Calander.cpp\n\n\n");

	Calander calander(2026, 6, 26);
	calander.Print();

	Calander calander2(calander.days);
	calander2.Print();



	Calander c2(2001, 12, 31);
	c2.Print();

	Calander c3(c2.days);
	c3.Print();

	Calander c4(2004, 12, 31);
	c4.Print();

	Calander c5(c4.days);
	c5.Print();

	Calander c6(2099, 12, 31);
	c6.Print();

	Calander c7(c6.days);
	c7.Print();

	Calander c8(2100, 12, 31);
	c8.Print();

	Calander c9(c8.days);
	c9.Print();

	Calander ca1(2100, 1, 1);
	ca1.Print();

	Calander ca2(ca1.days);
	ca2.Print();


	printf("\n=== 경계 검증 ===\n");

	// 케이스 1: 400년 주기의 경계선 (400년 차의 마지막 날)
	Calander test1(400, 12, 31);
	test1.Print();
	Calander test1_rev(test1.days);
	test1_rev.Print();

	// 케이스 2: 100년 주기의 경계선 (100년 차의 마지막 날)
	Calander test2(100, 12, 31);
	test2.Print();
	Calander test2_rev(test2.days);
	test2_rev.Print();

	// 케이스 3: 4년 주기의 경계선
	Calander test3(4, 12, 31);
	test3.Print();
	Calander test3_rev(test3.days);
	test3_rev.Print();


	printf("\n=== 경계 + 1 구간 검증 ===\n");

	// 케이스 A: 100년 차가 끝난 직후, 101년 차의 첫 번째 날
	Calander break1(101, 1, 1);
	break1.Print();
	Calander break1_rev(break1.days);
	break1_rev.Print();

	// 케이스 B: 200년 차가 끝난 직후, 201년 차의 첫 번째 날
	Calander break2(201, 1, 1);
	break2.Print();
	Calander break2_rev(break2.days);
	break2_rev.Print();

	Calander shit(1, 1, 1);
	shit.Print();

	Calander shit2(shit.days);
	shit2.Print();
}











#endif