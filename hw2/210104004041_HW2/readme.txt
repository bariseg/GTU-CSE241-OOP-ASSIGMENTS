Dosya kaydetme yapısı:
Bu yapı oluşturulurken C/C++ syntax'ından ilham alınmıştır.
'*' karakteri '{' karakterine,
'**' karakterleri '}' karakterine benzetilmiştir.


"* dir4 home/dir2/dir3/dir4/" ifadesinde;
    '*'                    - yeni bir girintiyi,
    "dir4"                 - yeni girintinin ismini,
    "home/dir2/dir3/dir4/" - yeni girintinin dosya yolunu,
ifade etmektedir.


--aşağıdaki yapı--

* home home/
* dir1 home/dir1
** dir1
* dir2 home/dir2/
* dir3 home/dir2/dir3/
* dir4 home/dir2/dir3/dir4/
** dir4
* dir5 home/dir2/dir3/dir5/
** dir5
** dir3
** dir2
** home

--aşağıdaki şekilde, içeriğe göre girintilenmiştir--

- home
  - dir1
  - dir2
    - dir3
      - dir4
      - dir5

-------------

