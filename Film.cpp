#include "Film.h"
#include <typeinfo>

//QTextStream qout;
QString sepChar="[::]";

Film::~Film()
{

}


Film::Film(QString id, QString title, QString dir, quint32 length, QDate relDate) {
    m_FilmID = id;
    m_Title = title;
    m_Director = dir;
    //m_FilmLength = length;
    m_ReleaseDate = relDate;

    if (length < 60)
        m_FilmLength = SHORT;
    else if (length > 60 && length < 120)
        m_FilmLength = MEDIUM;
    else
        m_FilmLength = LONG;
}

Film::Film(QStringList& propList) {
    m_FilmID       =  (QString)propList[0];
    m_Title        =  (QString)propList[1];
    m_Director     =  (QString)propList[2];

    QString len = propList[3];
    if (len == "short")
        m_FilmLength = SHORT;
    else if (len == "medium")
        m_FilmLength = MEDIUM;
    else if (len == "long")
        m_FilmLength = LONG;

    m_ReleaseDate  =  QDate::fromString(propList[4], "yy/MM/dd");
}

QString Film::toString(bool labeled, QString sepChar) {
    QString len = " ";
    if (m_FilmLength == SHORT)
        len = "short";
    else if (m_FilmLength == MEDIUM)
        len = "medium";
    else
        len = "long";

    if (!labeled)
        return m_FilmID + sepChar + m_Title + sepChar + m_Director + sepChar + len + sepChar +  m_ReleaseDate.toString("yy/MM/dd");
    else
        return "ID: " + m_FilmID + sepChar + "Title: " + m_Title + sepChar + "Director: "+ m_Director + sepChar + "Length: " + len + sepChar + "Release Date: " + m_ReleaseDate.toString("yy/MM/dd");
}

QDate Film::getRelDate() {
    return m_ReleaseDate;
}

QString Film::getID() {
    return m_FilmID;
}

QString Film::getTitle() {
    return m_Title;
}

QString Film::getDirector() {
    return m_Director;
}

Length Film::getLength() {
    return m_FilmLength;
}

Entertainment::Entertainment(QString id, QString title, QString dir, quint32 len, QDate relDate, Genres type, MPAARatings rtng) : Film((QString)id, (QString)title, (QString)dir, (quint32)len, (QDate)relDate) {
    m_Type = type;
    m_Rating = rtng;
}

Entertainment::Entertainment(QStringList& propList) : Film((QStringList&)propList) {
    QString type = QString(propList[5]);
    QString rat = QString(propList[6]);

    if (type == "ACTION")
        m_Type = ACTION;
    else if (type == "COMEDY")
        m_Type = COMEDY;
    else if (type == "SCIFI")
        m_Type = SCIFI;
    else if (type == "DRAMA")
        m_Type = DRAMA;
    else if (type == "DOCUM")
        m_Type = DOCUM;

    if (type == "G")
        m_Rating = G;
    else if (type == "PG")
        m_Rating = PG;
    else if (type == "PG13")
        m_Rating = PG13;
    else if (type == "R")
        m_Rating = R;
}

QString Entertainment::toString(bool labeled, QString sepChar) {
    QString rat = " ";
    QString typ = " ";

    if (m_Rating == G)
        rat = "G";
    else if (m_Rating == PG)
        rat = "PG";
    else if (m_Rating == PG13)
        rat = "PG13";
    else if (m_Rating == R)
        rat = "R";

    if (m_Type == ACTION)
        typ = "Action";
    else if (m_Type == COMEDY)
        typ = "Comedy";
    else if (m_Type == SCIFI)
        typ = "Sci-Fi";
    else if (m_Type == DRAMA)
        typ = "Drama";
    else if (m_Type == DOCUM)
        typ = "Documentary";

    if (labeled)
        return Film::toString(1, sepChar) + sepChar + "Ratings: " + rat + sepChar + "Genre: " + typ;
    else
        return Film::toString(0, sepChar) + sepChar + "Ratings: " + rat + sepChar + "Genre: " + typ;
}

Genres Entertainment::getGenre() {
    return m_Type;
}

MPAARatings Entertainment::getRatings() {
    return m_Rating;
}

Educational::Educational(QString id, QString title, QString dir, quint32 len, QDate relDate, QString subj, Grades grdlvl) : Film((QString)id, (QString)title, (QString)dir, (quint32)len, (QDate)relDate) {
    m_Subject = subj;
    m_GradeLevel = grdlvl;
}

Educational::Educational(QStringList &propList) : Film((QStringList&)propList) {
    QString sub = propList[5];
    QString gd = propList[6];

    if (gd == "ELEMENTARY")
        m_GradeLevel = ELEMENTARY;
    else if (gd == "MIDDLE")
        m_GradeLevel = MIDDLE;
    else if (gd == "HIGH")
        m_GradeLevel = HIGH;
    else if (gd == "COLLEGE")
        m_GradeLevel = COLLEGE;

}

QString Educational::toString(bool labeled, QString sepChar) {
    QString grd = " ";

    if (m_GradeLevel == ELEMENTARY)
        grd = "Elementary School";
    else if (m_GradeLevel == MIDDLE)
        grd = "Middle School";
    else if (m_GradeLevel == HIGH)
        grd = "High School";
    else if (m_GradeLevel == COLLEGE)
        grd = "College";

    if (labeled)
        return Film::toString(1, sepChar) + sepChar + "Subject: " + m_Subject + sepChar + "Grade: " + grd;
    else
        return Film::toString(0, sepChar) + sepChar + "Subject: " + m_Subject + sepChar + "Grade: " + grd;
}

Grades Educational::getGrade() {
    return m_GradeLevel;
}

QString Educational::getSubject() {
    return m_Subject;
}


FilmList::FilmList() : QList<Film*>() {}

FilmList::~FilmList() {
    qDeleteAll(*this);
    clear();
}

QString FilmList::toString() {
    QStringList myFilmList;
    QString sepChar;
    for(int i = 0; i < size(); ++i)
        myFilmList << at(i)->toString(true, sepChar);
    return myFilmList.join(sepChar);
}

Film* FilmList::findFilm(QString id) {
    for (int i = 0; i < size(); i++)
    {
        if (at(i)->getID() == id)
            return at(i);
    }
    return 0;
}

Film* FilmList::findTitle(QString title) {
    for (int i = 0 ; i < size(); i++) {
        if (at(i)->getTitle() == title)
            return at(i);
    }
}

QString FilmList::getID(QString title) {
    Film* fm;

    fm = findTitle(title);

    return fm->getID();
}


bool FilmList::exists(Film *film) {
    bool exs = false;

    for (int i = 0; i < size(); i++) {
        if (typeid(*at(i)) == typeid(*film))
            if (at(i)->getID() == film->getID())
                if (at(i)->getTitle() == film->getTitle())
                    if (at(i)->getDirector() == film->getDirector())
                        if (at(i)->getLength() == film->getLength())
                            if (at(i)->getRelDate() == film->getRelDate())
                                exs = true;
    }
    return exs;
}


void FilmList::addFilm(Film* film) {
    Film* add;

    if (film != NULL) {

        if (!exists(film))
            append(film);
        else
            qDebug() << "That entry already exists.";
    }
}

void FilmList::removeFilm(QString filmID) {
    Film* del;
    if (findFilm(filmID) != 0) {
        del = findFilm(filmID);
        delete del;
    }
}

FilmList& FilmList::operator=(const FilmList&){
    return *this;
}
