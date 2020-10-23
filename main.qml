import QtQuick 2.9
import QtQuick.Controls 2.2

ApplicationWindow {
    visible: true
    width: 640
    height: 480
    title: qsTr("Scroll")
    StackView {
        anchors.fill: parent
        id: stackView
        initialItem: s
    }
    Component {
        id: s
        Page {
            ScrollView {
                anchors.fill: parent

                ListView {
                    width: parent.width
                    model: ListModel {
                        Component.onCompleted: {
                            append({
                                       l: "https://stich.page.link/BG8L6ZDGv7YMBRW2A"
                                   })
                            append({
                                       l: "https://stich.page.link/jfJdcbJ8r8YjuY3h8"
                                   })
                            append({
                                       l: "https://stich.page.link/zL8Q6BVMS8FJfjAC6"
                                   })
                            append({
                                       l: "https://stich.page.link/Hk9a5QoDRuN1GmgC6"
                                   })
                            append({
                                       l: "https://stich.page.link/9XrDFPJD52HiuJFf6"
                                   })
                            append({
                                       l: "https://stich.page.link/DzrfVM1pZgwCPKpS9"
                                   })
                            append({
                                       l: "https://stich.page.link/6NzMHBTBkyE3dGN56"
                                   })
                            append({
                                       l: "https://stich.page.link/fYGkqrn1CPmXodqf7"
                                   })
                            append({
                                       l: "https://stich.page.link/8QLPDdugSnDUpRXq9"
                                   })
                        }
                    }

                    delegate: ItemDelegate {
                        text: "Item " + (index + 1)
                        width: parent.width
                        height: 100
                        onClicked: {
                            stackView.push(sa, {
                                               sas: model.l
                                           })
                        }
                        Rectangle {
                            width: 100
                            height: 100
                            color: "red"
                            z: 4
                            Image {
                                id: ms
                                width: parent.width
                                height: 100
                                cache: true
                                asynchronous: true
                                z: 1
                                sourceSize: Qt.size(width, height)
                                source: "image://remote/" + model.l
                            }
                        }
                    }
                }
            }
        }
    }

    Component {
        id: sa
        Page {
            id: k
            property var sas
            Rectangle {
                color: "red"
                width: height
                height: 50
                MouseArea {
                    anchors.fill: parent
                    onClicked: stackView.pop()
                }
            }
            Image {
                width: 200
                height: 200
                cache: true
                sourceSize: Qt.size(width, height)
                anchors.centerIn: parent
                fillMode: Image.PreserveAspectFit
                source: "image://remote/" + k.sas
            }
        }
    }
}
