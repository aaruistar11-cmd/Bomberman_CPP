#include "Librerie.hpp"
#include "Classifica.hpp"

Classifica::Classifica(){
    strcpy(numpunti,"INSERISCI QUANTI PUNTI VISUALIZZARE:");
    punti=0;
    backBtn = NULL;
}

// Quante righe ci sono nel file
int Classifica::contaRighe(char t[]) {
    ifstream inputFile;
    inputFile.open(t);
    if (!inputFile) return -1;
    int righe = 0;
    char ch;
    bool vuoto = true;
    while (!inputFile.eof()) {
        inputFile.get(ch);
        if (inputFile.eof()) break;
        vuoto = false;
        if (ch == '\n') {
            righe++;
            vuoto = true;
        }
    }
    if (vuoto == false) righe++;
    inputFile.close();
    return righe;
}

// Bottone per tornare indietro
void Classifica::aggiornaBackButton() {
    if (backBtn != NULL) {
        werase(backBtn);
        delwin(backBtn);
    }
    backBtn = newwin(3, 5, 1, 2);
    box(backBtn, 0, 0);
    mvwprintw(backBtn, 1, 2, "<");
    wrefresh(backBtn);
}

// Controlla se abbiamo premuto "indietro"
bool Classifica::isClickBackButton(MEVENT& event) {
    if (backBtn == NULL) return false;
    return (event.x >= 2 && event.x <= 6 && event.y >= 1 && event.y <= 3);
}

// Chiede quanti score far vedere
void Classifica::Npunti() {
    flushinp();
    bool inInput = true;
    while (inInput) {
        if (!sch.controllaDimensione(40,20)) {
            werase(stdscr);
            refresh();
        }
        int maxY, maxX;
        getmaxyx(stdscr, maxY, maxX);
        int w = 60;
        if (maxX<60) w=maxX-4;
        int h = 3;
        int startY = 5;
        int startX = (maxX - w)/2;
        int nm=w-4;
        WINDOW*win3 = newwin(h, w, startY, startX);
        box(win3, 0, 0);
        strcpy(numpunti,"INSERISCI QUANTI PUNTI VISUALIZZARE:");
        mvwaddnstr(win3, 1, 2, numpunti, nm);
        nm=9;
        keypad(win3,true);
        aggiornaBackButton();
        int a=0;
        int ch;
        numpunti[0]='\0';
        wmove(win3, 1, 2);
        wrefresh(win3);
        bool backClicked = false;
        bool needsRedraw = false;
        while (!backClicked) {
            ch = wgetch(win3);
            if (ch == '\n' && a >= 1) break;
            needsRedraw = false;
            switch (ch) {
            case KEY_RESIZE:
                getmaxyx(stdscr, maxY, maxX);
                if (!sch.controllaDimensione(40,20)) {
                    werase(stdscr);
                    refresh();
                }
                w = 60;
                if (maxX<60) w=maxX-4;
                startX = (maxX - w)/2;
                startY = 5;
                wresize(win3, h, w);
                mvwin(win3, startY, startX);
                aggiornaBackButton();
                if (a>nm) {
                    a=nm;
                    numpunti[a]='\0';
                }
                needsRedraw = true;
                break;
            case KEY_BACKSPACE:
            case 127:
                if(a>=1) {
                    a--;
                    numpunti[a]='\0';
                }
                needsRedraw = true;
                break;
            case KEY_MOUSE: {
                MEVENT event;
                if (getmouse(&event) == OK) {
                    if (isClickBackButton(event)) {
                        backClicked = true;
                    }
                }
                break;
            }
            default:
                if (ch >= 48 && ch <= 57){
                    if(a<nm) {
                        numpunti[a++]=ch;
                        numpunti[a] = '\0';
                    }
                }
                needsRedraw = true;
                break;
            }
            if (!backClicked && needsRedraw) {
                werase(win3);
                box(win3, 0, 0);
                mvwaddnstr(win3, 1, 2, numpunti, nm);
                wmove(win3, 1, 2 + a);
                wrefresh(win3);
            }
        }
        werase(win3);
        wrefresh(win3);
        delwin(win3);
        if (backBtn != NULL) {
            werase(backBtn);
            wrefresh(backBtn);
            delwin(backBtn);
            backBtn = NULL;
        }
        werase(stdscr);
        refresh();
        
        if (backClicked) {
            inInput = false;
        } else {
            int PUNTI=atoi(numpunti);
            mostra(PUNTI);
        }
    }
}

