ImgGradient
===========

Simple pixel sorting program.


## Apa ini?
Solusi ringkas dan mudah untuk problem yang dikemukakan oleh *hanadastore* dalam [thread kaskus][thread].

Berkas kode program ditulis dalam bahasa C++ yang disisipi komentar dan penjelasan yang panjang mengenai program tersebut. Diharapkan kode program dapat dibaca dan dimengerti dengan baik oleh programmer dari tingkat pemula hingga mahir. 


## Sekilas Algoritma
Pada dasarnya, program ini menerima masukan berupa berkas data berformat JPG (*.jpg) dan menghasilkan keluaran yang berupa berkas data berformat JPG juga.
Tiap-tiap data pixel dari gambar masukan akan diurut berdasarkan *value/brightness* dalam *colorspace* HSV/HSB atau berdasarkan *lightness* dalam colorspace HSL.

Tiap-tiap data pixel yang dibuka dari sebuah file JPG berada pada *colorspace* [RGB][RGB-Colorspace]. Data pixel ini dikonversi kedalam format [HSL atau HSV][HSL-and-HSV-Colorspaces]. 

![HSL HSV colorspaces](https://upload.wikimedia.org/wikipedia/commons/thumb/a/a0/Hsl-hsv_models.svg/400px-Hsl-hsv_models.svg.png "HSL HSV colorspace. Sumber: Wikipedia")

Seperti yang bisa dilihat pada gambar diatas, komponen L (*lightness*) pada HSL bergerak dari warna tergelap (hitam) ke warna paling terang (putih) sedangkan komponen V (*value* atau *brightness*) pada HSV/HSB bergerak dari warna tergelap (hitam) ke sebuah warna tertentu yang bergantung pada derajat silinder. Warna putih pada *colorspace* HSV berada pada tengah silinder.

Dengan mengkonversi *colorspace* RGB ke HSL atau HSV, kita bisa mengurutkan warna dari yang tergelap berdasarkan *lightness* atau *value* ke warna yang lebih terang.

Konversi dari RGB ke HSL dan HSV adalah sebagai berikut:

    M = max(R, G, B)
    m = min(R, G, B)

Dimana M adalah komponen RGB dengan nilai tertinggi dan m adalah komponen RGB dengan nilai terendah.
    
*Lightness* didefinisikan sebagai berikut:
   
    L = 1/2 (M + m) 

*Value* didefinisikan sebagai berikut:

    V = M
    

## Kompilasi

**PENTING**
Proyek program dikompilasi dengan menggunakan *build system* CMake yang bisa diunduh disini: http://cmake.org/cmake/resources/software.html .
CMake mendukung berbagai macam *compiler* dan IDE.

### Windows

Cara menggunakan CMake bisa dilihat disini: http://www.cmake.org/cmake/help/runningcmake.html . Setelah source code diunduh dan diekstrak.

1. Jalankan program cmake (cmake harus diinstall terlebih dahulu).
2. *"Where is the source code"* : masukkan direktori dimana source code telah diekstrak.
3. *"Where to build the binaries"*: masukkan direktori dimana kode sumber telah diekstrak. Bubuhi "build\". Misal C:\foo\bar\build dimana C:\foo\bar\ adalah direktori kode sumber.
4. Klik *Configure*.
5. Pilih kompiler yang tersedia. Gunakan *default compiler* yang disarankan cmake.
6. Klik *Configure* sekali lagi.
7. Klik *Generate*.
8. Buka direktori *build\". Disana ada file proyek untuk IDE yang dipilih pada *step* 5. Buka file tersebut.
9. *Compile* dengan IDE yang telah dipilih.

### Linux/Mac OS

Setelah source code diunduh dan diekstrak:

    $ cd <direktori source code>
    $ mkdir build
    $ cd build
    $ cmake ..
    $ make


## Penggunaan
Program yang telah dikompilasi merupakan program konsol dan harus dijalankan melalui *terminal* atau *command line* sebagai berikut:

    ./ImgGradient <input.jpg> <output.jpg> <lightness|value>

Contoh pada windows (dijalankan pada direktori dimana hasil program yang telah dikompilasi berada):

    ImgGradient data/cat.jpg data/cat-out.jpg lightness

Contoh pada linux (dijalankan pada direktori dimana hasil program yang telah dikompilasi berada):

    ./ImgGradient data/cat.jpg data/cat-out.jpg lightness

Akan menghasilkan berkas keluaran cat-out.jpg dalam direktori *data*. Gambar keluaran berupa gambar yang data pixelnya telah diurutkan berdasarkan *lightness*. Untuk mengurutkan data pixel berdasarkan *value*, ganti parameter *lightness* dengan *value*.


## Dokumentasi

Dokumentasi dapat dibuat dengan menggunakan [doxygen](http://www.stack.nl/~dimitri/doxygen/). Instalasi pada setiap sistem operasi berbeda, oleh karena itu ikuti petunjuk masing-masing sistem operasi. Apabila doxygen tersedia, dokumentasi dapat dibuat dengan mencentang pilihan BUILD_DOCS pada CMake atau pada linux:

    cmake -DBUILD_DOCS=ON ..

sebagai ganti dari 

    cmake ..

pada perintah kompilasi di linux.

Setelah proses kompilasi, dokumentasi akan berada dalam direktori *docs/*. Ini berlaku dalam sistem operasi Windows, Linux, dan Mac OS.


## Lisensi
Kode sumber program dilisensikan berdasarkan lisensi BSD.

### Tautan
[thread]: http://www.kaskus.co.id/thread/51cc06828327cf715b000002/bikin-program-c--plis-bantu-tugas-kuliah/
[RGB-Colorspace]: https://en.wikipedia.org/wiki/RGB
[HSL-and-HSV-Colorspaces]: https://en.wikipedia.org/wiki/HSL_and_HSV
