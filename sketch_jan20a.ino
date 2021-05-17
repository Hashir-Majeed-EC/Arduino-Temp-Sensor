#include <LiquidCrystal.h>
int ThermistorPin = 0;
int Vo;
float R1 = 10000;
float lnR2, R2, Temp;
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

float oldTemp;
bool puzzleCompleted = false;
//Steinhart-Hart coefficients
float  c1 = 0.010155, c2 = -0.00118225, c3 = 0.00000524;

void setup() {
 Serial.begin(9600);

 oldTemp = CalculateTemperature();
 Temp = oldTemp;
 Serial.print(oldTemp);
}
void loop() {
  Temp = CalculateTemperature();
  lcd.print(Temp);
  //CHANGE THE IF STATEMENT FOR -VE TEMP CHANGE
  if (Temp < oldTemp - 7 && Temp > 0){
    lcd.clear();
    lcd.print("911");
  }

  if(Temp > oldTemp + 3){
    lcd.clear();
    //lcd.setCursor(0,0);
    lcd.println("Excessive Heat");
    
  }
  delay(7000);
  lcd.clear();

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


