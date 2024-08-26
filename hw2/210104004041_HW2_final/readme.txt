Bütün işlemler Teams üzerinden bize sağlanan UBUNTU versiyonunda test edilmiştir.

Açıklamalar:

*   Komutlar ile ilgili açıklamaları İngilizce readme2.txt dosyasında bulabilirsiniz.
    (cp komutu ile dışarıdan dosya kopyalamadan önce ilgili açıklamayı okumanızı şiddetle öneririm.) 
*   Ödevde istenen bütün komutalr çalışmaktadır.
*   Bu işletim sistemine ait olan bütün fileentitylerin pathleri '/' karakteri ile sonlanmaktadır.
*   Dışardan 
*   İşletim sisteminin düzgün bir şekilde sonlanması ve kayıtlarını düzgün olarak yapması için "exit" komutu kullanılarak kapatılmalıdır.
*   Ana klasör "home" adına, "home/" dosya yoluna sahiptir.
    Yalnızca el ile fileStructure.txt dosyasındaki bütün "home" ve "home/" kelimeleri değiştirilerek değiştirilebilir. ANCAK ÖNERİLMEZ

OLASI ÇÖKME DURUMUNDA:(hiç sanmıyorum)
*   backıp.zip dosyasındaki storage.txt ve fileStructure.txt dosyalarını, harddisc klasöründekilerin yerine koyarak sistemi sıfırlayabilirsiniz.

fileStructure.txt oluşturulurken C/C++ syntax'ından ilham alınmıştır.
'*' karakteri '{' karakterine,
'**' karakterleri '}' karakterine benzetilmiştir.

----dosya hiyerarşisi----
-home
    -dir1
        -file2
        -dir2
            -copiedFileLinked
        -copiedFile
    -file1
    -file1L

----ifadesi ile gösterilir----
* home home/ Jan 07 19:45
* dir1 home/dir1/ Jan 07 19:46
*F file2 home/dir1/file2/ Feb 07 19:47
* dir2 home/dir1/dir2/ Jan 09 14:06
*S copiedFileLinked home/dir1/dir2/copiedFileLinked/ home/dir1/copiedFile/ Jan 09 14:14
** dir2
*F copiedFile home/dir1/copiedFile/ Jan 09 14:13
** dir1
*F file1 home/file1/ Jan 09 02:01
*S file1L home/file1L/ home/file1/ Jan 09 02:48
** home
-----------------------------


