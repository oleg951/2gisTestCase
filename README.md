[![Build](https://github.com/oleg951/2gisTestCase/actions/workflows/2GisBuildAndTest.yml/badge.svg)](https://github.com/oleg951/2gisTestCase/actions/workflows/2GisBuildAndTest.yml)
[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)

# 2gisTestCase - Тестовое задание 2gis.
___
## Консольное приложение для поиска слов в файле и подсчета контрольной суммы.
___
## Remark
+ Поиск слов осуществляется при помощи регулярного выражения.
+ Расчет контрольной суммы выполнется по алгоритму:<br>
checksumm = word<sub>1</sub> + word<sub>2</sub> + ... + word<sub>N</sub><br>
где word<sub>i</sub> - 32 битное слово.<br>
### Options
  -h [ --help ]&nbsp;&nbsp;&nbsp;&nbsp;Show help<br>
  -f [ --filePath ] arg&nbsp;&nbsp;&nbsp;&nbsp;The path to the file<br>
  -m [ --mode ] arg&nbsp;&nbsp;&nbsp;&nbsp;File mode<br>
  -w [ --word ] arg&nbsp;&nbsp;&nbsp;&nbsp;Prints the number of words in the file<br>
 
### Build and run
```
mkdir build
cd build
cmake ..
cmake --build .
make test
```


