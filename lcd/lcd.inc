LCD = $5000
LCDINST = $5000
LCDDATA = $5001

LCD_BUSY:
  pha
LCD_WAIT:
  lda LCDINST
  and #$80			; 1000 0000		-	Pull Busy Flag from status register
  bne LCD_WAIT			; Wait for LCD
  pla
  rts
  
LCD_INIT:
  lda #$38			; 0011 1000		-	8-bit mode, 2 lines, 5x8 font
  sta LCDINST
  jsr LCD_BUSY
  
  lda #$06			; 0000 0110		-	Cursor increment, No shift
  sta LCDINST
  jsr LCD_BUSY
  
  lda #$0E			; 0000 1110		-	Display on, Cursor on, Blink off
  sta LCDINST
  jsr LCD_BUSY
  
  lda #$01			; 0000 0001		-	Clear display
  sta LCDINST
  jsr LCD_BUSY
  
  lda #$80			; 1000 0000		-	Set DDRAM address to 0000000
  sta LCDINST
  jsr LCD_BUSY
  rts

LCDPRINT:
  pha
  sta LCDDATA			;output the character
  jsr LCD_BUSY
  lda LCDINST
  and #$7F			; 0111 1111
  cmp #$14			; 0001 0100
				;wrap from $13 (line 1 char 20)
  bne LCDPRINT0
  lda #$C0			; 1100 0000
				;... to $40 (line 2 char 1)
  sta LCDINST
  jsr LCD_BUSY
LCDPRINT0:
  pla
  rts
  
LCDSTRING:
  sta $0200
  pha
  tya
  ldy #$00			; 0000 0000  Start at first char of string
LCDSTR0
  lda message1,y
  beq LCDSTR1
  jsr LCDPRINT
  iny
  bne LCDSTR0
LCDSTR1:
  pla
  tay
  pla
  rts

