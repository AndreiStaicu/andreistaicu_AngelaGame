
  int numeroMetaScelto = 50;
  int numeroMetaPARTITA;
  int numeroSceltoGiocatore;
  int numeroSceltoAngela;
  int somma = numeroSceltoGiocatore + numeroSceltoAngela;
  int Giocata = 1;
  int PrimaGiocata[7] = {0,1,2,3,4,5,6};
  int Giocate[4];
  int Turni = 1;

void setup() {
  // put your setup code here, to run once:
}

void loop() {
  // put your main code here, to run repeatedly:
}

//////////////////AREA METODI/////////////////

void AumentaMeta()
{
  if(numeroMetaScelto > 99)
  {
    Serial.write("Non oltrepassare la soglia massima consigliata di 99")
  }
  else
  {
    numeroMetaScelto++;
  }
}

void RiduciMeta()
{
  if(numeroMetaScelto < 30)
  {
    Serial.write("Non oltrepassare la soglia minima consigliata di 30")
  }
}

void ControllaMeta()
{
  if(numeroMetaPARTITA 
}

