#define NOTE_B0 31

#define NOTE_C1 33

#define NOTE_CS1 35

#define NOTE_D1 37

#define NOTE_DS1 39

#define NOTE_E1 41

#define NOTE_F1 44

#define NOTE_FS1 46

#define NOTE_G1 49

#define NOTE_GS1 52

#define NOTE_A1 55

#define NOTE_AS1 58

#define NOTE_B1 62

#define NOTE_C2 65

#define NOTE_CS2 69

#define NOTE_D2 73

#define NOTE_DS2 78

#define NOTE_E2 82

#define NOTE_F2 87

#define NOTE_FS2 93

#define NOTE_G2 98

#define NOTE_GS2 104

#define NOTE_A2 110

#define NOTE_AS2 117

#define NOTE_B2 123

#define NOTE_C3 131

#define NOTE_CS3 139

#define NOTE_D3 147

#define NOTE_DS3 156

#define NOTE_E3 165

#define NOTE_F3 175

#define NOTE_FS3 185

#define NOTE_G3 196

#define NOTE_GS3 208

#define NOTE_A3 220

#define NOTE_AS3 233

#define NOTE_B3 247

#define NOTE_C4 262

#define NOTE_CS4 277

#define NOTE_D4 294

#define NOTE_DS4 311

#define NOTE_E4 330

#define NOTE_F4 349

#define NOTE_FS4 370

#define NOTE_G4 392

#define NOTE_GS4 415

#define NOTE_A4 440

#define NOTE_AS4 466

#define NOTE_B4 494

#define NOTE_C5 523

#define NOTE_CS5 554

#define NOTE_D5 587

#define NOTE_DS5 622

#define NOTE_E5 659

#define NOTE_F5 698

#define NOTE_FS5 740

#define NOTE_G5 784

#define NOTE_GS5 831

#define NOTE_A5 880

#define NOTE_AS5 932

#define NOTE_B5 988

#define NOTE_C6 1047

#define NOTE_CS6 1109

#define NOTE_D6 1175

#define NOTE_DS6 1245

#define NOTE_E6 1319

#define NOTE_F6 1397

#define NOTE_FS6 1480

#define NOTE_G6 1568

#define NOTE_GS6 1661

#define NOTE_A6 1760

#define NOTE_AS6 1865

#define NOTE_B6 1976

#define NOTE_C7 2093

#define NOTE_CS7 2217

#define NOTE_D7 2349

#define NOTE_DS7 2489

#define NOTE_E7 2637

#define NOTE_F7 2794

#define NOTE_FS7 2960

#define NOTE_G7 3136

#define NOTE_GS7 3322

#define NOTE_A7 3520

#define NOTE_AS7 3729

#define NOTE_B7 3951

#define NOTE_C8 4186

#define NOTE_CS8 4435

#define NOTE_D8 4699

#define NOTE_DS8 4978



#define CHOICE_OFF      0 

#define CHOICE_NONE     0 

#define CHOICE_RED  (1 << 0)

#define CHOICE_GREEN    (1 << 1)

#define CHOICE_BLUE (1 << 2)

#define CHOICE_YELLOW   (1 << 3)



#define LED_RED     10

#define LED_GREEN   3

#define LED_BLUE    13

#define LED_YELLOW  5




#define BUTTON_RED    9

#define BUTTON_GREEN  2

#define BUTTON_BLUE   12

#define BUTTON_YELLOW 6




#define BUZZER1  4

#define BUZZER2  7




#define ROUNDS_TO_WIN      13 

#define ENTRY_TIME_LIMIT   3000 



#define MODE_MEMORY  0

#define MODE_BATTLE  1

#define MODE_BEEGEES 2





byte gameMode = MODE_MEMORY; 

byte gameBoard[32]; 

byte gameRound = 0; 



void setup()

{



  pinMode(BUTTON_RED, INPUT_PULLUP);

  pinMode(BUTTON_GREEN, INPUT_PULLUP);

  pinMode(BUTTON_BLUE, INPUT_PULLUP);

  pinMode(BUTTON_YELLOW, INPUT_PULLUP);



  pinMode(LED_RED, OUTPUT);

  pinMode(LED_GREEN, OUTPUT);

  pinMode(LED_BLUE, OUTPUT);

  pinMode(LED_YELLOW, OUTPUT);



  pinMode(BUZZER1, OUTPUT);

  pinMode(BUZZER2, OUTPUT);



 

  gameMode = MODE_MEMORY; 



  

  if (checkButton() == CHOICE_YELLOW) play_beegees();





  if (checkButton() == CHOICE_GREEN)

  {

    gameMode = MODE_BATTLE; 





    setLEDs(CHOICE_GREEN);

    toner(CHOICE_GREEN, 150);



    setLEDs(CHOICE_RED | CHOICE_BLUE | CHOICE_YELLOW);



    while(checkButton() != CHOICE_NONE) ; 





  }



  play_winner(); 
}



void loop()

{

  attractMode(); 


  setLEDs(CHOICE_RED | CHOICE_GREEN | CHOICE_BLUE | CHOICE_YELLOW);

  delay(1000);

  setLEDs(CHOICE_OFF); 

  delay(250);



  if (gameMode == MODE_MEMORY)

  {

  
    if (play_memory() == true) 

      play_winner(); 

    else 

      play_loser(); 

  }



  if (gameMode == MODE_BATTLE)

  {

    play_battle(); 



    play_loser(); 

  }

}



//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=

//The following functions are related to the game

//0 = LOSS | 1 = WIN

boolean play_memory(void)

