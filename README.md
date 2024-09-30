# Quoridor_Game
Quoridor Game implemented on the LandTiger Board


Questo progetto riguarda l'implementazione del gioco da tavolo astratto Quoridor sulla scheda LandTiger o utilizzando il suo emulatore tramite l'ambiente di sviluppo Keil μVision. L'obiettivo è acquisire familiarità con il debug del software su questa piattaforma, emulando il comportamento del microcontrollore LPC1768.
Descrizione del Gioco

Quoridor è un gioco da tavolo in cui due giocatori cercano di portare il proprio token sulla linea opposta del tabellone, utilizzando mosse orizzontali o verticali e posizionando barriere per ostacolare l'avversario. Ogni giocatore ha 8 barriere a disposizione, e il gioco si svolge su un tabellone 7x7.
Funzionalità Implementate

    Movimento del token: il giocatore può muoversi di una casella in verticale o in orizzontale tramite il joystick sulla scheda.
    Posizionamento delle barriere: le barriere possono essere inserite tra le caselle per bloccare l'avversario, utilizzando il joystick e i pulsanti di controllo.
    Controllo del tempo: ogni giocatore ha 20 secondi per fare la propria mossa, altrimenti perde il turno.
    Gestione del gioco: il gioco inizia premendo il pulsante INT0 e si alternano le mosse dei due giocatori fino alla vittoria.

Output Grafico

    Visualizzazione del tabellone 7x7 e dei token dei giocatori.
    Indicazione delle mosse disponibili e delle barriere posizionate.
    Visualizzazione dei messaggi di errore (es. fine delle barriere, tempo scaduto).
