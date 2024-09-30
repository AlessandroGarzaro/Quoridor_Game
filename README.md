# Quoridor_Game
Quoridor Game implemented on the LandTiger Board

## Descrizione del Progetto
Questo progetto riguarda l'implementazione del gioco da tavolo astratto **Quoridor** sulla scheda **LandTiger** o utilizzando il suo emulatore tramite l'ambiente di sviluppo **Keil μVision**. L'obiettivo principale è acquisire familiarità con il debug del software su questa piattaforma, emulando il comportamento del microcontrollore **LPC1768**.

## Descrizione del Gioco
**Quoridor** è un gioco da tavolo in cui due giocatori competono per portare il proprio token sulla linea opposta del tabellone. Durante il loro turno, i giocatori possono:
- Muoversi orizzontalmente o verticalmente.
- Posizionare barriere per ostacolare l'avversario.

Ogni giocatore dispone di **8 barriere** e il gioco si svolge su un tabellone **7x7**.

## Funzionalità Implementate
- **Movimento del token**: Il giocatore può muoversi di una casella in verticale o in orizzontale tramite il joystick della scheda.
- **Posizionamento delle barriere**: Le barriere possono essere inserite tra le caselle per bloccare l'avversario, utilizzando il joystick e i pulsanti di controllo.
- **Controllo del tempo**: Ogni giocatore ha **20 secondi** per fare la propria mossa; se il tempo scade, il giocatore perde il turno.
- **Gestione del gioco**: Il gioco inizia premendo il pulsante **INT0**. Le mosse dei due giocatori si alternano fino a quando uno raggiunge il lato opposto e vince.

## Output Grafico
- Visualizzazione del tabellone **7x7** e dei token dei giocatori.
- Indicazione delle mosse disponibili e delle barriere posizionate.
- Visualizzazione di messaggi di errore (ad esempio: fine delle barriere o tempo scaduto).
