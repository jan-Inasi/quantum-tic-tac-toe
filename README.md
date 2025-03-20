# ZPR - quantum tic tac toe



### konfiguracja


pobranie managera pakietów vcpkg
```
git submodule update --init
```

pobranie pakietów - Linux
```
./vcpkg/bootstrap-vcpkg.sh
./vcpkg/vcpkg install restinio catch2
./vcpkg/vcpkg install boost-asio boost-graph
./vcpkg/vcpkg install nlohmann-json
```npm install -g npm

pobranie pakietów - Windows
```
.\vcpkg\bootstrap-vcpkg.bat
.\vcpkg\vcpkg install restinio:x64-windows catch2:x64-windows
.\vcpkg\vcpkg install boost-asio:x64-windows
.\vcpkg\vcpkg install boost-graph:x64-windows
.\vcpkg\vcpkg install nlohmann-json:x64-windows
```

### instalacja clang-format, clang-tidy, doxygen i ninja
#### Linux:
```
sudo apt-get clang-format clang-tidy doxygen lcov ninja-build
```
#### Windows:
TODO

przed pierwszą budową projektu
```
mkdir build
cmake -B build -S .
```

budowa serwera
```
cmake --build build
```

uruchomienie serwera
```
./build/app/server-qttt localhost 8888
```

formatowanie kodu
```
clang-format --style=file -i app/*.cpp include/*.hpp lib/*.cpp
```

statyczna analiza
```
clang-tidy -extra-arg=-std=c++20 -checks='-*,bugprone-*,cert-*,clang-analyzer-*,misc-*,performance-*,cppcoreguidelines-*' app/*.cpp lib/*.cpp -- -Iinclude -Ivcpkg/installed/x64-linux/include
```

generacja dokumentacji
```
doxygen Doxyfile
```
dokumentacja pojawi się w docs/html


uruchomienie frontendu wymaga zainstalowania node.js, npm oraz angular CLI

komenda uruchamiająca:
```
cd quantum-ttt-front
npm start
```

uruchomienie testów
```
./build/tests/test-quantum-tictactoe 
```
testy dla frontendu (po zainstalowaniu google chrome)
```
cd quantum-ttt-front
ng test
```

generowanie raportu pokrycia (linux, po zainstalowaniu lcov i zbudowaniu testów)
```
chmod +x coverage.sh
./coverage.sh
```
wyniki w docs/coverage
