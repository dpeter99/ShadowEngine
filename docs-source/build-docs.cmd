echo Building Documentation
echo %cd%

..\dependencies\code2yaml\code2yaml.exe code2yaml.json

IF "%1" == "" GOTO NORMAL_OUTPUT

..\packages\docfx.console.2.48.0\tools\docfx.exe docfx.json
GOTO END


:NORMAL_OUTPUT
..\packages\docfx.console.2.48.0\tools\docfx.exe docfx.json

:END