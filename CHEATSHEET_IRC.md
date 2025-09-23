# ft_irc Cheat Sheet (42)

Bu belge jüri sırasında hızlı referans içindir. Ayrıntılı açıklamalar kod içinde logik tutulmuştur.

## 1. Genel Mimari
- Katmanlar: Socket/Poll -> Server -> Client/Channel -> Message/CommandHandler -> Utils/Logger
- Event loop: `poll()` -> yeni bağlantı veya mevcut client IO.
- Mesaj framing: CRLF (`\r\n`) ayracı, `Client::_input_buffer` + `ExtractNextMessage()`.
- Komut dispatch: `_cmds_handler[CMD]->Execute()`.
- Kayıt (REGISTERED): PASS (opsiyonel veya gerekli) + NICK + USER tamamlanınca.

## 2. Önemli Veri Yapıları
- Server:
  - `_clients` (fd -> Client*)
  - `_clients_by_nick` (nick -> Client*)
  - `_channels` (name -> Channel*)
  - Silme kuyrukları: `_usersToDelete`, `_chnlsToDelete`
- Client:
  - Nick başlangıç: `*`; modlar: sadece `i` uygulanabilir (`o` reddedilir)
  - Output buffer: non-blocking yazım, POLLOUT sadece veri varken gerekli (şu an erken set)
- Channel:
  - Modlar: i (invite), t (topic lock), k (key), l (limit), o (operator)
  - İlk kullanıcı otomatik operator
  - Operator yoksa `TransOprts()` yeni operator atar

## 3. Komut Özeti
| Komut | Minimum Param | Ana İş | Hatalar (Seçme) | Not |
|-------|---------------|--------|-----------------|-----|
| PASS | 1 | Şifre doğrulama ve auth flag | 461, 462, 464 | Kayıt tamamlanmamışsa kullanılmalı |
| NICK | 1 | Nick set/değiştir | 431, 433, 451 | Değişimde kanal yayını NICK |
| USER | 4 | Username + realname | 461, 462 | Realname trailing (':' sonrası) |
| JOIN | 1 | Kanal gir / oluştur | 403, 471, 473, 475 | Mode kontrolleri + key/limit/invite |
| PART | 1 | Kanal çık | 403," 442 | Çoklu isim virgülle |
| PRIVMSG | 2 | Mesaj kullanıcı/kanal | 401, 403, 404, 412 | Tek hedef |
| QUIT | 0/1 | Tüm kanallardan çık | - | Boş kanal silinir |
| TOPIC | 1/2 | Kanal topic al/ayarla | 403, 442, 482, 331, 332 | +t modunda sadece op |
| MODE | 1+ | Kullanıcı/kana l modları | 403, 442, 472, 482, 461, 502 | Param mod: k l o |
| INVITE | 2 | Davet | 401, 403, 442, 482 | +i için op şart |
| KICK | 2 | Kullanıcı at | 401, 403, 441, 482 | Broadcast KICK |

## 4. Numerik Kodlar (Kullanılanlar)
001 Welcome
331 No topic
332 Topic
341 Invite sent
353 Names list
366 End of names
401 No such nick
403 No such channel
404 Cannot send to channel
412 No text to send
421 Unknown command
431 No nickname given
433 Nick in use
441 They are not on that channel
442 Not on that channel
461 Not enough parameters
462 Already registered / (bazı misuse: auth yok mesajı)
464 Password incorrect
471 Channel full (+l)
473 Invite-only (+i)
475 Bad key (+k)
481 Permission denied (oper yok)
482 Not channel operator
502 Cant change user mode (başkasına)

## 5. Mode Kuralları
Kanal modları:
- +i: Davet gerekli (`Channel::_modes['i']`)
- +t: Topic sadece operator
- +k <key>: Channel key
- +l <limit>: Üye limit (pozitif int)
- +o <nick>: Oper atama
Kullanıcı modları:
- +i (invisible) – tek desteklenen

## 6. Kayıt Akışı
1. (Gerekiyorsa) PASS <şifre>
2. NICK <takma_ad>
3. USER <user> 0 * :<realname>
4. Sunucudan 001 (Welcome)

## 7. Örnek Oturum
```
PASS secret
NICK alice
USER alice 0 * :Alice Liddell
JOIN #room
PRIVMSG #room :selam dunya
MODE #room +itk key  
INVITE bob #room
```

## 8. Edge Case Notları
- Nick değişimi sırasında 001 tekrar gönderiliyor (RFC’ye göre farklı numerik tercih edilebilir)
- `Server::BroadcastChannelMessage` doğrudan `send()` kullanıyor (tutarlılık için output buffer kullanılmalı)
- `FindUserByNick` harita yerine `_clients` tarıyor (optimizasyon fırsatı)
- PING/PONG implementasyonu yok (idle detection sınırlı)
- Uzun satır (>512) parçalama korunmuyor; tek recv boundary.

## 9. Performans
- O(N) poll + vector erase (küçük FD setinde yeterli)
- Broadcast O(K)
- Hafif string kopyalama (sstream). Yeterli ölçek.

## 10. Güvenlik & Sağlamlık
- Non-blocking, EAGAIN kontrolleri
- Şifre plaintext (42 kapsamı)
- Rate limit / flood yok
- Kanal boşalınca silinir (dangling pointer yok)

## 11. SSS (Kısa Cevaplar)
- Neden poll? Taşınabilir, yeterli FD ölçeği, basit.
- PING neden yok? Proje minimum gereksinim odaklı; eklenebilir.
- Timeout neyi kapsıyor? PASS vermeyen yeni bağlantı (~10 sn).
- Operator transfer mantığı? Son operator çıkınca ilk uygun üye operator.
- Mesaj framing? CRLF scanning; incomplete satır buffer’da.

## 12. İyileştirme Listesi
1. Broadcast tutarlılığı (hepsi buffer tabanlı)
2. `_clients_by_nick` her yerde kullan
3. PING/PONG ekle + activity timeout
4. Flood / rate limit (mesaj/saniye)
5. JOIN çoklu kanal desteği
6. Numerik kod semantik düzeltmeleri

---
Hazır: Bu dosyayı jüri öncesi hızlı gözden geçirme için kullan.
