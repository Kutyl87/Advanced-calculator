# Sztuka Wytwarzania Oprogramowania

## Laboratorium 2

1.  Każdy Zespół otrzymuje dostęp do projektu w swojej grupie w systemie GitLab.

2.  Projekt zawiera pliki implementacji pewnego produktu, składającego
    się z dwóch elementów:

    - Biblioteki dostarczanej jako samodzielny produkt klientom chcącym pisać aplikacje.
    - Aplikacji konsolowej wykorzystującej bibliotekę.

3.  Opisane poniżej zadania można wykonywać równolegle (sugestia: proszę _najpierw_
    przeczytać instrukcję do końca, a potem się podzielić). Na przykład kiedy jedna osoba
    pracuje nad kodem, druga może zajmować się konfigurowaniem CI.
    Oczywiście wzajemne wsparcie i pomoc są zalecane.

4.  Niestety projekt powstał w bałaganiarski sposób i wszystkie pliki są w jednym folderze.
    Nie ma też żadnego mechanizmu automatycznego budowania i testowania produktu.

    - Należy uporządkować pliki w foldery (podpowiedź: *lib*, *app* i *tests* jako podkatalogi
      odpowiedniego folderu).
    - Należy dodać konfigurację CMake umożliwiającą budowanie wszystkich potrzebnych wyników
      (program, testy, sama biblioteka).
    - Nie można zapomnieć o tym, że kompilacja powinna wymuszać odpowiednią jakość kodu:
        - ustawienia ostrzeżeń (*-Wall -Wextra -pedantic -Werror*) -- tak jak na lab1
        - wykorzystanie programu *clang-tidy* (podpowiedź: CXX_CLANG_TIDY)

5.  Produkt został dostarczony z testami jednostkowymi opartymi o bibliotekę Catch2.
    Poniższy kawałek konfiguracji CMake powinien być pomocny w instalacji i użyciu biblioteki:

    ```cmake
    Include(FetchContent)
    FetchContent_Declare(
        Catch2
        GIT_REPOSITORY https://github.com/catchorg/Catch2.git
        GIT_TAG v3.0.1)
    # w nowszych cmake (> 3.15) starczyłoby tylko:  FetchContent_MakeAvailable(Catch2)
    FetchContent_GetProperties(Catch2)
    if(NOT catch2_POPULATED)
        FetchContent_Populate(Catch2)
        add_subdirectory("${catch2_SOURCE_DIR}"
                         "${catch2_BINARY_DIR}")
    endif()
    # ...
    add_executable(<NAZWA TARGET ETC.>>.....................)
    target_link_libraries(<TARGET> Catch2::Catch2WithMain)
    ```

    Ważne -- ponieważ clang-tidy na bibliotece *Catch* może działać wolno i
    co gorsza *coś* znajdować (a nie jest celem ćwiczenia naprawianie biblioteki),
    opcje kompilacji dotyczące ostrzeżeń i analizy statycznej powinny być ustawione *per target*
    a nie na cały projekt -- tak, żeby kod *zewnętrznej* biblioteki, nie był sprawdzany.

6.  Jednocześnie produkt potrzebuje weryfikacji poprawności działania na
    co najmniej dwóch kompilatorach -- wersje będą podane na zajęciach.
    Można użyć do tego potok CI.

7.  Oprócz budowania i odpalanie testów, potok CI można wykorzystać do
    wykonania zadań dodatkowych:

    - Weryfikacja zgodności kodu ze standardem formatowania
      (podpowiedź: narzędzie `clang-format` i polecenie `find`,
      szczególnie w formie `$(find ...)`).
    - Uruchomienie lokalne testów akceptacyjnych klienta (patrz
      następny punkt) -- staną się wewnętrznymi testami walidacyjnymi.

8.  Klient dostarczył dwa pliki, jako przykład swoich testów
    akceptacyjnych:

    - `01-input.txt`
    - `01-output.txt`

    Klient przekazał też, że do weryfikacji będzie korzystał z prostego polecenia `diff`.

    Pliki do pobrania [tutaj](https://staff.elka.pw.edu.pl/~kgrochow/SWO/chars-tests.zip).

9.  Dostarczone pliki dobrze by było poddać kontroli wersji -- mogą się
    zmieniać razem z projektem, więc powinny być razem z nim w repozytorium.

    I najważniejsze, aby program przechodził testy klienta.

10. Te dodatkowe kroki nie powinny mieszać się z domyślnymi -- trzeba
    rozszerzyć etapy potoku (dyrektywa `stages`).

11. Dostarczone testy jednostkowe nie wydają się być kompletne -- trzeba
    je rozszerzyć, pamiętając, że testowanie jednostkowe dobrze jest
    wykorzystywać do sprawdzeń warunków _brzegowych_.

12. Na koniec, gdy już pipeline będzie gotowy i zielony i wszystko
    chodziło poprawnie, proszę zaimplementować najnowsze życzenia
    klienta (zarówno w bibliotece jak i w aplikacji):

    - Funkcje do liczenia najrzadziej i najczęściej występującej litery i znaku.
    - Funkcję do liczenia częstotliwości wystąpienia wybranej przez użytkownika litery względem wszystkich innych liter.

### Ocenie podlegają:

- Układ folderów i efektywność konfiguracji kompilacji (brak powtórzeń etc.).
- Poprawki wprowadzone w testach (jednostkowych i walidacyjnych).
- Jakość potoku CI (sensowne zależności między zadaniami, małe kroki etc.).
- Poprawność procesu wprowadzania zmian do programu (*code review*)

### Podpowiedzi:

- Ładny projekt to też czyste repozytorium git (.gitignore).

- `clang-format` w Dockerze:
   - można go doinstalować do jakiegokolwiek "czystego" kontenera bazowego.
   - Czyli image to może być np. `ubuntu:22.04` albo `alpine` -- to
     taki Linux lubiany w świecie kontenerów, bo bardzo lekki (w
     nim pakiety instaluje się poleceniem `apk add XYZ`)
   - Doinstalowywanie clanga do obrazu `gcc` też niby zadziała, tylko
     tam będzie dość stara wersja clanga (starsze kontenery gcc
     bazują na Debianie 10) i nie będzie działał z plikiem
     konfiguracyjnym dołączonym do repozytorium.

- `clang-format` może być w specjalnym _stage_, jeszcze przed _build_
  (ale „własnym", nie `.pre`).

- Domyślnie GitLab kopiuje wszystkie skonfigurowane artefakty z
  poprzedniego _stage_ do następnego _stage_; `needs` ogranicza co
  jest przekazywane (i pozwala ściągnąć coś z artefaktów
  wcześniejszych stagów niż poprzedni o jeden). Czyli może być
  problem, że jak się nie poda `needs` to skopiują się rzeczy z obu
  wersji gcc, co może dać "ciekawe" efekty.

- `find . ......... -print | xargs xyz` można uprościć do
  `xyz $(find \....)`
  - `$(abc)` to "wykonaj podprogram _abc_, jego wyjście wstaw tutaj"

- W testach walidacyjnych już nic nie trzeba budować - badamy program
  taki, jak chcemy dać klientowi
  - przy okazji: nazwa *testy akceptacyjne* jest zarezerwowana raczej dla rzeczy które robi klient).

- Jak się `#include <catch...` podświetla w kodzie, to dlatego, że `catch`
  jest ściągany przy uruchamianiu CMake dopiero i dopiero po pełnym
  pierwszym zbudowaniu Visual wszystkie pliki _widzi_.
