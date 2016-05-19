#ifndef FILM_H
#define FILM_H

enum Length {SHORT, MEDIUM, LONG};
enum Genres {ACTION, COMEDY, SCIFI, DRAMA, DOCUM};
enum MPAARatings {G, PG, PG13, R};
enum Grades {ELEMENTARY, MIDDLE, HIGH, COLLEGE};

#include <QDate>
#include <QString>
#include <QStringList>
#include <QDebug>


class Film {
private:
    QString  m_FilmID;
    QString  m_Title;
    QString  m_Director;
    Length   m_FilmLength;
    QDate    m_ReleaseDate;
public:
    virtual ~Film();
    Film(QString id, QString title, QString dir, quint32 length, QDate relDate);
    Film(QStringList& propList);
    virtual QString toString(bool labeled, QString sepChar);
    QDate getRelDate();
    QString getID();
    QString getTitle();
    QString getDirector();
    Length getLength();
};

class Entertainment: public Film {
private:
     Genres m_Type;
     MPAARatings m_Rating;

public:
    Entertainment(QString id, QString title, QString dir, quint32 len, QDate relDate, Genres type, MPAARatings rtng);
    Entertainment(QStringList& propList);
    QString toString(bool labeled, QString sepChar);
    Genres getGenre();
    MPAARatings getRatings();
};

class Educational: public Film {
private:
    QString m_Subject;
    Grades m_GradeLevel;

public:
    Educational(QString id, QString title, QString dir, quint32 len, QDate relDate, QString subj, Grades grdlvl);
    Educational(QStringList& propList);
    QString toString(bool labeled, QString sepChar);
    Grades getGrade();
    QString getSubject();
};

class FilmList: public QList<Film*> {
private:
    FilmList& operator=(const FilmList&);

public:
    ~FilmList();
    FilmList();
    QString toString();
    Film* findFilm(QString id);
    Film* findTitle(QString title);
    QString getID(QString title);
    void addFilm(Film* film);
    void removeFilm(QString filmID);
    bool exists(Film* film);
};
#endif // FILM_H
