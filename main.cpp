#include <QCoreApplication>
#include <iostream>
#include <fstream>
#include <QFile>
#include <QList>
#include <QDebug>
#include <QVector>
#include <QString>
#include <QTextStream>
#include <QtGlobal>
#include <stdio.h>
#include <string>

using namespace std;

void elochka(){
    int n, b;
    cin >> n;
    b = 1;
    for (int i = 0; i < n; i++)
    {
        int k = n - i;
        for (int j = k; j > 0; j--)
            cout << " ";
        for (int m = b; m > 0; m--)
        {
            cout << "*";
        }
        b+=2;
        cout << endl;
    }
}

struct StudentInfo {
    char* name;
    char* surname;
    int age;
    char* numTicket;
};

struct SubjMark {
    char* subj;
    int id_subj;
    QVector<int> marks_list;
    float averMark;

    SubjMark() {
        subj = new char[100];
    }
    SubjMark(const char* _subj) {
        subj = new char[strlen(_subj)];
        strcpy(subj, _subj);
    }

    SubjMark(const char* _subj, int _idSubj) {
        subj = new char[strlen(_subj)];
        strcpy(subj, _subj);
        id_subj = _idSubj;
    }

    ~SubjMark() {
        if (subj != nullptr) {
            delete [] subj;
        }
    }

};

int strcmp(char* perv, const char* vtor)
{
    int len = strlen(perv);
    int len1 = strlen(vtor);
   // int len2 = strlen(perv);
    if(len1<len)
    {
        len = len1;
    }
    for(int i = 0; i < len; i++)
    {
        if(int(perv[i]) < int(vtor[i]))
        {
            return -1;
        }
        if(int(perv[i]) > int(vtor[i]))
        {
            return 1;
        }
    }
    if(len>len1)
    {
        return 1;
    }
    if(len<len1)
    {
        return -1;
    }
    if(len==len1)
    {
        return 0;
    }
    return -2;
}

float* srznach(float** a, float* b, int n, int m){ // 5
    for (int i = 0; i < n; i++){
        float c = 0;
        for (int j = 0; j < m; j++){
            c += a[i][j];
        }
        b[i] = c / m;
        cout << b[i] << endl;
    }
    return b;
}


class Student {
private :
    StudentInfo* info;
    QList<SubjMark*> listSubjMark;
    int  lookForSub(const char* subjName) {
        for (int i = 0; i < listSubjMark.size(); i++) {
            if (strcmp(listSubjMark[i]->subj, subjName) == 0) {
                return i;
            }
        }
        listSubjMark.push_back(new SubjMark(subjName));
        return listSubjMark.size() - 1;
    }

public :
    void addSubject(const char* subjName, int idSubj = 0) {
        listSubjMark.push_back(new SubjMark(subjName, idSubj));
    }

    int addMarkToSubj(const char* subjName, int mark) {
        int numSubj = lookForSub(subjName);
        listSubjMark[numSubj]->marks_list.push_back(mark);
        float temp = 0;
                for(int i = 0; i < listSubjMark.length(); i++)
                {
                    temp = 0;
                    for(int t = 0; t < listSubjMark.at(i)->marks_list.length(); t++)
                        temp = temp + listSubjMark.at(i)->marks_list.at(t)/listSubjMark.at(i)->marks_list.length();
                    listSubjMark.at(i)->averMark = temp;
                }
        return 0;
    }

    void checkstud()
        {
            cout << "Surname: " << info->surname << endl;
            cout << "Name: " << info->name << endl;
            cout << "Age: " << info->age << endl;
            cout << "NumTicket: " << info->numTicket << endl;
            for(int i = 0; i < listSubjMark.length(); i++)
            {
                cout << "Average mark " << listSubjMark[i]->subj << ": " << listSubjMark.at(i)->averMark;
            }
        }
};

QByteArray fileData;

void ReadFromFile(const char* fileName) {
    QFile f(fileName);
    f.open(QIODevice::ReadOnly);

    fileData = f.readAll();

    f.close();
}

void WriteToFile(const char* fileName, int* ar) {
    QFile f(fileName);
        f.open(QIODevice::WriteOnly);

        for(int i = 0; i < 256; i++)
        {
            if(ar[i] != 0)
            {
                char c = i;
                QTextStream writeStream(&f);
                writeStream << c << " - " << ar[i] << " raz(a)\n";
            }
        }
}

void task1(const char* filename, const char* fileout) {
    ReadFromFile("test.txt");

    int ar[256];
    memset(&ar[0], 0x00, sizeof(int) * 256);

    for (int i = 0; i < fileData.size(); i++) {
        ar[fileData[i]]++;
    }

    WriteToFile(fileout, ar);
    cout << "Zadanie 1 vypolneno. Prochitan fail \"test.txt\". Resultat v faile \"test1.txt\"" << endl;
}

char binNumb[32];

void perevod(int numDecimal) {
    memset(binNumb, 0x00, 32 * sizeof(int));

    for (int i = 0; i < 32; i++) {
        binNumb[i] = ((numDecimal & 1 << i)) ? 0x31 : 0x30;
    }
}

void WriteToFile2(const char* fileout)
{
    QFile f(fileout);
    f.open(QIODevice::WriteOnly);

    for(int i = 0; i < 32; i++)
    {
        QTextStream writeStream(&f);
        writeStream << binNumb[i];
    }
    f.close();
}

void tempT() {

    for (int i = 0; i < 256; i++) {
        qDebug() << (int)i << "\t" << (char)i;
    }

}

QList<float> getAverStr(int* ar, int N, int M) {
    QList<float> averStr;

    for (int i = 0; i < N; i++) {
        float averStr_temp = 0;
        for (int j = 0; j < M; j++) {
            averStr_temp += ar[i*N + j] / (float)M;
        }

        averStr.push_back(averStr_temp);
        averStr.append(averStr_temp);
    }


    return averStr;
}

int main(int argc, char *argv[])
{
    QCoreApplication mainprog(argc, argv);

    setlocale(LC_ALL, "rus");

    task1("test.txt", "test1.txt");

    cout << "Zadanie 2. Vvedite chislo" << endl;
    int z;
    cin >> z;
    perevod(z);
    cout << binNumb << endl;

    cout << "Zadanie 4. Vvedite vysotu elochki" << endl;
    elochka();

    cout << "Zadanie 5. Vvedite razmer matritsy" << endl;
    int n, m;
    cin >> n >> m;
    //cout << "¬водите элементы матрицы";
    float* b = new float[m];
    float** a = new float* [m];
    for (int i = 0; i < n; i++){
        a[i] = new float [n];
        for (int j = 0; j < m; j++){
        //    cin >> a[i][j];
            a[i][j] = rand()%100;
        }
    }
    cout << endl << endl;
    for (int i = 0; i < n; i++){
        for (int j = 0; j < m; j++){
            cout << a[i][j] << "\t";
        }
        cout << endl;
    }
    cout << endl << endl;
    b = srznach(a, b, n, m);

    cout << "Zadanie 8. Functsii realizovany vrode by";

    tempT();
    return mainprog.exec();
}

