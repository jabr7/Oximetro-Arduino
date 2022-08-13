#include <Keypad.h>
#include <LiquidCrystal_I2C.h>

int random_pulse;

LiquidCrystal_I2C lcd = LiquidCrystal_I2C(0x27, 16,2);

const byte ROWS = 4; //four rows
const byte COLS = 3; //three columns
char keys[ROWS][COLS] = {
  {'1','2','3'},
  {'4','5','6'},
  {'7','8','9'},
  {'*','0','#'}
};

byte rowPins[ROWS] = {9, 8, 7, 6}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {5,4,3}; //connect to the column pinouts of the keypad

Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

void setup(){
 
  pinMode(A0,INPUT);
  lcd.init();                         
  lcd.backlight();                           
  Serial.begin(9600);
  imprimir("Bienvenido al sistema de control de salud.                ");
  delay(1000);
  lcd.clear();
  lcd.print("Presione una");
  lcd.setCursor(0,1);
  lcd.print("tecla");
}


void loop(){
  int edad;
  int peso;
  double altura;
  int pulso;
  double imc;
  String imcS;

  char keyEntrada = keypad.getKey();
  if(keyEntrada){
    imprimir("Ingrese su edad y presione #...                ");
    edad = capturoKey("Edad:");

    if(edad>=18){
      imprimir("Ingrese su altura en cm y presione #...                ");
      altura = capturoKey("Altura:");
      imprimir("Ingrese su peso en Kilogramos y presione #...                ");
      peso = capturoKey("Peso:");
      imprimir("Coloque su pulgar en el sensor de pulso y presione #...                ");
      pulso = capturoKey("Lectura de pulso");
  
      //Sistema de numero random para las pulsaciones
      randomSeed(analogRead(A2));
      random_pulse = random(50,110);

      //Paso la altura a metros ya que fue ingresada en centimetros, la potencio y aplico formula de IMC
      altura = altura/100;
      altura=pow(altura,2);
      imc = peso/altura;

      //Paso de Int a String y se lo paso a la funcion imprimir
      imcS = String(imc);
      imprimir("Su indice de masa corporal es: " + imcS);
      delay(2000);
      
      //Calculo Rango pulsacion y muestro
      
      imprimir("A partir de su edad y pulso cardiaco consideramos que usted tiene una:                   ");
      
      //Cargado con la informacion de marathonranking.com
      if(edad<=29){
        if(random_pulse<=60){
          imprimir("Excelente condicion");
        }else if(random_pulse<=68){
          imprimir("Buena condicion");
        }else if(random_pulse<=84){
          imprimir("Condicion normal");
        }else{
          imprimir("Condicion mala");
        }
      }

      if(edad>=30 && edad<=39){
        if(random_pulse<=62){
          imprimir("Excelente condicion");
        }else if(random_pulse<=70){
          imprimir("Buena condicion");
        }else if(random_pulse<=84){
          imprimir("Condicion normal");
        }else{
          imprimir("Condicion mala");
        }
      }
      if(edad>=40 && edad<=49){
        if(random_pulse<=64){
          imprimir("Excelente condicion");
        }else if(random_pulse<=72){
          imprimir("Buena condicion");
        }else if(random_pulse<=88){
          imprimir("Condicion normal");
        }else{
          lcd.print("Condicion mala");
        }
      }
      if(edad>50){
        if(random_pulse<=66){
          imprimir("Excelente condicion");
        }else if(random_pulse<=74){
          imprimir("Buena condicion");
        }else if(random_pulse<=88){
          imprimir("Condicion normal");
        }else{
          imprimir("Condicion mala");
        }
      }


      delay(4000);
    }else{
    imprimir("Debes de ser mayor de 18 para utilizar este sistema");  
    }
    
    delay(5000);
    lcd.clear();
    lcd.print("Presione una");
    lcd.setCursor(0,1);
    lcd.print("tecla");
  }
}

void imprimir(String texto){
  int largo = texto.length();
  boolean flecha=true; 
  if(largo>16){
    lcd.clear();
    lcd.print(texto.substring(0,15));
    delay(1500);
    for(int i=15;i<largo;i++){
      String imprimo = texto.substring(i-15,i+1);
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print(imprimo);
      if(flecha){
        lcd.setCursor(0,1);
        lcd.print("--> --> --> --> ");
        flecha=false;
      }else{
        lcd.setCursor(0,1);
        lcd.print(" --> --> --> -->");
        flecha=true;
      }

      //Velocidad de la funcion de impresion
      delay(350);
        lcd.setCursor(0,1);
        lcd.print("                ");
    }
  
  }else{
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print(texto);
  }
}
   
int capturoKey(String head){
  String temp="";
  int lectura=0;
  char key;

  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print(head);
  do{
    key = keypad.getKey();
    if(key){
      if(key!='#' && key!='*'){
      
        temp=temp+key;
        lcd.setCursor(0, 1);
        lcd.print(temp);
      }
    }
  }while(key!='#');
  lectura = temp.toInt();
  return lectura;
}






  
