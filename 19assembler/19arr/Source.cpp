#include <iostream>

int main()
{
	int amount, max[5];
	std::cin >> amount;
	int * numbers = new int[amount];
	for (int i = 0; i < amount; ++i)
		std::cin >> numbers[i];
	_asm
	{
		mov eax, numbers
		mov ecx, amount
		mov max[0], 7FFFFFFFh
		mov max[4], 7FFFFFFFh
		mov max[8], 80000000h
		mov max[12], 80000000h
		mov max[16], 80000000h
	finding :
		mov ebx, [eax + ecx * 4 - 4]
		cmp max[16], ebx
		jg greater
			mov edx, max[12]
			mov max[8], edx
			mov edx, max[16]
			mov max[12], edx
			mov max[16], ebx
			jmp endgr
		greater:
			cmp max[12], ebx
			jg greater2
			mov edx, max[12]
			mov max[8], edx
			mov max[12], ebx
			jmp endgr
		greater2:
			cmp max[8], ebx
			jg endgr
			mov max[8], ebx
		endgr:
			cmp max[0], ebx
			jl nextstep
			mov edx, max[0]
			mov max[4], edx
			mov max[0], ebx
			jmp end
		nextstep :
			cmp max[4], ebx
			jle end
			mov max[4], ebx
	end:
		loop finding
			mov eax, max[0]
			imul eax, max[4]
			imul eax, max[16]
			mov ebx, max[8]
			imul ebx, max[12]
			imul ebx, max[16]
			cmp eax, ebx
			jle ex
			mov eax, max[0]
			mov max[8], eax
			mov eax, max[4]
			mov max[12], eax
	ex:
	}
	for (int i = 2; i < 5; ++i)
		std::cout << max[i]<<" ";
	system("pause");
	return 0;
}