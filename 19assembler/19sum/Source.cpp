#include <iostream>
int main()
{
	int n;
	double x, y, z, rez;
	std::cin >> x >> y >> z >> n;
	__asm
	{

		mov ecx, n
		finit
		fld1 //numerator
		fld1 //total, rez
		fldz //sum
		fld1 //part of numerator
		fld1 //z
		cmp ecx, 0
		jne calculation
		inc ecx
		fld1
	calculation:
		fmul z
		fxch
		fmul x
		fmul y
		fmul st(4), st
		fxch
		fld st(0)
		fdivr st, st(5)
		faddp st(3), st
		fxch st(2)
		fmul st(3), st
		fxch st(2)
		loop calculation
		fxch st(3)
		fst rez
	}
	std::cout << rez;
	system("pause");
	return 0;
}