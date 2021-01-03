#include <QCoreApplication>
#include <iostream>
#include <QDir>
#include <QDebug>

void crearCarpeta();
void eliminarArchivos();

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    void crearCarpeta(){
        QString carpeta = "C:/Users/AP/Actividad Qt";
        QDir directorio (carpeta);
        //Lista de contenido ordenado
        QFileInfoList contenido = directorio.entryInfoList(QDir::Dirs,QDir::Name);
        int tam = contenido.size();
        //Obtener Ultima carpeta
        QFileInfo ultima_carpeta = contenido.at(tam-1);
        //Obtener el nombre de la ultima carpeta
        QString nombre_uc = ultima_carpeta.fileName();
        //QString numero_string = nombre_uc.remove(0.7);
        QString numero_string = nombre_uc.remove("Carpeta");
        int numero = numero_string.toInt();
        numero++;
        QString nueva_carpeta = "Carpeta" + QString::number(numero);
        qDebug() << nueva_carpeta;
        if (directorio.mkdir(nueva_carpeta)){
            qDebug() << "Se ha creado la carpeta" << nueva_carpeta;
        }else{
            qWarning() << "No se ha podido crear la carpeta" << nueva_carpeta;
        }
    }
    void eliminarDirectorios(){
        QString carpeta = "C:/Users/AP/Actividad Qt";
        QDir directorio (carpeta);
        //Lista de contenido ordenado por nombre y filtrado de directorios
        QFileInfoList contenido = directorio.entryInfoList(QDir::Dirs,QDir::Name);
        //Recorrer el contenido del directorio
        foreach (QFileInfo const &d, contenido) {
            QString nombre = d.fileName();
            if ((nombre == ".") || (nombre == ".."))
                continue;
            int numero = nombre.remove("Carpeta").toInt();
            if (numero%2 != 0){
                directorio.cd(d.fileName());
                QStringList archivos = directorio.entryList();
                for (int i = 0; i < archivos.length(); ++i){
                    if ((archivos[i] == ".") || (archivos[i] == ".."))
                        continue;
                    if (!directorio.remove(archivos[i])){
                        qDebug() << "\tNo se puede eliminar el archivo: " << archivos[i];
                    }
                }
                directorio.cdUp();
                if (directorio.rmdir(d.fileName())){
                    qDebug()<< "Eliminando Archivo: "<< d.fileName();
                }else{
                    qDebug() << "No se pudo eliminar el directorio: " << d.fileName();
                }
            }
        }
    }
  return a.exec();
}
