/**
 *  @file       main.cpp
 *  @brief      Client C++ source file
 *
 *  @author     Gemuele Aludino, Patrick Nogaj
 *  @date       09 Jan 2020
 *  @copyright  Copyright © 2020 Gemuele Aludino, Patrick Nogaj
 */
/**
 *  Copyright © 2020 Gemuele Aludino
 *
 *  Permission is hereby granted, free of charge, to any person obtaining
 *  a copy of this software and associated documentation files (the "Software"),
 *  to deal in the Software without restriction, including without limitation
 *  the rights to use, copy, modify, merge, publish, distribute, sublicense,
 *  and/or sell copies of the Software, and to permit persons to whom the
 *  Software is furnished to do so, subject to the following conditions:
 *
 *  The above copyright notice and this permission notice shall be included
 *  in all copies or substantial portions of the Software.
 *
 *  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 *  EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
 *  OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 *  IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
 *  DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
 *  TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH
 *  THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#include "mainwindow.h"

#include "socket.h"
#include "ftpgetter.h"
#include "downloader.h"

#include <QApplication>
#include <QDir>

#include <QDebug>

namespace ntwk {
    void downloader_test(void);
}

/**
 * @brief   main    Program execution begins here
 *
 * @param   argc    sizeof(argv) / sizeof *argv, argument count
 * @param   argv    Command line arguments
 *
 * @return  0 on success, else failure
 */
int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    MainWindow w;
    w.show();

    ntwk::downloader_test();

    return a.exec();
}

/**
 * @brief ntwk::backend_test    Testing ntwk::Downloader class
 */
void ntwk::downloader_test() {
    // backend code - downloads a file from a particular URL
    // and streams the buffer to a file on the client's disk.

    // destinationLocal determines where you want
    // the target file to be saved.

    // url is a string denoting the url of the target file.

    // Determine where you want the destination file to live
    QString destinationLocal = "/Users/gemuelealudino/Downloads";

    // Provide the complete URL of the file you want to download
    QString url = "https://raw.githubusercontent.com/galudino/gcslib/master/test__vptr/vector_ptr.h";

    // Parse the filename from the URL (last occurence of file separator, plus 1);
    QString separatorStr = QDir::separator();   // ensures portability
    char separator = separatorStr.toStdString().c_str()[0];
    const char *cstr = url.toStdString().c_str();

    // advance return val of strrchr to skip over separator (get filename only)
    QString filename = std::strrchr(cstr, separator) + 1;

    // instantiate ntwk::Downloader
    ntwk::Downloader d;

    // provide the destination filepath here (extern QString from downloader.h)
    ntwk::DownloadPath = destinationLocal + QDir::separator() + filename;

    // provide the path of the file you wish to download
    d.doDownload(url);
}
