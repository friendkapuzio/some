#include <iostream>

static bool prime[1000000000];

int main()
{
	int number, ind = 2;
	std::cin >> number;
	//bool * prime= new bool[number];
	__asm
	{
		cmp number, 2
			jg notwo
			mov eax, 0
			jmp end
		notwo :


		mov ecx, number
			sub ecx, 2//counter
			lea edi, prime//mov edi, prime // boolArr
			add edi, 2
			mov esi, 2//ind
			mov eax, 0//amount of prime numbers

	findNotDeleted :

		cmp [edi], 1
			jz nextStep

			inc eax
			lea edx, prime//mov edx, prime
			imul ebx, esi, 2
			add edx, ebx
		deletion :
			cmp ebx, number
			jge nextStep
				mov[edx], 1
				add edx, esi
				add ebx, esi
		jmp deletion

		nextStep:
			inc edi
			inc esi
	loop findNotDeleted
	
		end :
		mov number, eax
	}
	std::cout << (int)number;
	system("pause");
	return 0;
}