// Stampa la classifica a schermo
void Classifica::mostra(int PUN) {
    sch.controllaDimensione(80, 20);
    MEVENT event;
    int maxY, maxX;
    int h, w;
    getmaxyx(stdscr, maxY, maxX);
    h = maxY - 5;
    w = maxX - 16;
    bool redraw = true;
    bool cl=true;
    WINDOW* wClass = newwin(h, w, (maxY - h) / 2, (maxX - w) / 2);
    aggiornaBackButton();
    keypad(wClass, true);
    ifstream file("Classifica.txt");
    int cha;
    if (!file.is_open()) {
        ofstream NuovoFile("Classifica.txt");
        NuovoFile.close();
        file.open("Classifica.txt");
    }
    if (!file.is_open()) {
        box(wClass, 0, 0);
        mvwprintw(wClass, 3, 2, "Errore apertura file!");
        wrefresh(wClass);
        while (cl == true) {
            cha = wgetch(wClass);
            if (cha == KEY_RESIZE) {
                sch.controllaDimensione(40,20);
                werase(wClass);
                getmaxyx(stdscr, maxY, maxX);
                h = maxY - 5;
                w = maxX - 16;
                wresize(wClass, h, w);
                mvwin(wClass, (maxY - h) / 2, (maxX - w) / 2);
                werase(stdscr);
                touchwin(stdscr);
                refresh();
                box(wClass, 0, 0);
                mvwprintw(wClass, 3, 2, "Errore apertura file!");
                wrefresh(wClass);
                aggiornaBackButton();
            }
            if (cha == KEY_MOUSE) {
                if (getmouse(&event) == OK) {
                    if (isClickBackButton(event)) {
                        cl = false;
                    }
                }
            }
        }
    } else {
        int rig = contaRighe("Classifica.txt");
        if (rig>PUN) rig=PUN;
        char ch[70];
        int cont = 0;
        werase(wClass);
        box(wClass, 0, 0);
        mvwprintw(wClass, 1, 2, "CLASSIFICA:");
        int r = 2;
        while (file.getline(ch, 70) && r < h - 2 && r<=rig+1) {
            r++;
            mvwprintw(wClass, r, 2, "%s", ch);
        }
        wrefresh(wClass);
        while (cl == true) {
            cha = wgetch(wClass);
            switch (cha) {
                case KEY_RESIZE:
                    sch.controllaDimensione(80,20);
                    getmaxyx(stdscr, maxY, maxX);
                    h = maxY - 5;
                    w = maxX - 16;
                    wresize(wClass, h, w);
                    mvwin(wClass, (maxY - h) / 2, (maxX - w) / 2);
                    werase(stdscr);
                    touchwin(stdscr);
                    refresh();
                    if (cont > rig - (h - 4))
                        cont = max(0, rig - (h - 4));
                    redraw = true;
                    break;
                case KEY_UP:
                    if (cont > 0) {
                        cont--;
                        redraw = true;
                    }
                    break;
                case KEY_DOWN:
                    if (cont < rig - (h - 4)) {
                        cont++;
                        redraw = true;
                    }
                    break;
                case KEY_MOUSE:
                    if (getmouse(&event) == OK) {
                        if (isClickBackButton(event)) {
                            cl = false;
                            redraw = false;
                        }
                    }
                    break;
            }
            if (redraw) {
                file.clear();
                file.seekg(0);
                for (int i = 0; i < cont; i++)
                    file.getline(ch, 70);
                werase(wClass);
                box(wClass, 0, 0);
                mvwprintw(wClass, 1, 2, "CLASSIFICA:");
                int r = 2;
                while (file.getline(ch, 70) && r < h - 2 && r<=rig+1) {
                    r++;
                    mvwprintw(wClass, r, 2, "%s", ch);
                }
                touchwin(wClass);
                wrefresh(wClass);
                aggiornaBackButton();
                redraw = false;
            }
        }
    }
    werase(wClass);
    wrefresh(wClass);
    delwin(wClass);
    if (backBtn != NULL) {
        werase(backBtn);
        wrefresh(backBtn);
        delwin(backBtn);
        backBtn = NULL;
    }
    werase(stdscr);
    touchwin(stdscr);
    refresh();
    file.close();
}

// Aggiunge lo score al file
void Classifica::addclass(char t[], char nome[],int pu) {
    punti=pu;
    ifstream inputFile;
    inputFile.open(t);
    int n=0;
    int p=contaRighe(t);
    if (p==-1) return;
    while (n<p) {
        inputFile>>classifica[n].nom>>classifica[n].punt;
        n++;
    }
    inputFile.close();
    bool c=false;
    int tot=p;
    if (p == 0) {
        classifica[0].punt = punti;
        strcpy(classifica[0].nom, nome);
    }
    while (p>0 && c==false) {
        if (punti<=classifica[p-1].punt) {
            classifica[p].punt=punti;
            strcpy(classifica[p].nom,nome);
            c=true;
        }else {
            classifica[p].punt=classifica[p-1].punt;
            strcpy(classifica[p].nom,classifica[p-1].nom);
            if (p==1) {
                classifica[p-1].punt=punti;
                strcpy(classifica[p-1].nom,nome);
            }
        }
        p--;
    }
    ofstream outputFile;
    outputFile.open(t);
    for (int i=0;i<=tot;i++) {
        outputFile<<classifica[i].nom<<" "<<classifica[i].punt<<"\n";
    }
    outputFile.close();
};