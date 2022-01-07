# Strings / Floss
Just a quick filter for a Strings / Floss output file.

> Compile:
> `gcc -o <EXE> str_parser.c api.c`

> Run:
> `<EXE> <Strings/Floss>.txt -api | <SEARCH_TERM>`
> * `-api` filters for common API, list from [Malapi.io](https://malapi.io).
> * `<SEARCH_TERM>` filters for strings that start with user submitted search criteria

>Example:
> * str\_parse.exe input\_file.txt APICallFunc

## // TODO
* Add all Win32 api functions.............