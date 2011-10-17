%include	"loader.inc"
	
org	LoaderPhyAddr

jmp	LABEL_START	

%include	"fat12hdr.inc"
%include	"protect.inc"	
%include	"disp.inc"
%include	"lib.inc"	
[BITS 16]
PageDirBase		equ		100000h
PageTblBase		equ		101000h	

LABEL_GDT:		Descriptor 	0, 0, 0
	;; 0 - 4G excutable
LABEL_DESC_FLAT_C:	Descriptor 	0, 0fffffh, DA_CR|DA_32|DA_LIMIT_4K
	;; 0 - 4G rw
LABEL_DESC_FLAT_RW:	Descriptor 	0, 0fffffh, DA_DRW|DA_32|DA_LIMIT_4K
	;; video memory
LABEL_DESC_VIDEO:	Descriptor 	0b8000h, 0ffffh, DA_DRW|DA_DPL3
LABEL_DESC_PAGE_DIR:	Descriptor	PageDirBase, 4095, DA_DRW
LABEL_DESC_PAGE_TBL:	Descriptor	PageTblBase, 4096*8-1, DA_DRW

GdtLen			equ		$ - LABEL_GDT
GdtPtr			dw		GdtLen - 1		  	;GDT LIMIT
	                dd		LABEL_GDT 			;!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!GDT BASE
SelectorFlatC		equ		LABEL_DESC_FLAT_C - LABEL_GDT
SelectorFlatRW		equ		LABEL_DESC_FLAT_RW - LABEL_GDT
SelectorVideo		equ	 	LABEL_DESC_VIDEO - LABEL_GDT + SA_RPL3	
SelectorPageDir		equ		LABEL_DESC_PAGE_DIR - LABEL_GDT
SelectorPageTbl		equ		LABEL_DESC_PAGE_TBL - LABEL_GDT	
	
SectorNo		dw		0
N 			dw		NRootEntSec ;counter
KernelFileName		db		"KERNEL  BIN"	
odd 			db 		0
	
BaseofStack		equ		LoaderBase:LoaderOffset
KernelEntryPhyAddr	equ		0x30400	


_szPMMessage:			db	"In Protect Mode now. ^-^", 0Ah, 0Ah, 0	; 进入保护模式后显示此字符串
_szMemChkTitle:			db	"BaseAddrL BaseAddrH LengthLow LengthHigh   Type", 0Ah, 0	; 进入保护模式后显示此字符串
_szRAMSize			db	"RAM size:", 0
_szReturn			db	0Ah, 0

_dwDispPos:			dd	(80 * 6 + 0) * 2	; 屏幕第 6 行, 第 0 列。
_dwMemSize:			dd	0
	
_ARDStruct:			; Address Range Descriptor Structure
	_dwBaseAddrLow:		dd	0
	_dwBaseAddrHigh:	dd	0
	_dwLengthLow:		dd	0
	_dwLengthHigh:		dd	0
	_dwType:		dd	0

dwDispPos	equ	_dwDispPos
szReturn	equ	_szReturn	

	
_MemChkBuf:	times	256	db	0
_dwMemNum:	dw	0
	
LABEL_START:

	mov 	ax, cs
	mov	ds, ax
	mov	ss, ax
	mov	es, ax
	mov 	sp, BaseofStack
	
	mov	ebx, 0h
	mov	di, _MemChkBuf
	mov dword [_dwMemNum], 0
.loop:
	mov	eax, 0000e820h
	mov	ecx, 20
	mov	edx, 0534d4150h
	int	15h
	jc	.MemChk_Fail
	add	di, 20
	inc	dword [_dwMemNum]
	cmp	ebx, 0
	jne	.loop
	jmp 	.MemChk_OK
.MemChk_Fail:
	mov	dword [_dwMemNum], 0
.MemChk_OK:

	mov	dh, 3		;"loading k"
	call	DispBootStr

	xor ah, ah
	xor dl, dl
	int 13h			;reset floppy

	mov ax, KernelBase
	mov es, ax
	mov bx, KernelOffset	;es:bx = KernelBase:KernelOffset
	mov word [SectorNo], RootEntStart
	cld
	mov si, KernelFileName	;ds:si = "kernel bin"
	mov di, KernelOffset	;es:di = dirent

