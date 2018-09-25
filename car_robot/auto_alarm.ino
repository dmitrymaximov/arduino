
/* init buzzer */
void initBuzz()
{
  pinMode(BUZZ_PIN, OUTPUT);
}
  
void playTone(int _tone, int _duration) 
{
  for (long i = 0; i < _duration * 1000L; i += _tone * 2) 
  {
    digitalWrite(BUZZ_PIN, HIGH);
    delayMicroseconds(_tone);
    digitalWrite(BUZZ_PIN, LOW);
    delayMicroseconds(_tone);      
  }
}
  
void playNote(String note, int duration, int song_tempo) 
{
  for (int i = 0; i < song_tones_count; i++) 
  {
    if (noteNames[i] == note) 
    {
      if (note == "rest")
        delay(duration);
      else
        playTone(tones[i], duration);
    }
  }
  delay(song_tempo / 2);
}

void playSong()
{  
  // Magic is not work..
  //for (int i = 0; i < song_length; i++)
  //  playNote(notes[i], beats[i] * song_tempo, song_tempo);

  playNote(notes[0], beats[0] * song_tempo, song_tempo);
  playNote(notes[1], beats[1] * song_tempo, song_tempo);
  playNote(notes[2], beats[2] * song_tempo, song_tempo);
  playNote(notes[3], beats[3] * song_tempo, song_tempo);
  playNote(notes[4], beats[4] * song_tempo, song_tempo);
  playNote(notes[5], beats[5] * song_tempo, song_tempo);
  playNote(notes[6], beats[6] * song_tempo, song_tempo);
  playNote(notes[7], beats[7] * song_tempo, song_tempo);
  playNote(notes[8], beats[8] * song_tempo, song_tempo);
  playNote(notes[9], beats[9] * song_tempo, song_tempo);
  playNote(notes[10], beats[10] * song_tempo, song_tempo);
  playNote(notes[11], beats[11] * song_tempo, song_tempo);
  playNote(notes[12], beats[12] * song_tempo, song_tempo);
  playNote(notes[13], beats[13] * song_tempo, song_tempo);
  playNote(notes[14], beats[14] * song_tempo, song_tempo);
  playNote(notes[15], beats[15] * song_tempo, song_tempo);
  playNote(notes[16], beats[16] * song_tempo, song_tempo);
  playNote(notes[17], beats[17] * song_tempo, song_tempo);
  playNote(notes[18], beats[18] * song_tempo, song_tempo);
  playNote(notes[19], beats[19] * song_tempo, song_tempo);
  playNote(notes[20], beats[20] * song_tempo, song_tempo);
  playNote(notes[21], beats[21] * song_tempo, song_tempo);
  playNote(notes[22], beats[22] * song_tempo, song_tempo);
  playNote(notes[23], beats[23] * song_tempo, song_tempo);
  playNote(notes[24], beats[24] * song_tempo, song_tempo);
  playNote(notes[25], beats[25] * song_tempo, song_tempo);
  playNote(notes[26], beats[26] * song_tempo, song_tempo);
  playNote(notes[27], beats[27] * song_tempo, song_tempo);
  playNote(notes[28], beats[28] * song_tempo, song_tempo);
  playNote(notes[29], beats[29] * song_tempo, song_tempo);
  playNote(notes[30], beats[30] * song_tempo, song_tempo);
  playNote(notes[31], beats[31] * song_tempo, song_tempo);
  playNote(notes[32], beats[32] * song_tempo, song_tempo);
  playNote(notes[33], beats[33] * song_tempo, song_tempo);
  playNote(notes[34], beats[34] * song_tempo, song_tempo);
  playNote(notes[35], beats[35] * song_tempo, song_tempo);
  playNote(notes[36], beats[36] * song_tempo, song_tempo);
  playNote(notes[37], beats[37] * song_tempo, song_tempo);
  playNote(notes[38], beats[38] * song_tempo, song_tempo);
  playNote(notes[39], beats[39] * song_tempo, song_tempo);
  playNote(notes[40], beats[40] * song_tempo, song_tempo);
  playNote(notes[41], beats[41] * song_tempo, song_tempo);
  playNote(notes[42], beats[42] * song_tempo, song_tempo);
  playNote(notes[43], beats[43] * song_tempo, song_tempo);
  playNote(notes[44], beats[44] * song_tempo, song_tempo);
  playNote(notes[45], beats[45] * song_tempo, song_tempo);
}

