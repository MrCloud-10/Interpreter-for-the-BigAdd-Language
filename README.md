# Interpreter-for-the-BigAdd-Language

# Giriş
Gerçekleştirilen bu projede program çalıştırıcısından bir dosya adı talep edip .ba uzantılı dosyalara erişilip, .ba uzantılı dosyadaki veriler okunarak bu verilerin kurallar sonucundaki çıktıları ve hataları konsol üzerine yansıtılmıştır. Eğer .ba uzantılı dosya dizinde mevcut değilse hata verilerek programdan çıkılmaktadır.
Program ilk olarak yeni dize(\n) değerleri ile ayrılarak parse işlemi uygulandığı için aradaki boş herhangi bir içeriği bulunmayan dizeler işlemlere dahil edilmemiş ve dize değeri olarak ele alınmamıştır programın verilen hata değerlerindeki dize line değeri sadece içeriği bulunan dizelerden oluşmaktadır bu değerler içerisinde boşluk(“ ”,acii=32) değeri de bir line üzerinde bulunsa dahi line olarak sayılmaktadır.
Programda tüm komut ve işlemlerin tanımları gerçekleştirilmiştir.

# Lines of Code
Program içerisinde dizeler end of line karakteri olan “.” ile biter bu durum sadece loop değerlerinde code block kullanılmış ise farklılık göstermektedir. Aynı dize üzerinde birden fazla operatör kullanıla bilinmektedir. Programda operatörler sözcükleri arasında istenildiği kadar boşluk bırakılarak kullanıla bilinir.
Program hata ile karşılaşılan satırda çalışmayı durdurmaktadır.
Programda veriable declarationlar tamamen yapılmıştır ve declarationu önceden yapılmış bir veriable kabul edilmemektedir.
Programda assignment statementlar tamamen gerçekleştirilebilmektedir.
Addition ve subraction işlemleri tamamen gerçekletirilmiştir.
Programda output statementlar tamamen gerçekleşleştirilmiştir.
Programda loop işlemleri ve bu loop değerlerinin getirdiği block işlemlerinin takipleri yapılmış ve loop işleminde yapıla bilinecek out işlem atamaları yapılmıştır.
Programda sorunun gösterimesinde kullanılan line count değerleri sadece kod satırı içeren linelar üzerinden değerlendirilmiş aradaki sadece \n değerlerini içeren linelar line değeri olarak sayılamamıştır.
Code linelarında code yarım bırakılarak yeni bir line üzerinde devam durumunda code hata verecektir.
Seperator kullanımı tamamen gerçekleştirilmiştir.

# Comments
Programda dosya dizini açılmakta ve dosyadaki veriler okunduktan sonra isComment fonksiyonu çağırılarak dizinden comment değerleri çıkarılarak işleme sokulmaktadır. Yani programda kontrol edilen ilk hata durumları burada gerçekleşmektedir.
Comment parantezi açılır fakat kapatılmaz ise program kapatılmadığına dair hata vermektedir.
Comment parantezi kapatılıp fakat açılmaz ise program comment içerisindeki kısımda hatalar ile karşılaşıp tanımlanmamış değer hatası dönmektedir. Ve bir de kapatılıp program kurallarına uygun anlamlı değerler yazılmış ise program comment close parantezi tek başına undefine char kullanımı hatası vermektedir.
String içerisinde kullanılan open bracket(“{”) imleci tanımlanmamıştır ve bu durum sonucu program comment ayırımını o string içerisinde kullanılan comment başlangıç imlecinden itibaren ele almakta ve program hataları ile karşılaşılmaktadır.

# Int Constants, String Constants ve Variables
Int const değerleri BA Lang için olması gerektiği gibi talep edilmektedir bu durumların dışına çıkılması durumunda kod hata vermektedir.
String const değerleri istenildiği gibi atamaları yapılmıştır fakat sadece comment başlangıç imleci olan open bracket karakteri kullanılması durumunda hataların oluşması gerçekleşebilmektedir.
Variables atamaları istenilen şekilde kullanılmaktadır eğer bir variable ataması yapılmadan kullanılmışsa veya ataması yapılan verinin tekrar ataması yapılması istenildiğinde program hata vermektedir.

# Statements
Atama işlemleri için kullanılan move için istenilen şekilde atamalar gerçekleştirilmektedir. Belirlenen integer değer kurallarında veya daha önceden ataması yapılmış bir variable değeri ile gerçekleştirilmektedir.
Add atamasında istenildiği gibi programda gerçekleştirilmektedir. Integer değer ya da daha önceden ataması yapılmış bir variable ile daha önceden atması yapılmış veriable ile add işlemi gerçekleştirilir.
Sub atamasında istenildiği gibi programda gerçekleştirilmektedir. Integer değer ya da daha önceden ataması yapılmış bir variable ile daha önceden atması yapılmış veriable ile sub işlemi gerçekleştirilir.
Out statement atamaları gerçekleştirilmiştir. Out anahtarı newline, string const , int const ya da variable beklenilmektedir.
Loop statement değerleri iki şekilde oluşur loop ,variable or int const, times open block ya da loop, variable or int const, times, out, string const or int cosnt or variable or newline şeklindedir. Loop için kullanılan open block karakteri loop dizesinin sonunda veya yeni bir line üzerinde tek başına olmalıdır aksi taktirde loop işlemleri çalışmayabilir veya hatalar ile karşılaşılabilinir. Aynı şekilde close block karakteride tek başına bir line üzerinde durması beklenilmektedir. Loop işlemleri iç içe olarak kullanılabilinmektedir.
  
# Error Detection
Tüm olası hatalı durumlar için bir hata işlemleri çıktıları çalışmaktadır. Hatalar verilirken hata yapılan line numaraları da verilmiştir fakat arada \n içeren boş linelar bu line numaralarına işlenmemiş bu numaralar en az bir karakter içeren linelar baz alınarak numaralandırılmaktadır.
Error hata durumlarının kontrolleri öncelikle dosya işlemi ile sonrasında comment işlemleri, string const değer tanımlamalarında ve daha sonrasında state tanımlama atama durumları ile devam etmekte son olarakta loop işlem block kontrolleri ile bitmektedir.
