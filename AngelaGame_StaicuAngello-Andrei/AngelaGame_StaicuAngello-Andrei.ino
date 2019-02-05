#include <LiquidCrystal.h>

  int numeroMetaScelto;
  int numeroMetaPARTITA;
  int numeroSceltoGiocatore;
  int numeroSceltoAngela;
  int somma;
  int CodiceTurno;
  int NumeroTurni;
  int Turni;

  #define buttonMinus
  #define buttonOk
  #define buttonPlus
  #define ledMinus
  #define ledOk
  #define ledPlus

  const int rs = 8, en = 9, d4 = 10, d5 = 11, d6 = 12, d7 = 13;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
  
void setup() {
  // put your setup code here, to run once:

  Serial.begin(9600);
  int numeroMetaScelto = 50;
  int numeroMetaPARTITA;
  int numeroSceltoGiocatore;
  int numeroSceltoAngela;
  int somma;
  int CodiceTurno = 1;
  int NumeroTurni = 1;
  int Turni = 1;
  randomSeed(analogRead(0));

    // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  // Print a message to the LCD.
  lcd.print("hello, world!");
  Serial.print("Programma di svago -Angela Game- inizializzato");
}

void loop() {
  // put your main code here, to run repeatedly:
  // Turn off the display:

  
  if(CodiceTurno == 1 && somma < numeroMetaPARTITA)
  {
    InizioPartita();
    Serial.print("Scegliere una cifra da 0 a 6")
    numeroSceltoGiocatore = Serial.read;
    if(numeroSceltoGiocatore < 7 && numeroSceltoGiocatore > 0)
    {
      somma = somma + numeroSceltoGiocatore; 
      ControllaMeta();
      CodiceTurno = 2;
      NumeroTurni++;
    }
    else if(numeroSceltoGiocatore == 0 && NumeroTurni == 1)
    {
      Serial.print("Il numero 0 si può applicare solo un volta il PRIMO turno");
      somma = somma + numeroSceltoGiocatore;
      ControllaMeta(); 
      CodiceTurno = 2;
      NumeroTurni++;
    }
    else
    {
      Serial.print("Selezionare un numero tra 0/1 e 6")
    }
    
    
  }

  if(CodiceTurno == 2 && somma < numeroMetaPARTITA)
  {
      numeroSceltoAngela = random.millis(1,7);
      NumeroTurni++;
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

void PassaTurno()
{
  if(CodiceTurno == 1)
  {
    CodiceTurno = 2;
  }
  else if(CodiceTurno == 2)
  {
    CodiceTurno = 1;
  }
}

void RiduciMeta()
{
  if(numeroMetaPARTITA < 30)
  {
    Serial.write("Non oltrepassare la soglia minima consigliata di 30");
  }
}

int InizioPartita()
{
  Serial.print("Immettere la meta preferita da 30 a 99");
  Serial.read(numeroMetaPARTITA);
  if(numeroMetaPARTITA > 99)
  {
    Serial.print("Meta troppo alta");
  }
  else if(numeroMetaPARTITA < 30)
  {
    Serial.print("Meta troppo bassa");
  }
  else
  {
    return numeroMetaPARTITA;
  }
  
}

void ControllaMeta()
{
  if(somma > numeroMetaPARTITA && CodiceTurno == 1)
  {
    Serial.print("Hai Perso - La meta è stata oltrepassata dall'Utente")
  }
  else if(somma > numeroMetaPARTITA && CodiceTurno == 2)
  {
    Serial.print("Hai Vinto - La meta è stata oltrepassata da Angela")
  }
  else if(somma == numeroMetaPARTITA && CodiceTurno == 1)
  {
    Serial.print("Hai Vinto - Hai raggiunto la meta prima di Angela")
  }
    else if(somma == numeroMetaPARTITA && CodiceTurno == 2)
  {
    Serial.print("Hai Perso - Angela ha ragginto la meta per prima")
  }
}

