import Qt 4.7


Item {
    id: delegate

    width: delegate.ListView.view.width; height: 60

    Text {
        text: title.replace(",","\n").replace(",","\n")
        color: delegate.ListView.isCurrentItem ? "white" : "black"
        font { family: "Helvetica"; pixelSize: 16; bold: true }
        anchors {
            left: parent.left; leftMargin: 15
            verticalCenter: parent.verticalCenter
        }
    }

    Rectangle {
        width: delegate.width; height: 1; color: "#cccccc"
        anchors.bottom: delegate.bottom
        visible: delegate.ListView.isCurrentItem ? false : true
    }
    Rectangle {
        width: delegate.width; height: 1; color: "white"
        visible: delegate.ListView.isCurrentItem ? false : true
    }
    MouseArea {
        anchors.fill: delegate
        onClicked: {
            delegate.ListView.view.currentIndex = index
            delegate.ListView.view.text = "<b><center>" + title.replace(",","\n").replace(",","\n") + "</center></b><br/>" + summary //.replace(" />", "/><br/>");
            console.log(delegate.ListView.view.text);
        }
    }
}
