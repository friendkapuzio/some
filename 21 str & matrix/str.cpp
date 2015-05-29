#include <iostream>

int main()
{
	char * data = "f forb w roi ";
	char second[100] = { 0 };
	char first=0;
	_asm
	{
        cld
		mov edi, data
		mov esi, edi
		mov ecx, 0ffffffffh
		xor al, al
		repne scasb
		sub edi, esi
		dec edi
		mov ecx, edi
		lea edi, second
		mov edx, 0
	find:
		lodsb
		dec esi
		push edi
		mov edi, esi
		inc edi
		push ecx
		repnz scasb
		pop ecx
		pop edi
		jnz step
		movsb
		inc edx
		jmp e
	step:
		mov ebx, edi
		lea edi, second
		push ecx
		mov ecx, edx
		repnz scasb
		pop ecx
		jnz ex
		mov edi, ebx
		inc esi
	e:
		loop find
		jmp notfound
	ex:
		lea edi, first
		stosb
	notfound:
	}
	std::cout << first;
	system("pause");
	return 0;
}