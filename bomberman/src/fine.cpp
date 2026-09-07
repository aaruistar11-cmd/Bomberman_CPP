#include "Librerie.hpp"
#include "fine.hpp"

fine::fine() {
    strcpy(nome,"INSERISCI IL TUO NOME:");
    strcpy(end,"###   #   #   # #\n#     ##  #   #   #\n###   # # #   #   #\n#     #  ##   #   #\n###   #   #   # #\0");
    strcpy(end2,"END");
};

// Schermata per inserire il nome
void fine::drawnome(int pu) {
    sch.controllaDimensione(70,20);
    int maxY, maxX;
    getmaxyx(stdscr, maxY, maxX);
    int w = 60;
    if (maxX < 64) w = maxX - 4;
    int h = 3;
    int startY;
    int startX = (maxX - w)/2;
    int nm=w-4;
    if (nm<1) nm=1;
    bool dist;
    dist=drawend();
    if (dist)startY = 15;
    else startY = 8;
    win3 = newwin(h, w, startY, startX);
    box(win3, 0, 0);
    mvwaddnstr(win3, 1, 2, nome, nm);
    keypad(win3,true);
    int a=0;
    int ch;
    nome[0]='\0';
    wmove(win3, 1, 2);
    wrefresh(win3);
    while((ch = wgetch(win3)) != '\n'||a<=3) {
        switch (ch) {
        case KEY_RESIZE:
            getmaxyx(stdscr, maxY, maxX);
            if (!sch.controllaDimensione(70,20)) {
                clear();
                refresh();
            }
            w = (maxX < 64) ? maxX - 4 : 60;
            startX = (maxX - w)/2;
            wresize(win3, h, w);
            dist=drawend();
            if (dist)startY = 15;
            else startY = 8;
                mvwin(win3, startY, startX);
            if (a>nm) {
                a=nm;
                nome[a]='\0';
            }
            break;
        case KEY_BACKSPACE:
        case 127:
            if(a>=1) {
                a--;
                nome[a]='\0';
            }
            break;
        default:
            if ((ch >= 48 && ch <= 57)||(ch>=65 && ch<=90)||(ch>=97 && ch<=122)) {
                nm=w-4;
                if(a<nm) {
                    nome[a++]=ch;
                    nome[a] = '\0';
                }
            }
            break;
    }
        nm=w-4;
        if (nm<1) nm=1;
            werase(win3);
            box(win3, 0, 0);
            mvwaddnstr(win3, 1, 2, nome, nm);
            wmove(win3, 1, 2 + a);
            wrefresh(win3);
        }
    cl.addclass("Classifica.txt",nome,pu);
    clear();
    refresh();
    getch();
    endwin();
};

// Mostra la scritta END
bool fine::drawend() {
    int x,y;
    getmaxyx(stdscr,y,x);
    if (y > 30 && x > 80) {
        int w=21;
        int h=7;
        win4 = newwin(h, w, 3, (x - w) / 2);
        wattron(win4, COLOR_PAIR(1));
        mvwprintw(win4, 2, 0, "%s", end);
        wattroff(win4, COLOR_PAIR(1));
        wrefresh(win4);
        return true;
    } else {
        win4 = newwin(3, 15, 2, (x - 12) / 2 - 2);
        wattron(win4, A_BOLD | COLOR_PAIR(1) | A_UNDERLINE);
        mvwprintw(win4, 1, 6, end2);
        box(win4, 0, 0);
        wattroff(win4, A_BOLD | COLOR_PAIR(1) | A_UNDERLINE);
        wrefresh(win4);
        return false;
    }
};
