#ifndef ERRORDICTIONNARY_H
#define ERRORDICTIONNARY_H

#include <QObject>
#include <QString>
#include <QHash>

/**
 * @brief The StringDictionnary class is a global singleton container that gathers all the strings the app needs, thus facilitating application translation.
 */
class StringDictionnary : public QObject {
    Q_OBJECT
private:
    /**
     * @brief StringDictionnary is the default constructor. It's
     */
    StringDictionnary(): QObject() {
        msg["ER_TITLE"] = "Error";
        msg["ER_UHOH"] = "Uhoh...";
        msg["ER_NO_INTERNET"] = "<b>Lost connection to the mothership :(</b><br><br>Be sure to check your internet connection before using Tinu.";
        msg["ER_NOTHING_SELECTED"] = "<b>Nothing to do!</b><br><br>Are you sure you checked at least one software?";
    }

public:
    static StringDictionnary* getInstance() {
        if (instance == NULL) {
            instance = new StringDictionnary();
        }
        return instance;
    }

    static void destroy() {
        if (instance != NULL) {
            delete instance;
            instance = NULL;
        }
    }

    QString getMsg(QString key) {
        return msg.value(key);
    }


private:
    static StringDictionnary* instance;
    QHash<QString, QString> msg;

signals:

public slots:

};

#endif // ERRORDICTIONNARY_H
