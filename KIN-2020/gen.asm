.586
.model flat, stdcall
includelib kernel32.lib
includelib ../Debug/MASMStaticLib.lib

STD_OUTPUT			EQU - 11 
ExitProcess			PROTO : DWORD 
GetStdHandle		PROTO : DWORD; 
WriteConsoleA		PROTO : DWORD, : DWORD, : DWORD, : DWORD, : DWORD 
SetConsoleTitleA	PROTO : DWORD  
byte_to_char			PROTO : BYTE , : DWORD 
_pow					PROTO : BYTE, : BYTE  
_abs					PROTO : BYTE  
__push					PROTO 
__pop					PROTO 

.const
literal8 SBYTE -0000010b
literal9 SBYTE 10b
literal10 SBYTE 1010b
literal11 SBYTE 0b

.data
 buffer BYTE 10 dup(0) 
consoleOutHandle	dword ? 
_0x SBYTE 0b
_0y SBYTE 0b

.code
main PROC
invoke	GetStdHandle, STD_OUTPUT 
mov	consoleOutHandle, eax
mov al, literal8
call __push
call __pop
 mov _0y, al
mov al, _0y
call __push
mov al, literal9
call __push
call __pop
push eax
call __pop
push eax
call _pow
call __push
mov al, literal10
call __push
call __pop
 mov bl, al
call __pop
add al, bl
call __push
call __pop
 mov _0x, al
mov al, _0x
call __push
call __pop
invoke	byte_to_char, al, offset buffer
invoke WriteConsoleA, consoleOutHandle, offset buffer, sizeof buffer, 0, 0
mov al, _0y
call __push
call __pop
invoke	byte_to_char, al, offset buffer
invoke WriteConsoleA, consoleOutHandle, offset buffer, sizeof buffer, 0, 0
mov al, literal11
call __push
call __pop
ret
main ENDP
end
