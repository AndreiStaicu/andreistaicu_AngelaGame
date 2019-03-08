#include <LiquidCrystal.h>

  int numeroMetaScelto;
  int numeroMetaPARTITA;
  int numeroSceltoGiocatore;
  int numeroSceltoAngela;
  int somma;
  int CodiceTurno;
  int NumeroTurni;
  int controllo;
  int blocco;
  #define buttonMinus
  #define buttonOk
  #define buttonPlus
  #define ledMinus
  #define ledOk
  #define ledPlus

  const int rs = 8, en = 9, d4 = 10, d5 = 11, d6 = 12, d7 = 13;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

// "Firme" dei metodi

void AumentaMeta();
void RiduciMeta();
int InizioPartita(); 
void ControlloInput();
void ControllaMeta();
int InizioPartita();
int TurnoGiocatore();


void setup() 
{
  // put your setup code here, to run once:
  lcd.begin(16, 2);
  lcd.print("Angela Game");
  
    Serial.begin(9600);
    numeroMetaScelto = 50;
    numeroMetaPARTITA = 0;
    numeroSceltoGiocatore = 0;
    numeroSceltoAngela = 0;
    somma = 0;
    CodiceTurno = 0;
    NumeroTurni = 1;
    controllo = 0;
    randomSeed(analogRead(0));
    blocco = 0;

    pinMode(4, INPUT); //VERDE
    pinMode(3, INPUT); //BIANCO
    pinMode(2, INPUT); //ROSSO
    
   // pinMode(A5, INPUT); //START
    
    /*pinMode(2, OUTPUT); //BIANCO
    pinMode(3, OUTPUT); //VERDE
    pinMode(4, OUTPUT); //ROSSO*/
    
    digitalWrite(7, LOW); //VERDE
    digitalWrite(6, LOW); //BIANCO
    digitalWrite(5, LOW); //ROSSO
    
}

void loop() 
{
  // put your main code here, to run repeatedly
  
  if(CodiceTurno == 0 && somma <= numeroMetaPARTITA && blocco == 0)
  {
    lcd.print("Programma inizializzato");      
    blocco = 1;
    InizioPartita();
  }
  
  CodiceTurno = 1;
  Serial.println("Turno dell'Utente");
  
  if(CodiceTurno == 1 || blocco == 0)
  {
    TurnoGiocatore();
    CodiceTurno = 2;
  }
    
  if(CodiceTurno == 2 )
  {
      Serial.println("Turno di Angela");
      numeroSceltoAngela = random(1, 7);
      Serial.print("Numero scelto  ->  ");
      Serial.println(numeroSceltoAngela);   
      somma = somma + numeroSceltoAngela;
      Serial.print("SOMMA TOTALE  ->  "); 
      Serial.println(somma);
      Serial.print("META  ->  ");
      Serial.println(numeroMetaPARTITA); 
      NumeroTurni++;
      CodiceTurno = 1;
      ControllaMeta();      
  }
  
}



//////////////////AREA METODI/////////////////

void AumentaMeta()
{
  if(numeroMetaPARTITA > 99)
  {
    Serial.write("Non oltrepassare la soglia massima consigliata di 99");
  }
  else
  {
    numeroMetaScelto++;
  }
}

void RiduciMeta()
{
  if(numeroMetaPARTITA < 30)
  {
    Serial.write("Non oltrepassare la soglia minima consigliata di 30");
  }
  else
  {
    numeroMetaScelto--;
  }
}

