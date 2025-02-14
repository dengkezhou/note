SET PATH=%PATH%;D:\C-Sky\CDS\qemu\
set SDL_STDIO_REDIRECT=no
If "%~1"=="" (SET IMG=out/c906.elf) Else (SET IMG=%1)

@REM echo %IMG%

cskysim.exe -kernel %IMG% -soc tools/c906_cfg.xml -gdb tcp::112233 -nographic
