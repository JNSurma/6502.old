  .org $8000

RESET:
  ldx #$ff	; Setup stack pointer
  txs

  jsr LCD_INIT
  lda message1
  jsr LCDSTRING  

LOOP:
  jmp LOOP


message: .asciiz "Tricky Lights!!!"
message1: .asciiz "Super Tricky Lights Twinkle!!!"

  include lcd.inc

  .org $fffc
  .word RESET
  .word $0000
