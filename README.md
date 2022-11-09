
![enter image description here](https://raw.githubusercontent.com/Education-IT/Client-Server-ConsoleApps/main/images/banner.png)
## Projekt zaliczeniowy na przedmiot - *Sieci komputerowe* - **UAM**

> **Zrealizowano w trzecim semestrze studiów informatycznych.**

<img align="right" src="https://raw.githubusercontent.com/Education-IT/MicroShell/main/images/Bash.png" width="200"/>

Zadanie polegało na wykorzystaniu języka **C** oraz **Python** do napisania dwóch *programów **konsolowych***, komunikujących się ze sobą za pomocą **interfejsu obiektowego** i **gniazd BSD**. Aplikacja kliencka przesyła wybrany plik (dowolnej wielkości) który to zapisywany  jest na serwerze. Projekt realizowałem wspólnie z [**Szymonem Ptaszyńskim**](https://github.com/PTAKUU). Osobiście stworzyłem aplikacja kliencką w C, a mój kolega - aplikacje serwerową w Pythonie.  Transmisja połączeniowa między aplikacjami zachodzi za pomocą protokołu **`TCP`**. 
Programy te, z założenia, możliwe są do uruchomienia jedynie na systemach  ***Unix***. Działają tylko w zakresie *lokalnej sieci komputerowej*. W trakcie pracy, osobiście korzystaliśmy z sytemu operacyjnego - **Ubuntu**.

![enter image description here](https://img.shields.io/badge/C-A8B9CC.svg?style=for-the-badge&logo=C&logoColor=black) ![enter image description here](https://img.shields.io/badge/Python-3776AB.svg?style=for-the-badge&logo=Python&logoColor=white) ![enter image description here](https://img.shields.io/badge/GNU%20Bash-4EAA25.svg?style=for-the-badge&logo=GNU-Bash&logoColor=white)  ![enter image description here](https://img.shields.io/badge/Linux-FCC624.svg?style=for-the-badge&logo=Linux&logoColor=black)[ ![enter image description here](https://img.shields.io/badge/website-000000?style=for-the-badge&logo=About.me&logoColor=white)](https://education-it.pl/)
 ## 
**Program "`klient.c`" :**
 1)  Wyświetla **login** aktualnie zalogowanego użytkownika oraz **znak zachęty** w postaci `[{path}] $`, gdzie `{path}` jest ścieżką do bieżącego katalogu roboczego.
 2) Obsługuje polecenie `cd`, działające analogicznie jak [`cd`] znane nam z powłoki bash.
 3) Obsługuje autorskie polecenie **`transfer <nazwa_pliku>`** wysyłające plik do serwera o określonym przez użytkownika adresie **IP** oraz nasłuchiwanym **porcie**. Polecenie to obsługuje również flagę **`-two`** umożliwiającą wysłanie 2 różnych plików do 2 różnych serwerów jednocześnie. 
 5) Obsługuje polecenie `exit`, kończące działanie programu powłoki;
 6) Obsługuje polecenie `help`, wyświetlające na ekranie informacje o autorze programu i oferowanych przez niego funkcjonalnościach;
 7) Wypisuje komunikat błędu, gdy niemożliwe jest poprawne zinterpretowanie polecenia;
  
  **Program "`server.py`" :**
  1.  Nasłuchuje bez przerwy na porcie: `60000`.
  2. Obsługuje w jednym momencie tylko jednego klienta.
  3. Po przesłaniu przez aplikację kliencką pliku - serwer sprawdza czy w bieżącym katalogu znajduję się plik o podanej nazwie - jeśli tak, to zmienia nazwę nowego pliku, dodając odpowiednią liczbę w celu **uniknięcia nadpisania** innych ważnych dokumentów.
  4. Po zakończeniu połączenia - ponownie rozpoczyna się proces nasłuchiwania na wskazanym porcie.
  
  ##  Przykładowe działanie programów
 > Widok po skorzystaniu z polecenia `help`  (aplikacja kliencka)


![enter image description here](https://raw.githubusercontent.com/Education-IT/Client-Server-ConsoleApps/main/images/klient-help.PNG)
<br>

> Przykładowe wysyłanie pliku do nasłuchującego serwera .


![enter image description here](https://raw.githubusercontent.com/Education-IT/Client-Server-ConsoleApps/main/images/klient-transfer.PNG)
<br>

> Widok ze strony serwera - moment nawiązania połączenia i odebrania pliku. 

![enter image description here](https://raw.githubusercontent.com/Education-IT/Client-Server-ConsoleApps/main/images/server.PNG)

## Czego się nauczyłem:
- Utrwaliłem wiedzę dotyczącą wykorzystywania procesów potomnych - funkcje: `fork()` / `wait()`/ `waitpid()` / `exec()`. (wysyłanie dwóch różnych plików do 2 serwerów jednocześnie)
- Projekt był idealnym podsumowaniem sposobu nawiązywania połączenia między aplikacjami za pomocą protokołu **`TCP`**. 
- Była to moja pierwsza projektowa styczność z jednym z wielu głównych praktyk *inżynierii oprogramowania* - wykorzystywaniem już istniejącego kodu (nie tworzenia koła od nowa). Wykorzystałem szkielet mojego autorskiego programu [microshell.c](https://github.com/Education-IT/MicroShell) do pobierania od użytkownika ciągu znaków - a następnie przekształcanie go na tablicę, jak i całe polecenie `cd` umożliwiające poruszanie się po drzewie katalogów w systemie.