echo Building Documentation
echo %cd%

..\dependencies\code2yaml\code2yaml.exe code2yaml.json


..\packages\docfx.console.2.48.0\tools\docfx.exe docfx.json