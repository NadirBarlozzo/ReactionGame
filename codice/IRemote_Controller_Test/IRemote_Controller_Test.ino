#include <boarddefs.h>
#include <IRremote.h>
#include <IRremoteInt.h>
#include <ir_Lego_PF_BitStreamEncoder.h>

const byte RECV_PIN = 11;
IRrecv irrecv(RECV_PIN);
decode_results results;

long arraySelected[2];
int arrayFinal[2];
long val;
int modSelected;
bool b = true;

long button0 = 16738455;
long button1 = 16724175;
long button2 = 16718055;
long button3 = 16743045;
long button4 = 16716015;
long button5 = 16726215;
long button6 = 16734885;
long button7 = 16728765;
long button8 = 16730805;
long button9 = 16732845;
long buttonS = 16748655;

void setup() {
  Serial.begin(9600);
  irrecv.enableIRIn();
}

void loop()
{
  if (irrecv.decode(&results))
  {
    val = results.value;
    if (val == buttonS)
    {
      Serial.println("Premuto +");
      bool a = true;
      while (a)
      {
        if (irrecv.decode(&results))
        {
          //Serial.println(results.value);
          val = results.value;
          if (
            val == button0 || val == button1 ||
            val == button2 || val == button3 ||
            val == button4 || val == button5 ||
            val == button6 || val == button7 ||
            val == button8 || val == button9
          )
          {
            Serial.println("Selezionato primo numero");
            arraySelected[0] = val;
            delay(1);
            irrecv.resume();
            while (a)
            { 
              if (irrecv.decode(&results))
              {
                val = results.value;
                if (
                  val == button0 || val == button1 ||
                  val == button2 || val == button3 ||
                  val == button4 || val == button5 ||
                  val == button6 || val == button7 ||
                  val == button8 || val == button9
                )
                {
                  Serial.println("Selezionato secondo numero");
                  arraySelected[1] = val;

                  a = false;

                  convertValueToArray();
                  modSelected = convertArrayToNumber();
                }
                irrecv.resume();
              }
            }
          }
          irrecv.resume();
        }

      }
    }
    irrecv.resume();
  }

  if(modSelected != NULL)
  {
    if(b)
    {
      if(modSelected != -1)
      {
        Serial.print("Modalita' selezionata: ");
        Serial.println(modSelected); 
        
      }
      else
      {
        Serial.println("Modalita' fino a numero 23"); 
      }
      b = false;
    }
  }
}

void convertValueToArray()
{
  for (int i = 0; i < 2; i++)
  {
    if (arraySelected[i] == 16738455)
    {
      arrayFinal[i] = 0;
    }
    else if (arraySelected[i] == 16724175)
    {
      arrayFinal[i] = 1;
    }
    else if (arraySelected[i] == 16718055)
    {
      arrayFinal[i] = 2;
    }
    else if (arraySelected[i] == 16743045)
    {
      arrayFinal[i] = 3;
    }
    else if (arraySelected[i] == 16716015)
    {
      arrayFinal[i] = 4;
    }
    else if (arraySelected[i] == 16726215)
    {
      arrayFinal[i] = 5;
    }
    else if (arraySelected[i] == 16734885)
    {
      arrayFinal[i] = 6;
    }
    else if (arraySelected[i] == 16728765)
    {
      arrayFinal[i] = 7;
    }
    else if (arraySelected[i] == 16730805)
    {
      arrayFinal[i] = 8;
    }
    else if (arraySelected[i] == 16732845)
    {
      arrayFinal[i] = 9;
    }
  }
}

int convertArrayToNumber()
{
  if(arrayFinal[0] != NULL && arrayFinal[1] != NULL)
  {
    int c = arrayFinal[0]*10 + arrayFinal[1]; 
    if(c < 24)
    {
      return c;
    }
    else
    {
      return -1;
    }
  }
}

