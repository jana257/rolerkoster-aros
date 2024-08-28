# RolerKoster - AROS

Ovaj repozitorijum sadrži implementaciju jednostavnog "rolerkoster" programa, koji simulira osnovne operacije korišćenjem C programskog jezika. Program demonstrira upravljanje događajima i sinhronizaciju putem više niti.

## Struktura Repozitorijuma

- `rolerkoster.c`: Glavni izvorni fajl sa implementacijom logike za "rolerkoster".
- `Makefile`: Skripta za kompajliranje izvornog koda.
- `README.md`: Ovaj dokument koji pruža osnovne informacije o projektu.

## Kompajliranje

Za kompajliranje koda, koristite priloženi `Makefile`. Komanda za kompajliranje može izgledati ovako:

```bash
make
```

Ova komanda koristi `gcc` za kompajliranje izvornog koda.

## Pokretanje Programa

Nakon uspešnog kompajliranja, možete pokrenuti program koristeći izlaznu izvršnu datoteku. Na primer:

```bash
./rolerkoster
```

## Dodatne Napomene

- Ukoliko želite da prilagodite određene parametre programa, to možete uraditi direktno u izvornom kodu `rolerkoster.c`.