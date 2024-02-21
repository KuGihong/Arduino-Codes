#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,20,4);    

//lcd(0x27,16열,2행)

// 0x27 이 lcd의 고유주소라고 생각하면 됩니다. 보통 0x27이지만 다른 lcd도 있습니다.
// 혹시 다른 고유주소라면, 예제프로그램에서 확인한후 똑같이 입력하여 코딩하시면 됩니다.

// lcd(0x27,16열,2행)  ->  고유주소=0x27 이고 총 16열 2행으로 구성되어 있다는 뜻 입니다.

void setup()
{
  lcd.init();  // LCD초기 설정
  
  lcd.backlight(); // LCD초기 설정  
  
  lcd.setCursor(0,0); 
  
  //처음 텍스트가 LCD에 나타날 위치  lcd.setCursor(열, 행)
  //밑에 사진을 통해 출력시작 위치를 확인할 수 있습니다.
  
  lcd.print("Hello, world!"); 
  
  lcd.setCursor(3,1); 
  
  lcd.print("How are you?"); 
  
}

void loop()
{
  
}
