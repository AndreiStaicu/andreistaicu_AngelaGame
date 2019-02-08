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
  
void setup() {
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
  
}

void loop() {
  // put your main code here, to run repeatedly:
  // Turn off the display:

  
  if(CodiceTurno == 0 && somma <= numeroMetaPARTITA)
  {
    Serial.println("Programma di svago -Angela Game- inizializzato");
    InizioPartita();
    Serial.println("Turno dell'Utente");
    Serial.println("Scegliere una cifra da 0 a 6");
    while (Serial.available() > 0) 
    {
      String InputGiocatore = Serial.readString();

      if (InputGiocatore.toInt() >= 1 && InputGiocatore.toInt() <= 6) 
      {
        numeroSceltoGiocatore = InputGiocatore.toInt();
        Serial.print("Numero scelto  ->  ");
        Serial.println(numeroSceltoGiocatore);
        somma = somma + numeroSceltoGiocatore; 
        ControllaMeta();
        CodiceTurno = 2;
        NumeroTurni++;
      }
      else if(InputGiocatore.toInt() == 0 && blocco == 0)
      {
        Serial.println("Il numero 0 si può applicare solo un volta il PRIMO turno");
        numeroSceltoGiocatore = InputGiocatore.toInt();
        Serial.print("Numero scelto  ->  ");
        Serial.println(numeroSceltoGiocatore);
        somma = somma + numeroSceltoGiocatore; 
        ControllaMeta();
        CodiceTurno = 2;
        NumeroTurni++;
        blocco = 1;
      }
      else
      {
        Serial.println("Numero della meta non corretto");
      }
    }

    {
      Serial.println("Selezionare un numero tra 0 per il primo turno,oppure tra 1 e 6");
    }
  }

  if(CodiceTurno == 2 && somma < numeroMetaPARTITA)
  {
      Serial.println("Turno di Angela");
      numeroSceltoAngela = random(1, 7);
      CodiceTurno = 1;
      NumeroTurni++;
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
}

int InizioPartita()
{  
  Serial.print("Immettere la meta preferita da 30 a 99");
  while (Serial.available() > 0) 
  {
    String InputMeta = Serial.readString();

    if (InputMeta.toInt() >= 30 && InputMeta.toInt() <= 99) 
    {
      numeroMetaPARTITA = InputMeta.toInt();
      Serial.print("Punti Meta  :  ");
      Serial.println(numeroMetaPARTITA);
    }
    else 
    {
      Serial.println("Numero della meta non corretto");
    }

  }

  if(numeroMetaPARTITA > 99)
  {
    Serial.println("Non oltrepassare la soglia massima consigliata di 99");
  }
  else if(numeroMetaPARTITA < 30)
  {
    Serial.println("Non oltrepassare la soglia minima consigliata di 30");
  }
  else
  {
    return numeroMetaPARTITA;
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
    Serial.print("Hai Perso - La meta è stata oltrepassata dall'Utente");
    CodiceTurno = 0;
  }
  else if(somma > numeroMetaPARTITA && CodiceTurno == 2)
  {
    Serial.print("Hai Vinto - La meta è stata oltrepassata da Angela");
    CodiceTurno = 0;
  }
  else if(somma == numeroMetaPARTITA && CodiceTurno == 1)
  {
    Serial.print("Hai Vinto - Hai raggiunto la meta prima di Angela");
    CodiceTurno = 0;
  }
    else if(somma == numeroMetaPARTITA && CodiceTurno == 2)
  {
    Serial.print("Hai Perso - Angela ha ragginto la meta per prima");
    CodiceTurno = 0;
  }
}

