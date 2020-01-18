echo Publishing docs
cd ..
cd %FOLDER_TO_PUSH%
echo %cd%
dir



git add .
git commit -m "ApiGen Code Docs Regenerated"
git push origin HEAD:%PUSH_TO_BRANCH%