int TurnoGiocatore()
{
  blocco = 0;
  Serial.println("Scegliere una cifra da 0 a 6");
  while (Serial.available() == 0) 
    {
      String InputGiocatore = Serial.readString();
      if(InputGiocatore == "")
      {}
      else
      {
        if (InputGiocatore.toInt() >= 1 && InputGiocatore.toInt() <= 6) 
        {
        numeroSceltoGiocatore = InputGiocatore.toInt();
        Serial.print("Numero scelto  ->  ");
        Serial.println(numeroSceltoGiocatore);   
        somma = somma + numeroSceltoGiocatore;
        Serial.print("SOMMA TOTALE  ->  "); 
        Serial.println(somma);
        Serial.print("META  ->  ");
        Serial.println(numeroMetaPARTITA);         
        return numeroSceltoGiocatore;
        ControllaMeta();        
        CodiceTurno = 2;
        NumeroTurni++;
      
        }
        else if(InputGiocatore.toInt() == 0 && blocco == 0)
        {
          blocco = 1;
          Serial.println("Il numero 0 si può applicare solo un volta il PRIMO turno");
          numeroSceltoGiocatore = InputGiocatore.toInt();
          Serial.print("Numero scelto  ->  ");
          Serial.println(numeroSceltoGiocatore);       
          somma = somma + numeroSceltoGiocatore; 
          Serial.print("SOMMA TOTALE  ->  "); 
          Serial.println(somma);
          Serial.print("META  ->  ");
          Serial.println(numeroMetaPARTITA);
          ControllaMeta();          
          CodiceTurno = 2;
          NumeroTurni++;
          return numeroSceltoGiocatore;

        }
        else
        {
          Serial.println("Selezionare un numero tra 0 per il primo turno,oppure tra 1 e 6");
        }
      }
   }
}

int InizioPartita()
{
  lcd.print("Meta da 30 a 99");
  while (Serial.available() == 0) 
  {
    String InputMeta = lcd.read();

    if(InputMeta == "")
    {}
    else
    {
      if (InputMeta.toInt() >= 30 && InputMeta.toInt() <= 99) 
      {
        numeroMetaPARTITA = InputMeta.toInt();
        lcd.print("Punti Meta  :  ");
        lcd.println(numeroMetaPARTITA);
        return numeroMetaPARTITA;
        blocco = 0;
      }
      else if(InputMeta.toInt() > 99)
      {
        Serial.println("Soglia troppo alta");
      }
      else if(InputMeta.toInt() < 30)
      {
        Serial.println("Non oltrepassare la soglia minima consigliata di 30");
      }
      else    //if(InputMeta == "") + altri caratteri
      {
        Serial.println("Immettere un valore in cifre tra 30 e 99. Non altri caratteri.");
      }
  }
  }
}
  
/*
  else
  {
    return numeroMetaPARTITA;
  }
*/




void ControlloInput() 
{
  if (numeroSceltoGiocatore == 1 && numeroSceltoAngela != 6 && numeroSceltoAngela != 1) 
  {
    controllo = 1;
  }
  if (numeroSceltoGiocatore == 2 && numeroSceltoAngela != 5 && numeroSceltoAngela != 2) 
  {
    controllo = 1;
  }
  if (numeroSceltoGiocatore == 3 && numeroSceltoAngela != 4 && numeroSceltoAngela != 3) 
  {
    controllo = 1;
  }
  if (numeroSceltoGiocatore == 4 && numeroSceltoAngela != 4 && numeroSceltoAngela != 3) 
  {
    controllo = 1;
  }
  if (numeroSceltoGiocatore == 5 && numeroSceltoAngela != 5 && numeroSceltoAngela != 2) 
  {
    controllo = 1;
  }
  if (numeroSceltoGiocatore == 6 && numeroSceltoAngela != 6 && numeroSceltoAngela != 1) 
  {
    controllo = 1;
  }
}

void ControllaMeta()
{
  if(somma > numeroMetaPARTITA && CodiceTurno == 1)
  {
    Serial.println("Hai Perso - La meta è stata oltrepassata dall'Utente");
    numeroMetaPARTITA = 0;
    CodiceTurno = 0;
    blocco = 0;
  }
  else if(somma > numeroMetaPARTITA && CodiceTurno == 2)
  {
    Serial.println("Hai Vinto - La meta è stata oltrepassata da Angela");
    numeroMetaPARTITA = 0;
    CodiceTurno = 0;
    blocco = 0;
  }
  else if(somma == numeroMetaPARTITA && CodiceTurno == 1)
  {
    Serial.println("Hai Vinto - Hai raggiunto la meta prima di Angela");
    numeroMetaPARTITA = 0;
    CodiceTurno = 0;
    blocco = 0;
  }
    else if(somma == numeroMetaPARTITA && CodiceTurno == 2)
  {
    Serial.println("Hai Perso - Angela ha ragginto la meta per prima");
    numeroMetaPARTITA = 0;
    CodiceTurno = 0;
    blocco = 0;
  }
  else
  {
    
  }

}

