int8_t answer;
char aux_str[200];

void sendHTTP_REQ(int int_1, int int_2, int int_3) 
{
  Serial.println("Trying to Send Data to Cloud");
  answer = sendATcommand("AT+HTTPINIT", "OK", 20000);
  if (answer == 1)
  {
    answer = sendATcommand("AT+HTTPPARA=\"CID\",1", "OK", 5000);
    if (answer == 1)
    {
      sprintf(aux_str, "AT+HTTPPARA=\"URL\",\"http://shaifur.com/get.php?var1=%d&var2=%d&var3=%d", int_1, int_2, int_3);
      Serial.print(aux_str);
      answer = sendATcommand("\"", "OK", 6000);
      if (answer == 1)
      {
        // Starts GET action
        answer = sendATcommand("AT+HTTPACTION=1", "+HTTPACTION:0,200", 10000);
        if (answer == 0)
        {
          Serial.println(F("Data Sent Successfully!"));
        }
        else
        {
          Serial.println(F("Error getting url"));
        }
      }
      else
      {
        Serial.println(F("Error setting the url"));
      }
    }
    else
    {
      Serial.println(F("Error setting the CID"));
    }
  }
  else
  {
    Serial.println(F("Error initializating"));
  }
  sendATcommand("AT+HTTPTERM", "OK", 5000);
  delay(2000);
}


// sendATcommand
int8_t sendATcommand(char* ATcommand, char* expected_answer1, unsigned int timeout)
{
  uint8_t x = 0,  answer = 0;
  char response[100];
  unsigned long previous;
  memset(response, '\0', 100);    // Initialize the string
  delay(100);
  while ( Serial.available() > 0) Serial.read();   // Clean the input buffer
  Serial.println(ATcommand);    // Send the AT command
  x = 0;
  previous = millis();

  // this loop waits for the answer
  do {
    if (Serial.available() != 0) {
      response[x] = Serial.read();
      x++;
      // check if the desired answer is in the response of the module
      if (strstr(response, expected_answer1) != NULL)
      {
        answer = 1;
      }
    }
    // Waits for the answer with time out
  }
  while ((answer == 0) && ((millis() - previous) < timeout));
  return answer;
}

