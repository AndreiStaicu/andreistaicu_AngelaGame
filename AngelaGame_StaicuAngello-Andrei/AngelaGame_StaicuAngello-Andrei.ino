
  int numeroMetaScelto = 50;
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
  
// ValoreSelezionabile();

if(turni == 1)
{
  
}

}
void Partita()
{
  
}

 void AumentaMeta()
 {
  if(numeroMetaScelto == 99)
  {
    Serial.Print("Soglia massima raggunta")
  }
  else
  {
    numeroMetaScelto++;
  }
 }

 void DiminuisciMeta()
 {
  if(numeroMetaScelto == 30)
  {
    Serial.Print("Soglia minima raggiunta")
  }
  else
  {
    numeroMetaScelto--;
  }
 }
 
/*void ValoreSelezionabile()
{
  switch (Giocata)
  {
    case 0:
    Giocatore = 1;
    case 1 || 6:
    break;
    case 2 || 5:
    break;
    case 3 || 4:
  }
}
*/


