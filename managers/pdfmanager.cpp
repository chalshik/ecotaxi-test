#include "pdfmanager.h"

PDFmanager::PDFmanager() {}

QString PDFmanager::getStyleSheet()
{
  return
      R"S(
/*
reset css
*/
* {
  -webkit-tap-highlight-color: transparent;
}
*:focus {
  outline: none;
}
html,
body,
div,
span,
applet,
object,
iframe,
h1,
h2,
h3,
h4,
h5,
h6,
p,
blockquote,
pre,
a,
abbr,
acronym,
address,
big,
cite,
code,
del,
dfn,
em,
img,
ins,
kbd,
q,
s,
samp,
small,
strike,
strong,
sub,
sup,
tt,
var,
b,
u,
i,
dl,
dt,
dd,
ol,
ul,
li,
fieldset,
form,
label,
legend,
table,
caption,
tbody,
tfoot,
thead,
tr,
th,
td,
article,
aside,
canvas,
details,
embed,
figure,
figcaption,
footer,
header,
hgroup,
menu,
nav,
output,
ruby,
section,
summary,
time,
mark,
audio,
video {
  margin: 0;
  padding: 0;
  border: 0;
  vertical-align: baseline;
}
article,
aside,
details,
figcaption,
figure,
footer,
header,
hgroup,
menu,
nav,
section {
  display: block;
}
body,
#root {
  line-height: 1;
  overflow-wrap: anywhere;
  overflow-x: hidden;
}
ol,
ul {
  list-style: none;
}
blockquote,
q {
  quotes: none;
}
blockquote:before,
blockquote:after,
q:before,
q:after {
  content: "";
  content: none;
}
table {
  margin: 0;
  border-collapse: collapse;
  border-spacing: 0;
}

table, th, td {
  border: 1px solid;
}

h1, h2, p, td {
  text-align: center;
}

h1 {
  color: #007700;
}
)S";
}

QString PDFmanager::getAppDir()
{
  return QCoreApplication::applicationDirPath();
}
void PDFmanager::createPDF2( QString html,  QString title)
{
    // Устанавливаем курсор ожидания
    QApplication::setOverrideCursor(Qt::WaitCursor);

    // Получаем текущее время для имени файла
    QDateTime time = QDateTime::currentDateTime();
    QString appDir = QStandardPaths::writableLocation(QStandardPaths::DesktopLocation);
    QDir folder(appDir + "/отчеты");

    // Создаем папку "отчеты", если она не существует
    if (!folder.exists()) {
        folder.mkdir(appDir + "/отчеты");
    }

    // Формируем имя файла
    QString fileName = title + " " + time.toString("dd.MM.yyyy HH-mm-ss") + ".pdf";
    fileName.replace(" ", "_");

    // Полный путь к файлу
    QString filePath = appDir + "/отчеты/" + fileName;

    // Настройка принтера для создания PDF
    QPrinter printer(QPrinter::PrinterResolution);
    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setPageSize(QPageSize::A4);
    printer.setOutputFileName(filePath);

    qDebug() << "PDF будет сохранен в:" << printer.outputFileName();

    // Создаем документ и добавляем HTML
    QTextDocument doc;

    // Добавляем мета-тег для кодировки
    QString fullHtml = "<meta charset='UTF-8'>" + html;

    // Устанавливаем HTML в документ
    doc.setHtml(fullHtml);
    doc.setPageSize(printer.pageRect(QPrinter::Point).size());

    // Печатаем документ в PDF
    doc.print(&printer);

    // Копируем путь к файлу в буфер обмена
    QMimeData *mimeData = new QMimeData();
    mimeData->setUrls({QUrl::fromLocalFile(filePath)});

    QClipboard *clipboard = QApplication::clipboard();
    clipboard->setMimeData(mimeData);

    // Восстанавливаем курсор
    QApplication::restoreOverrideCursor();

    // Показываем сообщение об успешном создании PDF
    QMessageBox popup;
    popup.setTextFormat(Qt::MarkdownText);
    popup.setText("Отчет сохранен в папке 'отчеты' на рабочем столе и скопирован в буфер обмена.");
    popup.exec();
}
QString PDFmanager::getDesktopDir()
{
    return QStandardPaths::writableLocation(QStandardPaths::DesktopLocation);
}

