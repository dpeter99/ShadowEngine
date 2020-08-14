echo Building Documentation
echo %cd%

..\dependencies\code2yaml\2.0\code2yaml.exe code2yaml.json


..\dependencies\docfx\docfx-2.54\docfx.exe

cd output

..\..\dependencies\docfx\docfx-2.54\docfx.exe serve