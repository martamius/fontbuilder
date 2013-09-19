/**
 * Copyright (c) 2013 Jordan CM Wambaugh
 * email:support.andryblack@gmail.com
 *
 * Report bugs and download new versions at http://code.google.com/p/fontbuilder
 *
 * This software is distributed under the MIT License.
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use,
 * copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following
 * conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
 * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 */

#include "FirmamentExporter.h"
#include "../fontconfig.h"
#include "../layoutdata.h"

#include <QString>
FirmamentExporter::FirmamentExporter(QObject *parent) :
    AbstractExporter(parent)
{
    setExtension("json");
}
static QString charCode(uint code) {
    if (code=='\"') return QString().append("\"\\").append(code).append("\"");
    if (code=='\\') return QString("\"\\\\\"");
    return QString().append('\"').append(code).append('\"');
}

bool FirmamentExporter::Export(QByteArray& out) {
    QString res = "{\n";
    res+=QString("\t\"image\":\"")+texFilename()+QString("\"\n");
    res+="    ,\"tiles\":[\n";
    foreach (const Symbol& c , symbols()) {
        QString charDef=QString("        ,{");
        charDef+=" \"label\":";
        charDef+=charCode(c.id);
        charDef+=QString(",");
        charDef+=QString("\"width\":")+QString().number(c.placeW)+QString(",");
        charDef+=QString("\"height\":")+QString().number(c.placeH)+QString(",");
        charDef+=QString("\"topLeft\":{\"x\":")+QString().number(c.placeX)+",\"y\":"+QString().number(c.placeY)+QString("},");
        charDef+=QString("\"center\":{\"x\":")+QString().number(c.offsetX)
                +",\"y\":"+QString().number(c.offsetY)+QString("}");

       // charDef+=QString("ox=")+QString().number(c.offsetX)+QString(",");
        //charDef+=QString("oy=")+QString().number(c.offsetY)+QString("}");

        res+=charDef+QString("}\n");
    }
    res+=QString("    ]\n");

    res+=QString("}\n");
    out = res.toUtf8();
    return true;
}


AbstractExporter* FirmamentExporterFactoryFunc (QObject* parent) {
    return new FirmamentExporter(parent);
}
