# Bomberman - Progetto di Programmazione 1

Questo è il nostro progetto per l'esame di Programmazione 1 (Corso di Laurea in Informatica presso l'Università di Bologna). 
Abbiamo ricreato il classico **Bomberman** da giocare interamente da terminale, utilizzando il linguaggio **C++** e la libreria grafica **ncurses**.

## Funzionalità e Gameplay
Il giocatore si muove all'interno di una mappa 20x40 procedurale (generata casualmente ad ogni avvio). L'obiettivo è farsi strada distruggendo le casse (`%`), raccogliendo i potenziamenti ed eliminando tutti i nemici (`O`) per poter passare al livello successivo. 

### Comandi Principali
* **W, A, S, D** - Movimento del personaggio (`@`)
* **X** - Piazza una bomba (`B`). La bomba esploderà dopo 3 secondi, fatevi da parte!
* **N / P** - Naviga tra i livelli (Next o Prev)
* **Mouse** - Puoi usare il click del mouse per navigare comodamente nei bottoni del menù principale.

### Oggetti (Power-Up)
Quando distruggi una cassa, hai la possibilità di trovare degli oggetti temporanei o permanenti:
* **[R] Range:** Aumenta il raggio dell'esplosione delle bombe di 2 caselle (l'effetto dura per i successivi 3 utilizzi).
* **[S] Speed:** Raddoppia la velocità del personaggio per 5 secondi.
* **[L] Life:** Ti regala una vita extra per resistere agli attacchi.

##  Compilazione e Avvio

Il progetto è **multipiattaforma**: funziona sia nativamente su distribuzioni Linux, sia su Windows (grazie all'adattamento tramite la libreria `pdcurses`).
Per farlo partire, assicurati di avere installato un compilatore come `g++` e la libreria di sviluppo `ncurses` (es. `sudo apt install libncurses5-dev` su Ubuntu).

**Metodo 1: Tramite Makefile (Veloce)**
Apri il terminale nella directory principale ed esegui:
```bash
make
./bomberman
```

**Metodo 2: Tramite CMake**
Se preferisci CMake o sei su Windows, puoi compilare così:
```bash
mkdir build
cd build
cmake ..
make
./bomberman
```
*(Nota: il gioco mette il terminale in pausa in automatico se lo rimpicciolisci troppo!)*

## Il Gruppo di Lavoro
Il lavoro è stato organizzato e suddiviso in 3 parti distinte:
* **Lorenzo Gaglioti**: Gestione fisica del Player, sistema delle Bombe, comportamento IA dei Nemici polimorfici e implementazione delle liste concatenate.
* **Imran Numan Ali**: Generazione procedurale (LCG) dell'ambiente (Mappa), sistema di collisioni "Single Source of Truth", Items e lista bidirezionale dei Livelli.
* **Thomas Ghini**: Sistema responsivo dello Schermo, schermate Menu e Game Over (con click del mouse), calcolo del Tempo e gestione del salvataggio file della Classifica.


