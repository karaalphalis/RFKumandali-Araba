# 🚗 Uzaktan Kumandalı Akıllı Araç
Bu proje, nRF24L01 kablosuz haberleşme modülü kullanarak uzaktan kontrol edilen bir akıllı araç sistemidir. Araç, hız sensörü, mesafe sensörleri ve motor kontrol sistemi ile donatılmıştır. Arduino platformunda geliştirilmiş olup, gerçek zamanlı hız ve mesafe ölçümü yaparak güvenli bir sürüş sağlar.

📌 Proje Özellikleri
✅ Kablosuz Kontrol – nRF24L01 modülü ile uzaktan yönlendirme
✅ Hız Sensörü – RPM ölçümü ile motor dönüş hızını takip etme
✅ Mesafe Sensörleri – Ön ve arka mesafe algılama ile çarpışma önleme
✅ Motor Kontrolü – PWM sinyalleri ile hız ve yön ayarlama
✅ Vites Sistemi – 4 kademeli hız kontrolü

🛠️ Donanım Bileşenleri
Arduino (UNO, Mega vb.)
nRF24L01 Kablosuz Haberleşme Modülü
HC-SR04 Ultrasonik Mesafe Sensörleri (Ön ve Arka)
Hız Sensörü (Encoder)
DC Motorlar ve Motor Sürücü
LED ve Diğer Elektronik Bileşenler
🔧 Kurulum ve Kullanım
1️⃣ Gerekli Kütüphaneleri Yükleyin
cpp
Kopyala
Düzenle
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <TimerOne.h>
2️⃣ Haberleşme ve Sensörlerin Ayarlanması
📡 nRF24L01 ile alıcı-verici haberleşme adresleri tanımlanır.
🔄 Encoder ile hız ölçümü ve mesafe sensörleri ile çarpışma algılama yapılır.

3️⃣ Motor Kontrol ve Vites Sistemi
Araç, joystick veya uzaktan kumanda ile yönlendirilir.

0. Vites: Motor kapalı
1. Vites: Düşük hız (PWM: 85)
2. Vites: Orta hız (PWM: 170)
3. Vites: Maksimum hız (PWM: 255)
4️⃣ Çalıştırma
Arduino'ya kodu yükleyerek ve uzaktan kumandayı çalıştırarak aracı yönlendirebilirsiniz.

🎯 Kullanım Alanları
🚙 Uzaktan kontrollü robotik sistemler
🏎️ Hız ölçümü ve otomasyon sistemleri
🛡️ Engelden kaçınan akıllı araç projeleri

Bu proje, kablosuz haberleşme, sensör kullanımı ve motor kontrolü konularında uygulamalı bir örnek sunmaktadır.

# git config --global core.autocrlf true


