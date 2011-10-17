	BS_OMEName	DB	'NathanWu'
	BPB_BytsPerSec	DW	512
	BPB_SecPerClus	DB	1
	BPB_RsvdSecCnt	DW	1 		;Boot 记录占用多少扇区
	BPB_NumFATs	DB	2
	BPB_RootEntCnt	DW	224
	BPB_TotSec16	DW	2280 		;逻辑扇区总数
	BPB_Mediat	DB	0xf0
	BPB_FATSz16	DW	9
	BPB_SecPerTrk	DW	18
	BPB_NumHeads	DW	2
	BPB_HiddSec	DD	0
	BPB_TotSec32	DD	0
	BS_DrvNum	DB	0 		;int 13h 的驱动器号
	BS_Reserved1	DB	0
	BS_BootSig	DB	29h
	BS_VolID	DD	0
	BS_VolLab	DB	'XXX0.00    ' 	;11 bytes
	BS_FileSysType	DB	'FAT12   '	;8 bytes
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
	NRootEntSec	equ	14		;(BPB_RootEntCnt * 32 + BPB_BytsPerSec - 1) / BPB_BytsPerSec 
	RootEntStart	equ	19
	SectorNoOfFAT1  equ	1
	delta		equ 	1fh		;[BPB_NumFATs] * [BPB_FATSz16] + NRootEnt - 2 
