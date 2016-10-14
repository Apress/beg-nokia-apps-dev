import Qt 4.7


Rectangle {
    id: window

    property bool loading: feedModel.status == XmlListModel.Loading

    XmlListModel {
         id: feedModel
         source: "http://earthquake.usgs.gov/earthquakes/catalogs/1day-M2.5.xml"
         namespaceDeclarations: "declare default element namespace 'http://www.w3.org/2005/Atom';"
         query: "/feed/entry"
         XmlRole { name: "title"; query: "title/string()" }
         XmlRole { name: "link"; query: "link/string()" }
         XmlRole { name: "summary"; query: "summary/string()" }
    }

    width: 800
    height: 480

    Rectangle {
        id: listView
        anchors.left: window.left
        anchors.top: window.top;
        width: window.width/3
        height: window.height
        color: "#efefef"

        ListView {
            id: events
            property string text: window.loading ? "Loading data... please wait" : "<b><center>" + feedModel.get(0).title.replace(",","\n").replace(",","\n") + "</center></b><br/>" + feedModel.get(0).summary 
            focus: true
            anchors.fill: parent
            model: feedModel
            delegate: QuakeListDelegate {}
            highlight: Rectangle { color: "steelblue" }
            highlightMoveSpeed: 9999999
        }
    }

    Text {
        id: itemView
        anchors.left: listView.right
        anchors.top: window.top;
        width: window.width - listView.width
        height: window.height
        wrapMode: Text.Wrap
        text: events.text
    }
}
