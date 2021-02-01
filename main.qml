import QtQuick 2.12
import QtQml.Models 2.2
import QtQuick.Window 2.12
import QtCharts 2.3

Window {

    width: 640
    height: 480
    visible: true
    title: qsTr("Hello World")
    Component.onCompleted:{
        for(var i = 0; i < myController.count(); ++i)
        {
            theScatterSeries.append(myController.get(i).x, myController.get(i).y)
        }
    }

    Connections {
        target: myController
        onItemsChanged: {
            for(var i = 0; i < myController.count(); ++i)
            {
                theScatterSeries.append(myController.get(i).x, myController.get(i).y)
            }
        }
    }


    ChartView {
        id: scatte
        width: parent.width
        height: parent.height

        ScatterSeries {
            id: theScatterSeries
            name: "theScatterSeries"
        }

    }

}
