# arduino-blackjack
My assignment for arduino lecture
![image](https://user-images.githubusercontent.com/20695889/179253142-e72934fa-3133-45fe-8451-9c199b1a00c1.png)


# issues
## Why there is frame1-6, numA-K but unused?
- LiquidCrystal has 8 spaces for custom font(by using lcd.createChar method) and this storage(CGRAM, not on arduino board) follows FIFO so problem raised at 9th font
![image](https://user-images.githubusercontent.com/20695889/179250218-2000d8fc-e622-474b-b800-2bfcfa01312b.png)
- If 9th font is pushed, all currently displayed characters with that code change immediately(It overwrites new font at 0th index area)
## Why using 4-7 segments on the code?
- I had two 7 segments but one of them is broken so I used my 4-7 segments among the remaining parts of my kit.
- In upper picture I failed to use the right 7 segment.
