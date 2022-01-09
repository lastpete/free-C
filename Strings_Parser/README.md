# Strings / Floss Parser
Just a quick filter for a Strings / Floss. `sys_parser.c` runs either Strings or Floss against the submitted file and filters the output based on CMD-line input by calling to `popen()`.

> Compile:
> `gcc -o sys.exe sys_parser.c api.c`

> Run:
> `sys.exe {strings | floss} <ABSOLUTE_PATH_TO_FILE> {-api | <SEARCH_TERM>}`
> * `-api` filters for common API, list from [Malapi.io](https://malapi.io).
> * `<SEARCH_TERM>` filters for strings that start with user submitted search criteria.

>Example 1:
> * `sys.exe strings C:\Windows\malicious.exe __`

>Example 2:
> * `sys.exe floss C:\Windows\malicious.exe -api`

## // TODO
* Add all Win32 api functions.............