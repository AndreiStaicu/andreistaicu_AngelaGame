#include <LiquidCrystal.h>

  int numeroMetaScelto;
  int numeroMetaPARTITA;
  int numeroSceltoGiocatore;
  int numeroSceltoSecondo;
  int somma;
  int CodiceTurno;
  int NumeroTurni;
  int controllo;
  int blocco;
  bool bottoneConferma;
  //robe fatte da alessio
  int arrrayMosse[100];
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
    numeroMetaPARTITA = 50;
    numeroSceltoGiocatore = 3;
    numeroSceltoSecondo = 3;
    somma = 0;
    CodiceTurno = 0;
    NumeroTurni = 1;
    controllo = 0;
    randomSeed(analogRead(0));
    blocco = 0;
    //BOTTONI
    pinMode(4, INPUT_PULLUP); //VERDE
    pinMode(3, INPUT_PULLUP); //BIANCO
    pinMode(2, INPUT_PULLUP); //ROSSO
    //LED
    digitalWrite(7, LOW); //VERDE
    digitalWrite(6, LOW); //BIANCO
    digitalWrite(5, LOW); //ROSSO
    
}

void loop() 
{
  // put your main code here, to run repeatedly
  
  if(CodiceTurno == 0 && somma <= numeroMetaPARTITA && blocco == 0)
  {
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("AngelaGame");
    delay(1000);
    lcd.clear();      
    blocco = 1;
    InizioPartita();
  }
  
  CodiceTurno = 1;
  lcd.setCursor(0,0);
  lcd.print("Turno dell'Utente");
  delay(1000);
  lcd.clear();
  
  if(CodiceTurno == 1)
  {
    
    TurnoGiocatore();
    ControllaMeta(); 
    CodiceTurno = 2;
  }
    
  if(CodiceTurno == 2 )
  {
      TurnoGiocatore();
      ControllaMeta(); 
      CodiceTurno = 1;
  }
  
}



//////////////////AREA METODI/////////////////

int TurnoGiocatore() // O COPIA O IF
{
  lcd.setCursor(0,0);
  lcd.print("Da 0 a 6");
  delay(1000);
  lcd.clear();
  BottoniPremutiGiocatore();
        ControllaMeta();   
        CodiceTurno = 2;
        NumeroTurni++;
}
int InizioPartita()
{
        lcd.setCursor(0,0);
        lcd.print("Meta da 30 a 99");
        delay(1000);
        lcd.setCursor(7,1);//COLONNA,RIGA
        lcd.print(numeroMetaPARTITA);
        delay(1000);
        BottoniPremutiMeta();
        return numeroMetaPARTITA;

}

void Aspetta()
{
  bool fermo = true;
  while(digitalRead(4) == HIGH && digitalRead(3) == HIGH && digitalRead(2) == HIGH && fermo == true)
  {}
  if(digitalRead(4) == LOW)
  {fermo = false;}
  else if(digitalRead(5) == LOW)
  {fermo = false;}
  else if(digitalRead(6) == LOW)
  {fermo = false;}
}

//
void BottoniPremutiMeta()
{
  bool finito = false;
  while(!finito)
  {
    Aspetta();
    if(digitalRead(4) == LOW)
    {
        numeroMetaPARTITA++;
        lcd.setCursor(7,1);
        lcd.print(numeroMetaPARTITA);
    }
    if(digitalRead(3) == LOW)
    {
      finito = true;
      lcd.setCursor(7,1);
      lcd.print(numeroMetaPARTITA);

    }
    if(digitalRead(2) == LOW)
    {
        numeroMetaPARTITA--;
        lcd.setCursor(7,1);
        lcd.print(numeroMetaPARTITA);
    }
  }
}

void BottoniPremutiGiocatore()
{
  bool finito = false;
  if(CodiceTurno == 1)//Player 1
  {
    while(!finito)
  {
    Aspetta();
    if(digitalRead(4) == LOW)
    {
      digitalWrite(7, HIGH);
      delay(1000);
      digitalWrite(7, LOW);
      numeroSceltoGiocatore++;
      if(numeroSceltoGiocatore > 6)
      {
        numeroSceltoGiocatore = 6;
        lcd.setCursor(7,1);
        lcd.print(numeroSceltoGiocatore);
      }
    }
    if(digitalRead(3) == LOW)
    {
      digitalWrite(6, HIGH);
      delay(1000);
      digitalWrite(6, LOW);
      finito = true;
      somma = somma + numeroSceltoGiocatore;
      lcd.setCursor(7,1);
      lcd.print(numeroSceltoGiocatore);
    }
    if(digitalRead(2) == LOW)
    {
      digitalWrite(5, HIGH);
      delay(1000);
      digitalWrite(5, LOW);
      numeroSceltoGiocatore++;
      if(numeroSceltoGiocatore < 1)
      {
        numeroSceltoGiocatore = 1;
        lcd.setCursor(7,1);
        lcd.print(numeroSceltoGiocatore);
      }
    }
   }
  }
  else if(CodiceTurno == 2)//Player 2
  {
    while(!finito)
  {
    Aspetta();
    if(digitalRead(4) == LOW)
    {
      numeroSceltoSecondo++;
      if(numeroSceltoSecondo > 6)
      {
        numeroSceltoSecondo = 6;
        lcd.setCursor(7,1);
        lcd.print(numeroSceltoSecondo);
        delay(1000);
      }
    }
    if(digitalRead(3) == LOW)
    {
      finito = true;
      somma = somma + numeroSceltoSecondo;
      lcd.setCursor(7,1);
      lcd.print(numeroSceltoSecondo);
      delay(1000);
    }
    if(digitalRead(2) == LOW)
    {
      numeroSceltoSecondo++;
      if(numeroSceltoSecondo < 1)
      {
        numeroSceltoSecondo = 1;
        lcd.setCursor(7,1);
        lcd.print(numeroSceltoSecondo);
        delay(1000);
      }
    }
   }
  }
}



/*
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
*/
void ControllaMeta()
{
  if(somma > numeroMetaPARTITA && CodiceTurno == 1)
  {
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("G2 Vince! Turno: " + NumeroTurni);
    lcd.setCursor(0,1);
    lcd.print("G1 oltre la meta...");
    numeroMetaPARTITA = 0;
    CodiceTurno = 0;
    blocco = 0;
  }
  else if(somma > numeroMetaPARTITA && CodiceTurno == 2)
  {
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("G1 Vince! Turno: " + NumeroTurni);
    lcd.setCursor(0,1);
    lcd.print("G2 oltre la meta...");
    numeroMetaPARTITA = 0;
    CodiceTurno = 0;
    blocco = 0;
  }
  else if(somma == numeroMetaPARTITA && CodiceTurno == 1)
  {
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("G1 Vince! Turno: " + NumeroTurni);
    lcd.setCursor(0,1);
    lcd.print("G1 nella meta!");
    numeroMetaPARTITA = 0;
    CodiceTurno = 0;
    blocco = 0;
  }
    else if(somma == numeroMetaPARTITA && CodiceTurno == 2)
  {
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("G2 Vince! Turno: " + NumeroTurni);
    lcd.setCursor(0,1);
    lcd.print("G2 nella meta!");
    numeroMetaPARTITA = 0;
    CodiceTurno = 0;
    blocco = 0;
  }

}