void PDFmanager::createPDF(QString html, QString title)
{
    QApplication::setOverrideCursor(Qt::WaitCursor);

    QDateTime time = QDateTime::currentDateTime();
    QString appDir = getDesktopDir();
    QDir folder(appDir + "/отчеты");
    if (!folder.exists())
    {
        folder.mkdir(appDir + "/отчеты");
    }

    QString fileName = title + " " + time.toString("dd.MM.yyyy HH-mm-ss") + ".pdf";
    fileName.replace(" ", "_");

    QString filePath = appDir + "/отчеты/" + fileName;

    QPrinter printer(QPrinter::PrinterResolution);
    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setPageSize(QPageSize::A4);
    printer.setOutputFileName(filePath);

    qDebug() << printer.outputFileName();

    QTextDocument doc;

    // Добавляем мета-тег для кодировки
    html = "<meta charset='UTF-8'>" + html;

    doc.setDefaultStyleSheet(getStyleSheet());
    doc.setHtml(getHeader(time) + html + getFooter(time));
    doc.setPageSize(printer.pageRect(QPrinter::Point).size()); // Используем Point для более точного контроля
    qDebug() << html;
    doc.print(&printer);

    QMimeData *mimeData = new QMimeData();
    mimeData->setUrls({QUrl::fromLocalFile(filePath)});

    QClipboard *clipboard = QApplication::clipboard();
    clipboard->setMimeData(mimeData);

    QApplication::restoreOverrideCursor();

    QMessageBox popup;

    popup.setTextFormat(Qt::MarkdownText);
    popup.setText("Отчет сохранен в папке отчеты на рабочем столе и скопирован в буфер обмена");

    popup.exec();
}
QString PDFmanager::getHeader(QDateTime time)
{
  return "<p>" + time.toString("dd.MM.yyyy HH:mm:ss") + "</p><h1 width=100% color='#007700'>ECO TAXI</h1>";
}

QString PDFmanager::getFooter(QDateTime time)
{
  return "<br><p>ECO TAXI</p><p>" + time.toString("dd.MM.yyyy HH:mm:ss") + "</p>";
}

void PDFmanager::ToPDF(QString title, QString dates, QList<QAbstractItemModel *> models, int start)
{
  QString html = "<h2>" + title + "</h2>";
  html += "<p>" + dates + "</p><br>";

  for (int i = 0; i < models.size(); i++)
  {
    html += modelToHTML(models[i], start != 0 && i == 0 ? 1 : 0);
  }

  createPDF(html, title + " " + dates);
}

QString PDFmanager::modelToHTML(QAbstractItemModel *model, int start)
{
    QString html;
    
    // Remove margin, and set table width to 100%
    html += "<table style='margin: 0;' margin=0 width=100%><tr>";
    
    // Add row number column if start == 1
    if (start == 1)
    {
        html += "<th>#</th>";
    }
    
    // Add headers
    for (int i = start; i < model->columnCount(); i++)
    {
        html += "<th>" + model->headerData(i, Qt::Horizontal).toString() + "</th>";
    }
    html += "</tr>";
    
    // Add rows
    for (int i = 0; i < model->rowCount(); i++)
    {
        html += "<tr>";
        if (start == 1)
        {
            html += "<td>" + QString::number(i + 1) + "</td>";
        }
        
        for (int j = start; j < model->columnCount(); j++)
        {
            QString cellData = model->index(i, j).data(Qt::DisplayRole).toString();
            QString header = model->headerData(j, Qt::Horizontal).toString();
            
            // Check if the header is "Инвестору" to apply green color
            if (header == "Инвестору" && start != 1)
            {
                html += "<td style='border: 1px solid black; color:#007700;'>" + cellData + "</td>";
            }
            else
            {
                html += "<td>" + cellData + "</td>";
            }
        }
        html += "</tr>";
    }
    
    html += "</table>";
    return html;
}



void PDFmanager::exportToPDF(QString title, QString dates, QList<QAbstractItemModel *> models, int start)
{
    ColumnSelectionDialog dialog(models, title, dates, start);
    
    dialog.exec();
}
