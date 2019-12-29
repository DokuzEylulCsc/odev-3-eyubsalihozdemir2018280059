//	2018280059	Eyüb Salih Özdemir
#include <iostream>
#include <stdio.h>
#include <string>
#include <fstream>
#include <sstream>
#include <stdlib.h>
#include <vector>
#include <windows.h>

using namespace std;
ifstream file;
string data, data2;

void suSatiraGit(int satirNo) { //(kaynak: *1)
	file.clear();
	file.seekg (0, ios::beg);	//sayfanin basina gitme
	for (int i = 0; i < satirNo; i++) {
		getline(file, data);	//istenen satira gitme
	}
}

int main()
{
int soruSayisi = 0;
int ogrSayisi = 0;

file.open("input.txt", ios::in);

if (!file.is_open()) {      //dosya acilamaz ise hata vermek icin tum programi kapsayan bir if-else yapisi.
    cout << "Dosya acilamadi. Dosya ismi 'input.txt' olmali ve program ile ayni klasörde bulunmalidir. Tekrar deneyin." <<endl;
}
else {
cout<< "Verileriniz isleniyor..." << endl;
cout<<endl;
Sleep(1500);
getline(file,data);
istringstream(data) >> soruSayisi; 	//ilk satirdan soru sayisini, integer olarak aldik (kaynak: *3)

string cevapAnahtariArr[soruSayisi];


suSatiraGit(2); // cevap anahtari icin ilk satiri atladik, 2.'den okumaya basliyoruz


int p = 0;
stringstream s(data); //(kaynak: *2)
while (getline(s, data, ',')) {    //cevap anahtari verilerini 2. satirdan arraye koyma
	cevapAnahtariArr[p] = data;
	p++;
}


suSatiraGit(1);
//asagida ogrenci sayisini bulmak icin virgule kadar numaralari sayacagiz
//ama while loop zaten getline ile baslayip icinde de getline bulundugu icin
//direkt 3. satira atlamak yerine 1.'ye atliyoruz

while (getline(file, data) && !file.eof())   //ogrenci sayisi bulma (kaynak: *2)
{
    getline(file, data, ',');   //virgule kadar okuyup bir alt satira geciyor
    ogrSayisi++;
}

string ogrCevaplariArr[ogrSayisi][soruSayisi+1];  //ogrencilelerin cevaplarini tutacak 2d array tanimi
// ilk index ogr numarasini, sonrakiler cevaplarini tutacak. ogr numarasini da tuabilmek icin
//ikinci kisma +1 ekledik.

suSatiraGit(1);


int n = 0;
int m = 0;
int x = 3;
//bir alttaki bolumda for loop'u her line'i incelerken, alt basamaktaki while loop'u
//bu line'lardaki verileri, virgulu delimeter olarak kullanarak, adim adim inceliyor
for (int i = 0; i < ogrSayisi && x < ogrSayisi+3; i++, x++) { 	//ogrencilerin cevaplarinin ogrCevaplariArr'ye doldurulmasi
	suSatiraGit(x);
	//ogrenci numaralarini 3. satirdan almaya baslayip son satira kadar her loop adiminda atlama yapacagimiz icin
	//loop tanimina x<ogrSayisi+3 kosulunu da eklemek gerekti.
	//cunku, eger 5 ogrenci varsa ilk 2 satirda soru sayisi ve cevap anahtari verileri oldgu icin son ogrenci
	//7. satirda olacaktır. yani ogrSayisi+2, ancak son satirdaki veriyi de almak icin ogrSayisi+3 olarak ekliyoruz bu kosulu.
	stringstream ss(data);
	while (getline(ss, data, ',')) {    //(kaynak: *2)
		ogrCevaplariArr[m][n] = data;
		n++;
		//burada farkli bir yaklasim sergilemek durumunda kaldim. for'da ve while'da yeterince veriable var
		//isleri daha da karistirmamak icin asagidaki sekilde manuel yonlendirme yaparak kaydettim cevaplari
		//reminder: ogrCevaplariArr[ogrSayisi][soruSayisi+1] seklinde tanimli bir array.
		//asagida gerceklesen olay su: eger n, yani arraylerin cevaplarinin tutuldugu ikinci boyut, son indexe ulasmis ise
		//array'in ilk boyutunu 1 artiriyoruz(alt satira geciyoruz), ve ikinci boyutun indexini tekrar cevaplari
		//depolamaya baslamak icin, sifira esitliyoruz
		if (n == soruSayisi+1) {
			m++;
			n = 0;
		}
	}
}

file.close();  //dosyadaki tum verileri aldik, input dosyasi ile isimiz biti.

int ogrNotlari [ogrSayisi][2]; //notlarin, ogrID ile birlikte tutulacagi array tanimlamasi

for(int i = 0; i < ogrSayisi; i++) {    //ogrNotlari arrayinin 0(sifir) ile doldurulması
    for (int j = 0; j < 2; j++) {
        ogrNotlari[i][j] = 0;
    }
}

for (int i = 0; i < ogrSayisi; i++) {       //ogrNotlari'nin ilk boyutunun, ogr numaralari ile doldurulmasi
    int j;
    istringstream(ogrCevaplariArr[i][0]) >> j;  //daha sonra uzerinde islem yapmak üzere,
    ogrNotlari[i][0] = j;                       //integer'a cevirerek depoluyoruz
}

for (int k = 0; k < ogrSayisi; k++) {
    for (int i = 1; i < soruSayisi+1; i++) {        //ogr notlarinin hesaplanması
        if (ogrCevaplariArr[k][i] == " " || ogrCevaplariArr[k][i] == "") {
            ogrNotlari[k][1] += 0;
        }
        else if (ogrCevaplariArr[k][i] == cevapAnahtariArr[i-1]) {
            ogrNotlari[k][1] += 4;
        }
        else if (ogrCevaplariArr[k][i] != cevapAnahtariArr[i-1]) {
            ogrNotlari[k][1] -= 1;
        }
        else {
            cout << "Bir hata oldu." << endl;
        }
    }
}

for (int i = 0; i < ogrSayisi; i++) {           //ogrencilerin ham puanlarinin consolda gösterilmesi
    cout << i+1 << ". ogrencinin ham notu(" << ogrNotlari[i][0] << "): " << ogrNotlari[i][1] << endl;
}

cout<<endl;

for (int i = 0; i < ogrSayisi; i++) {       //ogrencilerin notlarinin 0-100 arası normalize edilmesi
    if (ogrNotlari[i][1] <= 0) {
        ogrNotlari[i][1] = 0;
    }
    else {
        ogrNotlari[i][1] = (100*ogrNotlari[i][1])/(soruSayisi*4);
    }
}

cout << "donusturulmus ogrenci notlari: " <<endl;    //ogrencilerin donusturulmus puanlarinin consolda gosterilmesi
for (int i = 0; i < ogrSayisi; i++) {
    cout << i+1 << ". ogrencinin normalize notu(" << ogrNotlari[i][0] << "): " << ogrNotlari[i][1] << endl;
}

cout<<endl;

for (int i = 0; i < ogrSayisi-1; i++) {             //notlarin ogrID ile birlikte sıralanmasi
    for (int j = 0; j < ogrSayisi-i-1; j++) {       //(bubble sort)
        if (ogrNotlari[j][1] > ogrNotlari[j+1][1]) {
            int tempNot, tempID;
            tempNot = ogrNotlari[j][1];
            ogrNotlari[j][1] = ogrNotlari[j+1][1];
            ogrNotlari[j+1][1] = tempNot;

            tempID = ogrNotlari[j][0];
            ogrNotlari[j][0] = ogrNotlari[j+1][0];
            ogrNotlari[j+1][0] = tempID;
        }
    }
}

int enBuyukNot = ogrNotlari[ogrSayisi-1][1];    //en kucuk ve en buyuk notun bulunması
int enKucukNot = ogrNotlari[0][1];

int aciklik = enBuyukNot - enKucukNot;   //aciklikin bulunmasi

int medyan;
if (ogrSayisi % 2 == 0) {       //medyanin bulunmasi
    medyan = (ogrNotlari[ogrSayisi/2][1] + ogrNotlari[(ogrSayisi/2)-1][1])/2;
} else {
    medyan = ogrNotlari[(ogrSayisi-1)/2][1];
}

int toplam = 0;
for (int i = 0; i<ogrSayisi; i++) {     //ortalamanin bulunmasi
    toplam += ogrNotlari[i][1];
}
int ortalama = toplam/ogrSayisi;

cout << "siralanmis ogrenci notlari: " << endl; //siralanmis ogrenci notlarinin consolda gosteirlmesi
for (int i = 0; i < ogrSayisi; i++) {
    cout << ogrNotlari[i][0] << ", " << ogrNotlari[i][1];
    cout<<endl;
}
cout<< "en kucuk not: " << enKucukNot <<", "<< "en buyuk not: " << enBuyukNot <<", ";
cout<< "ortalama: " << ortalama <<", "<< "medyan: " << medyan <<", "<< "aciklik: " << aciklik <<endl;

cout<<endl;

ofstream outFile;
outFile.open ("output.txt", ofstream::out);
cout << "Verileriniz yazdiriliyor..." << endl;

cout<<endl;

//tum bilgilerin dosyaya yazdirilmasi:
for (int i = 0; i < ogrSayisi; i++) {
    outFile << ogrNotlari[i][0] << ", " << ogrNotlari[i][1] << endl;
}
outFile << enKucukNot <<", "<< enBuyukNot <<", "<< ortalama <<", "<< medyan <<", "<< aciklik;

Sleep(1500);    //time delay'ler kullaniciya programin dogru calistigi konusundaa
                //guven verdigi ve hos bir izlenim yarattigi icin kullandim  (kaynak: *4)
cout << "Verileriniz 'output.txt' dosyasina yazdirildi." <<endl;
} return 0;
}

/*KAYNAKLAR:
    1) Dosyayi acip kapamak zorunda kalmadan sayfanin basina gitmeyi su adresten ogrendim:
    https://stackoverflow.com/a/5343297

    2) Verileri dosyadan bir loop ve delimeter kullanarak almak icin gereken yapiyi (stringstream)
    kurmayi su adresten ogrendim:
    https://stackoverflow.com/a/37957126

    3) stringstream kullanarak string değerleri nasıl integer olarak kaydedebileceğimizi öğrendiğim adres:
    https://www.techiedelight.com/convert-string-to-int-cpp/

    4) Sleep modülünü öğrendiğim adres:
    https://stackoverflow.com/questions/158585/how-do-you-add-a-timed-delay-to-a-c-program
*/