.sector_loop:
	cmp word [N], 0
	jz .end_sector_loop
	dec word [N]
	mov cl, 1
	mov ax, [SectorNo]
	call ReadSector
	mov dx, 10h		;16 records per sector
.record_loop:
	cmp dx, 0
	jz .end_record_loop
	dec dx
	mov cx, 11		;file name len: 11
.char_loop:
	cmp cx, 0
	jz .found
	dec cx
	lodsb
	cmp al, byte [es:di] 	;compare ds:si and es:di
	jz .char_go_on
.end_char_loop:
	and di, 0ffe0h
	add di, 20h
	mov si, KernelFileName
	jmp .record_loop	;load next record and continue
.char_go_on:
	inc di
	jmp .char_loop
.end_record_loop:
	add word [SectorNo], 1
	jmp .sector_loop
.end_sector_loop:

	mov dh, 5		;"No KERNEL"
	call DispBootStr
	jmp $

.found:			
	and di, 0ffe0h
	add di, 01ah
	mov cx, word [es:di]
	push cx				;save relative sector #
	add cx, delta
	mov ax, KernelBase
	mov es, ax
	mov bx, KernelOffset		;es:bx = destiny
	mov ax, cx			;ax = abs sector #
.goon_reading_file:
	push	ax			; `.
	push	bx			;  |
	mov	ah, 0Eh			;  | 每读一个扇区就在 "Booting  " 后面
	mov	al, '.'			;  | 打一个点, 形成这样的效果:
	mov	bl, 0Fh			;  | Booting ......
	int	10h			;  |
	pop	bx			;  |
	pop	ax			; /

	mov cl, 1
	call ReadSector
	pop ax				;find next sector if any
	call ReadFatEnt
	cmp ax, 0fffh
	jz .file_loaded
	push ax			 	;save relative sector #
	add ax, delta			;abs sector # 
	add bx, [BPB_BytsPerSec]	;es:bx = next destiny
	jmp .goon_reading_file
.file_loaded:
	mov dx, 03f2h
	mov al, 0
	out dx, al		;kill motor

	mov dh, 4		;"k ready"
	call DispBootStr

	lgdt [GdtPtr]		
	cli
	in al, 92h
	or al, 00000010b
	out 92h, al
	mov eax, cr0
	or eax, 1
	mov cr0, eax

	jmp dword SelectorFlatC:(LABEL_PM_START)


LABEL_PM_START:
[BITS 32]
	mov ax, SelectorVideo
	mov gs, ax
	mov ax, SelectorFlatRW
	mov ds, ax
	mov es, ax
	mov fs, ax
	mov ss, ax
	mov esp, TopofStack
	mov ah, 0fh
	mov al, 'P'
	mov [gs:((80*0+39)*2)], ax
	push _szMemChkTitle
	call DispStr
	add esp,4		;0x90457

	call DispMemSize
	call SetupPaging
	mov ax, SelectorFlatRW
	mov es, ax
	call InitKernel		;0x9046d
	jmp SelectorFlatC:KernelEntryPhyAddr
	jmp $
	
	
		
[BITS 16]
ReadSector:			;read %cl sectors from sector %ax to [%es:%bx]

	div byte [BPB_SecPerTrk]
	mov dl, cl
	mov cl, ah
	inc cl			;%cl:start sector
	mov ah, al
	shr ah, 1
	mov ch, ah		;%ch:cylinder
	and al, 01b
	mov dh, al		;%dh:head
	mov al, dl		;%al:number
	mov ah, 02h		;%ah = 02h
	mov dl, [BS_DrvNum]	;%dl disk num
.ReTry:
	int 13h
	jc .ReTry
	ret

ReadFatEnt:				;read sector %ax's FAT12 value
	push es
	push bx
	mov cx, KernelBase; `.
	sub cx, 0100h	;  | 在 BaseOfLoader 后面留出 4K 空间用于存放 FAT
	mov es, cx		; /
	mov byte [odd], 0
	mov bx, 3
	mul bx
	mov bx, 2
	div bx
	cmp dx, 0
	jz .even
	mov byte [odd], 1
