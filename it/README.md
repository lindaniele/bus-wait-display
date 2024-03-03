# Monitoraggio Tempi di Attesa dell'ATM

Il progetto "Monitoraggio Tempi di Attesa dell'ATM" utilizza un microcontrollore ESP8266 e uno schermo LCD per mostrare i tempi di attesa in tempo reale dei mezzi ATM Milano (Azienda Trasporti Milanesi). Impostando il codice della linea e della fermata, il dispositivo recupera le informazioni sui tempi di attesa dal server di GiroMilano ATM e le visualizza sullo schermo LCD.

Il linguaggio usato in questo README potrebbe risultare purista. [Leggilo in inglese.](../README.md)

## Indice
- [Panoramica](#panoramica)
- [Periferiche necessarie](#periferiche-necessarie)
- [Programmi necessari](#programmi-necessari)
- [Installazione e configurazione](#installazione-e-configurazione)
- [Utilizzo](#utilizzo)
- [Contribuisci](#contribuisci)
- [Licenza](#licenza)

## Panoramica

Il presente progetto offre un modo conveniente per monitorare i tempi di attesa di una specifica linea di autobus in una determinata fermata in tempo reale. Il microcontrollore ESP8266 si connette al server di ATM tramite Wi-Fi, recupera le informazioni sui tempi di attesa e le visualizza sullo schermo LCD. Con questa visualizzazione, gli utenti possono pianificare i loro viaggi con i mezzi più efficientemente.

## Periferiche necessarie

Per configurare il presente progetto, avrai bisogno dei seguenti componenti fisici:

- Microcontrollore ESP8266
- Schermo LCD (compatibile con la libreria LiquidCrystal_I2C e preferibilmente in formato 16x2)
- Cavi ponticello
- Basetta sperimentale (opzionale, per il prototipaggio)
- Alimentatore o pacchetto di batterie (se non alimentato tramite USB)

## Programmi necessari

Il progetto si basa sui seguenti programmi:

- Ambiente di sviluppo integrato di Arduino
- Libreria ESP8266WiFi
- Libreria ESP8266HTTPClient
- Libreria WiFiClient
- Libreria Arduino JSON
- Libreria LiquidCrystal_I2C

Assicurati di avere queste librerie installate nel tuo ambiente di sviluppo integrato prima di procedere con l'installazione.

## Installazione e configurazione

Segui questi passaggi per installare e configurare il progetto:

1. Clona o scarica il presente progetto sul tuo computer. 

2. Apri l'ambiente di sviluppo integrato e naviga in **File > Apri**. Seleziona il documento principale del progetto (quello con l'estensione `.ino`) dai documenti scaricati. 

3. Collega il microcontrollore ESP8266 e lo schermo LCD al tuo computer. 

4. Nell'ambiente di sviluppo integrato, assicurati di aver selezionato la scheda e la porta appropriate per il microcontrollore ESP8266:
   - Vai su **Strumenti > Scheda** e seleziona il modello della tua scheda ESP8266.
   - Vai su **Strumenti > Porta** e seleziona la porta COM a cui è collegato l'ESP8266. 

5. Apri il documento `main.ino` e modifica le seguenti variabili secondo le tue esigenze:
   - `ssid`: Imposta il nome identificativo della tua rete locale.
   - `password`: Imposta il codice d'accesso della tua rete locale.
   - `myLineCode`: Imposta il codice della linea di autobus di tuo interesse.
   - `myStopCode`: Imposta il codice della fermata corrispondente alla fermata dell'autobus che desideri monitorare. 

6. Carica il codice sul microcontrollore ESP8266 pigiando sul pulsante "Carica" nell'ambiente di sviluppo integrato. 

7. Una volta completato il caricamento, apri il Monitor Seriale nell'ambiente di sviluppo integrato per visualizzare lo stato della connessione e l'indirizzo IP del microcontrollore. 

8. Collega lo schermo LCD al microcontrollore ESP8266 seguendo le istruzioni di cablaggio fornite nel progetto. Generalmente, i collegamenti sono:
   - **VCC** del LCD a **3.3V** sull'ESP8266.
     - La maggior parte degli schermi LCD I2C è progettata per funzionare con un'alimentazione di **5V**. Tuttavia, molti possono funzionare anche a 3.3V, che è la tensione di esercizio dell'ESP8266. Assicurati che il tuo specifico modello di LCD possa funzionare in modo sicuro e affidabile a 3.3V. Se il tuo LCD richiede 5V, potresti dover utilizzare un regolatore di tensione per collegarlo in sicurezza all'ESP8266.
   - **GND** del LCD a **GND** sull'ESP8266.
   - **SDA** del LCD a **D2** (o al pin I2C SDA) sull'ESP8266.
   - **SCL** del LCD a **D1** (o al pin I2C SCL) sull'ESP8266. 

9. Accendi il microcontrollore ESP8266. Lo schermo LCD dovrebbe mostrare il codice della linea dell'autobus o del tram e le informazioni sui tempi di attesa.


## Utilizzo

Dopo il processo di installazione e configurazione, il progetto recupererà continuamente le informazioni sui tempi di attesa per la linea e il codice della fermata specificati dal server di ATM. Il display LCD aggiornerà le informazioni sui tempi di attesa più recenti ogni pochi secondi.

Monitora lo schermo LCD per rimanere aggiornato sui tempi di attesa in tempo reale dell'autobus o del tram. Ecco alcune considerazioni sull'utilizzo:

- Assicurati che il microcontrollore ESP8266 sia connesso a una rete stabile con accesso a Internet.
- Assicurati che il codice della linea dell'autobus o del tram e il codice della fermata che hai impostato corrispondano a valori validi riconosciuti dal server di ATM.
- Lo schermo LCD aggiornerà le informazioni sui tempi di attesa all'intervallo specificato (5 secondi per impostazione predefinita). Puoi modificare la variabile `timerDelay` nel codice per regolare la frequenza di aggiornamento secondo la tua preferenza.
- Se le informazioni sui tempi di attesa cambiano, il display LCD si aggiornerà di conseguenza. Il nuovo tempo di attesa sostituirà quello precedente sullo schermo.
- Se la connessione si perde, lo schermo LCD indicherà che la connessione è disconnessa.
- Se desideri monitorare una diversa linea di autobus o fermata, modifica le variabili `myLineCode` e `myStopCode` nel codice, carica il codice aggiornato sull'ESP8266 e riavvia il dispositivo.

Si prega di notare che questo progetto si basa sulla disponibilità e sull'accuratezza delle informazioni sui tempi di attesa fornite dal server di ATM. Qualsiasi modifica o problema con l'API del server o con i dati può influire sull'affidabilità delle informazioni visualizzate.

## Contribuisci

Sentiti libero di contribuire al progetto! Se hai idee, miglioramenti o correzioni, non esitare a segnalare un problema o inviare una richiesta di pull su GitHub.

## Licenza

Il progetto "Monitoraggio Tempi di Attesa dell'ATM" di Daniele Lin è [conforme ai Termini e Condizioni di ATM](CONFORMITÀ_ATM.md) ed è concesso in licenza secondo
[Licenza Creative Commons Attribuzione - Non commerciale - Condividi allo stesso modo 4.0 Internazionale][cc-by-nc-sa].

[![CC BY-NC-SA 4.0][cc-by-nc-sa-image]][cc-by-nc-sa]

[cc-by-nc-sa]: http://creativecommons.org/licenses/by-nc-sa/4.0/deed.it
[cc-by-nc-sa-image]: https://licensebuttons.net/l/by-nc-sa/4.0/88x31.png