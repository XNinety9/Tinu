#include "xmlparser.h"

XMLParser::XMLParser(QObject *parent) : QObject(parent) {
}

bool XMLParser::readFile(const QString &fileName) {
    QDomDocument doc("mydocument");
    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly))
        return false;
    if (!doc.setContent(&file)) {
        file.close();
        return false;
    }
    file.close();

    // print out the element names of all elements that are direct children
    // of the outermost element.
    QDomElement docElem = doc.documentElement();

    QDomNode n = docElem.firstChild();
    while(!n.isNull()) {
        QDomElement e = n.toElement(); // try to convert the node to an element.
        if(!e.isNull()) {
            SoftwareEntry *s = new SoftwareEntry();
            QDomNamedNodeMap map = e.attributes();
            s->actions = map.namedItem("actions").toAttr().value();
            s->app_name = map.namedItem("app_name").toAttr().value();
            s->category = map.namedItem("cat").toAttr().value();
            s->icon = map.namedItem("icon").toAttr().value();
            s->name = map.namedItem("name").toAttr().value();
            s->size = map.namedItem("size").toAttr().value();
            s->url = map.namedItem("url").toAttr().value();
            s->version = map.namedItem("version").toAttr().value();

            emit hasNewItem(s);
        }
        n = n.nextSibling();
    }

    emit finished();
    return true;
}

