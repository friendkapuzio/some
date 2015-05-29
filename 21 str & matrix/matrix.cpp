#include <iostream>


int main()
{
	int n, m;
	n = 4;
	m = 5;
	int matrix[4][5] =  { { 1, 2, 3, 4, 5 },
				  		  { 1, 2, 3, 4, 5 },
						  { 1, 2, 3, 4, 5 },
						  { 1, 2, 3, 4, 5 } };
	_asm
	{
		mov ecx, n
		cmp ecx, m
		jle ngr
		mov ecx, m
	ngr:
		imul edi, ecx, 4
		mov eax, edi
		mul m
		mov esi, eax
		add eax, edi
		mov ebx, edi
		imul edi, m, 4
		add esi, edi
		sub esi, ebx
		sub esi,4
		lea ebx, matrix
	changing:
		sub eax, edi
		sub eax, 4
		sub esi, edi
		add esi, 4
		mov edx, [ebx][eax]
		push edx
		mov edx, [ebx][esi]
		mov [ebx][eax], edx
		pop edx
		mov [ebx][esi], edx
	loop changing
	}
	for (int i = 0; i < n; ++i)
	{
		for (int j = 0; j < m; ++j)
			std::cout << matrix[i][j]<<" ";
		std::cout << std::endl;
	}
	system("pause");
	return 0;
}