.even:
	xor dx, dx
	div word [BPB_BytsPerSec]
	mov cl, 2
	push dx
	mov bx, 0 ; bx <- 0 于是, es:bx = (BaseOfLoader - 100):00
	add ax, SectorNoOfFAT1 ; 此句之后的 ax 就是 FATEntry 所在的扇区号	
	call ReadSector
	pop dx
	add bx, dx
	mov ax, [es:bx]
	cmp byte [odd], 1
	jnz .even_l
	shr ax, 4
.even_l:
	and ax, 0fffh

	pop bx
	pop es
	ret

[BITS 32]
SetupPaging:
	xor edx, edx
	mov eax, [_dwMemSize]
	mov ebx, 400000h
	div ebx
	mov ecx, eax
	test edx, edx
	jz .no_remainder
	inc ecx
.no_remainder:
	push ecx

	mov ax, SelectorPageDir
	mov es, ax
	mov ecx, 1024
	xor edi, edi
	xor eax, eax
	mov eax, PageTblBase|PG_P|PG_USU|PG_RWW
.1:
	stosd
	add eax, 4096
	loop .1


	mov ax, SelectorPageTbl
	mov es, ax
	pop eax,
	mov ebx, 1024
	mul ebx
	mov ecx, eax
	xor edi, edi
	xor eax, eax
	mov eax, PG_P|PG_USU|PG_RWW
.2:
	stosd
	add eax, 4096
	loop .2

	mov eax, PageDirBase
	mov cr3, eax
	mov eax, cr0
	or eax, 80000000h
	mov cr0, eax
	jmp short .3
.3:	nop
	ret


DispMemSize:
	push esi
	push edi
	push ecx

	mov esi, _MemChkBuf
	mov ecx, [_dwMemNum]

.loop:
	mov edx, 5
	mov edi, _ARDStruct
.1:
	push dword [esi]
	call DispInt
	pop eax
	stosd
	add esi, 4
	dec edx
	cmp edx, 0
	jnz .1
	call DispReturn
	cmp dword [_dwType], 1
	jne .2
	mov eax, [_dwBaseAddrLow]
	add eax, [_dwLengthLow]
	cmp eax, [_dwMemSize]
	jb .2
	mov [_dwMemSize], eax
.2:
	loop .loop

	call DispReturn
	push _szRAMSize
	call DispStr
	add esp, 4

	push dword [_dwMemSize]
	call DispInt
	add esp, 4
	
	pop ecx
	pop edi
	pop esi
	ret

InitKernel:
	xor esi, esi
	mov cx, word [KernelFilePhyAddr + 2ch]
	movzx ecx, cx
	mov esi, [KernelFilePhyAddr + 1ch]
	add esi, KernelFilePhyAddr

.Begin:
	mov eax, [esi+0]
	cmp eax, 0
	jz .NoAction
	push dword[esi+010h]
	mov eax, [esi+04h]
	add eax, KernelFilePhyAddr
	push eax
	push dword[esi+08h]
	call MemCpy
	add esp, 12

.NoAction:
	add esi, 020h
	dec ecx
	jnz .Begin

	ret


; ------------------------------------------------------------------------
; 内存拷贝，仿 memcpy
; ------------------------------------------------------------------------
; void* MemCpy(void* es:pDest, void* ds:pSrc, int iSize);
; ------------------------------------------------------------------------
MemCpy:
	push	ebp
	mov	ebp, esp

	push	esi
	push	edi
	push	ecx

	mov	edi, [ebp + 8]	; Destination
	mov	esi, [ebp + 12]	; Source
	mov	ecx, [ebp + 16]	; Counter
.1:
	cmp	ecx, 0		; 判断计数器
	jz	.2		; 计数器为零时跳出

	mov	al, [ds:esi]		; ┓
	inc	esi			; ┃
					; ┣ 逐字节移动
	mov	byte [es:edi], al	; ┃
	inc	edi			; ┛

	dec	ecx		; 计数器减一
	jmp	.1		; 循环
.2:
	mov	eax, [ebp + 8]	; 返回值

	pop	ecx
	pop	edi
	pop	esi
	mov	esp, ebp
	pop	ebp

	ret			; 函数结束，返回
; MemCpy 结束-------------------------------------------------------------
	

times 1024 db 0
TopofStack		equ		$