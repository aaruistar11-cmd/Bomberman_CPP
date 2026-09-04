# Relazione Tecnica Progetto: Bomberman
**Corso**: Programmazione 1
**Candidati**: 

---

## INTRODUZIONE E VINCOLI DI PROGETTO
Il progetto è una rivisitazione del classico gioco *Bomberman*, realizzato in **C++11** eseguito in terminale tramite la libreria grafica **ncurses**.
L'intera codebase è stata progettata nel rigido rispetto dei **vincoli accademici tipici del corso di Programmazione 1**:
- **Nessuna Standard Template Library (STL)** per i contenitori: divieto di utilizzo di `std::vector`, `std::map` o `std::string`. Tutto è gestito tramite array nativi C-style e strutture dati custom (liste concatenate).
- **Gestione manuale della Memoria**: ogni istanza dinamica creata tramite la keyword `new` viene rigorosamente tracciata e distrutta tramite `delete` per evitare *memory leak*.
- **Paradigma Object-Oriented (OOP)**: il codice è diviso in classi incapsulate. Si fa uso dell'Information Hiding (attributi `protected` o privati con *getter/setter*) e si separa la dichiarazione delle classi (`include/*.hpp`) dalle loro implementazioni (`src/*.cpp`).

---

## 1. STRUTTURE DATI E GESTIONE MEMORIA (Le Liste Concatenate)

Per gestire una quantità variabile di entità dinamiche (bombe in esplosione, nemici sulla mappa, oggetti a terra) senza usare `std::vector`, abbiamo implementato delle **Liste Concatenate Singole** nel file `Lists.hpp`.
Abbiamo definito delle struct chiamate "nodi" (es. `bnode`, `enode`, `inode`), ognuna contenente:
1. Un puntatore (o istanza) all'entità (`Bomb`, `Enemy*`, `Item*`).
2. Un puntatore `next` al nodo successivo.

**Vantaggio Architetturale**: L'inserimento avviene in testa (O(1)). L'eliminazione in mezzo alla lista avviene "ricucendo" i puntatori (`prev->next = curr->next`) e chiamando la `delete` sul nodo rimosso e sull'oggetto puntato.
**Pulizia della Memoria (Garbage Collection)**:
Il metodo `Gamemaster::svuotaEntita()` è chiamato ad ogni cambio livello e a fine partita. Questa funzione itera i puntatori (usando un ciclo `while(curr != nullptr)`), salvando il puntatore al prossimo nodo prima di chiamare `delete` su quello attuale, garantendo una disallocazione a cascata impeccabile e impedendo segment fault.

---

## 2. GESTORE LIVELLI (Lista Bidirezionale e Transizioni)

I livelli (`Mappa`) sono gestiti dalla classe `GestoreLivelli`, strutturata come una **Lista Bidirezionale** (Doubly Linked List).
Ogni istanza di `Mappa` possiede due puntatori pubblici: `Mappa* next` e `Mappa* prev`.
- **Navigazione**: Il giocatore può usare i tasti `n` e `p` per cambiare livello.
- **Persistenza**: Quando si cambia mappa, la funzione nel `Gamemaster` conta quanti nemici sono ancora vivi nella lista (`ehead`) e salva questo intero in `mappa->nemici_rimasti`. Al ritorno, `spawnNemici` spawnerà esattamente questa quantità.
- **Deallocazione Dinamica (rimuoviLivello)**: Quando un livello viene "sconfitto" (0 nemici), il `Gamemaster` chiama `GestoreLivelli::rimuoviLivello()`. Questa funzione scavalca il livello attuale (es. `livello->prev->next = livello->next`), restituisce un livello adiacente in cui spostare il giocatore, e infine effettua un `delete` della mappa eliminata liberando fisicamente la RAM in real-time.

---

## 3. ARCHITETTURA DELLE CLASSI E POLIMORFISMO

Il progetto sfrutta fortemente i concetti OOP. 

**Il Gamemaster (State Machine)**
Cuore pulsante del gioco, controlla il loop principale (bloccante a `timeout(100)` millisecondi) in `startpartita()`. Raccoglie l'input, sposta le entità, disegna la mappa, e gestisce lo *State Machine* (STATO_MENU, STATO_PARTITA, STATO_FINE).

**Mappa e Generazione Procedurale**
Per l'algoritmo di piazzamento di muri (fissi `#` o fragili `%`) è stato implementato in `Mappa::generaCasuale()` un **algoritmo LCG (Linear Congruential Generator)** usando `seme_casuale`, per simulare l'aleatorietà senza infrangere restrizioni di librerie esterne.
La mappa contiene l'array logico 20x40 `char griglia[20][40]`. Tutto il rendering a schermo dei caratteri e dei colori `ncurses` passa da `disegnaLayout()`.

**Nemici (Ereditarietà e Polimorfismo)**
La classe base `Enemy` è estesa da derivate come `Enemy_t1`, `Enemy_t2`, `Enemy_t3`. 
Anche se usano IA semplici (movimenti sequenziali, randomici, o a inseguimento riga/colonna), il design polimorfico permette al Gamemaster di ciclarli tramite un puntatore alla classe base `Enemy*`, chiamando il metodo virtuale (o sovrascritto) corretto per lo spostamento.