{

  randomSeed(millis()); 



  gameRound = 0; 



  while (gameRound < ROUNDS_TO_WIN) 

  {

    add_to_moves(); 



    playMoves(); 



   

    for (byte currentMove = 0 ; currentMove < gameRound ; currentMove++)

    {

      byte choice = wait_for_button(); 



      if (choice == 0) return false; 



      if (choice != gameBoard[currentMove]) return false; 

    }



    delay(1000); 

  }



  return true; 

}

void playMoves(void)

{

  for (byte currentMove = 0 ; currentMove < gameRound ; currentMove++) 

  {

    toner(gameBoard[currentMove], 150);



    delay(150); 
  }

}

// Adds a button to the sequence

void add_to_moves(void)

{

  byte newButton = random(0, 4); 





  if(newButton == 0) newButton = CHOICE_RED;

  else if(newButton == 1) newButton = CHOICE_GREEN;

  else if(newButton == 2) newButton = CHOICE_BLUE;

  else if(newButton == 3) newButton = CHOICE_YELLOW;



  gameBoard[gameRound++] = newButton; 

}



//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=

// Hardware related functions

void setLEDs(byte leds)

{

  if ((leds & CHOICE_RED) != 0)

    digitalWrite(LED_RED, HIGH);

  else

    digitalWrite(LED_RED, LOW);



  if ((leds & CHOICE_GREEN) != 0)

    digitalWrite(LED_GREEN, HIGH);

  else

    digitalWrite(LED_GREEN, LOW);



  if ((leds & CHOICE_BLUE) != 0)

    digitalWrite(LED_BLUE, HIGH);

  else

    digitalWrite(LED_BLUE, LOW);



  if ((leds & CHOICE_YELLOW) != 0)

    digitalWrite(LED_YELLOW, HIGH);

  else

    digitalWrite(LED_YELLOW, LOW);

}




byte wait_for_button(void)

{

  long startTime = millis(); 



  while ( (millis() - startTime) < ENTRY_TIME_LIMIT) 

  {

    byte button = checkButton();



    if (button != CHOICE_NONE)

    { 

      toner(button, 150); 



      while(checkButton() != CHOICE_NONE) ;  



      delay(10); 



      return button;

    }



  }



  return CHOICE_NONE; 

}




byte checkButton(void)

{

  if (digitalRead(BUTTON_RED) == 0) return(CHOICE_RED); 

  else if (digitalRead(BUTTON_GREEN) == 0) return(CHOICE_GREEN); 

  else if (digitalRead(BUTTON_BLUE) == 0) return(CHOICE_BLUE); 

  else if (digitalRead(BUTTON_YELLOW) == 0) return(CHOICE_YELLOW);



  return(CHOICE_NONE); 

}




void toner(byte which, int buzz_length_ms)

{

  setLEDs(which); 



  
  switch(which) 

  {

  case CHOICE_RED:

    buzz_sound(buzz_length_ms, 1136); 

    break;

  case CHOICE_GREEN:

    buzz_sound(buzz_length_ms, 568); 

    break;

  case CHOICE_BLUE:

    buzz_sound(buzz_length_ms, 851); 

    break;

  case CHOICE_YELLOW:

    buzz_sound(buzz_length_ms, 638); 

    break;

  }



  setLEDs(CHOICE_OFF);

}




void buzz_sound(int buzz_length_ms, int buzz_delay_us)

{

  

  long buzz_length_us = buzz_length_ms * (long)1000;



 

  while (buzz_length_us > (buzz_delay_us * 2))

  {

    buzz_length_us -= buzz_delay_us * 2; 


    digitalWrite(BUZZER1, LOW);

    digitalWrite(BUZZER2, HIGH);

    delayMicroseconds(buzz_delay_us);



    digitalWrite(BUZZER1, HIGH);

    digitalWrite(BUZZER2, LOW);

    delayMicroseconds(buzz_delay_us);

  }

}





void play_winner(void)

{

  setLEDs(CHOICE_GREEN | CHOICE_BLUE);

  winner_sound();

  setLEDs(CHOICE_RED | CHOICE_YELLOW);

  winner_sound();

  setLEDs(CHOICE_GREEN | CHOICE_BLUE);

  winner_sound();

  setLEDs(CHOICE_RED | CHOICE_YELLOW);

  winner_sound();

}



void winner_sound(void)

{



  for (byte x = 250 ; x > 70 ; x--)

  {

    for (byte y = 0 ; y < 3 ; y++)

    {

      digitalWrite(BUZZER2, HIGH);

      digitalWrite(BUZZER1, LOW);

      delayMicroseconds(x);



      digitalWrite(BUZZER2, LOW);

      digitalWrite(BUZZER1, HIGH);

      delayMicroseconds(x);

    }

  }

}



void play_loser(void)

{

  setLEDs(CHOICE_RED | CHOICE_GREEN);

  buzz_sound(255, 1500);



  setLEDs(CHOICE_BLUE | CHOICE_YELLOW);

  buzz_sound(255, 1500);



  setLEDs(CHOICE_RED | CHOICE_GREEN);

  buzz_sound(255, 1500);



  setLEDs(CHOICE_BLUE | CHOICE_YELLOW);

  buzz_sound(255, 1500);

}




void attractMode(void)

{

  while(1) 

  {

    setLEDs(CHOICE_RED);

    delay(100);

    if (checkButton() != CHOICE_NONE) return;



    setLEDs(CHOICE_BLUE);

    delay(100);

    if (checkButton() != CHOICE_NONE) return;



    setLEDs(CHOICE_GREEN);

    delay(100);

    if (checkButton() != CHOICE_NONE) return;



    setLEDs(CHOICE_YELLOW);

    delay(100);

    if (checkButton() != CHOICE_NONE) return;

  }

}
