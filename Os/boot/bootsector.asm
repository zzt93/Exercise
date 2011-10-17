%include	"loader.inc"	
org 07c00h

	jmp LABEL_START

%include	"fat12hdr.inc"
%include	"disp.inc"	
	
SectorNo		dw	0
N 			dw	NRootEntSec ;counter
LoaderFileName		db	"LOADER  BIN"
odd 			db 	0
	

StackBase		equ 	0x7c00	
	
LABEL_START:

	mov ax, 0600h
	mov bx, 0700h
	mov cx, 0
	mov dx, 0184fh
	int 10h			;cls

	mov dh, 0		;"booting"
	call DispBootStr

	xor ah, ah
	xor dl, dl
	int 13h			;reset floppy

	mov ax, LoaderBase
	mov es, ax
	mov bx, LoaderOffset	;es:bx = LoaderBase:LoaderOffset
	mov word [SectorNo], RootEntStart
	mov ax, cs
	mov ds, ax
	mov ss, ax
	mov sp, StackBase
	cld
	mov si, LoaderFileName	;ds:si = "loader bin"
	mov di, LoaderOffset	;es:di = dirent

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
	mov si, LoaderFileName
	jmp .record_loop	;load next record and continue
.char_go_on:
	inc di
	jmp .char_loop
.end_record_loop:
	add word [SectorNo], 1
	jmp .sector_loop
.end_sector_loop:

	mov dh, 2		;"No Loader"
	call DispBootStr
	jmp $

.found:			;0x7cd4
	and di, 0ffe0h
	add di, 01ah
	mov cx, word [es:di]
	push cx				;save relative sector #
	add cx, delta
	mov ax, LoaderBase
	mov es, ax
	mov bx, LoaderOffset		;es:bx = destiny
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
	mov dh, 1		;"ready"
	call DispBootStr
	jmp LoaderBase:LoaderOffset
	

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
	mov cx, LoaderBase; `.
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
	
times 510-($-$$)  db 0
	dw 0xaa55
times 1474560-512 db 0
	