---

## 4. GESTIONE TEMPO, COOLDOWN E MECCANICHE

**1. Il timer di gioco (`<ctime>`)**
Tramite la libreria `time(NULL)`, la classe `Tempo` calcola i secondi trascorsi con una sottrazione matematica pura rispetto all'ora di avvio. Un livello completato evoca `Tempo.aggiungiTempo(120)`, che incrementa la durata totale concessa.

**2. Cooldown Bombe (`<chrono>`)**
Per prevenire il *bomb-spamming*, la classe `Player` utilizza `std::chrono::steady_clock`. È un orologio ad altissima risoluzione e monotono (non viene sfalsato se cambia l'ora di sistema locale). Quando il giocatore piazza una bomba, si registra il timestamp. La funzione `canPlaceBomb()` consente una nuova bomba solo se la differenza (`duration_cast<milliseconds>`) supera i 1000 millisecondi.

**3. Sistema di Power-Up (Items)**
Il sistema di Item estrae casualmente oggetti quando scoppia una cassa (`%`). 
La logica sfrutta la *Dependency Injection*: quando il player calpesta l'item, viene invocato `item->apply(Player* p)`. L'item modifica internamente il Player senza che il `Gamemaster` debba conoscere la logica di quell'oggetto specifico, rispettando il *Single Responsibility Principle*.
Tipi di power-up:
- **Range (R)**: Ricarica bonus consumabili che aumentano il raggio delle successive bombe a croce (+2 tessere).
- **Speed (S)**: Regala dei "ticks" di velocità. Per 5 secondi, il Gamemaster elaborerà due iterazioni di getch()/input del giocatore invece di una, raddoppiandone fisicamente la velocità su schermo.
- **Life (L)**: Ripristina vite perse (fino al cap massimo).

**4. Gestione Danni e Collisioni**
In caso di tocco letale (fuoco di bomba `*` o nemici `O`), la funzione `Player::looseLife()` scala i punti vita. Invece del game over istantaneo, il giocatore ha un *teleport* forzato di sicurezza alle coordinate originarie `(1,1)` per concedergli una seconda chance in quel livello. Se la vita raggiunge lo zero, si passa a `STATO_FINE`.

---

## 5. FILE I/O E CLASSIFICA

Il punteggio del giocatore scala uccidendo nemici, trovando casse e superando i livelli (+500 pt a stage). Inoltre, i secondi risparmiati si convertono in punti bonus alla vittoria (`tempo_rimasto * 10`). 
La `Classifica.cpp` utilizza gli stream di file C++ (`std::ifstream` e `std::ofstream`) per caricare la leaderboard dal `Classifica.txt`. 
Legge riga per riga, memorizza nome utente e punteggio temporaneamente, ordina i risultati aggiornando il record in tempo reale, e li riscrive sul file, il tutto processando array di stringhe e buffer di caratteri classici.

---

## DOMANDE FREQUENTI DA ESAME E RISPOSTE (Q&A)

**Q: Come hai evitato i Memory Leak dato che non potevi usare gli Smart Pointer?**
**A**: Ogni volta che un'entità esce dal gioco (es. una bomba scoppia, un livello termina o un item viene raccolto) il suo nodo viene isolato dalla Linked List modificando i puntatori limitrofi (`prev->next = current->next`). Subito dopo chiamo esplicitamente `delete` sull'oggetto e sul nodo stesso. Ad ogni fine partita (o chiusura prematura) viene garantita la deallocazione massiva dal metodo `svuotaEntita()`.

**Q: Come hai gestito le dipendenze circolari negli headers (se ce ne sono state)?**
**A**: Ho utilizzato la *Forward Declaration* (dichiarando `class Player;` o `class Mappa;` nei vari file `.hpp`) e ho incluso i veri header (`#include "Player.hpp"`) solo all'interno dei file di implementazione `.cpp`. Questo evita che il compilatore entri in un loop di dipendenze (es. Mappa include Player che include Mappa).

**Q: Qual è la differenza tra l'uso di `<ctime>` in `Tempo` e `<chrono>` nel `Player`?**
**A**: `time_t` di `<ctime>` lavora a granularità di secondi ed è sufficiente per il macro-tempo del gioco visibile nella UI. Per il cooldown delle bombe necessitavo di precisione millimetrica sotto il secondo, quindi `std::chrono` (che è standard in C++11) era l'unica soluzione affidabile senza pesare sul loop nativo della macchina.

**Q: Come fate ad allineare perfettamente i bordi della scatola UI in base al livello?**
**A**: Nel metodo `Mappa::disegnaLayout`, invece di usare stringhe hardcoded, abbiamo implementato un calcolo dinamico. Il programma conta quante cifre compongono l'ID del livello dividendo ripetutamente per 10, ricava la lunghezza stringa totale (es. 24 char per livello 1, 25 per 10) e adatta matematicamente il riempimento orizzontale in ASCII per chiudere l'angolo perfettamente a scatto.
