#include "mbed.h"
 
AnalogOut aout(PA_4);

 
 
 /*
 Analoge Werte:
 
 65000  3,3 V
39393  2 V
19696  1 V
 
 */

int main() 
{
   const double anfangswert = 19696; //umin = 1 V
   const double endwert =  39393; //umax = 2 V
   double abstufung = 10; //die abstufung von der angabe verwenden
   double offset = 300; //wenn die amplitude nicht genau umax trifft , erhöht man einfach die spannungswerte mit dem offset(ausgleich)
   //r = 100000;  //10 kohm
   //7c = 0.000010; //10 mikrofarad
   //tau = r*c;
   //periode = 3 * tau //die formel in der angabe benutzen
   double periode = 5; //in ms , erhöht die dauer einer stufe    
   
   
   double zaehlwert =((endwert-anfangswert)/abstufung);  //formel um den Schrittwert auszurechnen
   
   
   uint16_t sample = 0; //wir brauchen 16 bit um die analoge Spannung darzustellen
   
   
    
    while(1) 
    {
        
        
        //für die steigende Sägezahnspannung, anfangswert wird immer um den zählwert erhöht
        for(double i = anfangswert; i < endwert;i = i + zaehlwert)
        {
             sample = (uint16_t)(i+offset);
             aout.write_u16(sample);
             wait_ms(periode);
            
        }
        
        //für die sinkende Sägezahnspannung, auskommentieren um nur steigende Sägezahnspannung zu haben
        for(double i = endwert; i > anfangswert;i = i - zaehlwert)
        {
             sample = (uint16_t)(i+offset);
             aout.write_u16(sample);
             wait_ms(periode);
            
        }
        
               // zur probe ob die Ausgabe überhaupt funktioniert aout.write_u16(19696);
   
   
    }
}
