# Hastane Acil Polikliniği Sistemi

Bu Proje, C dilinde Yazılmış basit bir hastane acil polikliniği sistemidir. Yönetici ve doktor girişleri, hasta kayıtları, teşhis, ilaç ekleme ve reçete yazma işlemlerini içermektedir. Ayrıca, sistem HL7 ( Health Level Seven) standardına uygun hasta kayıt mesajları oluşturur.

## Özellikler

- Yönetici ve doktor girişi
- Doktor kaydetme (yalnızca yönetici)
- Hasta kaydetme
- Teşhis ve şikayet kaydetme
- İlaç ekleme ( yalnızca yönetici)
- Reçete yazma ve rastgele reçete numarası atama

## Kullanım

### Giriş

Program başlatıldığında kullanıcı adı ve şifre istenir. Yönetici ve doktor girişleri için geçerli kullanıcı adı ve şifreler:

- Yönetici:  `admin` , Şifre:  `admin123`
- Doktor: `doktor` , Şifre: `doktor123`

Doktor kayıt sistemi ile eklediğiniz doktorların giriş bilgileri de ana menüye döndükten sonra kullanılabilir.

### Ana Menü

- **Yönetici Menüsü**
- Doktor Kaydet
- Hasta Kaydet
- İlaç Ekle
- Ana Menüye Dön

-  **Doktor Menüsü**
-  Mevcut Hastaları Listele
-  Hasta Kaydet
-  Hasta Teşhis
-  Reçete Yaz
-  Ana Menüye Dön

 ### Hasta Kaydetme

Hasta kaydetme işlemi sırasında hasta bilgileri (TC Kimlik Numarası ve Adı) girilir ve hasta numarası atanır.

###  Teşhis ve Şikayet Kaydetme

Teşhis işlemi sırasında hastanın ID numarası girilerek mevcut hasta bilgileri getirilir. Hasta şikayeti ve doktor görüşü girilerek kaydedilir.

### İlaç Ekleme

Yalnızca Yönetici tarafından yapılan bu işlem, yeni ilaçları tüm ilaçlar listesine ekler.

### Reçete Yazma

Reçete yazma işlemi sırasında hastanın ID numarası girilir ve mevcut hasta bilgileri, şikayet ve doktor görüşü görüntülenir. Rastgele bir reçete numarası atanır ve tüm ilaçlar listesi görüntülenir. Seçilen ilaç reçeteye eklenir.

## Derleme

Proje dosyasını derlemek için GCC derleyicisini kullanabilirsiniz:

```sh
gcc hastane_acil_sistemi.c -o hastane_acil_sistemi.exe
