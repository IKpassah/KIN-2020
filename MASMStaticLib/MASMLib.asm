.586
.model flat, stdcall
includelib kernel32.lib

.const
byte_for_end word 11111111b
.data
stack_size		dword 0
stack	BYTE 100 dup(0)
buffconStr byte 255 dup(0)

.code
__push PROC
.if stack_size >= 100
	jmp end__push
.endif
	mov	esi,  offset stack
	add	esi,  stack_size
	mov [esi], al
	inc stack_size
end__push:
	ret
__push ENDP

__pop PROC
.if stack_size == 0
	jmp endpop
.endif
	dec stack_size
	mov	esi,  offset stack
	add	esi,  stack_size
	mov al, [esi]
endpop:
	ret
__pop ENDP

_pow PROC a: sbyte, b: sbyte
	.if		b == 0b
		mov		al, 1b
		jmp		endproc
	.elseif	b < 0b
		jmp		endproc
	.elseif	b == 1b
		jmp		endproc
	.endif
	movsx		ecx, b
	sub		ecx, 1
	mov		al, a
	mov		bl, a
	cycle:						
		imul bl						; al домножается на a -> записывается в ax
		jc overflow
		loop	cycle
	jmp endproc
overflow:
	mov eax, 0
endproc:
	ret 
_pow ENDP

_abs PROC a: sbyte
	mov		al, a
	.if		a >= 0b
		jmp		endproc
	.endif
	neg		al	
endproc:
	ret 
_abs ENDP

byte_to_char PROC b: sbyte, buff: dword
	mov bl, 10000000b
	mov bh, b
	mov edi, buff
	.if b < 0
		neg bh
		add bh, bl
	.endif
	mov ecx, 8
	cycle:
		test bl, bh
		jz zero
		jnz nzero
	zero:
		mov al, '0'
		mov [edi], al
		jmp afterzero
	nzero:
		mov al, '1'
		mov [edi], al
	afterzero:
		inc	edi	
		shr bl, 1
	loop cycle
	mov al, 'b'
	mov [edi], al
	ret
byte_to_char ENDP

fill_str PROC receiver: dword, source : dword
	mov edi, receiver
	mov esi, source
	mov ecx, 2
	cyclef:
		mov al, [esi]
		.if al == 0
			jmp cyclefend
		.else 
			mov ecx, 2
		.endif
		mov [edi], al
		inc esi
		inc edi
	loop cyclef
cyclefend:
mov al, 0b
mov [edi], al
mov eax, receiver
	ret
fill_str ENDP

find_len PROC
mov esi, eax
mov edx, 0
mov ecx, 2 
cyclerff: 
	mov bl, [esi] 
	.if bl == 0 
	jmp cycleffend 
	.else 
	mov ecx, 2 
	.endif 
	inc edx 
	inc esi 
loop cyclerff 
cycleffend:
ret
find_len ENDP

_strcat PROC str1: dword, str2: dword
	mov edi, offset buffconStr
	mov esi, str1
	mov ecx, 2
	cycle1:
		mov al, [esi]
		.if al == 0
			jmp cycle1end
		.else 
			mov ecx, 2
		.endif
		mov [edi], al
		inc esi
		inc edi
	loop cycle1
cycle1end:
	mov esi, str2
	mov ecx, 2
	cycle2:
		mov al, [esi]
		.if al == 0
			jmp cycle2end
		.else 
			mov ecx, 2
		.endif
		mov [edi], al
		inc esi
		inc edi
	loop cycle2
cycle2end:
	mov al, 0
	mov [edi], al
	mov eax, offset buffconStr
	ret
_strcat ENDP

end

