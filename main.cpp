#include "Film.h"
//#include "Film.cpp"
#include <QCoreApplication>


enum Choices {ADD=1, FIND, REMOVE, GETID, QUIT};
enum Types {FILM=1, ENTERTAINMENT, EDUCATIONAL};
QTextStream cout(stdout);
QTextStream cin(stdin);


Choices nextTask() {
    int choice;
    QString response;
    do {
        cout << ADD << ". Add to FilmList.\n"
        << FIND << ". Find and display a Film.\n"
        << REMOVE << ". Remove an item from FilmList.\n"
        << GETID << ". Find ID by film title.\n"
        << QUIT << ". Exit from this program.\n"
        << "Your choice: " << flush;
        response = cin.readLine();
        choice = response.toInt();
    } while(choice < ADD or choice > QUIT);
    return static_cast<Choices>(choice);
}

QStringList promptFilm() {
    cout << "Please provide the following information." << endl << flush;
    QStringList respList;
    QStringList qList;
    qList << "ID" << "Title" << "Director" << "Length (integer)" << "Date (YYYY/MM/DD)";
    QString in;
    for(int i = 0; i < qList.size(); i++)
    {
        cout << qList.at(i) << ": " << flush;
        in = cin.readLine();
        respList.append(in);
    }

    return respList;
}

QStringList promptEntertainment(){
    cout << "Please provide the following information." << endl << flush;
    QStringList respList;
    QStringList qList;
    qList << "ID" << "Title" << "Director" << "Length (integer)" << "Date (YYYY/MM/DD)" << "FilmType (Action, Comedy, SciFi or Horror)" << "Rating (G, PG, PG13 or R)";
    QString in;
    for(int i = 0; i < qList.size(); i++)
    {
        cout << qList.at(i) << ": " << flush;
        in = cin.readLine();
        respList.append(in);
    }

    return respList;
}

QStringList promptEducational() {
    cout << "Please provide the following information." << endl << flush;
    QStringList respList;
    QStringList qList;
    qList << "ID" << "Title" << "Director" << "Length (integer)" << "Date (YYYY/MM/DD)" << "Subject" << "Grade (Elementary, Middle, High or College)";
    QString in;
    for(int i = 0; i < qList.size(); i++)
    {
        cout << qList.at(i) << ": " << flush;
        in = cin.readLine();
        respList.append(in);
    }

    return respList;
}

bool add(FilmList& myList) {
    int choice;
    //do {
        cout << "Follow the instructions to add a Film" << endl << flush;
        cout << "What kind of film is it?" << endl << flush;
        //enum options(E)
        cout << EDUCATIONAL << ". Educational\n" << ENTERTAINMENT << ". Entertainment\n" << FILM << ". Film\n" << flush;
        cout << "Your choice: " << flush;
        choice = cin.readLine().toInt();
     //} //while(choice < EDUCATIONAL or choice > FILM);

    Types genre = static_cast<Types>(choice);

     switch(genre) {
     case FILM: {
        QStringList list = promptFilm();
        Film* ref = new Film(list);
        myList.addFilm(ref);
        break;
        }
     case ENTERTAINMENT: {
        QStringList list = promptEntertainment();
        Entertainment* ref = new Entertainment(list);
        myList.addFilm(ref);
        break;
        }
     case EDUCATIONAL: {
         QStringList list = promptEducational();
         Educational* ref = new Educational(list);
         myList.addFilm(ref);
         break;
        }
     }
     return true;
}

void find(FilmList& myList) {
    cout << "Please enter the ID of the desired Film: " << flush;
    QString id = cin.readLine();
    Film* film = myList.findFilm(id);
    if(film != NULL) {
        cout << film->toString(1, "\n") << flush;
    }
    cout << "\n" << flush;
}

void remove(FilmList& myList) {
    cout << "Please enter the ID of the desired Film: " << flush;
    QString id = cin.readLine();
    myList.removeFilm(id);
}

void findbyTitle(FilmList& myList) {
    cout << "Please enter the Title of the desired Film: " << flush;
    QString title = cin.readLine();
    Film* film = myList.findTitle(title);
    if (film != NULL) {
        cout << film->toString(1, "\n") << flush;
    }
    cout << "\n" << flush;
}


int main()
{
    FilmList myFilmList;
    bool done = false;

    while(!done) {
        switch(nextTask()) {
        case ADD:
            add(myFilmList);
            cout << myFilmList.toString();
            break;
        case FIND:
            find(myFilmList);
            cout << myFilmList.toString();
            break;
        case REMOVE:
            remove(myFilmList);
            cout << myFilmList.toString();
            break;
        case GETID:
            findbyTitle(myFilmList);
            cout << myFilmList.toString();
            break;
        case QUIT:
            done = true;
        }
    }
    return 1;
}

