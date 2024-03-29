/*
  Copyright (C) 2013 Jolla Ltd.
  Contact: Thomas Perl <thomas.perl@jollamobile.com>
  All rights reserved.

  You may use this file under the terms of BSD license as follows:

  Redistribution and use in source and binary forms, with or without
  modification, are permitted provided that the following conditions are met:
    * Redistributions of source code must retain the above copyright
      notice, this list of conditions and the following disclaimer.
    * Redistributions in binary form must reproduce the above copyright
      notice, this list of conditions and the following disclaimer in the
      documentation and/or other materials provided with the distribution.
    * Neither the name of the Jolla Ltd nor the
      names of its contributors may be used to endorse or promote products
      derived from this software without specific prior written permission.

  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
  ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
  WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDERS OR CONTRIBUTORS BE LIABLE FOR
  ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
  (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
  LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
  ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
  SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

import QtQuick 2.0
import Sailfish.Silica 1.0


Page {
    id: page

    SilicaFlickable {
        anchors.fill: parent

        PullDownMenu {
            MenuItem {
                text: "coderusinbox@gmail.com"
                onClicked: Qt.openUrlExternally("mailto:coderusinbox@gmail.com?subject=Proximity Speaker")
            }
            MenuItem {
                text: "by coderus in 0x7DE"
                enabled: false
            }
        }

        PageHeader {
            title: qsTr("Proximity Speaker")
        }

        Rectangle {
            width: page.width - (Theme.paddingLarge * 2)
            height: width
            //radius: width / 2
            border.width: 2
            border.color: Theme.highlightColor
            color: Theme.rgba(proximityClient.sensorActive ? Theme.highlightColor : Theme.primaryColor, mArea.down ? 0.5 : 1.0)
            anchors.centerIn: parent

            Label {
                anchors.centerIn: parent
                text: proximityClient.sensorActive ? qsTr("Active") : qsTr("Inactive")
                font.pixelSize: Theme.fontSizeLarge
                color: proximityClient.sensorActive ? Theme.primaryColor : Theme.highlightColor
            }

            MouseArea {
                id: mArea
                property bool down: pressed && containsMouse
                anchors.fill: parent
                onClicked: {
                    proximityClient.sensorActive = !proximityClient.sensorActive
                }
            }
        }
    }
}


