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
    lcd.print("AngelaGame inizializzato");
    lcd.clear();      
    blocco = 1;
    InizioPartita();
  }
  
  CodiceTurno = 1;
  lcd.setCursor(0,0);
  lcd.print("Turno dell'Utente");
  
  if(CodiceTurno == 1 || blocco == 0)
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
  lcd.print("Scegliere cifra da 0 a 6");
  Aspetta();
  BottoniPremutiGiocatore();
  
     //CONTROLLO + SOMMA
      
        if (InputGiocatore.toInt() >= 1 && InputGiocatore.toInt() <= 6) 
        {
        numeroSceltoGiocatore = InputGiocatore.toInt();
        lcd.print("Numero scelto  ->  ");
        lcd.print(numeroSceltoGiocatore);   
        somma = somma + numeroSceltoGiocatore;
        lcd.print("SOMMA TOTALE  ->  "); 
        lcd.print(somma);
        lcd.print("META  ->  ");
        lcd.print(numeroMetaPARTITA);         
        return numeroSceltoGiocatore;
        ControllaMeta();        
        CodiceTurno = 2;
        NumeroTurni++;
      
        }
        else if(InputGiocatore.toInt() == 0 && blocco == 0)
        {
          blocco = 1;
          lcd.print("Il numero 0 si può applicare solo un volta il PRIMO turno");
          numeroSceltoGiocatore = InputGiocatore.toInt();
          lcd.print("Numero scelto  ->  ");
          lcd.print(numeroSceltoGiocatore);       
          somma = somma + numeroSceltoGiocatore; 
          lcd.print("SOMMA TOTALE  ->  "); 
          lcd.print(somma);
          lcd.print("META  ->  ");
          lcd.print(numeroMetaPARTITA);
          ControllaMeta();          
          CodiceTurno = 2;
          NumeroTurni++;
          return numeroSceltoGiocatore;

        }
        else
        {
          lcd.print("Selezionare un numero tra 0 per il primo turno,oppure tra 1 e 6");
        }
      }
   }
}

int InizioPartita()
{
        lcd.print("Meta da 30 a 99");
        lcd.setCursor(7,1);//COLONNA,RIGA
        lcd.print(numeroMetaPARTITA);
        BottoniPremutiMeta();
        return numeroMetaPARTITA;

}

void Aspetta()
{
  while(digitalRead(4) == HIGH && digitalRead(3) == HIGH && digitalRead(2) == HIGH)
  {}
}

//
void BottoniPremutiMeta()
{
  bool finito = false;
  if(CodiceTurno == 1)//Player 1
  {
    while(!finito)
  {
    aspetta();
    if(digitalRead(4) == LOW)
    {
      numeroSceltoGiocatore++;
      if(numeroSceltoGiocatore > 6)
      {
        numeroSceltoGiocatore = 6;
        lcd.print(numeroSceltoGiocatore);
      }
    }
    if(digitalRead(3) == LOW)
    {
      finito = true;
      somma = somma + numeroSceltoGiocatore;
      lcd.print(numeroSceltoGiocatore);
    }
    if(digitalRead(2) == LOW)
    {
      numeroSceltoGiocatore++;
      if(numeroSceltoGiocatore < 1)
      {
        numeroSceltoGiocatore = 1;
        lcd.print(numeroSceltoGiocatore);
      }
    }
   }
  }
  else if(CodiceTurno == 2)//Player 2
  {
    while(!finito)
  {
    aspetta();
    if(digitalRead(4) == LOW)
    {
      numeroSceltoSecondo++;
      if(numeroSceltoSecondo > 6)
      {
        numeroSceltoSecondo = 6;
        lcd.print(numeroSceltoSecondo);
      }
    }
    if(digitalRead(3) == LOW)
    {
      finito = true;
      somma = somma + numeroSceltoSecondo;
      lcd.print(numeroSceltoSecondo);
    }
    if(digitalRead(2) == LOW)
    {
      numeroSceltoSecondo++;
      if(numeroSceltoSecondo < 1)
      {
        numeroSceltoSecondo = 1;
        lcd.print(numeroSceltoSecondo);
      }
    }
   }
  }

void BottoniPremutiGiocatore()
{
  bool finito = false;
  if(CodiceTurno == 1) //Giocatore 1
  while(!finito)
  {
    Aspetta();
    if(digitalRead(4) == LOW)
    {
      if(numeroMetaPARTITA > 99)
      {
        lcd.print("Soglia troppo alta");
      }
      else
      {
        numeroMetaPARTITA++;
        lcd.print(numeroMetaPARTITA);
      }
    }
    if(digitalRead(3) == LOW)
    {
      finito = true;
      lcd.print(numeroMetaPARTITA);
    }
    if(digitalRead(2) == LOW)
    {
      if(numeroMetaPARTITA < 30)
      {
        lcd.print("Non oltrepassare la soglia minima consigliata di 30");
      }
      else
      {
        numeroMetaPARTITA--;
        lcd.print(numeroMetaPARTITA);
      }
    }
  }
}




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
    lcd.print("Hai Perso - La meta è stata oltrepassata dall'Utente");
    numeroMetaPARTITA = 0;
    CodiceTurno = 0;
    blocco = 0;
  }
  else if(somma > numeroMetaPARTITA && CodiceTurno == 2)
  {
    lcd.print("Hai Vinto - La meta è stata oltrepassata da Angela");
    numeroMetaPARTITA = 0;
    CodiceTurno = 0;
    blocco = 0;
  }
  else if(somma == numeroMetaPARTITA && CodiceTurno == 1)
  {
    lcd.print("Hai Vinto - Hai raggiunto la meta prima di Angela");
    numeroMetaPARTITA = 0;
    CodiceTurno = 0;
    blocco = 0;
  }
    else if(somma == numeroMetaPARTITA && CodiceTurno == 2)
  {
    lcd.print("Hai Perso - Angela ha ragginto la meta per prima");
    numeroMetaPARTITA = 0;
    CodiceTurno = 0;
    blocco = 0;
  }
  else
  {
    
  }

}


