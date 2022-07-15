# arduino-blackjack
My assignment for arduino lecture

# issues
## Why there is frame1~6, numA~K but unused?
- LiquidCrystal has 8 spaces for custom font(by using lcd.createChar method) and this storage follows FIFO so problem raised at 9th font
