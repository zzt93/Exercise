MessageLength		equ	9
BootMessage:		db	"Booting  " ; 9字节, 不够则用空格补齐. 序号 0
Message1		db	"LDR Ready" ; 9字节, 不够则用空格补齐. 序号 1
Message2		db	"No LOADER" ; 9字节, 不够则用空格补齐. 序号 2
Message3		db	"Loading K" ; 9字节, 不够则用空格补齐. 序号 3
Message4		db	"K Ready. " ; 9字节, 不够则用空格补齐. 序号 4
Message5		db	"NO KERNEL" ; 9字节, 不够则用空格补齐. 序号 5	


;----------------------------------------------------------------------------
; 函数名: DispStr
;----------------------------------------------------------------------------
; 作用:
;	显示一个字符串, 函数开始时 dh 中应该是字符串序号(0-based)

DispBootStr:
	mov	ax, MessageLength
	mul	dh
	add	ax, BootMessage
	mov	bp, ax			; `.
	mov	ax, ds			;  | ES:BP = 串地址
	mov	es, ax			; /
	mov	cx, MessageLength	; CX = 串长度
	mov	ax, 01301h		; AH = 13,  AL = 01h
	mov	bx, 0007h		; 页号为0(BH = 0) 黑底白字(BL = 07h)
	mov	dl, 0
	int	10h			; int 10h
	ret
