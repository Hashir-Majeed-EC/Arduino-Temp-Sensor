#include <LiquidCrystal.h>
int ThermistorPin = 0;
int Vo;
float R1 = 10000;
float lnR2, R2, Temp;
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

float oldTemp;
bool puzzleCompleted = false;
//Steinhart-Hart coefficients
float  c1 = 0.00050, c2 = 0.0002999991, c3 = 0.0000003;

void setup() {
 Serial.begin(9600);
 //lcd.begin(16,2);
 oldTemp = CalculateTemperature();
 Temp = oldTemp;
}
void loop() {

 while (!puzzleCompleted){
  lcd.print("Temp: ");

  Temp = CalculateTemperature();
  lcd.print(Temp);

  lcd.println(" C   ");


  //Check temperature change (7 degrees)
  if ((oldTemp - Temp >= 7) && (oldTemp - Temp < 50)){
    int Display = 911;
    lcd.clear();
    lcd.print(Display);
    delay(100000);
    puzzleCompleted = true;
  }else if (Temp - oldTemp > 4){
    lcd.clear();
    lcd.print("Too Hot!");
  }else{
    oldTemp = Temp;
  }

 delay(2500);
 lcd.clear();
 }
 lcd.print("Code: 911");
}

float CalculateTemperature(){
 //reads v out, in an analog form
 Vo = analogRead(ThermistorPin);

 //Calculates R2 from the potential dividor equation
 R2 = R1 * (1023.0 / (float)Vo - 1.0);

 //Natural logarithm of the voltage
 lnR2 = log(R2);
 //Conversion of R to temp using the Steinhart-Hart equation (Extension of the B parameter Equation)
 Temp = (1.0 / (c1 + c2*lnR2 + c3*lnR2*lnR2*lnR2));
 //Kelvin to Celcius
 Temp = Temp - 273.15;
 return Temp;
}
